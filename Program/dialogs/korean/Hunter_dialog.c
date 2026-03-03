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
			
			dialog.text = GetFullName(PChar)+"! "+"우리는 꽤 오랫동안 너를 쫓아다녔는데, 드디어 이제 너는 우리 손아귀에 들어왔군.";
			Link.l1 = "너 누구야, 그리고 나한테 뭘 원하는 거지?";
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name)+" 네 머리에 꽤 괜찮은 현상금이 걸렸으니, 너를 그들의 식민지 아무 데나 넘기기만 하면 살아 있든 죽어 있든 우리는 돈을 받게 된다.";
			Link.l1 = "이봐, 나 좀 내버려두면 돈을 줄게.";
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("실례지만, 뭔가 착각하신 것 같군요. 나는 "+GetFullName(TempChar)+" - 이 땅에서 잘 알려진 상인이오.","실례지만, 착각하신 것 같아요. 저는 그냥 평범한 소녀일 뿐이고, 제 아버지는\n "+GetFullName(TempChar)+" - 이 땅에서 잘 알려진 상인이오.")+".";
    			Link.l2.go = "lier";
			}
            Link.l3 = "좋아, 원한다면 운을 시험해 봐라.";
			Link.l3.go = "battle";
		break;
        
        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = "오! 우리가 정말로 착각했을 수도 있겠군. 부디, 용서해 주시오, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "그럴 수도 있지, 신경 쓰지 마...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "나는 네가 거짓말한다고 생각해!";
                Link.l1 = "이봐, 날 그냥 두면 돈을 줄게.";
			    Link.l1.go = "Cost_Head";
			    Link.l2 = "좋아, 원한다면 운을 시험해 봐라.";
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
			dialog.text = "내 생각에는 "+PChar.HunterCost+" 페소면 우리한테 딱 맞아.";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "하지만 나에겐 그런 돈이 없어.";
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = "여기 네 돈이다, 받아서 꺼져.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "너희 같은 악당들에게 그런 돈을 주다니... 차라리 여기서 다들 배를 갈라버리겠다!";
                Link.l2.go = "battle";
            }
		break;

        case "NoMoney":
			dialog.text = "그렇다면, 우리의 대화는 끝이오!";
			Link.l1 = "넌 날 절대 산 채로 잡지 못할 거다.";
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = "잠깐만, "+GetSexPhrase("동료","아가씨")+"... 네가 뭔가 흥미로운 걸 가지고 있는 것 같은데. 친구라면 서로 발견한 보물을 나눠야 하지 않겠어?";
            Link.l1 = "이봐, 날 그냥 두면 돈을 줄게.";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("실례합니다만, 착각하신 것 같군요. 저는 "+GetFullName(TempChar)+" - 이 땅에서 유명한 시민이지만, 보물 사냥꾼은 아니지.","실례지만, 착각하신 것 같아요. 저는 그냥 평범한 소녀일 뿐이고, 보물 사냥꾼이 아니에요. 그리고 제 아버지는\n "+GetFullName(TempChar)+" - 이 일대에서 잘 알려진 시민")+"!";
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = "이제 네 놈들 목이 몸에서 떨어질 시간이 된 것 같군.";
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = "오! 그럼 정말 우리가 착각한 것일지도 모르겠군. 부디 용서해 주시오, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "그럴 수도 있지, 신경 쓰지 마...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "네가 거짓말하는 것 같아!";
			    Link.l1 = "그럼 내 검의 노래를 들어라.";
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		case "TreasureCaptain":
			dialog.text = LinkRandPhrase("내 보물 지도를 훔친 게 바로 너였군! 이제 네가 훔친 모든 걸 내놓을 때가 된 것 같군...","오, 경쟁자군! 내 보물의 무게에 짓눌려서는 멀리 가지 못할 거다...","허, 드디어 널 따라잡았군! 이 동굴 안의 모든 보물은 다 내 거야, 알겠어? 이제 주머니 다 털어놔, 이 친구야!");
			Link.l1 = LinkRandPhrase("이제 내 칼맛을 볼 시간이야, 이 친구!","네 보물이라고? 그건 네 거였지, 이제는 내 거니까!","내 칼로 네 배를 갈라버리는 게 더 낫겠군, 이 친구야.");
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
			dialog.text = LinkRandPhrase("그래, 대령 말이 맞았군. 보물은 이 동굴에 숨겨져 있었어... 주머니 털어놔, 선원!","결국 이 빌어먹을 정글이랑 가시덤불, 늪을 헤치고 너를 잡았군. 이제, 이 자식아, 가진 거 다 내놔라...","이봐, 선원! 저 해적의 보물은 우리 거니까 더러운 손 떼라!");
			Link.l1 = LinkRandPhrase("설마, 군 장교한테서 그런 행동을 볼 줄은 몰랐지! 하지만 좋아, 그래도 한 수 가르쳐주지...","저 사람 좀 봐, 장교 제복을 입은 해적이라니...","요즘은 군인이나 해적이나 별반 다르지 않지...");
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
			dialog.text = "그리고 드디어 우리의 금이 오는군. 적어도 기다린 보람은 있었네.";
			link.l1 = RandPhraseSimple("무슨 말씀을 하시는 겁니까, 신사 여러분? 저는 네덜란드 서인도 회사의 대표로, 이곳을 그냥 지나가던 중입니다! 해안 경치를 감상하려고 잠시 멈춘 것뿐입니다!","저를 다른 사람으로 착각하신 것 같군요. 저는 "+GetSexPhrase("프랑수아 마리 파가넬, ","마리아-테레사, ")+"나는 식물학자야. 여기서 이 지역 식물 표본을 모으고 있지. 내 유카 잎 컬렉션 한번 볼래? 아주 흥미로운 것들이 몇 개 있어!");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "뭐야, 너?! 내 앞길에서 비켜!";
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "이런, "+GetSexPhrase("친애하는 친구여","내 예쁜 아가씨")+". 그건 통하지 않아. 네가 그 지도의 소유자였다는 건 우리가 확실히 알고 있거든 "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN)+". 그리고 그는 얼마나 구두쇠였던지, 그의 궤짝들은 돈으로 가득 차서 터질 지경이었지. 그러니 우리도 빈손으로 떠나진 않을 거야.";
			link.l1 = "네 말이 맞아. 상자들은 정말 가득 차 있었지. 하지만 넌 그것들을 얻지 못할 거야. 그 동굴에 가봐도 돼, 구멍 뚫린 양동이 몇 개쯤은 아직 남아 있을 테니까.";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "네 말이 맞아. 보물은 가져가도 돼. 하지만 그게 피로 물든 것이라 행복을 가져다주진 않을 거라는 걸 명심해.";
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = ""+GetSexPhrase("헤헤, 선장님, 죽기엔 아직 너무 젊잖아요...","헤헤, 아가씨, 죽기엔 아직 너무 어리지 않나...")+"...";
			link.l1 = "사실, 나는 죽지 않을 거야!";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = "이제야 이게 이성적인 사람의 말이로군!";
			link.l1 = "저주받을 너와 그 모든 보물들...";
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
			dialog.text = "이봐,"+GetSexPhrase("동료","아가씨")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" 우리에게 줄 게 있다고 말했다고 하더군.";
			link.l1 = "무슨 뜻이야?";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dialog.text = "의 지도 "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN);
				link.l1 = "가져가서 안부 전해 줘 "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+"... 곧 만나게 될 거라고 그에게 전해 주시오...";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" 그가 내가 자기 대신 위험을 무릅쓰고 일해 줄 거라고 생각한다면, 그건 큰 오산이지.";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "네가 총독에게서 훔친 보석.";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "가져가서 안부 전해 줘 "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+"... 곧 만날 거라고 그에게 전해 줘...";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" 그가 내가 자기 대신 위험을 무릅쓰고 문제를 해결해 줄 거라고 생각한다면, 그건 큰 오산이지.";
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
			dialog.text = "이봐,"+GetSexPhrase("동료","아가씨")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" 당신에게 몇 가지 질문이 있습니다.";
			link.l1 = "그런데 왜 그가 직접 물어보지 않는 거지?";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dialog.text = "그의 지위에 맞지 않아. 너 때문에 우리 작전이 망했고, 우리는 잃었어 "+sti(pchar.questTemp.ReasonToFast.p10)+" 너 때문에 페소를 잃었어. 이제 빚을 갚아야 해.";
			link.l1 = "이걸 가져가서 안부 전해 줘 "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". 곧 만날 거라고 그에게 전해 주시오...";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" 그가 내가 자기 대신 위험을 감수해 줄 거라고 생각한다면 큰 오산이지.";
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
				dialog.text = "오, 그런 돈은 없구나! 그래, 선택은 이미 했지... ";
				link.l1 = "오래전에...";
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = "그래, 선택은 끝났군...";
			link.l1 = "오래전에...";
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
