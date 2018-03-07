// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "hash-ops.h"

#ifdef _MSC_VER
#include <malloc.h>
#elif !defined(__FreeBSD__) && !defined(__OpenBSD__) && !defined(__DragonFly__)
 #include <alloca.h>
#else
 #include <stdlib.h>
#endif

/*** 
* Redoblar ronda, para *(count >= 3)* y para que *(count)* no sea tan largo (cálculo del árbol-hash)
*/
size_t tree_hash_cnt(size_t count) {
 // Este algoritmo sirve para realizar *( 1 << floor(log2(count)) )*
 // Existen munchas maneras de hacer un *(log2)* . Se eligió una manera complicada a propósito.
 //
 // El método iterativo implementado a continuación tiene como objetivo la limpieza por sobre la velocidad, 
 // si el rendimiento fuera una necesidad entonces mi consejo es usar la instrucción BSR en x86
 // Todas las implementaciones "paranoicas" han sido eliminadas, ya que es trivial demostrar matemáticamente 
 // que el retorno siempre será una potencia de 2. 
 // El espacio del problema se ha definido como *(3 <= count <= 2 ^ 28)* . Por supuesto, la cuarta parte de 
 // mil millones de transacciones no es un límite superior sensato para un bloque, por lo que habrá límites más 
 // estrictos en otras partes del código.

 assert( count >= 3 ); // los casos para 0,1,2 son tratados en otro lugar.
 assert( count <= 0x10000000 ); // límite limpio de 2^28, MSB=1 causa un ciclo infinito.

 size_t pow = 2;
 while(pow < count) pow <<= 1;
 return pow >> 1;
}

void tree_hash(const char (*hashes)[HASH_SIZE], size_t count, char *root_hash) {
// Un bloque de blockchain puede ser atacado para forzarlo a tener 514 transacciones, lo cual desencadena un 
// mal cálculo de la  variable *(cnt)* en el código original de Cryptonote. 
// Este bug aparece en todas las cryptomonedas basadas en Cryptonote.

  assert(count > 0);
  if (count == 1) {
    memcpy(root_hash, hashes, HASH_SIZE);
  } else if (count == 2) {
    cn_fast_hash(hashes, 2 * HASH_SIZE, root_hash);
  } else {
    size_t i, j;

    size_t cnt = tree_hash_cnt( count );

    char (*ints)[HASH_SIZE];
    size_t ints_size = cnt * HASH_SIZE;
    // asignar, y poner a cero como protección adicional para el uso de memoria no inicializada
    ints = alloca(ints_size);  memset( ints , 0 , ints_size);  
    
    memcpy(ints, hashes, (2 * cnt - count) * HASH_SIZE);

    for (i = 2 * cnt - count, j = 2 * cnt - count; j < cnt; i += 2, ++j) {
      cn_fast_hash(hashes[i], 64, ints[j]);
    }
    assert(i == count);

    while (cnt > 2) {
      cnt >>= 1;
      for (i = 0, j = 0; j < cnt; i += 2, ++j) {
        cn_fast_hash(ints[i], 64, ints[j]);
      }
    }

    cn_fast_hash(ints[0], 64, root_hash);
  }
}
