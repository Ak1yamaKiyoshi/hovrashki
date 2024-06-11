

class math_utils:
    @staticmethod
    def clip(value, min_value, max_value):
        """
        Clips the given value between the specified minimum and maximum values.
        
        Args:
            value (float): The value to be clipped.
            min_value (float): The minimum value of the range.
            max_value (float): The maximum value of the range.
            
        Returns:
            float: The clipped value within the specified range.
        """
        return max(min_value, min(value, max_value))