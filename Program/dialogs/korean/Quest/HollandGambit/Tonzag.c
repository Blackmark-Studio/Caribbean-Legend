// Эркюль Тонзаг, он же Плешивый Гастон
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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "오, 안녕, "+pchar.name+". 살아 있어서 다행이오.";
				link.l1 = "가스통! 너냐?";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "안녕하시오, "+pchar.name+". 이미 자네 거래에 대해 다 알고 있네 - 존이 전부 말해줬거든. 뭐라 해야 할지 모르겠군. 자네가 정말 대단하네!";
				link.l1 = "그런 칭찬을 듣게 되어 기쁘오, 에르큘!";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "안녕하십니까. 저에게 맡길 일이 있으십니까?";
			link.l1 = "아니. 내 실수야. 미안해. 잘 가. .";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "그 이름으로 나를 알았겠지. 하지만 내 진짜 이름은 에르퀼이야. 에르퀼 톤자가.";
			link.l1 = "성스러운 주님! 나도 그대를 다시 보게 되어 기쁘오... 전투의 열기 속에서 그대를 알아보지 못했소. 도와주러 딱 맞춰 도착했구려.";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "네가 떠나자마자, 플리트우드가 자기 집을 지키기 위해 경계를 강화했다는 소식을 들었네. 나는 그 뒤에 함정이 있을지도 모른다고 했지. 그래서 즉시 내 배 '트와일라잇'을 타고 앤티가로 출항했네—그리고 지금 보듯, 충분한 이유가 있었던 거야.";
			link.l1 = "그렇소. 집 안에 있던 경비병들은 가까스로 처리했지만, 거리에서 계속 싸우기엔 너무 지쳐 있었소...";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "이번 싸움 이후로 플리트우드는 네덜란드 첩자를 수배 명단에 올렸지. 그들이 널 네덜란드 첩자로 생각했거든. 그는 그들과 오랜 원한이 있어. 가장 나빴던 건, 집 안에 있던 병사 한 명이 살아남아서 네 얼굴을 기억했다는 거야. 하지만 이제는 아무 문제 없어. 네가 시작한 일을 내가 끝냈으니. 그 병사는 이제 더 이상 아무도 알아볼 수 없고, 누구도 그를 알아보지 못할 거야...";
			link.l1 = "그를 죽였나? 그렇군...";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "그래. 네가 존의 집에서 의식 없이 누워 있을 때, 내가 플리트우드를 다치게 했지만 그 자식이 살아남았어. 내가 그놈 눈에 후추를 뿌려서 앞을 못 보게 만들고, 칼을 뽑기도 전에 한 방 먹였지. 그런데 그 쓰레기가 제복 아래에 사슬 갑옷을 입고 있었어. 그 덕에 목숨을 건진 거지. 영악하더군. 지금은 집에서 경비를 늘리고 침대에 누워 있다. 살아남은 게 정말 유감이야.";
			link.l1 = "그럼, 앤티과에서 네 주 임무는 플리트우드를 제거하는 것이었나?";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "대체로 그렇소. 하지만 지금은 불가능해 보이오 - 저택은 항상 잠겨 있고, 하루 종일 엄선된 경비병 여섯 명이 교대로 지키고 있소. 그리고 그의 신임을 받는 자만이 만날 수 있소 - 늙은 포수 찰리, 일명 크니펠이라는 자요.";
			link.l1 = "그것만으로도 괜찮군...";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "잠깐만... 이 일에 끼어들 생각이오?";
			link.l1 = "왜 안 되겠어? 도움이 필요하지 않아? 네가 나를 구해줬으니, 나도 돕고 싶어. 그리고 아직 돈도 더 필요하거든.";
			link.l1.go = "SJ_talk_6";
			// belamour legendary edition -->
			link.l2 = "왜 안 되겠소? 당신들은 진지한 사람들이잖소. 그리고 진지한 사람들은 후하게 돈을 주지. 나는 그냥 일자리를 찾고 있을 뿐이오.";
			link.l2.go = "SJ_talk_6a";
		break;
		
		case "SJ_talk_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			dialog.text = "믿어라, 친구야, 그건 네가 해낼 수 없어. 너 참 괜찮은 녀석이고, 정말 재능도 있지. 네가 가져온 항해일지가 내게 플리트우드의 목숨을 노릴 계획을 세우는 데 큰 도움이 됐어. 경비병 처리도 잘했지. 하지만 이제는 네가 플리트우드에게 접근하는 건 절대 불가능해. 나조차도 그 방법은 전혀 모르겠거든.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "생각해 보겠소. 아직 시간은 있지. 내 배가 압수당하고 선원도 없으니 안타깝군.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "그 점에 대해서는 생각해 보겠소. 나는 시간도 있고 배도 있소.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_6":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "믿어라, 친구. 그건 네가 해낼 수 없는 일이야. 넌 훌륭한 녀석이고, 진짜 재능도 있지. 네가 가져온 항해일지가 내게 플리트우드의 목숨을 노릴 계획을 세우는 데 큰 도움이 됐어. 경비병 처리도 잘했지. 하지만 이제 네가 플리트우드에게 접근하는 건 절대 불가능해. 나조차도 그 방법을 전혀 모르겠거든.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "생각해 보겠소. 아직 시간은 있지. 내 배를 빼앗기고 선원도 없으니 아쉽군.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "그 점은 생각해 보겠소. 내겐 시간도 있고 배도 있소.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "그건 걱정하지 마시오. 자네 배가 나포됐을 때, 나는 자네의 모든 장교들과 일부 선원들을 내 '트와일라잇'호에 태웠지. 그들은 자네가 살아 있다는 걸 알고 있고, 계속 복무하기로 동의했네. 그리고 일지에 대한 보상으로, 내 배 '트와일라잇'호를 자네에게 넘기겠네.";
			link.l1 = "고마워! 꼭 기억할게!";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "네, 일지 값을 지불하고 싶소. 15,000페소밖에 지금은 없으니 양해해 주시오. 하루 안에 나머지는 정산하겠소. ";
			link.l1 = "필요 없어. 이걸로 충분해. 네가 제때 오지 않았으면, 돈 따위는 애초에 필요 없었을 거야.";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "좋아, "+pchar.name+", 나 가봐야 해. 아직 브리지타운으로 돌아가지 않을 거야. 혹시 내 도움이 필요하면 존에게 물어봐. 행운을 빌어!";
			link.l1 = "행운을 빌어, 에르큘!";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			DialogExit();
			AddDialogExitQuestFunction("HollandGambit_NewShipTwilight");
		break;
		
		case "SJ_talk_11":
			dialog.text = "플리트우드를 제거해 준 대가로 이 갑옷을 드리고 싶소. 앞으로의 전투에서 당신을 지켜줄 것이오.\n이제 존에게 가봅시다. 그가 당신과 이야기하고... 흥미로운 제안을 하려 하오.";
			link.l1 = "선물 고맙소. 좋아, 가세...";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//дать вещь
			sld = characterFromId("Merdok");
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "나도 당신과 이야기하고 싶소, 선장. 원래는 내가 내 기술을 가르쳐주려 했는데, 이제 보니 내가 오히려 당신에게 배워야 할 것 같군. 내게 당신 배의 장교 자리를 주시오. 절대 후회하지 않을 것이오.";
			link.l1 = "기꺼이 그러지, 에르퀼! 우리 선원으로 온 걸 환영한다!";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "에르퀼, 내가 그대의 상관이 된다는 건 상상할 수 없소. 제안은 고맙지만, 그대를 내 부하로 여길 수는 없겠소.";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1":
			ForceHeroAutolevel(npchar);//Тонзага - в офицеры
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			LAi_SetImmortal(npchar, false);
		
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "원하시는 대로, "+pchar.name+". 또 보지. 아마 다시 만날 수도 있겠군. 함께 일해서 즐거웠어.";
			link.l1 = "행운을 빌어, 친구!";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "tonzag_officer":
			dialog.text = "듣고 있소, 선장. 무슨 할 말이 있소?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "선장님, 표정이 어두운데. 무슨 일이라도 있었습니까?";
				Link.l1 = "난 군도를 떠나야 해. 2주 후에. 남의 배에, 승객으로서.";
				Link.l1.go = "SharlieEpilog_Tonzag_1";
				break;
			}

			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "에르퀼, 나는 지금 고대 인디언 도시 타야살로 갈 생각이오. 더 기이하게도, 내 길은 순간이동 동상을 통해 이어지지. 함께할 생각이오?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "에르퀼, 배에 대한 전체 보고를 해 주게.";
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
				NextDiag.TempNode = "tonzag_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "내 명령을 들어라!";
            Link.l1.go = "stay_follow";
			link.l2 = "지금은 아무 일도 없다. 편히 쉬어!";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "선장님, 죄송하지만 저는 숫자나 계산에는 관여하지 않습니다. 그런 일은 반 메르덴에게 물어보십시오. 그는 그런 데 소질이 있지만, 자기 둥지를 떠날 생각이 있을지는 의문이군요.";
			Link.l1 = "네 말이 맞아, 에르퀼. 에휴, 나도 급히 회계 담당을 찾아야겠군...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "선장님, 제가 바베이도스에서 여관을 할 때는 럼주랑 식량만 샀습니다. 그리고 식량이라 하면, 그냥 건빵이나 콘비프 말고 제대로 된 음식을 말하는 겁니다. 미안하지만, 그건 제 담당이 아닙니다.";
			link.l1 = "내 배를 선술집으로 바꿔야 하나... 농담이야, 에르퀼. 됐다, 내가 직접 할게.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "듣고 있소.";
			Link.l1 = "이건 승선에 관한 일이야.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "이건 당신 배에 관한 일이오.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "아직 아무 소식도 없어.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "그래서 무엇을 원하시오?";
			Link.l1 = "적선에 올라타지 마라. 너와 선원들부터 챙기라고.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "적선에 올라타 주었으면 하오.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "그러면 무엇을 원하시오?";
			Link.l1 = "배에 탄 후에는 다른 배로 바꾸지 않았으면 하오. 너무 귀중하니까.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "적선에 올라타면, 그 배가 쓸 만하다면 네 것으로 삼을 수 있지.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "예, 알겠습니다.";
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
			dialog.Text = "아이 아이.";
			Link.l1 = "그렇게 하겠습니다.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "그렇게 하겠습니다.";
			Link.l1 = "편히 있으시오.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		
		case "stay_follow":
            dialog.Text = "무슨 명령이십니까?";
            Link.l1 = "여기 있어!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "나를 따라와, 뒤처지지 말고!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "탄약 종류를 변경하십시오.";
					Link.l3.go = "SetGunBullets";
				}	
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
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "아이!";
            Link.l1 = "편히 있으시오.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "아이!";
            Link.l1 = "편히 있으시오.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "운이 지지리도 좋은 놈이구만, 선장. 너랑 나, 그리고 존이 같이 일하던 때 네 편에 붙은 게 다행이야. 이번 일에서 널 안 도우면 상어 밥이 되어도 좋아!";
			link.l1 = "고마워, 에르큘! 내가 너를 믿은 게 옳았다는 게 기쁘군.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "그래서, 언제 출발하는 거지?";
			link.l1 = "조금 있다가. 이제 여행 준비를 해야겠군.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "거의 아무것도 아니야, 선장. 이게 우리 일이랑 관련 있었다면 벌써 고문대에 올려졌겠지.\n바로 심문하러 데려가지 않은 걸 보면, 급한 일은 아닌가 봐.\n함정이거나 갈취겠지.\n아무 설명도 없이 며칠 여기서 묵히다가, 결국 우리가 받아들일 수밖에 없는 제안을 들고 올 거야.";
			link.l1 = "직접 겪어본 일인가?";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "그래, 지금 당장 그런 제안을 하게 만들 방법이 있나?";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "물론이지. 그루오는 한때 죽은 남자의 친척들에게서 트리니다드의 사형집행인의 마지막 손길을 피하게 해달라는 돈을 받은 적이 있지.\n그녀는 유치장 복도를 걸을 권리를 얻으려고 지휘관에게 돈을 건넸어. 흔한 일이야. 많은 이들이 아무런 저항도 못 하는 자들을 괴롭히려고 병사들에게 돈을 쥐여주지, 아무도 보는 이 없이.\n그 남자는 조용히, 고통 없이 죽었어. 깔끔하고 점잖은 일이었지.";
			link.l1 = "그루오? 그게 누구야?";
			link.l1.go = "tonzag_jailed_1_1";
		break;
		
		case "tonzag_jailed_1_1":
			dialog.text = "미안해, 선장. 때와 장소를 잘못 잡았어.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "해볼 수는 있지. 먹이 주는 시간까지 기다렸다가, 내가 보초랑 몇 마디 나눠보겠어. 저놈들 아직 제대로 수색하는 법을 모르는 것 같거든. 에휴...";
			link.l1 = "무슨 일이야?";
			link.l1.go = "tonzag_jailed_2_1";
		break;
		
		case "tonzag_jailed_2_1":
			dialog.text = "이상한 기분이야, 선장. 예감이라고도 할 수 있겠어. 미안한데, 나중에 이야기하자.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_killed_hunters":
			dialog.text = "내가 뭔가 놓쳤나, 선장?";
			link.l1 = "오, 별일 없지, 그냥 또 하루 바다 위일 뿐이야. 이봐, 이 늙은 악당아! 여기서 나한테 꽤 큰 소동을 벌였구나.";
			link.l1.go = "tonzag_killed_hunters_1";
		break;
		
		case "tonzag_killed_hunters_1":
			dialog.text = "피는 찬물로 씻으면 지워집니다, 선장. 우리 얘기 좀 해야겠소.";
			link.l1 = "그런가? 우선 오늘 하루라도 살아남는 게 나쁘진 않겠지.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_Victory");
		break;
		
		case "tonzag_after_victory_helena":
			dialog.text = "나도 반갑네, 룸바. 선장님, 지금은 방해하지 않겠소, 나중에 이야기합시다.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;
		
		case "tonzag_after_victory_mary":
			dialog.text = "이봐, 진저. 선장님, 방해하지 않겠소, 나중에 이야기합시다.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;
		
		case "tonzag_after_victory_alonso":
			dialog.text = "선장님, 방해하지 않겠습니다, 나중에 이야기합시다.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_drink":
			dialog.text = "내 말 들을 준비됐나, 선장?";
			link.l1 = "이제야 우리 대화를 나눌 때가 되었군, 에르퀼. 방금 깨달았는데, 내가 자네에 대해 아는 게 거의 없더군.";
			link.l1.go = "tonzag_drink_1";
		break;
		
		case "tonzag_drink_1":
			dialog.text = "이제 서로 인사를 나눌 때가 되었군. 어린 시절 이야기는 건너뛰자고, 어차피 별로 할 말도 없으니 말이야 – 승리한 병사, 패배한 병사, 탈영병, 약탈자... 어떻게 돌아가는지 알겠지.";
			link.l1 = "사실 그렇진 않지만, 지금까지는 꽤 평범하게 들리는군.";
			link.l1.go = "tonzag_drink_2";
		break;
		
		case "tonzag_drink_2":
			dialog.text = "그런 군 경력을 쌓고 나면 내게 남은 진로는 도적, 교수형 죄수, 아니면 네덜란드 서인도 회사에서 일할 만한 경비밖에 없었지. 나는 마지막 길을 택했네, 알겠지?";
			link.l1 = "거기서도 도망쳤나?";
			link.l1.go = "tonzag_drink_3";
		break;
		
		case "tonzag_drink_3":
			dialog.text = "반대로, 나는 그곳에서 출세했지. 회사 정보부의 전투 부서에 합류하라는 제안을 받았고, 거기서 미래의 아내를 만났어.";
			link.l1 = "좋아, 지금까지는 이야기가 꽤 평화롭군... 네덜란드인들의 수법에 대해 너무 깊이 생각하지 않는다면 말이지.";
			link.l1.go = "tonzag_drink_4";
		break;
		
		case "tonzag_drink_4":
			dialog.text = "정직하게 해서는 큰돈을 벌 수 없어, 그리고 경쟁자들은 여러 방법으로 처리할 수 있지. 그래, 우리는 특별한 수단을 썼다네...";
			link.l1 = "무슨 말인지 알 것 같군...";
			link.l1.go = "tonzag_drink_5";
		break;
		
		case "tonzag_drink_5":
			dialog.text = "그래, 뭐든 될 수 있었지: 해적질에서부터 상품으로 가득 찬 창고에 불을 지르는 일까지. 결국 그 계략이 들통나서 우리는 해산당했네... 물론 서류상으로만 말이야. 그렇게 해서 리그가 탄생했지. 회사 상층부에서 선택받은 지도자들만이 알고 통제하는 조직이었어. 제대로 된 카리브 해의 무법자라면 선택지는 두 가지뿐이었지: 해적질 아니면 리그. 그리고 리그가 대개 더 많은 돈을 줬어\n대부분의 경우 리그는 여전히 네덜란드인을 위해 일했지만, 가끔은 다른 일거리도 맡을 수 있었지...";
			link.l1 = "슬슬 상황이 명확해지고 있군...";
			link.l1.go = "tonzag_drink_6";
		break;
		
		case "tonzag_drink_6":
			dialog.text = "토르투가에서 벌어진 그 소동도 리그 짓이었지. 그리고 그 상륙조도...";
			link.l1 = "그럴 줄 알았지. 그런데 왜지?";
			link.l1.go = "tonzag_drink_7";
		break;
		
		case "tonzag_drink_7":
			dialog.text = "리그에서 살아 나가는 놈은 없으니까, 그리고 우리가 거기서 저지른 짓들을 그냥 넘어갈 수는 없지, 선장. 난 은퇴하고 싶어서 시도해 봤어. 보다시피, 별로 성공적이진 않았지만.";
			link.l1 = "네 옛 동료들이 엄청난 돈을 쏟아붓고, 거의 백 명이나 희생시키고, 방화선을 태워버리고, 전함까지 위험에 빠뜨리면서까지... 단지 네 탈영죄로 널 죽이려고 했다는 말이오?";
			link.l1.go = "tonzag_drink_8";
		break;
		
		case "tonzag_drink_8":
			dialog.text = "나는 연맹에서 그냥 하찮은 놈이 아니었소, 선장. 그 조직에 대해 너무 많은 걸 알고 있지. 놈들이 날 그냥 놔둘 수 없고, 또 아무나 쉽게 빠져나갈 수 없다는 걸 보여줘야 하오... 예전에도 날 노린 적이 있었소... 아주 오래전에... 그때 내 아내를 죽이고, 내 얼굴까지 망가뜨렸지. 놈들도 큰 대가를 치렀지만 말이오. 이 이야기에 해피엔딩은 없소, 선장. 명령만 내리시오. 내가 배에서 내려 마지막으로 놈들과 맞서겠소.";
			link.l1 = "헛소리하지 마, 에르퀼... 그리고 루카스 로덴부르크는 이 모든 일에서 무슨 역할을 했지? 분명히 이 일에 관여했을 거야! 네, 아니, 그의 '조직', 리그 말이야...";
			link.l1.go = "tonzag_drink_9";
		break;
		
		case "tonzag_drink_9":
			dialog.text = "기관이 달랐지요, 선장님. 물론, 그들은 종종 같은 인물의 명령을 따르고 긴밀히 협력하곤 했습니다. 하지만 로덴부르크의 특수 요원들은 정확하고 효과적인 타격을 가했고, 리그는 대규모 작전을 수행했지요. 그런데 지금, 리그는 어떻게 되었습니까? 보다시피 조직은 더 이상 존재하지 않습니다. 나는 여기 당신과 있고, 존 머독은 떠났으며, 롱웨이는 도망쳤고, 판 베르크는 바다 밑에 있고, 로덴부르크는 처형당했지요... 그래도 나는 그 죽은 악당에게 빚이 있었소. 그가 리그에서 나를 눈여겨봤고, 내가 떠나려 했을 때 심각한 곤경에서 나를 끌어내어 자신의 부관으로 삼았지요. 물론 다른 이들은 그걸 달가워하지 않았지만, 아무도 감히 그에게 거역하지 못했소... 그리고, 알려진 사정에 따라 그는 머독과 나를 제거하기로 했지만, 당신이 끼어들어 나를 데려가 부하로 삼았지요\n그래서 나는 생각했소. '이제 과거와 결별할 두 번째 기회가 왔구나...' 당신이 로덴부르크를 이겼고, 리그는 후원자를 잃었고, 더 이상 위험도 없었지요... 하지만, 물론 내가 틀렸소... 늙은 바보 같으니... 하지만 그 이야기는 이쯤 하죠, 선장님. 이제 다음에 뭘 해야 할지 생각해봅시다. 물론, 당신이 정말로 첫 항구에서 나를 풀어줄 생각이 아니라면 말이오.";
			link.l1 = "아니. 자네에게 무슨 계획이라도 있나?";
			link.l1.go = "tonzag_drink_10";
		break;
		
		case "tonzag_drink_10":
			dialog.text = "사실 별거 아니야. 놈들을 전부 쓸어버릴 순 없겠지만, 우리가 놈들에게 큰 피해를 입히면 더 이상 나... 아니, 우리를 쫓는 게 그들에게 이득이 되지 않을 거야.";
			link.l1 = "그걸 어떻게 하지? 저놈들 캠프라도 있나?";
			link.l1.go = "tonzag_drink_11";
		break;
		
		case "tonzag_drink_11":
			dialog.text = "큰 요새라고? 전혀 아니지. 그건 연맹에게 너무 눈에 띄고 위험할 테니까. 그리고 내가 말한 손실은 인명 손실이 아니야—그 자들은 사람 따윈 신경 안 쓰지만, 금을 잃는 건 달가워하지 않지. 이제 회사에서 오는 돈도 더 이상 받지 못하고 있잖아? 연맹이 새로운 후원자를 찾았을 것 같지도 않고, 결국 어디선가 금을 쥐어짜고 있을 거야.";
			link.l1 = "그게 어디란 말이오?";
			link.l1.go = "tonzag_drink_12";
		break;
		
		case "tonzag_drink_12":
			dialog.text = "모르겠습니다, 선장님.";
			link.l1 = "에르퀼, 그런데 방금 전에 네가 너무 많은 걸 알아서 쫓기고 있다고 말하지 않았나!";
			link.l1.go = "tonzag_drink_13";
		break;
		
		case "tonzag_drink_13":
			dialog.text = "잠깐 생각해 보자... 아마 지금쯤 리그가 스페인 놈들을 상대로 움직이고 있을 거야. 제대로 한탕하기엔 걔네가 제일 좋은 먹잇감이지. 그런데 말인데, 로덴부르크는 늘 카스티야 졸부들이랑 사이가 좋았거든. 가끔 리그 녀석들을 그쪽 일에 투입시키기도 했고, 절대 해코지하지 말라고 늘 못 박았지. 그게 말이야, 리그 녀석들은 그 점을 아주 못마땅해했어...\n";
			link.l1 = "좋은 조건이라고? 그런데 네가 나더러 네 선술집까지 끌고 오게 만든 그 이달고 놈과 그의 손가락은 어쩔 건데?";
			link.l1.go = "tonzag_drink_14";
		break;
		
		case "tonzag_drink_14":
			dialog.text = "그건 특별한 경우였지, 곁다리 주문이었어. 죄책감이 든다면, 선장, 안심해도 돼 – 그 돈은 당연한 대가를 치렀으니까...\n하지만 내가 말하는 건 그게 아니야: 그들의 고용주가 사라진 뒤에, 리그 요원들은 그냥 욕망에 따라 움직여서 스페인 파이에서 한 몫 챙기려고 했을 수도 있지. 로덴부르크 밑에서 스페인 놈들과 일해 본 덕분에, 어디서 뭘 빼앗아야 할지 다 알고 있거든.";
			link.l1 = "흠... 네 말이 맞을지도 모르지. 하지만 내가 알기로는, 진짜로 스페인 은행을 털거나 바다에서 스페인 놈들을 상대로 작전하는 건 순전히 운에 달린 일이야... 차라리 스페인 사업체를 찾아보는 게 어떻겠어? 공장 같은 거?";
			link.l1.go = "tonzag_drink_15";
		break;
		
		case "tonzag_drink_15":
			dialog.text = "합리적인 추측이오, 선장. 다른 단서는 없소?";
			link.l1 = "흠... 오늘 우리를 공격한 배는 남쪽으로 갔지...";
			link.l1.go = "tonzag_drink_16";
		break;
		
		case "tonzag_drink_16":
			dialog.text = "그들의 선장이 다시 우리를 귀찮게 하진 않을 것 같소. 하지만 그는 다른 이들에게 일이 계획대로 되지 않았음을 경고해야 하고, 어쩌면 선원들을 다른 곳으로 옮길지도 모르지. 더 할 말 있소?";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain")) {
				link.l1 = "그래, 토르투가 감옥 사령관과 다정하게 얘기 좀 나눴지... 그가 본토에 대해 뭔가 언급하더군.";
				link.l1.go = "tonzag_drink_know";
			} else {
				link.l1 = "아니, 더는 없어.";
				link.l1.go = "tonzag_drink_notknow";
			}
		break;
		
		case "tonzag_drink_know":
			dialog.text = "훌륭합니다, 선장님! 남쪽, 본토, 스페인 놈들… 그럼 곧 찾을 수 있겠군요. 출항합니까? 그리고 제 이야기를 들어주셔서 감사합니다.";
			link.l1 = "그래, 너와 내가 결국 이렇게 속 깊은 얘기를 하게 될 줄이야... 출항하자!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_drink_notknow":
			dialog.text = "별로 단서가 없군. 하지만 우리 같은 놈들에겐 그 정도면 충분하지. 남쪽으로 가볼까? 스페인 무역회사를 찾아보자고? 내 이야기를 들어줘서 고맙다.";
			link.l1 = "그래, 너랑 나랑 결국 속 깊은 얘기를 하게 됐군... 자, 출항하자!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_dead":
			dialog.text = "봐요, 선장님. 저게 저놈들이 움직이는 방식입니다.";
			link.l1 = "너도 그렇게 일했어?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "가자, 안에 뭐가 있는지 보자.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;
		
		case "tonzag_afterminefight":
			dialog.text = "더러운 일이었소, 선장. 이 소굴은 쓸어냈지만, 분명 마지막은 아닐 것이오...";
			link.l1 = "광산은 어쩔 거야, 에르퀼?! 밖에 있던 사람들은?! 그들도 '처리'된 거야?! 그리고 그 악당이 한 말은 무슨 뜻이었지?";
			link.l1.go = "tonzag_afterminefight_1";
		break;
		
		case "tonzag_afterminefight_1":
			dialog.text = "이 이야기는 나중에 합시다, 선장님. 저들의 지휘관이 살아남았으니, 우리가 심문해야 합니다.";
			link.l1 = "그가 아무것도 모른다면 어쩌지?";
			link.l1.go = "tonzag_afterminefight_2";
		break;
		
		case "tonzag_afterminefight_2":
			dialog.text = "저 자식 뭔가 알고 있어. 생각해 봐, 우리를 기다리고 있었고, 금도 다 옮겼으며, 목격자도 없앴지. 즉, 계획이 있었다는 거야. 나는 여기 좀 둘러볼 생각이니, 나중에 저 악당을 내가 직접 배로 데려가겠다. 너도 주위를 잘 살펴봐. 혹시 서두르다가 뭔가 놓쳤을 수도 있으니까.";
			link.l1 = "좋아, 하지만 배로 돌아가면 진지하게 얘기 좀 해야겠어!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
			DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
			AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;
		
		case "tonzag_in_hold":
			dialog.text = "좋은 소식입니다, 선장님.";
			link.l1 = "우리 상황에 좋은 점은 하나도 안 보여, 에르퀼. 가자, 따로 얘기 좀 해야겠어.";
			link.l1.go = "tonzag_in_hold_1";
		break;
		
		case "tonzag_in_hold_1":
			dialog.text = "그래, 그런 거였군? 예, 선장님.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;
		
		case "tonzag_drink_again":
			dialog.text = "진지한 대화를 나눠야 할 것 같군, 선장.";
			link.l1 = "그래, 그리고 내가 직접 말할 거야. 우선, 여기 뭔가 흐름이 보이지 않아? 우리가 가는 곳마다 시체 더미가 따라다니고 있어! 처음엔 네가 산탄에 배를 맞았고, 그 다음 날엔 백 명이 넘는 사람들이, 좋은 놈이든 나쁜 놈이든, 죽었지... 이건 해전이라고 부르기도 민망해! 며칠 전엔 정착지가 통째로 쓸려나갔고, 오늘은 우리가 광산에서 사람들을 도륙내서 그 시체 더미에 한몫 거들었잖아.";
			link.l1.go = "tonzag_drink_again_1_1";
		break;
		
		case "tonzag_drink_again_1_1":
			dialog.text = "";
			link.l1 = "물론 내일 이 더미가 산처럼 불어날까 봐 걱정이 되긴 하지만, 정말 두려운 건 이 모든 피가 한 사람 때문에 흘러지고 있다는 사실이야. 그리고 그 사람이 내 선원 중에서 중요한 자리를 차지하고 있다는 거지!";
			link.l1.go = "tonzag_drink_again_1";
		break;
		
		case "tonzag_drink_again_1":
			dialog.text = "";
			link.l1 = "둘째로, 너 내게 거짓말을 했군, 에르퀼. 네 옛 동료들이 너를 없애려고 저렇게까지 애쓰는 걸 보면, 단순 탈영병 때문은 아니겠지. 우리가 광산에서 잡은 포로가 뭐라고 외쳤지? 배신자? 포르토 벨로? 그루오크? 네가 뭔가를 저질렀구나, 에르퀼. 이번엔 진실을 듣고 싶다.";
			link.l1.go = "tonzag_drink_again_2";
		break;
		
		case "tonzag_drink_again_2":
			dialog.text = "진실이요? 진실을 말하자면, 선장님, 나는 아내 그루오와 함께 정말로 탈영했소. 통작 부인은 리그를 떠나기 싫어했지. 그 삶을 사랑했으니까. 하지만 나를 더 사랑했소. 우리는 원래 스페인 이달고를 처리해야 했는데, 그자가 더 좋은 제안을 했소. 그게 우리의 기회였고, 둘 다 그의 밑으로 들어가기로 합의했지. 물론 리그 쪽에서는 우리가 임무 중에 죽은 줄 알고, 복수를 위해 두 번째 조를 포르토 벨로로 보냈소.";
			link.l1 = "그리고 네가 그놈들을 전부 죽였다는 거냐?";
			link.l1.go = "tonzag_drink_again_3";
		break;
		
		case "tonzag_drink_again_3":
			dialog.text = "처음에는 그루오를 죽이고 나를 흉하게 만들었지. 이젠 이달고가 나를 거들떠보지도 않고 내쫓았어. 그때 로덴부르크가 나를 찾아냈지...";
			link.l1 = "이제 와서 내가 어떻게 너를 믿으란 말이냐? 너는 군대도 버렸고, 동맹도 버렸으며, 네 동료들까지 죽였지! 때가 오면 나도 배신할 셈이냐?";
			link.l1.go = "tonzag_drink_again_4";
		break;
		
		case "tonzag_drink_again_4":
			dialog.text = "그래, 나 탈영했고, 계약도 깼고, 리그 놈들 몇십 명도 죽였지. 하지만 그 덕에 교훈은 제대로 배웠소, 선장. 게다가, 죽은 자는 누구도 배신할 수 없지. 난 포르토 벨로에서 이미 오래전에 죽은 몸이오. 어쩌면 그래서 지금 나를 죽이기가 그렇게 힘든 걸지도 모르지.";
			link.l1 = "오늘은 이만하지. 아직도 뭔가 숨기고 있는 것 같은데.";
			link.l1.go = "tonzag_drink_again_5";
		break;
		
		case "tonzag_drink_again_5":
			dialog.text = "죄수는 내가 직접 처리하겠소, 아니면 같이 하겠소?";
			link.l1 = "가자. 내가 직접 심문하겠다.";
			link.l1.go = "tonzag_drink_again_hold";
			link.l2 = "아니, 그런 일은 내 소관이 아니야. 반 시간 뒤에 내 선실에서 보자!";
			link.l2.go = "tonzag_drink_again_cabin";
		break;
		
		case "tonzag_drink_again_hold":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;
		
		case "tonzag_drink_again_cabin":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;
		
		case "tonzag_hold":
			dialog.text = "지금 누가 책임자지? 아르노?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;
		
		case "tonzag_hold_1":
			dialog.text = "그 쓰레기가 권력을 잡았다고? 너희가 평범한 도적 떼로 전락하는 데 오래 걸리지도 않았군...";
			link.l1 = "오스틴이 누구야?";
			link.l1.go = "tonzag_hold_2";
		break;
		
		case "tonzag_hold_2":
			dialog.text = "오스틴 패거리는 자유 선장들을 숲으로 유인해 토막 내고, 시신에서 돈이나 장신구까지 모조리 털어가는 짓으로 악명이 높았지. 장사도 잘됐고, 모험을 찾는 놈들도 넘쳐났으니 아무도 신경 쓰지 않았어. 그런데 어느 선장 하나에게 제대로 걸려들고 말았지. 그래서 그자는 어쩔 수 없이 패거리와 함께 회사의 보호 아래 들어가야 했어. 우리는 그를 통제하며, 일이 빠르고 간단하게 처리되어야 할 때만 풀어줬지.";
			link.l1 = "저런 사람과는 협상을 할 수 있을지 의심스럽군.";
			link.l1.go = "tonzag_hold_3";
		break;
		
		case "tonzag_hold_3":
			dialog.text = "그건 확실하지. 이제 그 자와 그놈들이 판을 치면, 곧 리그도 그냥 또 다른 깡패 집단이 되어버릴 거야.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;
		
		case "tonzag_after_hold":
			dialog.text = "흥미로운 대화였군.";
			link.l1 = "얼마나 사실인지 알고 싶군... 포르토 벨로에서의 학살은 어찌 된 일이지? 그가 거짓말을 하지 않았다면, 지난번 당신과 내가 대화했을 때도 당신의 화려한 이력에서 또 몇 가지 중요한 사실을 빼먹은 셈이로군.";
			link.l1.go = "tonzag_after_hold_1";
		break;
		
		case "tonzag_after_hold_1":
			dialog.text = "포르토 벨로는 무척 더웠소, 선장. 나는 내 목숨을 위해, 내 고용주의 목숨을 위해, 내 아내의 목숨을 위해 싸웠소. 죽은 자를 세거나, 때마침 거리에 나와 있다가 죽은 농민 하나하나를 애도할 틈조차 없었소.";
			link.l1 = "그 순서로 우선순위를 두라는 건가?";
			link.l1.go = "tonzag_after_hold_2";
		break;
		
		case "tonzag_after_hold_2":
			dialog.text = "아니, 당연히 아니지. 그녀가 먼저야. 항상 그래.";
			link.l1 = "어떻게 생각해? 카라카스로 갈까?";
			link.l1.go = "tonzag_after_hold_3";
		break;
		
		case "tonzag_after_hold_3":
			dialog.text = "저라면 그렇게 하지 않겠소, 선장. 그리고 선장께도 권하지 않겠소. 이제 연맹에게 선장은 더 이상 적이 아니고, 나는 적어도 선장 밑에 있는 동안은 그들에게 아무런 관심거리도 아니오. 게다가 마음 한구석에 불길한 예감이 드는군\n거기로 가면 안 좋은 일이 생길 거요. 아주 안 좋을 거요. 이 이야기는 해피엔딩이 아니오. 하지만 끝까지 함께하겠소, 선장.";
			link.l1 = "생각해 보지.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_hold_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_hold_4":
			dialog.text = "";
			link.l1 = "그런데 네 말이 맞았어 – 광산을 제대로 정리하지 못했더군. 봐.";
			link.l1.go = "tonzag_after_hold_5";
		break;
		
		case "tonzag_after_hold_5":
			dialog.text = "장교의 일지군... 암호화되어 있지만, 오래된 암호라서 내가 알지\n별다른 건 없는 것 같아. 우리 포로의 일지였군. 왜 그렇게 쉽게 입을 열었는지 이제야 알겠어. 여기 봐 – 숨겨진 보물에 대한 단서가 있네! 저 악당, 분명 은퇴할 생각이었고 언제든 도망칠 준비가 되어 있었던 거야!";
			link.l1 = "그럼 그 숨겨진 곳이 어디에 있지?";
			link.l1.go = "tonzag_after_hold_6";
		break;
		
		case "tonzag_after_hold_6":
			dialog.text = "그 섬을 아시잖습니까, 선장님. 그 바다에서 반 베르드를 끝장내셨지요.";
			link.l1 = "좋아, 멀지 않으니 가서 확인해 보자. 카라카스에 관해서는 아직 결정하지 않았지만, 한 달 정도 여유가 있을 것 같아.";
			link.l1.go = "tonzag_after_hold_7";
		break;
		
		case "tonzag_after_hold_7":
			dialog.text = "원하시는 대로 하겠습니다, 선장님. 끝까지 함께하겠습니다.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_after_drink":
			dialog.text = "끝났습니다, 선장님. 오스틴은 지금 카라카스에 있습니다; 우리에겐 한 달 정도 시간이 있을 것 같습니다.";
			link.l1 = "우선 중요한 것부터. 죄수가 뭐라고 했지? 이 오스틴이라는 자는 누구인가? 그리고 우리가 왜 카라카스로 가야 하지?";
			link.l1.go = "tonzag_after_drink_1";
		break;
		
		case "tonzag_after_drink_1":
			dialog.text = "오스틴 패거리는 자유 선장들을 숲으로 유인해 토막 내고, 시신에서 돈이나 장신구까지 몽땅 털어가는 걸로 유명했지. 짭짤한 장사였고, 모험을 찾아 헤매는 놈들도 끊이지 않았으니 아무도 신경 쓰지 않았어. 그런데 어느 선장 하나에게는 제대로 걸려들었고, 그래서 결국 자기 패거리를 회사의 보호 아래 두게 됐지. 우리는 그를 철저히 통제했고, 필요할 때만 문제를 빠르고 단순하게 해결하려고 풀어놨다네.";
			link.l1 = "저런 사람과는 협상을 할 수 있을지 의심스럽군.";
			link.l1.go = "tonzag_after_drink_2";
		break;
		
		case "tonzag_after_drink_2":
			dialog.text = "그건 확실하지. 이제 그 자와 그 일당이 주도권을 잡았으니, 곧 리그도 그냥 또 다른 깡패 집단으로 전락할 거야. 하지만 카라카스로는 가지 마시오, 선장.";
			link.l1 = "진심이야? 무서운 거야?";
			link.l1.go = "tonzag_after_drink_3";
		break;
		
		case "tonzag_after_drink_3":
			dialog.text = "그런 게 아니에요, 선장님. 포로가 죽기 전에 상처로 인해, 당신이 더 이상 리그의 적이 아니라고 털어놨어요. 그리고 저는, 적어도 당신 밑에서 일하는 동안은 리그에게 아무런 관심도 받지 않을 거라고 했죠. 리그에 새로 영향력 있는 후원자가 생겨서 우리를 건드리지 말라고 명령한 것 같아요\n그리고 카라카스... 가슴 깊은 곳에서 불길한 예감이 들어요... 거기 가면 안 좋은 일이 생길 거예요. 아주 안 좋을 거예요. 이 이야기는 해피엔딩이 아닐 거예요. 하지만 저는 끝까지 함께할게요, 선장님.";
			link.l1 = "생각해 보겠소. 물론 이 일을 이번 기회에 완전히 해결하고 싶지만, 어쩌면 그대 말이 옳을 수도 있겠군. 지난주에 있었던 일들 이후로 저들이 다시 우리에게 감히 다가올 것 같지는 않소.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_drink_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_drink_4":
			dialog.text = "";
			link.l1 = "그런데 네 말이 맞았어 – 놈들이 광산을 제대로 정리하지 못했더군. 봐.";
			link.l1.go = "tonzag_after_drink_5";
		break;
		
		case "tonzag_after_drink_5":
			dialog.text = "장교의 일지군... 암호화되어 있지만, 오래된 암호라서 내가 알고 있지\n별로 흥미로운 건 없는 것 같군. 우리 죄수의 일지였어. 여기 봐 – 숨겨진 보물에 대한 표시가 있네! 저 악당, 분명히 은퇴할 생각이었고 언제든 도망칠 준비가 되어 있었던 거야!";
			link.l1 = "그럼 그 숨겨진 곳이 어디에 있지?";
			link.l1.go = "tonzag_after_drink_6";
		break;
		
		case "tonzag_after_drink_6":
			dialog.text = "그 섬을 아시지요, 선장님. 그 바다에서 반 베르드를 끝장내셨으니까요.";
			link.l1 = "좋아, 멀지 않으니 가서 확인해 보자. 카라카스에 관해서는 아직 결정하지 않았지만, 한 달 정도 여유가 있을 것 같아.";
			link.l1.go = "tonzag_after_drink_7";
		break;
		
		case "tonzag_after_drink_7":
			dialog.text = "원하시는 대로 하겠습니다, 선장님.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_church":
			dialog.text = "잠깐만요, 선장님. 저 혼자 가겠습니다.";
			link.l1 = "그건 왜지? 이제 와서 영웅이라도 된 기분인가? 이미 늦었어; 이 사단을 낸 건 너지만, 우리 둘이서 수습해야 해.";
			link.l1.go = "tonzag_church_1";
		break;
		
		case "tonzag_church_1":
			dialog.text = "내 실수 때문에 선장님이 대가를 치를 필요는 없소. 선장님 말이 옳았소 – 내가 가는 곳마다 사람들이 죽고, 무고한 피가 흐르지. 우리가 함께 저 교회에 들어가면 또 다른 포르토 벨로가 될 거요, 난 그런 일은 바라지 않소.";
			link.l1 = "거기서 도대체 무슨 일이 있었던 거지?";
			link.l1.go = "tonzag_church_2";
		break;
		
		case "tonzag_church_2":
			dialog.text = "학살이었지. 은퇴하고 싶었소, 선장. 금화와 아내를 데리고 카르카손으로 돌아가고 싶었소. 연맹이 내 일을 끝내려고 더 많은 사람을 보낼 줄 알았기에, 새 후원자에게서 넉넉한 선금을 받았지. 그다음엔 도시 경비대를 내 옛 동료들과 새 고용주에게 들이밀기만 하면 됐소. 그 소란 속에서 나는 돈을 들고 사라질 생각이었지. 시간이 허락한다면 포르토 벨로의 뚱뚱한 졸부 몇 놈도 털고 말이오.";
			link.l1 = "좋은 계획이군, 하지만 내가 했다면 다르게 했을 거야. 일이 잘못될 수 있는 게 너무 많아.";
			link.l1.go = "tonzag_church_2a";
			link.l2 = "나도 천사는 아니지만, 자네 방식은 나조차 소름이 돋게 하네. 자네가 아직 나를 배신하지 않은 게 놀랍군, 리그나 이달고, 심지어 자기 아내까지도 배신했던 자가.";
			link.l2.go = "tonzag_church_2a";
		break;
		
		case "tonzag_church_2a":
			dialog.text = "모든 게 잘못될 수 있는 건 다 잘못됐지. 세 파운드짜리 대포를 총독 관저 쪽으로 쏜 건 실수였어. 총독 본인은 거의 다치지도 않았지만, 듣자 하니 그의 아름다운 딸은 목숨을 구하려고 무릎 아래로 두 다리를 절단해야 했대. 그 뒤의 보복은 끔찍했지. 피바다가 벌어졌고, 많은 사람들이 죽었어, 선장. 지금 네 앞에 있는 내가 그 사건의 마지막 생존자야. 그리고 얼마 전, 너 스스로 또 한 명을 베어버렸지.";
			link.l1 = "설명해.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_2b":
			dialog.text = "만약 톤자가 부인이 아직 살아 있었다면, 나는 주저 없이 당신을 배신했을 것이오, 선장. 나는 이미 죽은 목숨이오. 이 세상에 더는 내 자리가 없으니 당신을 따르는 것뿐이오. 이제 당신은 그 사건들의 마지막 생존 증인을 보고 있는 것이고, 얼마 전에는 또 다른 증인을 당신 손으로 베었지.";
			link.l1 = "설명해.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_3":
			dialog.text = "용서해 주십시오, 선장님. 그동안 모든 것을 말씀드리지 못한 점 사과드립니다. 우리가 처음 만났을 때, 저는 선장님도 저처럼 그냥 또 하나의 악당일 뿐이라고 생각했소. 그리고 제가 제일 먼저 한 일이 뭔지 아시오? 선장님을 제 뒤처리나 하라고 보냈지요. 처음엔 죽이고 싶지 않았던 그 스페인 돈을 죽이러, 그리고 결국 배신하기로 마음먹었던 그 자를 말이오. 그 이달고, 로드리게스...\n";
			link.l1 = "그의 손가락이 왜 필요했지?";
			link.l1.go = "tonzag_church_4";
		break;
		
		case "tonzag_church_4":
			dialog.text = "여기엔 속임수 없어. 그냥 시험일 뿐이야, 선장. 우리 같은 젊은 악당들을 매년 수십 명씩 뽑지. 기본적인 정직성 검사조차 통과하는 놈들은 몇 안 되고, 그마저도 첫 작전에서 죽어 나가. 너는 플리트우드의 항해일지 작전에서 살아남을 생각이 아니었어. 나는 그냥 집에 들어가서 살아남은 놈들 처리하고, 항해일지만 챙길 생각이었지.";
			link.l1 = "내 기억이 맞다면, 이야기가 약간 다르게 전개됐지.";
			link.l1.go = "tonzag_church_5";
		break;
		
		case "tonzag_church_5":
			dialog.text = "그래요, 선장님. 왜 내가 당신을 도왔는지 나도 모르겠소. 하지만 당신이 여우 놈들과 싸울 때 그 살아 있는 열정이 잠시나마 나에게도 전염됐지. 결국 당신은 모르는 사이에 나를 구했소. 당신은 나에게 빚진 것 없소, 선장님. 그리고 나는 당신을 거기 들여보내지 않을 거요. 이건 내 일이자, 내 속죄요.";
			link.l1 = "원하는 대로 하시오, 에르퀼. 이런 싸움꾼을 잃는 건 아프지만, 자네는 이미 오래전에 자신을 잃었고, 더 이상 피 흘릴 가치도 없지. 나에게 빚진 것도 없으니, 저 작은 교회에서 속죄를 찾길 바라오.";
			link.l1.go = "tonzag_church_bad";
			link.l2 = "좋은 연설이었군, 에르큘. 지옥이나 가라! 아직 눈치 못 챘다면, 네 문제는 요즘 내 문제가 됐다는 걸 알아둬라. 넌 내 부하니까, 네가 용서를 받을 자격이 있는지 없는지는 오직 내가 결정한다. 그러니 우리랑 좀 더 같이 있으면서, 내 선원으로서 용맹을 보여 네 죗값을 치러야 할 거다!";
			link.l2.go = "tonzag_church_good";
		break;
		
		case "tonzag_church_bad":
			dialog.text = "모든 것에 감사드립니다, 선장님. 안녕히 계십시오!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;
		
		case "tonzag_church_good":
			dialog.text = "알겠어요, 선장님!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;
		
		case "tonzag_afterchurchfight":
			dialog.text = "내가 살면서 수많은 악당들을 봤지만, 선장님, 이번만큼은 처음으로 속이 뒤틀릴 만큼 소름이 끼쳤소. 어떻게 생각하시오? 작은 괴물이 더 큰 괴물을 죽인다면, 그것이 구원이라 할 수 있을까?";
			link.l1 = "럼에 물을 타나? 알아내면 말해 줘. 가자, 여기서 할 일 끝났으니.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;
		
		// Эпилог
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "하! 그 말을 네 입에서 들을 줄은 몰랐다. 다음엔 수도원에 들어가겠다는 거냐?";
			link.l1 = "진심이야, "+npchar.name+"… 아버지의 건강이 날마다 나빠지고 있어. 너무 늦기 전에 보고 싶어.";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "우리 배가 뭐가 마음에 안 들었나? 아니면 대서양이 이제는 우리에게 너무 벅차다고 진심으로 생각하는 거야?";
			link.l1 = "나는 이제 육지에 내려 편안히 지내는 것에 대해 생각해봤어. 아직 바다 없는 삶이 어떤지 상상도 못 하지만, 그런 날이 온다면 준비하고 싶어. 내 안에서 싸워야 할 것들을 이해하고 싶어.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "이번 대화에서 너 때문에 두 번째로 말문이 막혔네. 정말로 돛의 바람을 벽난로와 따뜻한 죽으로 바꾸려는 거냐?";
			link.l1 = "아버지 병세가 악화된 걸 보고, 우리 중 누구도 영원하지 않다는 걸 깨달았어. 그 다음에 무슨 일이 있을지는 아직 결정하지 않았어. 지금은 — 그냥 집으로 가는 길뿐이야. 그리고… 너에게 함께 가자고 말하려 했어. 친구로서. 하지만 네가 거절한다면 이해할게. 억지로 설득하진 않을 거야.";
			link.l1.go = "SharlieEpilog_Tonzag_4";
		break;

		case "SharlieEpilog_Tonzag_4":
			dialog.text = "거절? 혼자 가게 내가 놔둔다면 평생 닻 닦는 일만 하게 될 거야! 날 전혀 모르는구나, 선장.";
			link.l1 = "바로 그런 대답을 기대했어. 옛날 프랑스는 이제 예전 같지 않아. 너무 허전하고, 지루하고, 낯설어… 거기서 친구라 부를 사람은 남아 있지 않을 거야. 2주 후에 출항하고, 난 시간을 낭비할 생각 없어. 출항을 기념해서 술집에서 잔치를 벌이자. 어때?";
			link.l1.go = "SharlieEpilog_Tonzag_5";
		break;

		case "SharlieEpilog_Tonzag_5":
			dialog.text = "하! 네가 내가 거절할 거라 생각한다면 — 오랫동안 기다릴 거야!";
			link.l1 = "그럼 결정됐네 — 내 볼 일 다 끝내면 술집에서 보자.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tonzag_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Tonzag = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;

	}
}