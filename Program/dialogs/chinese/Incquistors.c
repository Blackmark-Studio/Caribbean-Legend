void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("弟兄们, 宗教裁判所里混进敌人了! ", "拉响警报, 弟兄们! ");
					link.l1 = "确实, 宗教裁判所的敌人正在警觉... ";
					link.l1.go = "fight";		   
			}
			else
			{   
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你好, "+ GetSexPhrase("我的孩子","我的女儿") +"。 什么风把你吹来了? ..", "很高兴在我们的住所见到你, "+ GetSexPhrase("我的孩子","我的女儿") +"。 你有什么事? "),
							""+ GetSexPhrase("我的孩子","我的女儿") +", 我们今天已经谈过了。 你还有什么需要吗? ", ""+ GetSexPhrase("我的孩子","我的女儿") +", 我们修道会的修士们可没有无限的耐心。 所以, 我再问你一次: 你有什么需要吗? ",
							RandPhraseSimple("你在分散别人的注意力。 我不会再和你说话了。 ", ""+ GetSexPhrase("我的孩子","我的女儿") +", 我不喜欢毫无意义的闲聊。 我不会再和你说话了。 "), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("只是顺道来看看..", "忙得不可开交... "), 
							"哦, 不, 神父... ... ", "不, 神父, 我只是想谈谈... ", RandPhraseSimple("嗯... ", "好吧, 随你便, 神父... "), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //摄像头守卫
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "拿起武器! 有间谍! 抓住他! ";
					link.l1 = "该死! ";
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase("这是一个戒备森严的牢房, 严禁入内。 ", "别想进去, 这是死罪。 ", "只要你踏进这个牢房一步, 你就完了。 ");
					link.l1 = RandPhraseSimple("我明白了, 士兵。 ", "知道了... ");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //囚犯
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("哈哈, 看着那些'圣人'直下地狱不是很有趣吗? ! ", "哦天哪, 真的有人敢挑战他们? ! ", "他们把我折磨得半死, 我很快就要死了, 但你让我在生命的最后时刻开心了一次... ");
					link.l1 = RandPhraseSimple("哼! ", "不客气... ");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("那些伪君子完全没有人性。 他们对我们所做的一切, 都将在地狱中燃烧... ", "他们每天都在折磨我! 但在上帝面前我是无辜的! ", "我的狱友昨天死了... 他们在刑架上折磨了他两天... 谁知道我还能坚持多久... ");
					link.l1 = RandPhraseSimple("嗯... 好吧, 我不知道... ", "哦, 我明白了... ");
					link.l1.go = "exit";
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
	}
}