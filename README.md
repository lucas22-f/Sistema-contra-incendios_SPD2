
# Sistema de Control contra Incendios con Arduino (Sistema-contra-incendios_SPD2)
Sistema contra incendios ,  codeado en c++ 2do parcial de SPD (Sistema de procesamiento de Datos) 


![image](https://github.com/lucas22-f/Sistema-contra-incendios_SPD2/assets/71677198/36b8c275-7648-494c-b3af-27951f6cb262)

Este código en Arduino implementa un sistema de control contra incendios utilizando un servo, un sensor de temperatura y un control remoto IR. El sistema muestra información en un LCD y utiliza LEDs para indicar el estado de funcionamiento.

## Descripción del sistema

El sistema de control contra incendios se encarga de monitorear la temperatura ambiente y activar medidas de prevención en caso de detectar una temperatura peligrosa. A continuación, se describe el funcionamiento del sistema:

1. **Sensor de temperatura:** El sistema utiliza un sensor de temperatura conectado al pin analógico A0 para medir la temperatura ambiente. El sensor proporciona una lectura analógica proporcional a la temperatura.

2. **Verificación de temperatura:** La función `verificar_rangos_temperatura(temperatura)` se encarga de verificar el rango de temperatura medida y determinar la estación del año correspondiente. Dependiendo de la temperatura leída, se asigna una etiqueta de estación (invierno, otoño, primavera, verano) a la variable `estacion`.

3. **Control remoto IR:** El sistema permite activar o desactivar el funcionamiento del sistema a través de un control remoto IR. Al presionar el botón correspondiente en el control remoto, se cambia el valor de la variable `activar_sistema`, lo que determina si el sistema debe estar activo o no.

4. **Interfaz de usuario:** El sistema muestra información en un LCD de 16x2 caracteres. Utilizando la función `imprimir_lcd(estacion, temp)`, se muestra en el LCD la estación del año y la temperatura ambiente actual. Además, si la temperatura supera los 60 grados Celsius, se muestra una alerta de "ALERTA! t:XX C" indicando la temperatura actual.

5. **Movimiento del servo:** En caso de que la temperatura supere los 60 grados Celsius, se activa el movimiento del servo. Utilizando la función `movimiento_servo()`, el servo realiza un movimiento desde la posición inicial (0 grados) hasta una posición final (`end`) en un intervalo de tiempo determinado. Este movimiento puede ser utilizado, por ejemplo, para cerrar una válvula de gas o activar un sistema de rociadores.

6. **Indicadores de estado:** Para indicar el estado de funcionamiento del sistema, se utilizan dos LEDs conectados a los pines `LEDVERDE` y `LEDROJO`. Cuando el sistema está activo, el LED verde se enciende, indicando un estado seguro. Si se detecta una temperatura peligrosa y se activa el movimiento del servo, el LED rojo se enciende para indicar una alerta de incendio.

## Componentes utilizados

El sistema de control contra incendios utiliza los siguientes componentes:

![image](https://github.com/lucas22-f/Sistema-contra-incendios_SPD2/assets/71677198/da0fea65-7dea-4070-b256-3c930af5c46e)
## Vista esquematica:
![image](https://github.com/lucas22-f/Sistema-contra-incendios_SPD2/assets/71677198/5d54310c-f1c3-47c3-bb76-3cb90c4d243e)

## funciones principales:
### Función `run_sistema()`

Esta función se encarga de controlar el estado de funcionamiento del sistema. Verifica si `activar_sistema` es `HIGH` (activo) o `LOW` (inactivo). Dependiendo del estado, realiza las siguientes acciones:

- Si `activar_sistema` es `HIGH`:
  - Imprime "Prendemos Sistema" en el monitor serie a través de `Serial.println()`.
  - Adjunta (`attach()`) el servo al pin `SERVON` utilizando `miServo.attach(SERVON)`.
  - Retorna `true` para indicar que el sistema está activo.

- Si `activar_sistema` es `LOW`:
  - Imprime "Apagamos Sistema" en el monitor serie a través de `Serial.println()`.
  - Limpia el contenido del LCD utilizando `lcd.clear()`.
  - Desconecta (`detach()`) el servo del pin `SERVON` utilizando `miServo.detach()`.
  - Apaga los LEDs mediante la función `apagar_leds()`.
  - Retorna `false` para indicar que el sistema está inactivo.
 ```cpp
bool run_sistema(){
  if (activar_sistema == HIGH){
 
    Serial.println("Prendemos Sistema");
    miServo.attach(SERVON);
    
    return true;
    	
  }else{
    Serial.println("Apagamos Sistema");
    lcd.clear();
    miServo.detach();
    apagar_leds();
    return false;
  }
}

```

### Función `verificar_rangos_temperatura(int temperatura)`

Esta función verifica el rango de temperatura medido y determina la estación correspondiente en base a la temperatura proporcionada como argumento. Dependiendo del valor de `temperatura`, se encargaria de el manejo del flujo de la informacion por el sistema : 
```cpp
void verificar_rangos_temperatura(int temperatura){
  if (temperatura <=10){
    imprimir_lcd("invierno",temperatura);
  }else if(temperatura > 10 && temperatura < 19){
    imprimir_lcd("otonio",temperatura);
  }else if (temperatura > 19 && temperatura < 26){
    imprimir_lcd("primavera",temperatura);
  }else if (temperatura > 26 && temperatura <60){
    imprimir_lcd("verano",temperatura);
  }else if(temperatura > 60){
  	imprimir_lcd("ALERTA INCENDIO",temperatura);
    cambio_led = true;
    movimiento_servo();
    
  }
}
```

este fue mi sistema contra incendios creado con arduino UNO y codeado en c++

link del proyecto : [LINK](https://www.tinkercad.com/things/etIt6ldsVgO-spd-parcial-2-practico/editel?sharecode=I_iT20NXuCzjjEVeeWIdGrc5Cro2OrHPhnTrTYioBPA)



