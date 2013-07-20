import com.sun.jna.Structure;


public class FT_HANDLE extends Structure {
	public FT_TRANSFER_AREA transfer_area;
	
	@Override
	protected List getFieldOrder() {
		return Arrays.asList(new String[]{
			"transfer_area"
		});
	}
}
