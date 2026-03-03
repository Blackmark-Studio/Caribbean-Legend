void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "축하합니다! 이건 버그입니다. Jason에게 연락해서 어떻게, 어디서 이 버그를 발견했는지 알려주십시오. 평안하길!";
			link.l1 = "즉시 하겠습니다!";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(1.00);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("바다의 아들아, 반갑다! 네 소문을 들었지. 우리 땅에서 자유롭게 다녀도 된다.",""+npchar.name+" 창백한 얼굴의 형제여, 그대가 우리 손님으로 와서 기쁘다.","용감한 창백한 얼굴의 전사여, 그대를 맞이하오! "+npchar.name+" 인디언들의 친구를 만나 기쁘다. 평안히 가라!");
				link.l1 = RandPhraseSimple("붉은 피부의 형제여, 그대에게도 인사를! 사냥이 잘 되길 바라네!","용감한 전사여, 안녕하시오! 신들께서 그대와 그대 가족에게 축복을 내리시길 바라오!");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("붉은 피부의 형제여, 네가 관심 가질 만한 게 있어. 거래할래?","용감한 전사여, 흥미로운 물건을 팔 수 있소. 거래해 볼 텐가?");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("멈춰라, 창백한 얼굴! 무슨 권리로 내 땅을 밟고 다니는 거냐?","멈춰라, 백인 놈! 여기는 내 조상들의 땅이자 내 땅이다!","멈춰라, 창백한 놈! 내 땅에 네가 있을 곳은 없다");
				link.l1 = RandPhraseSimple("네 땅이라고? 꺼져라, 이 붉은 얼굴 잡놈아!","저 놈 좀 봐라 - 말하는 원숭이잖아! 이제 꺼져라!");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("나는 평화롭게 왔소, 붉은 피부의 전사여. 아무 이유 없이 싸울 필요는 없지.","나는 너나 네 땅의 적이 아니네, 전사여. 나는 평화를 위해 왔네.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > hrand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("나는 싸우러 온 게 아니라 거래하러 왔어.","나는 인디언들과 싸우지 않아. 그들과 거래하지.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > hrand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("네가 태어난 그날을 후회하게 해주지, 창백한 놈아... 네 심장을 도려내서 불에 구워주마!","돌멩이나 처먹게 해주마, 창백한 놈아! 네가 무릎 꿇고 죽여달라고 빌 때 우린 실컷 비웃어주지, 하얀 잡놈아!");
			link.l1 = RandPhraseSimple("아직도 그 더러운 입을 다물지 못하겠어, 화장한 허수아비 녀석? 네가 기어 나온 정글로 다시 쫓아버릴 거다!","감히 나를 협박해? 이 쓰레기야?! 이제 막 나무에서 내려온 주제에 다시 기어올라가라!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("네 목소리가 진실을 말하는 것 같군. 오늘은 도끼를 너에게 들이대지 않겠다. 평안히 가라, 창백한 얼굴.","창백한 얼굴의 자들은 좀처럼 평화를 가져오지 않지. 하지만 네 눈을 보니 진심인 것 같구나. 이제 가거라.");
			link.l1 = RandPhraseSimple("현명한 결정이오, 전사여. 행운을 빌겠소.","우리가 이해를 하게 되어 기쁘네, 전사여.");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("거짓말하지 마라, 창백한 놈! 인디언을 죽이려고 온 거잖아! 싸울 준비 됐냐, 창백한 놈?!","너희는 인디언을 죽인다. 백인의 혀는 거짓말쟁이 혀다. 내가 그 혀를 잘라내어 불에 구워버리겠다!");
			link.l1 = RandPhraseSimple("글쎄, 친구야, 그럼 나한테 탓하지 마라. 신만이 아시겠지만, 나도 피하려고 했거든...","좋아, 네가 원한 거다, 전사.");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "거래? 우리는 백인들의 무기가 필요하다. 창백한 얼굴들이 쓰는 한 손 불무기 말이다! 그걸 위해서라면 우리 물건을 내놓지. 불무기, 거래할 수 있나?";
				link.l1 = "흠. 있지. 그런데 뭘 줄 건데?";
				link.l1.go = "war_indian_trade";
				link.l2 = "이 악당아! 그리고 내 권총으로 식민지 사람들을 쏘겠다고? 그건 절대 안 돼! 그리고 너희 자칼들, 지금 당장 전부 베어버리겠다...";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "네가 우리가 원하는 걸 가지고 있지 않구나, 창백한 얼굴 녀석... 넌 우리 전리품이 될 거다!";
				link.l1 = "해볼 테면 해봐라, 허수아비...";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("우리는 창백한 얼굴의 개들과 거래하지 않는다. 죽이고 빼앗는다!","우리는 더러운 미스키토족이나 아라와크족이 아니다, 우리는 창백한 얼굴들과 거래하지 않아! 우리는 그놈들을 죽이고 전리품을 챙긴다!");
			link.l1 = RandPhraseSimple("그렇다면 한번 털어보시지, 이 악당아!","먼저, 내 세이버부터 빼앗아야 할 거다, 이 더러운 놈아!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "네가 가진 걸 보여 줘라, 그러면 우리가 얼마를 줄지 말해 주지.";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Offer "+XI_ConvertString("pistol"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (hrand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(9)+14);
				iTotalTemp = hrand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "이봐! 우리가 그걸 위해 줄게 "+sText+".";
			link.l1 = "거래 성사!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "아니. 절대 안 돼.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (hrand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(3)+1);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "이봐! 영리한 무기구만... 우리가 그걸로 뭔가 줄게\n "+sText+".";
			link.l1 = "거래 성사!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "아니. 절대 안 돼.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (hrand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = hrand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful pearl";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(2)+2);
				iTotalTemp = hrand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  this beautiful stone";
			}
			dialog.text = "이봐! 대단한 무기다! 적을 아주 많이 죽이지! 그걸로 우리가 너한테 준다 "+sText+".";
			link.l1 = "거래 성사!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "아니. 절대 안 돼.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "obereg_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "이봐! 무시무시한 무기군... 그걸 주면 이걸 주지\n "+sText+".";
			link.l1 = "거래 성사!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "아니. 절대 안 돼.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (hrand(7) < 7)
			{
				if (hrand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+hrand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = hrand(4)+10;
				}
				qty = hrand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = hrand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful and precious petrified tar";
			}
			else
			{
				npchar.quest.item = "indian_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "이봐! 아름답고 강력한 무기구나! 적을 아주 많이 죽였지! 우리가 그걸 위해 네게 준다 "+sText+".";
			link.l1 = "거래 성사!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "아니. 절대 안 돼.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "amulet_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "이봐! 쓸만한 무기군... 그거에 대해 뭔가 챙겨줄게 "+sText+".";
			link.l1 = "거래 성사!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "아니. 절대 안 돼.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(1.00);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("You have given "+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("You have received "+XI_ConvertString(npchar.quest.item)+" in amount of "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+hrand(2));
			{
				dialog.text = "좋아. 여기 네 물건이다. 더 이상 거래하지 않겠다. 나중에 다시 와라. 더 좋은 화염 무기를 가져오면 더 많이 주지. 이제 가!";
				link.l1 = "잘 가시오, 붉은 피부의 전사여.";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "좋아. 여기 네 물건이야. 더 불붙는 무기를 거래할 생각 있나?";
				if (CheckCaribGuns())
				{
					link.l1 = "있어. 살 거야?";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "아니. 다음에는 더 가져올게.";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "가져와라. 더 좋은 화염 무기를 가져오면 더 많이 쳐주지. 이제 가!";
			link.l1 = "또 보자, 전사야...";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "그럼 이제 다 공짜로 가져가겠다, 창백한 놈아!";
				link.l1 = "시도해 보시지...";
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase("이봐, 백인. 우리 정글에 무슨 일로 왔지?","우리 정글은 매우 위험해. 여기서 뭐 하고 있어?","무슨 일로 여기 왔나, 용감한 창백이?");
			link.l1 = RandPhraseSimple("나는 그냥 지나가던 참이야, 내 붉은 피부 친구. 이 길은 우리 둘 다 지나갈 만큼 충분히 넓지 않겠어?","정글의 아들아, 반갑다! 나는 일 때문에 왔고, 인디언들과 싸우려는 게 아니야.");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("그걸 왜 알려고 해? 네 갈 길이나 가고 괜히 문제 일으키지 마!","네 갈 길이나 가라, 붉은 피부 녀석. 나는 너랑 이야기할 시간 없다.");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("우리는 평화로운 사람들이오. 우리는 백인들과 적이 아니오. 가시오, 하지만 우리 땅에서는 조심하시오!","나는 인디언들의 창백한 얼굴 친구를 만나게 되어 기쁘다. 평안히 가라, 바다의 아들아!");
			link.l1 = RandPhraseSimple("행운을 빌지, 셀바의 아들아...","잘 가라, 붉은 피부 친구야.");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("우리는 평화로운 사냥꾼이다. 하지만 우리 땅에서 창백한 얼굴들이 그런 식으로 말하는 건 용납하지 않겠다!","우리는 백인들과 싸우지 않는다. 하지만 백인들이 우리를 모욕하면, 조상들께서 가르쳐주신 대로 응징한다!");
			link.l1 = RandPhraseSimple("아직도 그 더러운 입을 다물지 못하겠냐, 칠해진 허수아비 녀석아? 네가 기어 나온 정글로 다시 쫓아버릴 거다!","감히 나를 협박해? 이 쓰레기 같은 놈! 이제 네가 방금 내려온 그 나무나 다시 기어올라가라!");
			link.l1.go = "exit_fight";
		break;
	}
}
