// китаец Лонгвэй, подручный Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "선장. 내 이름은 롱웨이요. 롱웨이의 배는 당신의 지휘 아래 있소. 롱웨이 역시 당신의 명령을 따르겠소. 로덴부르크 나리의 명령이오.";
			link.l1 = "안녕하시오, 롱웨이. 샤를 드 모르라 하오, 내 도움이 필요하면 말씀하시게. 야코브 판 베르크를 제거하는 작전에 대해 단서가 있소?";
			link.l1.go = "Longway_friend";
			link.l2 = "만나서 반갑소, 롱웨이. 내 이름은 샤를 드 모르요. 지체할 시간 없소 – 로덴부르크 나리께서는 빠르고 질 좋은 일을 중히 여기시지. 지금 야코프 판 베르흐는 어디에 숨어 있소?";
			link.l2.go = "Longway_neutral";
			link.l3 = "좋소, 내 이름은 샤를 드 모르요! 우리 둘이 잘 협력하길 바라오! 자, 롱웨이 나리, 말씀해 주시오, 우리 일행은 야콥 판 베르흐를 어디서 찾아야 하오?";
			link.l3.go = "Longway_enemy";
			NextDiag.TempNode = "First time";
			pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;
		
//-----------------------------------------------за Голландию-----------------------------------------------
		case "Longway_neutral":
			dialog.text = "롱웨이는 우리가 잘 협력할 거라고 확신하오, 촌장. 야콥 판 베르흐는 현재 "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". 내가 그와 이 근처 선술집에서 만남을 주선했네. 그가 거기 있을 걸세.";
			link.l1 = "출항하자!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayNeutral = "true";//признак враждебности китайца
		break;
		
		case "Longway_enemy":
			dialog.text = "로덴부르흐 나리의 법에 따른 명령, 롱웨이에게... 야코프 판 베르흐는 현재 "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". 내가 그와 이 지역 선술집에서 만남을 약속해 두었네. 그가 거기 있을 것이오.";
			link.l1 = "출항하자!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayEnemy = "true";//признак враждебности китайца
			Notification_Approve(false, "Longway");
		break;
		
		case "Longway_friend":
			dialog.text = "롱웨이가 할 수 있는 건 다 할 거요, 촌장. 그리고 야콥 판 베르흐는 현재 "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+". 내가 그와 이 지역 선술집에서 만남을 주선했네. 그는 거기 있을 걸세.";
			link.l1 = "출항하자!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayFriend = "true";//признак враждебности китайца
			Notification_Approve(true, "Longway");
		break;
		
		case "Longway_JacobGo":
			//Лонгвэя - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 18;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
			AddQuestRecord("Holl_Gambit", "1-8");
			ForceHeroAutolevel(npchar);
			SetCharacterPerk(npchar, "Captain");
			AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat"));
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Holl.JacobCity, true);
			AddLandQuestMark(characterFromId(""+pchar.questTemp.HWIC.Holl.JacobCity+"_tavernkeeper"), "questmarkmain");
			pchar.questTemp.HWIC.Holl = "JacobOnMain";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 30, false);
			}
			else SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;
		
		case "hired":
			dialog.text = "롱웨이가 뭘 할 수 있지, 촌장?";
			link.l1 = "지금은 아무것도 없어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			if (pchar.questTemp.HWIC.Holl == "MirageFail")
			{
				dialog.text = "이 멍청한 몽골 놈, 선장! 우리 임무는 쉬웠다—'미라주'를 '메이펑'을 잃지 않고 포획하는 거였지. 그녀는 선장이 없어서 쉬운 표적이었는데, 너는 그 일조차 제대로 못 했어\n롱웨이는 더 이상 너를 섬기지도, 만나지도 않을 거다. 롱웨이는 로덴부르크 나리께서도 이 결정을 승인하실 거라 확신한다.";
				link.l1 = "네 놈이랑 네 주인 다 지옥에나 떨어져라!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-10");
			}
			if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "이 멍청한 몽골 놈, 촨장! 네 개인적인 일에 시간을 너무 허비해서 야코프 판 베르흐를 만나지 못했잖아. 그는 이미 떠났어\n "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"\n임무를 완수하지 못했소. 롱웨이는 더 이상 당신을 섬기거나 다시 보고 싶어 하지 않소. 롱웨이는 로덴부르크 나리도 자신의 결정을 지지할 것이라 확신하오.";
				link.l1 = "네 놈이랑 네 주인 다 지옥에나 떨어져라!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-9");
			}
			if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
			{
				dialog.text = "선장, 그동안 아무 성과도 없이 너무 많은 시간을 허비했소. 여긴 당신 배가 아니고, 롱웨이는 당신의 쿨리가 아니오. 롱웨이는 빌렘스타트로 돌아가겠소\n롱웨이는 더 이상 당신을 섬기지도, 만나지도 않을 것이오. 롱웨이는 로덴부르크 나리께서 이 결정을 분명히 승인하실 거라 믿소.";
				link.l1 = "네 놈이랑 네 주인 모두 지옥에나 떨어져라!";
				link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)//если сам на Мейфенг
			{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i=1; i < COMPANION_MAX; i++)
				{
					int iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Longway_hire":
			PlaySound("Voice\English\hambit\Longway-03.wav");
			dialog.text = "선장님, 롱웨이는 로덴부르크 나리 곁을 떠났소. 롱웨이는 다시는 그에게 돌아가지 않을 것이오. 당신은 롱웨이에게 친절했고, 용감한 선장이오. 롱웨이는 당신의 하인으로서, 선장님 선원으로 들어가고 싶소.";
			link.l1 = "하인이 아니라 장교로서지! 배에 탄 걸 환영한다, 친구!";
			link.l1.go = "Longway_hire_1";	
			link.l2 = "고맙지만 사양하겠네, 롱웨이. 자넨 이제 자유인이야. 내겐 자네의 도움이 필요 없네.";
			link.l2.go = "Longway_exit";	
		break;
		
		case "Longway_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
			AddQuestRecord("Holl_Gambit", "1-37");
		break;
		
		case "Longway_hire_1"://нанимаем китайца
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			npchar.CanTakeMushket = true;
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Longway_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 200, 200);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddQuestRecord("Holl_Gambit", "1-38");
			ForceHeroAutolevel(npchar);
			
			//Sinistra - квест Лонгвэя "Путеводная звезда"
			PChar.quest.PZ_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Start.win_condition.l1.location = "Curacao";
			PChar.quest.PZ_Start.win_condition = "PZ_Start";
		break;
		
//---------------------------------------------против всех-------------------------------------------------
		case "Longway_abordage":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			dialog.text = "왜 멈췄지? 날 죽여라. 롱웨이는 지쳤다, 롱웨이는 죽음을 원한다. 싱... 용서해 줘.";
			link.l1 = "그렇게 서두르지 마라, 중국놈. 내가 원하면 널 죽일 수도 있지만, 먼저 할 말이 있다. 네 운명은 앞으로 네가 어떻게 하느냐에 달려 있다. 일단은, 내 화물창에 온 걸 환영하지!";
			link.l1.go = "Longway_abordage_1";			
		break;
		
		case "Longway_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-45");
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "LongwayPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Longway_prisoner":
			DelLandQuestMark(npchar);
			dialog.text = "";
			link.l1 = "이제 귀에서 쇳소리가 울리지 않으니 제대로 얘기할 수 있겠군. 들어라, 롱웨이. 내가 정보를 필요로 하는데, 네가 내가 원하는 걸 알고 있다는 건 의심하지 않는다. 문제는 이거다: 순순히 말할 거냐, 아니면 힘들게 말하게 할 거냐?";
			link.l1.go = "Longway_prisoner_1";			
		break;
		
		case "Longway_prisoner_1":
			dialog.text = "";
			link.l1 = "입 다물겠다는 건가? 좋아. 거래를 제안하지. 네 목숨은 살려주고, 다음 육지에 내려주겠다. 대신, 루카스 로덴부르흐가 널 어디로, 왜 보냈는지 말해라. 거래할래?";
			link.l1.go = "Longway_prisoner_2";			
		break;
		
		case "Longway_prisoner_2":
			dialog.text = "";
			link.l1 = "자네가 영어, 네덜란드어, 프랑스어를 이해한다는 것, 그리고 귀가 얇다는 것도 알고 있지. 이제 말할 차례야. 결국엔 자네가 아는 모든 걸 말하게 될 거다. 중국인들이 고문 기술에 자부심이 있다는 것쯤은 알지만, 우리 서양인들도 그 오랜 학문에서 나름의 발전을 이루었지. 여기 알론소는 사람들의 혀를 풀어내는 데 일가견이 있네. 내 배에 들어오기 전 산티아고에서 성스러운 종교재판소의 심문관이었거든. 고백을 받아내는 예술을 완성한 신부님들에게서 온갖 비법을 배웠지... 굳이 자네가 신교도가 아니어도 말이야!";
			link.l1.go = "Longway_prisoner_3";			
		break;
		
		case "Longway_prisoner_3":
			dialog.text = "";
			link.l1 = "내 재치가 너한테는 아깝군. 다 말하게 될 거야, 내 째진 눈 친구야... 전부 다... 하지만 그 뒤엔 오래 못 살 거다, 그래, 못 살아. 네 몸은 알론소를 만나고 나서 크게 고통받게 될 거다. 선택은 네 몫이야. 진실을 다 말하고 살아남든지, 아니면 진실을 다 말하고 고문대에서 고통스럽게 죽든지. 고문대에서 고통에 몸부림치게 될 거다. 알겠어? 걱정 마라, 신부도 꼭 불러서 네 이교도 영혼이 지옥의 영원한 불길에서 벗어나도록 세례를 주게 할 테니.";
			link.l1.go = "Longway_prisoner_4";
		break;
		
		case "Longway_prisoner_4":
			dialog.text = "";
			link.l1 = "그 어두운 눈에 의심이 자라고 있군. 네 주인의 죄 때문에 네가 죽어야 할 이유가 뭐지? 그럴 만한 가치가 있는 자인가? 로덴부르크가 정말로 네가 고통 속에서 영혼까지 빼앗길 만큼 가치 있는 인물인가?";
			link.l1.go = "Longway_prisoner_5";			
		break;
		
		case "Longway_prisoner_5":
			dialog.text = "롱웨이가 말하겠다. 하지만 먼저, 롱웨이는 네가 약속을 지킬 것인지 확실히 하고 싶다, 촨장.";
			link.l1 = "하! 현명한 말이로군! 내 약속하마, 이 소년아.";
			link.l1.go = "Longway_prisoner_6";			
		break;
		
		case "Longway_prisoner_6":
			dialog.text = "미안하다, 선장, 네 말만으로는 부족해. 네가 정보를 얻고 나서 롱웨이를 죽일 수도 있잖아! 롱웨이는 확실한 보장을 원한다.";
			link.l1 = "흥정을 참 세게 하는군. 어떤 보장을 원하지?";
			link.l1.go = "Longway_prisoner_7";			
		break;
		
		case "Longway_prisoner_7":
			dialog.text = "과들루프 남쪽에 마리 갈랑트라는 작은 섬이 있다네. 접근 불가 곶이지. 거기서 롱웨이를 상륙시키고 무기를 건네주게. 그래야만 롱웨이가 루카스 로덴부르크에 대해 아는 모든 것을 말해줄 걸세.";
			link.l1 = "너는 지금 나와 흥정할 처지가 아니야, 중국놈.";
			link.l1.go = "Longway_prisoner_8";			
		break;
		
		case "Longway_prisoner_8":
			dialog.text = "네가 롱웨이였다면 똑같이 했을 거다, 촌장. 고문을 해도 네 부하들이 내 입에서 말을 빼내긴 쉽지 않을 거다. 롱웨이는 약한 백인놈이 아니니까.";
			link.l1 = "좋아. 거래지. 하지만 경고한다 - 날 속이려 들면 내가 직접 널 갈기갈기 찢어줄 거다. 천 가지 방법으로, 아주 천천히... 네 황제들이 하듯이 말이야. 알론소!";
			link.l1.go = "Longway_prisoner_9";
			// belamour legendary edition -->
			link.l2 = "네 말이 맞아. 하지만 명심해라 - 내가 여기까지 온 길이 얼마나 먼지. 내 일에 방해라도 하면, 벌레 밟듯 네 목숨을 끊어버릴 거다.";
			link.l2.go = "Longway_prisoner_9a";
		break;
		
		case "Longway_prisoner_9a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_9":
			ChangeCharacterComplexReputation(pchar, "nobility",-5);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_0":
			dialog.text = "마리 갈랑트에 도착했습니까, 선장님?";
			link.l1 = "진정해, 곧 도착할 거야.";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Longway_prisoner_0";
		break;
		
		case "Longway_prisoner_10":
			dialog.text = "약속을 지켰군, 선장. 롱웨이도 그럴 거다. 롱웨이의 임무에 대해 알고 싶은가?";
			link.l1 = "예. 하지만 당신이 내게 한 약속을 상기시켜 드리고 싶군요: 당신이 아는 *모든 것*을 내게 말해주겠다고 했지요.";
			link.l1.go = "Longway_prisoner_11";			
		break;
		
		case "Longway_prisoner_11":
			dialog.text = "롱웨이는 기억하고 있소. 로덴부르크에 대해 묻는 것은 뭐든 대답할 것이오, 촨장.";
			link.l1 = "말을 시작해.";
			link.l1.go = "Longway_prisoner_12";			
		break;
		
		case "Longway_prisoner_12":
			dialog.text = "'메이펑'은 빌렘스타트 항구에서 출항해 북쪽의 세인트 크리스토퍼 해안으로 향하고 있었다.\n오일 뒤에는 피터 스타이브센트가 지휘하는 갤리온이 올 예정이었다.\n롱웨이의 명령은 그 선장과 함께 그 배를 침몰시키라는 것이었다.";
			link.l1 = "하늘에 계신 하나님! 로덴부르크가 그대에게 스튀베상트를 죽이라고 명령했단 말이오? 그건 미친 짓이오!";
			link.l1.go = "Longway_prisoner_13";			
		break;
		
		case "Longway_prisoner_13":
			dialog.text = "롱웨이가 사실을 말하는 거요, 선장. 그건 로덴부르크 나리의 명령이었소. 롱웨이는 그걸 달가워하지 않았지만, 명령에는 토 달지 않소.";
			link.l1 = "참 중국인답군. 네 주인은 무슨 수작을 부리고 있는 거지?";
			link.l1.go = "Longway_prisoner_14";			
		break;
		
		case "Longway_prisoner_14":
			dialog.text = "이제 내 주인은 아니야, 췬장. 롱웨이는 더 이상 마인헤르 로덴부르크에게 돌아가지 않을 거다. 로덴부르크가 퀴라소에서 권력을 장악했지. 마티아스 벡은 쉬운 먹잇감이었고, 로덴부르크의 권위와 사령관과의 인맥만으로도 총독을 감옥에 보내기에 충분했어\n이제 남은 장애물은 서인도 회사의 이사, 마인헤르 스토이베산트뿐이야. 스토이베산트만 제거되면, 로덴부르크가 네덜란드 식민지의 모든 권력을 손에 넣게 되지.";
			link.l1 = "말해 보게, 롱웨이. 로덴부르크처럼 존경받고 권력 있는 자가 어찌하여 자기 회사와 공화국을 상대로 그토록 과격한 행동을 하게 되었는가? 그리고 햇볕을 너무 쬐어서라든가, 미친 발작 때문이라는 식의 말은 하지 말게.";
			link.l1.go = "Longway_prisoner_15";			
		break;
		
		case "Longway_prisoner_15":
			dialog.text = "롱웨이가 직접 듣고 싶어 했어, 촌장. 네가 바로 그 회사 패킷선을 나포해서 로덴부르크에게 편지를 가져다준 거 맞지? 그 이유가 바로 그 편지에 있었어.";
			link.l1 = "이제 알겠군... 존 머독의 기록 보관소에는 로덴부르크가 자기 나라를 상대로 반란을 일으킬 만큼 두려워할 만한 놀라운 것들이 많이 있는 모양이야.";
			link.l1.go = "Longway_prisoner_16";			
		break;
		
		case "Longway_prisoner_16":
			dialog.text = "더 궁금한 거 있소, 선장?";
			link.l1 = "그래. 로덴부르크가 또 무슨 짓을 했지?";
			link.l1.go = "Longway_prisoner_17";			
		break;
		
		case "Longway_prisoner_17":
			dialog.text = "로덴부르흐 나리가 너를 죽이라고 명령했어. 롱웨이는 스토이베상트를 쫓기 전에 카라카스에 있었고, 추안장 야곱과 만난 뒤 그에게 명령을 내렸지.";
			link.l1 = "Jacob van Berg 선장?";
			link.l1.go = "Longway_prisoner_18";			
		break;
		
		case "Longway_prisoner_18":
			dialog.text = "정보가 빠르군. 그래. 취안장 야콥 판 베르흐가 너를 쫓고 있어, 선장. 결국엔 널 찾아낼 거다. 판 베르흐에게 오래 숨어 있을 수 있는 자는 없어.";
			link.l1 = "피를 흘린다면, 내가 죽일 수 있지. 반 베르크와 그 자가 자랑하는 유령선은 내가 처리하겠다.";
			link.l1.go = "Longway_prisoner_19";			
		break;
		
		case "Longway_prisoner_19":
			dialog.text = "많이 아는군, 선장. 롱웨이는 더 할 말 없어. 더 물어볼 게 있으면 물어봐.";
			link.l1 = "스타이베산트가 세인트 크리스토퍼 해안 근처에 있을까?";
			link.l1.go = "Longway_prisoner_20";			
		break;
		
		case "Longway_prisoner_20":
			dialog.text = "네, 선장님. 약 일주일 후쯤 이 섬 해안 근처에서 그의 갈레온선을 찾을 수 있을 것입니다.";
			link.l1 = "좋아! 이 여우를 자기 덫에 걸리게 하자... 더 이상 물을 것도 없어. 알고 싶던 건 다 알았으니까.";
			link.l1.go = "Longway_prisoner_21";			
		break;
		
		case "Longway_prisoner_21":
			dialog.text = "마지막으로 한 가지 더 조언하지, 촌장. 갤리온에 가까이 다가가서 공격받지 않으려면 반드시 '메이펑'을 데려가야 해.";
			link.l1 = "알겠습니다. 정보 주셔서 감사합니다.";
			link.l1.go = "Longway_prisoner_22";			
		break;
		
		case "Longway_prisoner_22":
			dialog.text = "롱웨이가 이제 떠난다. 잘 있어라, 촨장.";
			link.l1 = "행운을 빌네, 내 동방 친구.";
			link.l1.go = "Longway_prisoner_23";			
		break;
		
		case "Longway_prisoner_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-49");
			pchar.questTemp.HWIC.Self = "MeetingStivesant";
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
			pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
			pchar.quest.RemoveLongwayTimer.over = "yes";//снять прерывание
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
			AddMapQuestMarkIsland("Nevis", true);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Longway_officer":
			dialog.text = "잘 듣고 있소, 선장.";
			// Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "명령이 무엇입니까, 선장님?";
				Link.l1 = ""+npchar.name+"야, 나는 유럽으로 떠나기로 했어 — 아버지를 찾아서. 여정은 쉽지 않을 거고, 언제 돌아올 수 있을지도 몰라. 이제는 헤어질 때가 된 것 같아. 네가 여기서 날 기다릴 것 같지도 않고 — 그건 위험하기도 하지.";
				Link.l1.go = "SharlieEpilog_Longway_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "롱웨이, 나는 고대 인디언 도시 타야살로 갈 생각이오. 분명히 말하겠소, 이번 여정은 정말 위험할 뿐만 아니라 신비로운 여행이 될 것이오. 우리는 텔레포트 우상을 통해 그곳에 갈 거요. 자네도... 함께하겠소?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "롱웨이, 배에 대한 전체 보고를 해 주게.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "우리가 항구에 도착할 때마다 특정 물품을 구입해 주었으면 하오.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "명령에 따라 도착했습니다, 선장님.";
				Link.l2 = "당신에게 몇 가지 명령을 내려야겠소.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Longway_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "내 명령을 들어라!";
            Link.l1.go = "stay_follow";
			link.l2 = "아무것도 아니다. 해산!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Longway_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "롱웨이는 한 번도 보급장(급사)이었던 적 없어, 촌장장. 롱웨이는 트리니다드에서 아바나까지 어떻게 항해하고 얼마나 걸리는지 말해줄 수 있지. 하지만 화물이나 판매, 거래는 절대 세지 않아.";
			Link.l1 = "그대 말이 맞소. 이렇게 훌륭한 항해사를 허투루 쓰는 건 아깝지.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "롱웨이는 귀외로(서양놈)와 거래하지 않는다, 촨장(선장). 롱웨이는 항상 키를 잡아왔지, 늙은 갈고리코가 마지막 에잇피스를 두고 흥정하는 가게에 있던 적은 없다네.";
			link.l1 = "흠, 네 말이 맞군. 상인들이 겁먹겠어.";
			link.l1.go = "exit";
		break;

		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "듣고 있소.";
			Link.l1 = "선상 습격에 대해 이야기해 보자.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "네 배에 대해 이야기해 보자.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "잠시 내 함대에서 떨어져 혼자서 운을 시험해 보았으면 하네.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "아직 아무것도 없어.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "무엇을 원하십니까?";
			Link.l1 = "적선에 올라타지 마라. 너 자신과 선원들부터 챙겨.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "적선에 적극적으로 승선해 주었으면 한다.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "무엇을 원하시오?";
			Link.l1 = "배에 올라탄 뒤에는 다른 배로 바꾸지 마라. 이 배는 너무 귀중하니까.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "적선에 올라타면, 배가 쓸 만하다 싶으면 네 것으로 삼을 수 있지.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "알겠어.";
			Link.l1 = "편히 있으시오.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "그렇게 하겠습니다.";
			Link.l1 = "편히 있으시오.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "알겠소.";
			Link.l1 = "그렇게 하겠습니다.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "그리하겠습니다.";
			Link.l1 = "편히 있으시오.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		case "stay_follow":
            dialog.Text = "명령이십니까, 선장님?";
            Link.l1 = "버텨라!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "나 따라와서 뒤처지지 마!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "화기의 탄환 종류를 변경하십시오.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "당신의 머스킷에 사용할 탄약 종류를 변경하십시오.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "전투에 사용할 주무기를 변경하십시오.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "특정 거리에서 적을 향해 포격해 주었으면 하네, 론웨이.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "탄약 종류 선택:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "탄약 종류를 선택하십시오:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "전투가 시작되면, 당신은 다음을 사용하게 됩니다:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "기세가 바뀌었다!";
            Link.l1 = "물러가라.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "성향이 바뀌었소!";
            Link.l1 = "해산!";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "그 거리가 얼마나 된다는 거요? 명심하시오, 대위 나리. 머스킷으로는 이십 미터만 넘어도 아무것도 맞출 수 없소.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "무슨 말씀이십니까, 선장 나리?";
				link.l1 = "미안해, 가끔 네가 농담을 잘 못 받아들이는 걸 잊어버려.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "나는 내 자리를 지키고, 너무 가까이 오는 적이 있으면 사격하겠소. 그게 원하는 거요?";
				link.l1 = "그래, 맞아, 롱웨이.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "너무 멀어요, 선장 나리. 군중을 맞출 수는 있겠지만, 단일 표적을 노린다면 가망이 없소.";
				link.l1 = "시도해볼 만할지도 모르겠군, 알겠어.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "알겠습니다, 선장 나리.";
			link.l1 = "훌륭하군.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "롱웨이는 오랫동안 너를 따라다녔다. 롱웨이는 언제나처럼 너를 따를 거다. 롱웨이는 자기 촨장(船長)을 절대 떠나지 않아.";
			link.l1 = "고맙소, 롱웨이! 내가 자네를 믿은 게 옳았군.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "언제 시작하지?";
			link.l1 = "조금 있다가. 우리도 준비해야 해.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "24");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// Эпилог
		case "SharlieEpilog_Longway_1":
			dialog.text = ""+npchar.name+" 생각하다 — 자신은 존경하는 선장의 친구. 나 어디든 따라갈 준비됐어, 유럽이라도.";
			link.l1 = "여기서 외국인인 너에게 어떻게 대하는지 기억하지? 유럽에선 그보다 더해. 물론 널 해치게 두진 않겠지만 — 시선과 조롱까지 막을 순 없어. 그러니까 명령은 못 해. 선택은 너의 몫이야: 함께 가거나, 혹은...";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = ""+npchar.name+" 그런 대우에 익숙하다. 창 신 죽은 후, 선장님은 롱웨이가 신경 쓰는 유일한 사람. 나 당신 따라가고, 당신 등 뒤 지킬 거야.";
			link.l1 = "그렇다면... 너의 충성심에 감사하고, 곁에 있어줘서 정말 기쁘다. 사실, 약간 부럽기도 해. 넌 중국도 보고, 카리브도 봤지 — 이제 유럽까지. 그런 긴 여정을 겪는 사람은 드물어... 반 마르덴이 지어준 이름, 예언 같았군.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = "...";
			link.l1 = "우리는 2주 후에 출항한다. 그 전에 선술집에서 제대로 떠나는 걸 축하하려고 해. 넌 초대받은 사람 중 하나야. 거절은 금지다.";
			link.l1.go = "SharlieEpilog_Longway_4";
		break;

		case "SharlieEpilog_Longway_4":
			dialog.text = ""+npchar.name+" 거절 안 해. 나 갈게요, 선장님.";
			link.l1 = "그 대답을 기대했지. 술판이 시작되면 알려줄게. 먼저 다른 일들부터 마무리해야 해.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Longway_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Longway = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (hrand(4))
	{
		case 0: sTemp = "Cumana" break;
		case 1: sTemp = "Caracas" break;
		case 2: sTemp = "Maracaibo" break;
		case 3: sTemp = "Cartahena" break;
		case 4: sTemp = "Portobello" break;
	}
	return sTemp;
}
