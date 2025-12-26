// Якоб ван Берг - злодей и пират, капитан Миража
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
				dialog.text = "うぐっ！ひっく…てめえは誰だ？あのクソ中国人はどこ行きやがった？おい、聞いてんのか、耳が遠いのか？ひっく！";
				link.l1 = "よく聞こえてるから、大声出すな。中国人は来ねえよ。代わりに俺が来たんだ。";
				link.l1.go = "HollJacob_inRoom";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "バグだ。開発者に伝えてくれ。";
			link.l1 = "そう言うなら……";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "HollJacob_inRoom":
			dialog.text = "何だと？お前は誰だ？ここで一体何してやがる？質問に答えろ、このクズ野郎！";
			link.l1 = "それを知る必要はねえ。俺にはお前の船が必要なんだ。";
			link.l1.go = "HollJacob_inRoom_1";			
		break;
		
		case "HollJacob_inRoom_1":
			dialog.text = "うぐっ…なんだと！？てめえ、ふざけやがって…待てよ！てめえはイギリス野郎じゃねえか！くそっ！やっぱり俺の居場所を嗅ぎつけやがったな…ここが貴様の墓場だ！俺は絶対に降参なんかしねえぞ！";
			link.l1 = "さて、別にお前に降伏してほしいわけじゃねえんだが…";
			link.l1.go = "HollJacob_inRoom_fight";			
		break;
		
		case "HollJacob_inRoom_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern_upstairs")], false);
			pchar.quest.JacobOnMainOver.over = "yes";//снять таймер
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
				dialog.text = "うおっ！くそっ！なんてこった！お前、商人じゃねえよな？";
				link.l1 = "なんて賢い坊やだ。俺の部下は選りすぐりのイギリス海兵ばかりだ、最初からお前の負けだったんだよ。 リチャード・フリートウッドと俺で商人の話をでっち上げた、そしてこうしてお前が現れた。 お前の冒険はこれで終わりだ、このろくでなし！";
				link.l1.go = "JacobBerg_abordage_1";
			}
			else
			{
				dialog.text = "ついにお会いできましたな、船長。あなたはなかなかの切れ者ですね……これほど手強い相手に会うのは久しぶりです。";
				link.l1 = "そして俺が最後の相手だ、ジェイコブ。ここから生きては帰れねえぞ。";
				link.l1.go = "JacobBerg_abordage_3";
			}
		break;
		
		case "JacobBerg_abordage_1":
			dialog.text = "そのようだな。お前の乗組員がこの船を奪った以上、俺が助かる見込みはないだろう。だが、 奴らが来る前にお前を地獄に送ってやる！ヴァン・ベルグはただでは死なねえぞ！";
			link.l1 = "それはお前の勝手な意見だ。俺はお前の命なんざ一文の価値もねえと思ってるぜ。もういい、覚悟しやがれ！";
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
			dialog.text = "ほう、本当か？お前が逃げられないように手を打っておいたぜ。火薬庫に導火線をつけてやったんだ。 もうすぐ俺たちの船は木っ端みじんになるぞ。";
			link.l1 = "俺はな、お前とそのオンボロ船だけが吹っ飛ぶと思ってるぜ。俺はお前をぶっ殺して、自分の船を取り戻し、 花火を眺めながら悠々と出航させてもらうからな。";
			link.l1.go = "JacobBerg_abordage_4";			
		break;
		
		case "JacobBerg_abordage_4":
			dialog.text = "先にお前を殺して、窓から飛び出して、泳いで岸まで行って、自分で花火を見物するまでの話だな！";
			link.l1 = "「賭け金か？」";
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
