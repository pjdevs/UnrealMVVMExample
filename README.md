# Unreal MVVM Example

This is a simple MVVM example using health on a character.


The project contain a level with a character with a world space health bar.
Data of the character's HealthComponent is bound to the widget via MVVMModelViewHealth.

The ViewModel is initialized in C++ in the Character class. 

Press P to loose life, L to set MaxHealth to 200.