import React from 'react'

export default class Submit extends React.Component {

  state = {

    code: `#include <iostream>
using namespace std;

int main(){

  return 0;
}`,
  }

  onChange = (e) => {
    this.setState({
      code: e.target.value,
    })
  }
  onSubmit = (e) => {

    e.preventDefault()

    if (this.state.code !== '') {

      this.props.onSubmit(this.state.code)
    }

  }

  render () {
    return (
      <form onSubmit={this.onSubmit} className={'submit-solve-problem'}>
        <div className={'form-item'}>
          <textarea
            autoCapitalize={'None'} autoCorrect={'None'}
            onChange={this.onChange} value={this.state.code}
            className={'form-textarea'} cols={10} rows={15}/>
        </div>
        <button className={'primary-btn'}>Submit</button>
      </form>
    )
  }
}