import com.sun.jna.Structure;

import java.util.Arrays;
import java.util.List;


public class FT_HANDLE extends Structure {
	public FT_TRANSFER_AREA transfer_area;

    @Override
    protected List getFieldOrder() {
            return Arrays.asList("transfer_area");
    }
}
