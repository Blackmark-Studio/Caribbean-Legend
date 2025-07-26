// 雅各布.范.贝格 - 恶棍与海盗, "幻影"号船长
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "啊! 嗝... 你他娘的是谁? 那个该死的中国人呢? 我在跟你说话, 你聋了吗? 嗝! ";
				link.l1 = "我听得很清楚, 别嚷嚷。 中国人不会来的。 我代替他来了。 ";
				link.l1.go = "HollJacob_inRoom";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "有个漏洞。 告诉开发者。 ";
			link.l1 = "如果你这么说... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "HollJacob_inRoom":
			dialog.text = "什么? 你是谁? 你他娘的在这儿干什么? 我问你话呢, 人渣! ";
			link.l1 = "你不需要知道。 我需要你的船。 ";
			link.l1.go = "HollJacob_inRoom_1";			
		break;
		
		case "HollJacob_inRoom_1":
			dialog.text = "啊... 什么? ! 你他妈的... 等等! 你是该死的英国狗! 去他的! 他们终究还是追踪到我了... 你死到临头了! 我不会投降的! ";
			link.l1 = "好吧, 我不需要你投降... ";
			link.l1.go = "HollJacob_inRoom_fight";			
		break;
		
		case "HollJacob_inRoom_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern_upstairs")], false);
			pchar.quest.JacobOnMainOver.over = "yes";//移除计时器
			chrDisableReloadToLocation = true;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "HollJacob_dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "JacobBerg_abordage":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "啊! 该死! 一团糟! 你不是商人, 对吧? ";
				link.l1 = "真聪明。 我的船员全是精选的英国海军陆战队员, 所以从一开始你就完蛋了。 理查德.弗利特伍德和我编了个商人的故事, 而你上钩了。 你的冒险结束了, 混蛋! ";
				link.l1.go = "JacobBerg_abordage_1";
			}
			else
			{
				dialog.text = "船长, 我们终于见面了。 你是个聪明人... 我已经很久没遇到过这么棘手的对手了。 ";
				link.l1 = "而我是你最后的对手, 雅各布。 你活不了离开这里。 ";
				link.l1.go = "JacobBerg_abordage_3";
			}
		break;
		
		case "JacobBerg_abordage_1":
			dialog.text = "看来是这样。 你的船员占领了船, 我也不指望能被宽恕。 但在他们来帮你之前, 我会先送你下地狱! 范.贝格会让你付出高昂代价的! ";
			link.l1 = "那只是你的看法。 我觉得你的命连一分钱都不值。 废话少说, 准备受死吧! ";
			link.l1.go = "JacobBerg_abordage_2";			
		break;
		
		case "JacobBerg_abordage_2":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "JacobBerg_abordage_3":
			dialog.text = "哦, 真的吗? 我确保你逃不掉。 我已经点燃了火药室的导火索。 很快我们的船就会被炸成碎片。 ";
			link.l1 = "我想只有你和你的破船会被炸掉。 我会把你开膛破肚, 夺回我的船, 然后在我驶离时欣赏烟火。 ";
			link.l1.go = "JacobBerg_abordage_4";			
		break;
		
		case "JacobBerg_abordage_4":
			dialog.text = "如果我先杀了你, 跳出窗户, 游到岸边, 自己欣赏烟火呢! ";
			link.l1 = "赌一把? ";
			link.l1.go = "JacobBerg_abordage_5";			
		break;
		
		case "JacobBerg_abordage_5":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
}
}