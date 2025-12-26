// Тичингиту - индеец-офицер
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
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "뭘 원하지, 창백한 얼굴? 티칭기투는 너한테 할 말 없어.";
			link.l1 = "네 이름이 티칭기투라고? 흠. 이봐, 전사야, 나는 너를 구경하러 온 게 아니야. 묻고 싶은 게 있어서 왔다. 왜 그 뚱뚱한 놈의 집에 침입했지?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "아무 말도 안 하는 건가? 현명하지 못하군. 도둑질과 그동안 저지른 모든 일로 목이 매달릴 거야. 왜 그런 짓을 했는지 말해 봐. 그러면 내가 도와줄 수도 있지.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "티칭기투는 수많은 길을 따라, 거대한 바다를 건너, 광활한 숲과 늪을 지나 창백한 얼굴들의 마을에 왔다. 티칭기투는 지쳐 있었고, 먹고 싶었다. 티칭기투는 굶주림에 죽어가고 있었다. 아무도 티칭기투를 도와주려 하지 않았다. 그들은 소리쳤다. '꺼져라, 붉은 피부의 개야.' 술집 주인은 인디언을 들개처럼 내쫓았다. 티칭기투는 먹고 싶었다.";
			link.l1 = "젠장, 그런데 왜... 네 숲에서 이 정착지로 온 거지?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "티칭기투는 원주민 부족에서 쫓겨났다. 티칭기투는 부족의 주술사와 싸움을 벌였고, 주술사는 족장에게 이를 알렸다. 주술사는 티칭기투에게 저주를 내렸고, 티칭기투는 부족을 떠나 아주 멀리, 원주민 땅에서 멀리 떨어져 나갔다. 티칭기투에겐 집도, 무기도, 아무것도 남지 않았다.";
			link.l1 = "이게 바로 불운이지. 왜 자기 동료들과 싸운 거야?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "부족의 주술사는 사악한 자요. 그는 내 아내의 몸에 악령이 깃들었다고 했소. 내 아내는 죽어야만 했지. 하지만 내 아내는 단지 병에 걸렸을 뿐, 어떤 영도 깃들지 않았소. 티칭기투가 내 아내를 치료하려 했으나, 주술사가 그녀를 죽였소. 티칭기투가 주술사에게 맞섰고, 모두가 티칭기투를 등지게 되었소, 그래서 티칭기투는 떠났소.";
			link.l1 = "아내를 구하려고 했던 거야? 그래서 마을에서 쫓겨난 거냐?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "그래, 창백한 얼굴. 티칭기투는 선택의 여지가 없어. 훔치거나 굶어 죽거나...";
			link.l1 = "흠, 이런... 굶주린 자가 몇 푼 훔쳤다고 교수대라니... 티칭기투, 내가 도와보마. 네가 몰래 들어간 집의 건장한 사내, 파데이도 알고 있지. 내가 뭔가 해볼 수 있을지도 모르겠군... 사령관에게 가서 이야기해보마.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			AddDialogExitQuestFunction("Tichingitu_DlgExit_1");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "티칭기투는 기다린다. 인디언은 죽음을 두려워하지 않는다. 주술사가 티칭기투에게 저주를 내렸으니, 티칭기투는 죽어야 한다.";
			link.l1 = "아직 모든 게 끝난 건 아니야. 내가 도와보겠어...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "티칭기투는 기다린다. 인디언은 죽음을 두려워하지 않는다. 주술사가 티칭기투에게 저주를 걸었으니, 티칭기투는 죽어야 한다.";
			link.l1 = "비관적일 필요 없어. 네 감금 생활은 끝났어. 내가 널 풀어주는 데 도움을 줬지.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "창백한 얼굴 농담이냐? 티칭기투가 자유로운 거야?";
			link.l1 = "아니, 농담 아니야. 곧 네 감방 문을 열고 널 내보낼 거야. 따라와, 내가 감옥에서 데리고 나가줄게.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tichingitu_DlgExit_2");
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "여기 있군, 다시 자유야. 가라, 티칭기투, 다시는 도둑질하지 말고 더 이상 문제 일으키지 마! 인디언 마을을 찾아가서 네 동족들과 함께 사는 게 좋을 거다, 그들도 널 받아주는 데 반대하지 않을 거라 생각한다.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "티칭기투 안 가. 주인이 티칭기투 목숨 살려줬어. 티칭기투 남아. 티칭기투 목숨은 주인 거야.";
			link.l1 = "어? 무슨 소리야? 무슨 주인, 무슨 인생? 내가 하는 말 못 알아듣겠어? 이제 자유야! 가!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "인디언에게 빚이 있소, 백인 주인 나리. 티칭기투는 충성과 진실로 주인님을 섬기오. 티칭기투는 싸우는 법을 알지. 티칭기투는 주인님을 위해 전장에서 죽을 것이오. 그는 남겠소.";
			link.l1 = "오, 주여! 젠장... 내가 너한테 무슨 주인이라는 거냐, 티칭기투? 나는 너를 노예로 만들려고 도운 게 아니야.";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "티칭기투는 노예 아니야. 티칭기투는 자유로운 인디언이야. 티칭기투는 너를 섬기고 싶어. 티칭기투는 싸우는 법 알아, 어떤 개도 주인 가까이 오기 전에 죽을 거야. 티칭기투는 머스킷 청소하고 장전하는 법도 알아. 티칭기투는 머스킷 쏠 수 있어.";
			link.l1 = "하지만... 있잖아, 티칭기투, 그거 나쁜 생각은 아니군. 나는 충직한 사람이 필요하고, 너도 나쁜 놈 같진 않아. 게다가 머스킷도 쏠 줄 알잖아. 그리고 혼자서 뭘 할 건데? 결국 또 뭔가를 훔치다가 다음엔 정말로 교수형 당할 거야... 좋아, 남아도 돼. 하지만 명심해라: 나랑 있으면 인생이 평탄하지 않을 거다.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "좋아, 이제 됐다. 평안히 가거라, 붉은 피부의 형제여. 네 신들이 너를 지켜주길!";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			AddDialogExitQuestFunction("Tichingitu_DlgExit_3");
		break;
		
		case "Tichingitu_13":
			dialog.text = "티칭기투는 아무것도 두렵지 않소, 백인 나리. 티칭기투는 당신을 섬길 수 있어 기쁘오. 티칭기투는 마지막 숨이 다할 때까지 충성하겠소.";
			link.l1 = "좋아. 승선을 환영한다, Tichingitu!";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			AddDialogExitQuestFunction("Tichingitu_Hire");
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "티칭이투가 당신 말을 듣고 있소, 선장. "+pchar.name+"!";
			// Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = ""+npchar.name+" 는 선장 "+pchar.name+" 의 눈에서 혼란을 본다.";
				Link.l1 = "역시 넌 내 마음을 꿰뚫어 보는구나, 친구. 사실 나는 고향인 유럽으로 돌아가야 해. 어려운 결정을 내렸지 — 남의 배를 타고, 승객으로 항해하겠어.";
				Link.l1.go = "SharlieEpilog_Tichingitu_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "티칭이투, 나는 이제 타야살이라는 옛 인디언 마을로 떠나려 해. 솔직히 말해서, 이건 정말 위험하고 평범하지 않은 여정이야. 순간이동 우상(아이돌)을 통해 가야 하거든. 너... 나와 함께 갈래?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "티칭이투, 배에 대한 전체 보고를 해 주게.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "우리가 항구에 도착할 때마다 특정 물품을 구입해 주었으면 하오.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "내 명령을 들어라!";
            Link.l1.go = "stay_follow";
			link.l2 = "지금은 아무 일도 없다. 편히 쉬어!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "배 보고서? 티칭기투는 보고서 없소, 주인님. 무기랑 옷만 있소. 티칭기투는 어디서도 보고서 안 받았소.";
			Link.l1 = "좋아, 뭐든지.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "주인님, 티칭기투는 당신 없이는 절대 식민지에 들어가지 않소. 티칭기투가 상점에 들어가면 모두가 또 도둑이라고 생각하오. 그러면 감옥이지.";
			link.l1 = "그래, 네 말이 맞을 거야. 또 감옥 얘기는 그만두자. 게다가, 아무도 네가 급사라고는 믿지 않을걸.";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "무슨 명령이 있소?";
            Link.l1 = "여기서 멈춰!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "나를 따라오고 뒤처지지 마!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "화기의 탄종을 바꿔야 해.";
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
					Link.l5 = "전투에 사용할 주 무기를 변경하십시오.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "목표물과 거리를 유지해 주길 바라오.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "탄약 종류를 선택하십시오:";
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
			Dialog.Text = "싸움이 시작될 때 사용할 것은 다음과 같습니다:";
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
            dialog.Text = "계획 변경이다!";
            Link.l1 = "편히 있으시오.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "계획이 바뀌었다!";
            Link.l1 = "긴장 풀게.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "얼마나 남았나, 선장? 티칭기투에게 몇 야드인지 말해 줘. 하지만 스무 야드를 넘지 않게.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "선장님, 티칭기투를 용서해 주십시오만, 저는 당신을 이해하지 못하겠습니다.";
				link.l1 = "미안해, 내 실수야...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "티칭이투가 가만히 서 있고, 움직이지 않습니다. 그게 원하시는 바입니까, 선장님?";
				link.l1 = "예, 바로 그렇소.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "티칭이투는 목표에서 스무 야드 이상 떨어질 수 없어. 그러면 놓치거든.";
				link.l1 = "좋아, 이십 야드 떨어져 있어.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "티칭이투는 모든 것을 이해한다. 티칭이투는 네가 말한 자리를 맡겠다.";
			link.l1 = "좋아.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "티칭기투의 삶은 오랫동안 내 선장의 삶과 하나가 되었소. 인디언은 선장님이 티칭기투를 위해 해주신 일을 잊지 않소. 선장님이 어디로 가라 하시든, 티칭기투는 아무런 의문도 망설임도 없이 따를 것이오.";
			link.l1 = "고맙다, 친구야!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "우리는 언제 출발하나?";
			link.l1 = "조금 있다가 말이지. 지금은 여행 준비부터 해야겠어.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "우리는 백인에게 두블론 100개를 주고, 떠나서 자유롭게 일을 끝낸다.";
			link.l1 = "또다시 잡히면 어쩌지?";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "우리는 천 두블룬을 지불한다.";
			link.l1 = "냉소적이지만, 매우 통찰력이 있다.";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "과들루프는 더 심해.";
			link.l1 = "어째서지?";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "저기서는 티칭기투만 혼자 목매달려고 하고, 여기서는 여러 명을 목매달려 하네. 그렇게 나쁘진 않군.";
			link.l1 = "이건 정말 너무 냉소적이잖아!";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "근거리 사격이었소. 선장님, 저 노인은 강인하니 우리가 빨리 움직이면 살릴 수 있소.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "백인 놈들은 자비란 게 없지. 내 동료들도 많이 죽었어, 선장. 정말 많아. 하지만 네 쪽은, 그보다 더 많더군.";
			link.l1 = "그들이 네 부족이냐?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "내 것도... 조금 있지.";
			link.l1 = "버텨라, 친구.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "또 40두블론이라고?";
			link.l1 = "어? 또다시 들뤽의 석방금을 내가 내줄 거냐고 묻는 거야?";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "그래.";
			link.l1 = "나도 잘 모르겠어... 너는 어떻게 생각해?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "우리가 그를 빼내야 해.";
			link.l1 = "고귀하군. 동료를 절대 버리지 않는 거지, 응?";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "아니면 그냥 두어라. 약한 놈은 정글의 재규어에게 맡겨.";
			link.l1 = "누구?";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "큰 고양이.";
			link.l1 = "티칭이투, 자네 말을 이해하기가 어렵군. 그냥 말해 주게: 이 상황에서 내가 뭘 해야 하지?";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "네 머리로 생각해.";
			link.l1 = "아주 도움이 됐어!";
			link.l1.go = "Del_Deluck_6";
		break;
		
		case "Del_Deluck_6":
			DialogExit();
			AddQuestRecord("FolkeDeluc", "2");
			ReturnOfficer_Tichingitu();
		break;
		
		// Эпилог
		case "SharlieEpilog_Tichingitu_1":
			dialog.text = "선장 "+pchar.name+" 은 "+npchar.name+" 를 데려가지 않나?";
			link.l1 = "넌 내 친구야, "+npchar.name+" 그리고 물론 이 여정에 함께하길 바래. 하지만 알아둬야 해 — 구세계 사람들은 원주민을 보는 데 익숙하지 않아. 널 손가락질하며 내 노예라고 생각할 거고, 그렇게 대할 거야.";
			link.l1.go = "SharlieEpilog_Tichingitu_2";
		break;

		case "SharlieEpilog_Tichingitu_2":
			dialog.text = ""+npchar.name+" 는 신경 쓰지 않아. "+npchar.name+" 는 백인들이 원주민을 경멸한다는 걸 알고 있어. 그리고 약속한 대로 선장 "+pchar.name+" 을 마지막 숨이 다할 때까지 따를 거야.";
			link.l1 = "모두가 원주민을 경멸하는 건 아니야. 하지만 대부분은 경계하지 — 그들에겐 낯선 것을 신앙으로부터 지키는 방식이니까. 어쨌든, 난 누구도 너를 모욕하거나 노예로 대하게 두지 않을 거야. 너희 부족 중엔 유럽을 본 사람이 없을 거야 — 저주받은 그 주술사조차도, 가장 대담한 꿈속에서도 상상 못 했겠지.";
			link.l1.go = "SharlieEpilog_Tichingitu_3";
		break;

		case "SharlieEpilog_Tichingitu_3":
			dialog.text = "마스코기 인디언은 항해자가 아니야. 그들은 유럽에 도달하지 못해. 들었어 — 큰 카누로 가도 두 달이 걸린다고.";
			link.l1 = "그래, "+npchar.name+" 그리고 그건 바람이 도와줄 때의 얘기야. 쉬운 여정은 아니지. 우리는 2주 후 출항해... 그리고 네가 함께한다니 기쁘다. 출항을 기념해서 선술집에서 작은 파티를 열 생각이야. 네가 불의 물을 좋아하지 않는 건 알지만, 그래도 함께 해주면 기쁠 거야.";
			link.l1.go = "SharlieEpilog_Tichingitu_4";
		break;
		
		case "SharlieEpilog_Tichingitu_4":
			dialog.text = ""+npchar.name+" 도 갈게. 하지만 축하 겸 선상 급습은 어때?";
			link.l1 = "하하하. 이번엔 안 돼, 친구 — 그런 자리 아니거든. 시작할 때 알려줄게. 지금은 가야 해 — 할 일이 있거든.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Tichingitu = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
