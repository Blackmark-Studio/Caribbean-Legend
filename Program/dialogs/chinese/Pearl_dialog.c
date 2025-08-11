void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "我们没什么可谈的! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> 定居点的采珠人
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("你好! 我叫" + GetFullName(npchar) + "。 有什么能为你效劳的吗? ", 
				"再次问候你! ", 
				"在这种穷乡僻壤, 客人可真少见... ",
				"能和新面孔聊天真是太好了! 我已经看腻了那些老面孔... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("哦, 没什么... ", 
				"我也是... ",
				"了解... ", 
				"呵... ", npchar, Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "我们在这里采集珍珠, 为" + NationNameGenitive(sti(npchar.nation)) + "效力, 你知道的... ";
			link.l1 = "嗯, 我知道... ";
			link.l1.go = "exit";
			link.l2 = "嘿, 听着, 有没有可能直接从'生产者'手里买几颗这种小玩意儿, 你觉得呢? ";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "哦不, 当然不行! 哪怕偷一颗小珍珠都要被判处死刑! ";
				link.l1 = "你们这里的规矩确实够狠... ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "是啊, 我们这里规矩很严, 任何错事都可能让人掉脑袋。 我不做这生意, 但我可以建议你和当地印第安人谈谈。 如果出了什么事, 他们有地方可逃, 所以应该比我们更胆大... ";
				link.l1 = "明白了... 好吧, 谢谢。 ";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("你完全疯了吗? 滚蛋, 你这个白痴! ", 
				"什么? ! 你脑子坏掉了吗, 蠢货? ! 带着你那些问题滚蛋... ", 
				"你脑子进水了吗, 亲爱的? 什么海盗? 这里? ! 快滚蛋, 你这个傻瓜... ");
			link.l1 = RandPhraseSimple("没必要这么粗鲁... ", "说话注意点! ");
			link.l1.go = "exit";
		break;

		// ==> 定居点的印第安人
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat("白脸人想说话? ", 
				"又是你, 白脸人。 ", 
				"白脸人喜欢说话, 看起来像个娘们。 ",
				"神灵把我的白脸兄弟/姐妹带到了我面前。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("是的。 ", 
				"嗯, 又是我。 ",
				"真有诗意。 ", 
				"我也很高兴见到你", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "告诉我, 你为什么来这里。 ";
			link.l1 = "哦, 没什么特别的, 只是想听听你想说什么。 ";
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "船长, 你在做什么? 把武器收起来, 免得惹上大麻烦! ";
			link.l1 = LinkRandPhrase("好的。 ", "好的。 ", "别担心, 我这就收起来... ");
			link.l1.go = "exit";
		break;  

	}
}