package tree_view;

import java.awt.Component;
import java.util.Enumeration;

import javax.swing.Icon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTree;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeCellRenderer;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

public class TreeView extends JFrame {
	private static JTree tree;

	public void TreeView() {
	}

	private static void expandAll(JTree tree, TreePath parent) {
		TreeNode node = (TreeNode) parent.getLastPathComponent();
		if (node.getChildCount() >= 0) {
			for (Enumeration e = node.children(); e.hasMoreElements();) {
				TreeNode n = (TreeNode) e.nextElement();
				TreePath path = parent.pathByAddingChild(n);
				expandAll(tree, path);
			}
		}
		tree.expandPath(parent);
		// tree.collapsePath(parent);
	}

	public static void expandAll(JTree tree) {
		TreeNode root = (TreeNode) tree.getModel().getRoot();
		expandAll(tree, new TreePath(root));
	}
	/*
	@Override
    public Component getTreeCellRendererComponent(JTree tree,
            Object value, boolean selected, boolean expanded,
            boolean isLeaf, int row, boolean focused) {
        Component c = super.getTreeCellRendererComponent(tree, value,
                selected, expanded, isLeaf, row, focused);
        if (selected)
            setIcon(loadIcon);
        else
            setIcon(saveIcon);
        return c;
    }
    */
	private static DefaultMutableTreeNode addMsg(DefaultMutableTreeNode parent, String logMsg, String srcFile, int srcLine, int logLine)
	{
		String txt = logMsg + "       [" + srcFile + " " + srcLine + " # " + logLine + "]";
		DefaultMutableTreeNode node = new DefaultMutableTreeNode(txt);
		parent.add(node);
		return node;
	}
	private static DefaultMutableTreeNode addMsg(DefaultMutableTreeNode parent, String logMsg, String srcFile, int srcLine, int logLine, int correctedSrcLine) // srcLine - line no in log
	{
		String txt = logMsg + "       [" + srcFile + " " + correctedSrcLine + "(" + srcLine + ") # " + logLine + "]";
		DefaultMutableTreeNode node = new DefaultMutableTreeNode(txt);
		parent.add(node);
		return node;
	}
	private static DefaultMutableTreeNode addFunc(DefaultMutableTreeNode parent, String funcName, String callFile, int callLine, String srcFile, int srcFirstLine, int srcLastLine) {
		String txt = funcName + "       [" + callFile + " " + callLine + " -> " + srcFile + " " + srcFirstLine + " : " + srcLastLine + "]";
		DefaultMutableTreeNode node = new DefaultMutableTreeNode(txt);
		parent.add(node);
		return node;		
	}
	private static void createModel(DefaultMutableTreeNode root) {
		DefaultMutableTreeNode func1 = addFunc(root, "QmMgrClass::QueueTask", "???", 0, "qm_task.cpp", 79, 225);
			DefaultMutableTreeNode label1 = addMsg(func1, "QM event", "qm_task.cpp", 102, 4464710);
			DefaultMutableTreeNode func2 = addFunc(func1, "QmMgrClass::NewCmdArrivedEvent", "qm_task.cpp", 155, "qm_task.cpp", 286, 415);
				DefaultMutableTreeNode label2 = addMsg(func2, "QM new cmd arrived task", "qm_task.cpp", 288, 4464711);			
				DefaultMutableTreeNode func3 = addFunc(func2, "QmDefaultClass::AttemptSequentialLink", "qm_task.cpp", 323, "qm_default.cpp", 14338, 14430);
					DefaultMutableTreeNode label3 = addMsg(func3, "QM attemp seq link", "qm_default.cpp", 14347, 4464712);
				DefaultMutableTreeNode func4 = addFunc(func2, "QmDefaultClass::PromoteReceiveQueueCmd", "qm_task.cpp", 364, "qm_default.cpp", 558, 694);
					DefaultMutableTreeNode label4 = addMsg(func4, "QM promote receiveQ", "qm_default.cpp", 560, 4464713);
					DefaultMutableTreeNode func5 = addFunc(func4, "QmDefaultClass::RestrictionCheck", "qm_default.cpp", 591, "qm_default.cpp", 8402, 8631);
						DefaultMutableTreeNode label5 = addMsg(func5, "QM RestrictionCheck", "qm_default.cpp", 8411, 4464714);
						DefaultMutableTreeNode func6 = addFunc(func5, "QmOutputClass::NoCommandConflict", "qm_default.cpp", 8430, "qm_out.cpp", 1671, 2215);
							DefaultMutableTreeNode label6 = addMsg(func6, "QM NoCmdConflict", "qm_out.cpp", 1821, 4464715);
						
		DefaultMutableTreeNode func7 = addFunc(root, "SasMgrClass::OtherActionDataPointer", "???", 0, "hi_sasmgr.cpp", 1151, 1373);
			DefaultMutableTreeNode label7 = addMsg(func7, "HI action other data pointer", "hi_sasmgr.cpp", 1193, 4464716, 1157);
		
							DefaultMutableTreeNode func8a = addFunc(func6, "QmOutputClass::FillInRangeDataFromCmdBlockPtr", "qm_out.cpp", 1857, "qm_out.cpp", 2223, 2322);
								DefaultMutableTreeNode func8 = addFunc(func8a, "DriveData32Class::GetIbaFromLba", "qm_out.cpp", 2297, "cb_def.cpp", 935, 956);
									DefaultMutableTreeNode label8 = addMsg(func8, "CB IbaFromLba", "cb_def.cpp", 972, 4464717);
							DefaultMutableTreeNode func9 = addFunc(func8a, "DriveData32Class::GetIbaFromLba", "qm_out.cpp", 2299, "cb_def.cpp", 935, 956);
								DefaultMutableTreeNode label9 = addMsg(func9, "CB IbaFromLba", "cb_def.cpp", 972, 4464718, 951);			
							DefaultMutableTreeNode func10a = addFunc(func6, "QmIdClass::PeekCommandRange", "qm_out.cpp", 1865, "qm_id.cpp", 1210, 1242);
								DefaultMutableTreeNode func10 = addFunc(func10a, "CeRwClass::FillRangeData", "qm_id.cpp", 1232, "ce_rw_uty.cpp", 6402, 6626);
									DefaultMutableTreeNode label10 = addMsg(func10, "CE rw fill range data", "ce_rw_uty.cpp", 6625, 4464719);
							DefaultMutableTreeNode func11 = addFunc(func6, "QmOutputClass::AnalyzeCmdProximity", "qm_out.cpp", 2024, "qm_out.cpp", 3382, 3445);
								DefaultMutableTreeNode label11 = addMsg(func11, "QM AnalyzeCmdEarlyRet", "qm_out.cpp", 3395, 4464720);

/*		
		DefaultMutableTreeNode f_FindSequentialExtendCmds = new DefaultMutableTreeNode(
				"QmDefaultClass::FindSequentialExtendCmds   [qm_default.cpp 9944 : 10038]");
		root.add(f_FindSequentialExtendCmds);

		DefaultMutableTreeNode label14 = addMsg(f_FindSequentialExtendCmds, "QM find seq extend cmds", "qm_default.cpp", 9960, 0);

		DefaultMutableTreeNode f_RestrictionCheck = new DefaultMutableTreeNode(
				"QmDefaultClass::RestrictionCheck   [qm_default.cpp 9963 -> 8402 : 8631]");
		f_FindSequentialExtendCmds.add(f_RestrictionCheck);

//		DefaultMutableTreeNode f_NoCommandConflict = new DefaultMutableTreeNode(
//				"QmOutputClass::NoCommandConflict   [qm_default.cpp 8430 -> qm_out.cpp 1671 : 2215]");
//		f_RestrictionCheck.add(f_NoCommandConflict);
		
		DefaultMutableTreeNode f_NoCommandConflict = addFunc(f_RestrictionCheck, "QmOutputClass::NoCommandConflict", "qm_default.cpp", 8430, "qm_out.cpp", 1671, 2215);

		DefaultMutableTreeNode label13 = new DefaultMutableTreeNode(
				"QM NoCmdConflict   [qm_out.cpp 1821]");
		f_NoCommandConflict.add(label13);

		DefaultMutableTreeNode f_AnalyzeCmdProximity = new DefaultMutableTreeNode(
				"QmOutputClass::AnalyzeCmdProximity   [qm_out.cpp 2024 -> 3382 : 3445]");
		f_NoCommandConflict.add(f_AnalyzeCmdProximity);

		DefaultMutableTreeNode label12 = new DefaultMutableTreeNode(" QM AnalyzeCmdEarlyRet   [qm_out.cpp 3395]");
		f_AnalyzeCmdProximity.add(label12);

		DefaultMutableTreeNode label3 = new DefaultMutableTreeNode("QM SeqAttDbg   [qm_out.cpp 2029]");
		f_NoCommandConflict.add(label3);

		DefaultMutableTreeNode f_ScanForDirtyWriteConflicts = new DefaultMutableTreeNode(
				"SgMgrClass::ScanForDirtyWriteConflicts   [qm_out.cpp 2193 -> sg_hash.cpp 435 : 808]");
		f_NoCommandConflict.add(f_ScanForDirtyWriteConflicts);

		DefaultMutableTreeNode label4 = new DefaultMutableTreeNode("SG DW ScanConflicts   [sg_hash.cpp 484]");
		f_ScanForDirtyWriteConflicts.add(label4);

		DefaultMutableTreeNode label5 = new DefaultMutableTreeNode(
				"SgDirtyWrite::Table::GetIterator   [sg_hash.cpp 493 -> SgDirtWriteTable.cpp 589 : 592]");
		f_ScanForDirtyWriteConflicts.add(label5);

		DefaultMutableTreeNode label6 = new DefaultMutableTreeNode(
				"SgDirtyWrite::IrqDisablingIterator::IrqDisablingIterator   [SgDirtWriteTable.cpp 591 -> SgDirtyWriteIrqDisablingIterator.cpp 266 : 299]");
		label5.add(label6);

		DefaultMutableTreeNode label7 = new DefaultMutableTreeNode(
				"SG DwTableCreateIter   [SgDirtyWriteIrqDisablingIterator.cpp 291]");
		label6.add(label7);

		DefaultMutableTreeNode label8 = new DefaultMutableTreeNode(
				"SgDirtyWrite::IrqDisablingIterator::Reset   [SgDirtyWriteIrqDisablingIterator.cpp 298 -> 149 : 184]");
		label6.add(label8);

		DefaultMutableTreeNode label9 = new DefaultMutableTreeNode(
				"SG DwTableIterReset   [SgDirtyWriteIrqDisablingIterator.cpp 151]");
		label8.add(label9);

		DefaultMutableTreeNode label1 = new DefaultMutableTreeNode("SG DW LimitReadAhead   [sg_hash.cpp 555]");
		f_ScanForDirtyWriteConflicts.add(label1);

		DefaultMutableTreeNode label2 = new DefaultMutableTreeNode("SG DW ScanConflicts exit   [sg_hash.cpp 802]");
		f_ScanForDirtyWriteConflicts.add(label2);

		DefaultMutableTreeNode label10 = new DefaultMutableTreeNode("QM DbgRestrict   [qm_default.cpp 8513]");
		f_RestrictionCheck.add(label10);

		DefaultMutableTreeNode label11 = new DefaultMutableTreeNode(
				"QM done restriction check   [qm_default.cpp 8618]");
		f_RestrictionCheck.add(label11);
	*/	
	}
	
	private static void createAndShowGUI() {
		// Create and set up the window.
		JFrame frame = new JFrame("HelloWorldSwing");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// Add the ubiquitous "Hello World" label.
		JLabel label = new JLabel("Hello World");
		frame.getContentPane().add(label);

		
		
				 
		 
		// create the root node
		DefaultMutableTreeNode root = new DefaultMutableTreeNode("Root");


		// create the tree by passing in the root node
		tree = new JTree(root);
		createModel(root);
		
		
        tree.setCellRenderer(new DefaultTreeCellRenderer() {
            private Icon icon1 = UIManager.getIcon("OptionPane.errorIcon");
            private Icon icon2 = UIManager.getIcon("OptionPane.informationIcon");
            private Icon icon3 = UIManager.getIcon("OptionPane.questionIcon");
            @Override
            public Component getTreeCellRendererComponent(JTree tree,
                    Object value, boolean selected, boolean expanded,
                    boolean isLeaf, int row, boolean focused) {
                Component c = super.getTreeCellRendererComponent(tree, value,
                        selected, expanded, isLeaf, row, focused);
                if(row == 0)
                    setIcon(icon3);               	
                else if (isLeaf)
                    setIcon(icon1);
                else
                    setIcon(icon2);
                return c;
            }
        });		
		expandAll(tree);
		frame.getContentPane().add(tree);

		// Display the window.
		frame.pack();
		frame.setVisible(true);
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				// new TreeView();
				createAndShowGUI();
			}
		});
	}

}
