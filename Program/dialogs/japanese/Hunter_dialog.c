void ProcessDialogEvent()
{
	ref NPChar, TempChar, sld;
	aref Link, Diag;
	
	int i, iTemp;
	string sTemp, sTemp1;
	string sGroup;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			chrDisableReloadToLocation = false;
			//Lai_SetPlayerType(pchar);
			
			dialog.text = GetFullName(PChar)+"! "+"俺たちはずいぶん長い間お前を追ってきたんだが、ついにお前は俺たちのものになったぜ。";
			Link.l1 = "お前は誰だ、俺に何の用だ？";
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name)+" お前の首にかなりの賞金がかけられてるんだ。どこの植民地に連れて行っても、 死んでいようが生きていようが報酬はもらえるってわけさ。";
			Link.l1 = "聞け、俺に構わず立ち去ってくれたら金を払うぞ。";
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("失礼ですが、あなたは勘違いしているようです。私は "+GetFullName(TempChar)+" - この地で名の知れた商人だ。","失礼ですが、何かお間違いではありませんか。私はただの普通の娘ですし、父は "+GetFullName(TempChar)+" - この地で名の知れた商人だ。")+".";
    			Link.l2.go = "lier";
			}
            Link.l3 = "よし、運試しをしてみてもいいぜ、もし望むならな。";
			Link.l3.go = "battle";
		break;
        
        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = "「おお！本当に勘違いかもしれません。どうかお許しください。」 "+GetAddress_Form(NPChar)+".";
                Link.l1 = "そういうこともあるさ、気にすんな…";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "俺はお前が嘘をついてると思うぜ！";
                Link.l1 = "聞け、俺に構わず立ち去ってくれたら金を払うぞ。";
			    Link.l1.go = "Cost_Head";
			    Link.l2 = "よし、運試しをしてみてもいいぜ、望むならな。";
			    Link.l2.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
            
        break;
        
        case "lier_2":
            AddDialogExitQuest("GoAway_Hunters_Land");
            DialogExit();
        break;
        // boal <--
        
        case "battle":
            AddDialogExitQuest("Battle_Hunters_Land");    // BOAL Весь код я перенес сюда по всем нациям, просто не переименовал
            DialogExit();
        break;

        case "Cost_Head2":
            AddMoneyToCharacter(pchar, -sti(PChar.HunterCost));

            AddDialogExitQuest("GoAway_Hunters_Land"); 
            DialogExit();
        break;

        case "Cost_Head":
			dialog.text = "私はそう思う "+PChar.HunterCost+" ペソで十分だぜ。";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "でも、そんな金は持ってねえんだ。";
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = "ほら、金だ。受け取って、とっとと失せろ。";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "こんな大金をお前らみたいなろくでなしに渡すくらいなら……ここで全員ぶった斬ってやるぜ！";
                Link.l2.go = "battle";
            }
		break;

        case "NoMoney":
			dialog.text = "その場合、俺たちの話はこれで終わりだ！";
			Link.l1 = "俺を生きたまま捕まえられると思うな。";
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = "「待て、」 "+GetSexPhrase("相棒","娘")+"…お前、何か面白いものを持ってるんじゃねえか。仲間同士なら見つけた宝は分け合うべきだと思わねえか？";
            Link.l1 = "聞けよ、俺に構わずにいてくれたら金を払うぜ。";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("失礼ですが、あなたは勘違いされているようです。私は "+GetFullName(TempChar)+" - この地で名の知れた市民だが、決して財宝探しの者ではない。","失礼ですが、何かお間違いではありませんか。私はただの普通の娘で、宝探しなんてしません。それに、私の父は "+GetFullName(TempChar)+" - この辺りでは有名な市民だ")+"!";
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = "どうやら、そろそろお前らの首と胴体を引き離す時が来たようだな。";
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = "「おお！それなら、俺たちが間違っていたかもしれねえな。どうか許してくれ、」 "+GetAddress_Form(NPChar)+".";
                Link.l1 = "そういうこともあるさ、気にすんな…";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "俺はお前が嘘をついてると思うぜ！";
			    Link.l1 = "ならば俺の刃の歌を聞け。";
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		case "TreasureCaptain":
			dialog.text = LinkRandPhrase("お前が俺の宝の地図を奪った張本人か！そろそろ奪ったものを全部返してもらおうか…","おお、ライバルか！俺の財宝の重みに押しつぶされて、お前はそう遠くへは行けねえぞ……","ふん、やっと追いついたぜ！この洞窟の財宝は全部俺のもんだ、わかったか？さあ、持ち物を全部出しな、相棒！");
			Link.l1 = LinkRandPhrase("俺の刃に会う時が来たぜ、相棒！","お前の宝だと？それは昔の話だな、今は俺のものだぜ！","俺はお前の腹をこの刃でぶちまけてやりてえんだぜ、相棒。");
			Link.l1.go = "TreasureCaptain_fight"; 
		break;
		
		case "TreasureCaptain_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться // patch-6
			for(i=1; i<=4; i++)
			{
				sld = characterFromId("Treasure_sailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "TreasureOfficer":
			dialog.text = LinkRandPhrase("そうか、大佐の言った通り、この洞窟に宝が隠されていたんだな……ポケットの中身を全部出せ、水夫！","とうとうこの忌々しいジャングルや茨、沼地を追い回して、やっとお前に追いついたぜ。さあ、野郎、 持ってるもの全部出しやがれ……","おい、水夫！その海賊の財宝は俺たちのもんだ、だから汚ねえ手をどけや！");
			Link.l1 = LinkRandPhrase("まさか軍人からそんなことを言われるとは思わなかったぜ！だがまあ、どうせお前に一発教えてやるさ……","あいつを見ろよ、士官の制服を着た海賊だぜ……","確かに、最近じゃ兵士も海賊も大して変わらねえな……");
			Link.l1.go = "TreasureOfficer_fight"; 
		break;
		
		case "TreasureOfficer_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться // patch-6
			for(i=1; i<=4; i++)
			{
				sld = characterFromId("Treasure_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// генератор "A reason to hurry"
		case "ReasonToFast_THunter_1":
			if(CheckAttribute(pchar,"GenQuest.CannotWait"))	DeleteAttribute(pchar, "GenQuest.CannotWait");
			dialog.text = "そして、ついに俺たちの金が来たぜ。少なくとも待った甲斐はあったな。";
			link.l1 = RandPhraseSimple("何をおっしゃっているのです、旦那方？私はオランダ西インド会社の代表者で、ここを通りかかっただけです！ 海岸の景色を眺めるために立ち寄っただけですよ！","私を誰かと間違えているようですね。私は "+GetSexPhrase("「フランソワ・マリー・パガネル」 ","「マリア＝テレジア」 ")+"博物学者だ。ここでこの地の植物の標本を集めているんだ。\nユッカの葉のコレクションを見てみないか？面白いものがいくつかあるぜ！");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "何の用だ！？俺の邪魔をするんじゃねえ！";
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "「ああ、いやだ」 "+GetSexPhrase("親愛なる友よ","「俺の可愛い娘」")+"。それは通用しない。我々はお前がその地図を持っていたことを確かに知っているんだ "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN)+"。それに、あいつはとんでもない守銭奴で、金でいっぱいの箱が中からはち切れそうだったんだ。だから、 俺たちが手ぶらで帰るわけがねえだろう。";
			link.l1 = "お前の言う通りだ。確かに宝箱は満杯だった。\nだが、お前には渡さねえ。あの洞窟に行ってみるといい、穴だらけのバケツが二つ三つまだ残ってるはずだぜ。";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "あんたの言う通りだ。宝は好きにしな。だが覚えておけ、それは血で汚れているから幸せはもたらさねえぞ。";
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = ""+GetSexPhrase("へっ、船長、あんたは死ぬにはまだ若すぎるじゃねえか……","へっ、お嬢ちゃん、死ぬにはまだ早いだろう…")+"...";
			link.l1 = "実は、俺は死ぬつもりなんてねえぞ！";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = "「これぞ分別ある者の言葉だな！」";
			link.l1 = "呪われちまえ、お前もその財宝も……";
			link.l1.go = "ReasonToFast_THunter_GoAway";
		break;
		
		case "ReasonToFast_THunter_GoAway":			
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			if(pchar.questTemp.ReasonToFast == "GetTreasure")
			{
				AddQuestRecord("ReasonToFast", "24");
				AddQuestUserData("ReasonToFast", "sName", GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
				CloseQuestHeader("ReasonToFast");	
			}
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFastTHunter_Fight":
			sGroup = "LAND_HUNTER";
			sTemp = "LandHunter0";
			iTemp = sti(pchar.HunterCost.Qty);
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			for(i = 1; i <= iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_TrHuntersDied");	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "ReasonToFast_HunterShore1":
			dialog.text = "「おい、」"+GetSexPhrase("相棒","娘")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" 「俺たちに何か用があるって言ってたぜ。」";
			link.l1 = "どういう意味だ？";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dialog.text = "「の地図」 "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN);
				link.l1 = "受け取って、よろしく伝えてくれ "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+"……彼にもうすぐ会うと伝えてくれ……";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" 俺があいつのために火中の栗を拾うと思ってるなら、大間違いだぜ。";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "お前が総督から盗んだ宝飾品だ。";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "これを持って、よろしく伝えてくれ "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+"……彼に、私たちがすぐに会うと伝えてくれ……";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" 俺があいつのために火中の栗を拾うと思ってるなら、大間違いだぜ。";
				link.l2.go = "ReasonToFast_HunterShore23";				
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore12_1":
			TakeNItems(pchar, "mapQuest", -1); 
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "a map of");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore12_2":
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}			
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "treasures");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.city + "_townhall");
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.LakeyLocation);
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore2":
			dialog.text = "「おい、」"+GetSexPhrase("相棒","娘")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" あなたにいくつか質問がある。";
			link.l1 = "「それなら、なぜ自分で彼らに聞かないんだ？」";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dialog.text = "身分相応の扱いじゃない。お前のせいで作戦が台無しになり、俺たちは失った "+sti(pchar.questTemp.ReasonToFast.p10)+" お前のせいでペソを失った。だから今、お前には返すべき借りがあるんだ。";
			link.l1 = "受け取って、「よろしく」と伝えてくれ "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+"「……彼に、私たちはすぐに会うことになると伝えてくれ……」";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" 俺があいつのために火中の栗を拾うと思ってるなら、大間違いだぜ。";
			link.l2.go = "ReasonToFast_HunterShore23";
		break;
		
		case "ReasonToFast_HunterShore22":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p10))
			{
				AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p10)));
				AddQuestRecord("ReasonToFast", "20");
				AddQuestUserData("ReasonToFast", "sText", "money");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
				DialogExit();	
				AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
			}
			else
			{
				dialog.text = "ああ、そんな金は持ってないのか！まあ、自分で選んだことだ…… ";
				link.l1 = "昔々……";
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = "……まあ、自分で選んだんだな……";
			link.l1 = "昔々……";
			link.l1.go = "ReasonToFastTHunter_Fight";
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
				pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
			}
		break;
		// генератор "A reason to hurry"
	}
}

string GetLocHunterName()
{
	int nLoc = FindLocation(Pchar.location);
	string ret = "";

	if (CheckAttribute(&locations[nLoc],"islandId"))
	{
		if (locations[nLoc].islandId != "Mein")
		{
			ret = "island of " + GetIslandNameByID(locations[nLoc].islandId);
		}
		else
		{
			ret = "mainland of ";
		}
	}
	//
	if (CheckAttribute(&locations[nLoc],"fastreload"))
	{
		ret += " (" +GetCityName(locations[nLoc].fastreload) + ")";
	}

	return ret;	
}
