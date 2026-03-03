// Раймонд Бейкер - палач Сент-Джонса и возможный офицер
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
			dialog.text = "뭐 필요해?";
			link.l1 = "아니, 아무것도 아니야.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "감사합니다, 선장님! 선장님이 아니었으면 어쩔 뻔했는지 상상도 못 하겠어요...";
			link.l1 = "짐작이 가는군. 자칫하면 굶어 죽었거나 도미니카의 야만인 뱃속에서 끝났을 거야. 하지만 이제 나한테 갚을 기회가 있지.";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "무엇을 도와드릴까요, 선장님?";
			link.l1 = "한 남자에 대해 더 알고 싶소. 우리 둘 다 아는 사이랄까. 사실, 그대와 아주 가까운 친구지. 도살장 선장을 말하오. 그래, 그대가 이십 년 전에 교수형에 처한 바로 그 사람 말이오. 이런, 왜 이렇게 창백해졌소? 럼 한 모금 하겠소?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "그... 그 사람이 보낸 건가?";
			link.l1 = "말도 안 돼! 그 자가 죽었는데 내가 어떻게 '그가 보냈다'는 사람이 될 수 있겠어! 나는 도살자 그 자체보다는 그가 남긴 것들에 더 관심이 있네. 편지, 문서, 그런 것들 말이야. 혹시 그의 주머니에서 뭔가 찾은 게 있나... 잠깐! 이해가 안 되는군. 설마 자네는 도살자가 살아 있다고 생각하는 건가? 자네가 직접 그를 처형했잖아!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "젠장! 너 아무것도 모르잖아. 그럼 내가 생각한 대로 도살장이 널 보낸 게 아니란 말이군...";
			link.l1 = "흠, 흥미로워지는군. 헨리가 도살꾼을 두려워할 만한 이유가 충분히 있었던 모양이야, 그래서 심장마비로 죽은 거고... 도살꾼은 살아 있나?";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "그렇소, 선장님... 그리고 그들이 나를 찾고 있소.";
			link.l1 = "레이몽, 자네가 바보는 아니라 들었네. 나와 장난치려 들지 마. 여기서는 어떤 위협도 없으니 안심하게. 아는 걸 전부 말해주면 내가 도울 방법을 생각해보지. 어쩌면 우리에게 공통의 적이 있을지도 모르지. 도살자 얘기부터 시작하세.";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "그는 살아 있어, 하지만 지금은 이름이 달라! 처형 당일 밤에 그 놈의 부하들이 나를 찾아왔지. 잭맨하고, 별명이 좀 이상한 다른 남자였어. 내가 기억하기로는 '익사한 자'였던 것 같아.";
			link.l1 = "교수형 집행인. 교수형 집행인 헨리.";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "좋아! 놈들이 내게 간단한 선택을 내밀더군 – 가장 고통스럽게 죽든가, 아니면 자기네 선장을 구하든가. 그래서 나는 여분 시간에 만들어 둔 특수 장비로 처형을 위장해야 했지. 알겠지만, 벨트와 클램프를 이렇게 배치하면 몸무게가 분산돼.\n내가 할 일은 밧줄에 숨겨진 갈고리에 그걸 거는 것뿐이었어. 물론 '시체' 역할을 맡은 사람도 연기를 제대로 해야 했지. 솔직히 말해, 로렌스의 연기는 정말 그럴듯했어. 모든 걸 완벽하게 해냈지, 다만... 오줌을 싸는 건 끝내 거부하더라고, 그건...";
			link.l1 = "방금 도살장을 '로렌스'라고 불렀어?";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "그게 그의 진짜 이름이오. 내가 그를 로렌스 벨트로프라 부른다고 말했지. 1년 전 그가 카리브로 돌아온 뒤로 계속 불안했소. 그리고 누군가 위험한 자들이 나를 찾고 있다는 걸 알게 되었을 때는...\n혹시 몰라서 당국에 제출할 자백서도 써 두었소. 너무 두려워서 아직 넘기지 못하고 항상 지니고 다니오. 그들이 내가 자발적으로 공범이었다고 생각할 수도 있으니까. 제발, 당신 선원들과 함께 있게 해주시오. 맹세코, 나는 훌륭한 의사이니 당신께 큰 도움이 될 수 있소.";
			link.l1 = "좋아. 그럼 도살꾼의... 아니, 벨트로프의 개인 물건은 어떻게 되었지? 그가 토마스 벨트로프와 관련이 있나?";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "모르겠어. 벨트로프 본인에게서 특별히 남은 건 없어. 하지만 내가 가진 건 전부 줄게. 네 마음대로 해도 돼. 관련된 모든 서류는 내 가방에 있어. 만일을 대비해서 다 챙겨두고 항상 가까이 두고 있지.\n자, 여기 봐... 이건 부처 선장의 전설이고, 이건 내 고백이야... 그리고 이건 조슈아 리드비터에게 속했던 것들이지...";
			link.l1 = "멈춰! 리드비터? 그게 누구야?";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "오! 그는 정말 특별한 사람이었지. 그가 바로 도살자 놈을 직접 추적했던 인물이야. 사람들은 그를 '가면 쓴 사나이'로 기억했지. 도살자가 처형된 직후에 그도 살해당했어. 누군가 상어 이빨로 그의 목을 그어버렸지! 한 번에 끝났어. 살아 있을 때는 엄청난 고통을 겪었을 거야.\n가면 밑의 얼굴을 봤다면, 살덩이뿐이었어! 죽을 때 그의 주머니에 이 일지 한 장이 들어 있었지. 제시카 로즈가 쓴 글에서 나온 것임이 틀림없어. 소름 끼치는 이야기야! 읽어봐, 훨씬 더 명확해질 거야.\n그리고 이게 바로 그 이빨이야. 글자가 보이지? S.D.... 무슨 뜻인지는 모르겠어. 피 자국도 아직 남아 있네.";
			link.l1 = "그만! 나는 모든 걸 꼼꼼히 읽고 곰곰이 생각해 봐야겠어. 그리고 네가 이 모든 일이 끝날 때까지 내 승객이든 배의 의사든 되어야 하네. 이제 숨 좀 돌려도 돼, 레이몬드. 내 배에선 안전하니까.";
			link.l1.go = "baker_10";
		break;
		
		case "baker_10":
			DialogExit();
			sld = characterFromId("Baker_Cap");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
			//sld.ship.hp = 0;
			//sld.SinkTenPercent = true;
			bQuestDisableMapEnter = false;
			GiveItem2Character(pchar, "shark_teeth");
			GiveItem2Character(pchar, "letter_jess");
			GiveItem2Character(pchar, "letter_baker"); // показания бейкера
			ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
			AddQuestRecordInfo("Legend_CapBucher", "1");
			AddQuestRecordInfo("Letter_jess", "1");
			AddQuestRecord("Shadows", "5");
			pchar.questTemp.Saga.Shadows = "islatesoro";
			// в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Baker_officer";
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Baker_officer":
			dialog.text = "예, 선장님?";
			Link.l1 = "내 명령을 들어라!";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "선장님, 무척 당황하신 것 같군요. 안색도 꽤 안 좋아 보입니다... 다른 상황이라면 제 약초주를 권했을 텐데 말이죠...";
				Link.l1 = "의학 지식도 제법 쌓았나 보군, "+npchar.name+"? 고맙지만, 난 괜찮아. 지금 내가 하려는 일은 아마 평소라면 절대 하지 않았을 선택이니까.";
				Link.l1.go = "SharlieEpilog_Baker_1";
				break;
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Raymond, 배에 대한 전체 보고를 해 주게.";
			    Link.l11.go = "QMASTER_1";

			    // Warship. Автозакупка товара
				Link.l12 = "우리가 정박할 때마다 특정 물품을 구입해 주었으면 하네.";
				Link.l12.go = "QMASTER_2";
			}
			
			link.l2 = "별거 아니오. 해산!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "어서요, 선장님, 저는 의사지 급사(회계 담당자)가 아닙니다. 예전에야 다른 일도 했었지만... 아무튼 됐고요. 저는 정말 회계는 못 합니다, 미안합니다.";
			Link.l1 = "좋아, 그렇게 하자. 네가 내 선의라는 것, 내 선원으로 들어온 뒤 우리가 합의한 대로다.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "선장님, 솔직히 말씀드리자면 저는 무역 경험이 거의 없습니다. 흥정도 해본 적 없고, 시세도 따져본 적이 없습니다. 그리고... 괜찮으시다면 저는 그냥 배에 남고 싶습니다. 저 상인들 중에 저를 알아보는 사람이 있을 수도 있고, 그러다 보면 곧 복면 쓴 놈들이 들이닥칠지도 모릅니다.";
			link.l1 = "그래, 과거에 대한 두려움 속에서 계속 살겠다는 거군... 좋아, 숨 내쉬어. 내가 직접 하지.";
			Link.l1.go = "exit";
        break;
		
		case "stay_follow":
            dialog.Text = "명령이오?";
            Link.l1 = "여기 서 있어!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "나를 따라오고 뒤처지지 마!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "당신의 화기의 탄종을 변경하십시오.";
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
            dialog.Text = "성향이 바뀌었다!";
            Link.l1 = "해산하라.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "기세가 바뀌었군!";
            Link.l1 = "해산하라.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// Эпилог
		case "SharlieEpilog_Baker_1":
			dialog.text = "흠... 뭔가 제가 잘못 이해하고 있는 것 같군요. 저는 다가올 소식이 당신을 기쁘게 할 줄 알았습니다.";
			link.l1 = "무슨 말이야?";
			link.l1.go = "SharlieEpilog_Baker_2";
		break;

		case "SharlieEpilog_Baker_2":
			dialog.text = "크흠... 실례했습니다. 저도 왜 그랬는지 모르겠네요. 아마 햇볕에 머리가 데였나 봅니다. 사실, 당신과 얘기하고 싶었습니다, 선장님.";
			link.l1 = "그래? 무슨 이야기인데?";
			link.l1.go = "SharlieEpilog_Baker_3";
		break;
		
		case "SharlieEpilog_Baker_3":
			dialog.text = "이제 저는 이 끝없는 해전에서 벗어날 나이가 된 것 같습니다. 직접 싸우는 건 아니지만요. 약간의 저축도 있고, 이제는 육지에 정착해 개인 병원을 열고 싶습니다. 괜찮으시겠습니까?";
			link.l1 = "물론이지, "+npchar.name+" 씨. 당신 같은 유능한 장교가 그리울 거야. 하지만 당신의 결정을 이해하고 존중해. 행운을 빌게. 당신은 곧 훌륭하고 존경받는 의사가 될 거라 확신해.";
			link.l1.go = "SharlieEpilog_Baker_nothing";
			link.l2 = "현명한 판단이야. 당연히 나는 아무런 반대도 없어. 추가로 한 달 치 월급을 지급하라고 지시하겠어 — 쓸모가 있을 테니까. 뭐, 더 할 말은 없지... 새 삶에 행운이 따르길.";
			link.l2.go = "SharlieEpilog_Baker_salary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // только если есть жена
			{
				link.l3 = "하하, 당연히 반대하지 않을게, 친애하는 "+npchar.name+" 씨. 지금은 정말 네 마음이 이해돼. 자, 여기 있어. 3개월치 월급이야. 모든 일이 잘 풀리길 바란다.";
				link.l3.go = "SharlieEpilog_Baker_salary_X3";
			}
		break;
		
		case "SharlieEpilog_Baker_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
		break;
		
		case "SharlieEpilog_Baker_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
			//
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Baker_salary_X3":
			dialog.text = "감사합니다, 선장님. 당신도 아내분과 함께 조용하고 아늑한 집을 빨리 마련하셔야 할 겁니다. 결국, 배의 흔들림은... 자궁 속 어떤 과정엔 좋지 않거든요...";
			link.l1 = "자궁...? 무슨 말이야? 우리 선원 중에는 멀미하는 사람도 없는데.";
			link.l1.go = "SharlieEpilog_Baker_salary_X3_2";
			//
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Baker_salary_X3_2":
			dialog.text = "그냥 혼잣말입니다, 선장님. 신경 쓰지 마세요. 부인과 자신 모두 잘 챙기시길.";
			link.l1 = "너도 몸조리 잘해, "+npchar.name+" 씨. 정착하면 생피에르 교회의 브누아 신부님께 소식을 전해줘.";
			link.l1.go = "SharlieEpilog_Baker_salary_X3_3";
		break;
		
		case "SharlieEpilog_Baker_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
