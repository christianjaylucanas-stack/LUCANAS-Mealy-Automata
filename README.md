class MealyCStyleCommentDetector:
    def __init__(self):
        self.reset()

    def reset(self):
        self.state = 'q0'

    def transition(self, char):
        # Maps (state, input) -> (next_state, output)
        if self.state == 'q0':
            if char == '/':
                self.state, output = 'q1', '0'
            else:
                self.state, output = 'qE', '0'

        elif self.state == 'q1':
            if char == '*':
                self.state, output = 'q2', '0'
            else:
                self.state, output = 'qE', '0'

        elif self.state == 'q2':
            if char == '*':
                self.state, output = 'q3', '0'
            elif char in ('a', '/'):
                self.state, output = 'q2', '0'
            else:
                self.state, output = 'qE', '0'

        elif self.state == 'q3':
            if char == '/':
                self.state, output = 'q4', '1'
            elif char == '*':
                self.state, output = 'q3', '0'
            elif char == 'a':
                self.state, output = 'q2', '0'
            else:
                self.state, output = 'qE', '0'

        elif self.state in ('q4', 'qE'):
            self.state, output = 'qE', '0'

        else:
            self.state, output = 'qE', '0'

        return self.state, output

    def process(self, input_string):
        self.reset()
        state_history = [self.state]
        output_history = []

        for char in input_string:
            next_state, out = self.transition(char)
            state_history.append(next_state)
            output_history.append(out)

        # String is accepted if the final output emitted is '1'
        is_accepted = (output_history[-1] == '1') if output_history else False
        return state_history, output_history, is_accepted


# --- Verification Suite ---
if __name__ == "__main__":
    machine = MealyCStyleCommentDetector()

    accepted_samples = ["/*a*/", "/**/", "/***/", "/*aaa*aaa*/", "/*a/a*/"]
    rejected_samples = ["/**", "/**/a/*aa*/", "aaa/**/aa", "/*/", "/**a/", "//aaaa"]

    print("=== ACCEPTED STRINGS ===")
    for s in accepted_samples:
        states, outputs, accepted = machine.process(s)
        print(f"Input: {s:15} | Outputs: {' '.join(outputs)} | Result: ACCEPTED")

    print("\n=== REJECTED STRINGS ===")
    for s in rejected_samples:
        states, outputs, accepted = machine.process(s)
        print(f"Input: {s:15} | Outputs: {' '.join(outputs)} | Result: REJECTED")