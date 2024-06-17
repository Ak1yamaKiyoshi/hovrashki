

### file structure: 
```
src/events: # global events
src/types: 
  type:
  - events
  - actions 
  - type

utils:
  accounting: # event and object handlers 
```

### game class anatomy:
```
Game: 
- setup - use setup handler 
- update - use update handler 
- events - use event handler 
- draw - use draw handler 
```
