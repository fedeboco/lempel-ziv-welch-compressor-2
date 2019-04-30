# tp1_algo2
Este repositorio es para la realización del [tp1](https://drive.google.com/open?id=1HRHVCG4rCPjeaJc4PGqhb3bqituB64NW) de Algoritmos y programación II FIuba-1°C 2019.

## Git Workflow
El flujo de trabajo que pretendemos es el propuesto por Vincent Driessen en [a successful git brnach model](https://nvie.com/posts/a-successful-git-branching-model/).

* **Master**  
    Contiene la última versión estable.
    Cuando se realiza un release (ver **release** debajo) taguear de la sigueinte forma.
    
    > git tag -a tp1_1.0 -m "Comentario adicional 
    
    _Cómo taguear:_
    - **tp1** : hace referencia al tp en si.
    - **1.0** : hace referencia a la versión del TP.
* **develop**  
    En esta rama se agregan cambios incrementales, bugs o mejoras, hasta que se considera que es el momento de hacer una release nueva.   
    Antes de hacer la release comprobar el funcionamiento integral del código.
* **Release_xx**  
    Se utiliza para renombrar archivos que contienen en su nombre algún indicador de la versión de release.  
    Por ejemplo:
    - **Nombre inicial**: tp1_1.0
    - **Nombre final**: tp1_1.1
* **Issue_xx**  
    En estas ramas se implementan mejoras o correcciones de bugs.  
    El *flow* es el siguiente:  
    1. Se agrega una *issue* [aca](https://github.com/fedeboco/tp1_algo2/issues), donde se describe el tipo  :negative_squared_cross_mark: Bug o Mejora  :white_check_mark:.  
      _ Si es una mejora, agregar breve descripción, qués lo que se espera modificar, posible forma de implementación.  
      _ Si es un bug, describirlo, explicar los pasos para repoducioerlo, cuál es el funcionamiento esperado y cual es el que sucede.  
    2. Asignar la issue a la persona encargada.  
    3. Asignar la etiqueta doing cuando se comience a desarrollar.  
    4.Crear una rama desde develop para implementarla:  
    ```
    git checkout develop //vas a la rama develop
    git checkout -b issue_xx // creas la rama y te posicionas en dicha rama
    ```  
    5. Una vez testeada mergerar a develop y luego borrarla:  
    ```
    git checkout develop 
    git merge --no-ff issue_xx
    git -d issue_xx
    git push
    ```
    NOTA: Con `$ git -d issue_xx` se elimina la rama localmente, en caso de que se haya pusheado dicha rama a origin (repo en la nube) eliminarla de allí también mediante  `$ git push origin --delete the_remote_branch`  
    6. Cambiar la etiqueta de *Doing* a *Closed*.  
   
   ## Comandos de actualización de Master.  
    
    Una vez testeada la rama de develop, realizar:
    ```
    git checkout master  
    git merge develop
    ```
    
    
    
  
