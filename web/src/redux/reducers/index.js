import { combineReducers } from 'redux'
import scoreboard from './scoreboard'
import problem from './problem'
import submission from './submission'
import message from './message'
import app from './app'

export default combineReducers({
  scoreboard,
  problem,
  submission,
  message,
  app,
})