// Элен МакАртур - сомнительная любовь и офицер
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
			dialog.text = "무슨 일이야?";
			link.l1 = "아니, 아무것도 아니야.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "도와줘서 고마워요, 선장님!";
			link.l1 = "세상에... 내가 상상했던 것보다 훨씬 더 아름답구나!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "내 아름다움은 다 저주받으라고 해! 그게 나한테 얼마나 많은 고통을 줬는지 알아? 명성만 아니면 코라도 잘라버렸을 거야. 그 자식이 나를 코르벳에서 살아 나가지 못하게 하려고 했어, ‘너무 많은 걸 안다’면서. 어제는 기다리는 것도 지겹다며 내 의사와 상관없이 날 차지하겠다고 했지\n정말 완벽한 타이밍에 와줬네! 그런데 예의가 없었지, 내 이름은 헬렌 맥아더야. 아버지가 내가 자꾸 ‘입수’한 고급 도자기를 깨뜨린다고 나를 룸바라고 불렀거든, 그래서 내 선원들도 날 그렇게 불러.";
			link.l1 = "내 이름은 "+GetFullName(pchar)+" 그리고 내가 널 구하러 왔어. 며칠 동안 카리브 해를 샅샅이 뒤지며 글래디스 아가씨를 위해 널 찾고 있었지.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "글래디스 양!? 그녀는 어떻게 지내?";
			link.l1 = "너무 걱정했어. 하지만 곧 그녀를 보게 될 거야, 우리는 블루웰드로 항해 중이니까. 가는 길에 무슨 일이 있었는지 전부 말해줘.";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "솔직히 말해서, "+pchar.name+", 지금 당장 밥도 먹고 한숨 자고 싶어. 그 괴물 같은 배에서 며칠이나 보내고 나니 완전히 지쳤어...";
			link.l1 = "물론이지요, 맥아더 양. 집사에게 식사를 대접하고, 당신만의 개인 방에 침대를 준비하라고 명령하겠습니다.";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "드 모르 선장, 제때 구해주셔서 다시 한 번 진심으로 감사드립니다. 꼭 저와 어머니를 찾아와 주세요. 저희 집은 여기서 멀지 않아요, 부두에서 오시면 왼편에 있습니다. 그리고 이것만은 알아두세요\n "+pchar.name+", 작별 인사도 없이 떠나면 절대 용서하지 않을 거야!";
			link.l1 = "기쁨은 전적으로 제 몫이었습니다, 맥아더 양. 반드시 다시 찾아뵙겠습니다!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "아, 거기 계셨군요, 드 모르 선장! 와 주셔서 정말 기뻐요, 묻고 싶은 게 정말 많거든요.";
			link.l1 = "죄송합니다, 맥아더 양, 하지만 우리 대화는 잠시 미뤄야겠습니다.\n만족스러운 답을 드리기 전에 더 많은 정보를 모아야 하거든요.\n지금은 부디 거리에 나서지 말아 주십시오.\n기다림이 오래 걸리지 않길 바랍니다.\n저를 믿고 기다려 주세요.";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "네가 직접 말했잖아, 내가 들르지 않으면 용서하지 않겠다고.";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "Helena_hire":
			dialog.text = "아, 여기 계셨군요, 내 캡틴! 당신 눈빛을 보니 소식이 있는 것 같네요!";
			link.l1 = "스벤슨 선장께서 당신이 저와 함께 항해하고 싶어 한다고 말씀해 주셨어요. 관심 가져주셔서 감사하고, 글래디스 양도 당신이 바다를 그리워했다고 하더군요. 환영합니다, 헬렌 맥아더 양!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "스벤슨 선장이 당신이 나와 함께 항해하고 싶어한다고 말했어요. 관심 가져줘서 고마워요, 그리고 글래디스 양이 당신이 바다를 그리워했다고 하더군요. 내 선원으로 온 걸 환영해요, 헬렌 샤프 양!";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "알겠어요, 선장님! 이런 말 하긴 싫지만, 나리, 나는 내 몸은 내가 지켜요. 남자들이 함부로 굴면 절대 참지 않을 거예요. 잘린 손이나 찔린 눈에 대해서는 책임 못 집니다.";
			link.l1 = "걱정 마, 내 배에서는 흔들림 없는 규율이 있어. 그런데 한 가지 물어볼 게 있어...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "...네?";
			link.l1 = "얀 스벤손과 나는 네가 이슬라 테소로의 정당한 상속자라는 사실을 알아냈어. 그래, 사실이야, 고개 저을 필요 없어! 나는 네 권리를 증명하는 지도 절반을 가지고 있어. 쉽진 않겠지만, 얀과 나는 네가 진정한 주인이 될 수 있도록 최선을 다해 도울 거야.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", 정말이야? 가난한 소녀를 그렇게 놀리는 건 친절하지 않아! 내가 어떻게 섬 전체를 소유할 자격이 있겠어?!";
			link.l1 = "저는 정말 진지합니다, 맥아더 양. 그리고 당신이 정당한 권리를 되찾을 수 있도록 도울 생각입니다. 지금 바로 출항합시다!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "뭐, 뭐라고 했어? 헬렌 샤프? 왜 샤프지?";
			link.l1 = "헬렌, 너는 비트리스 샤프의 딸이자 샤프 가문의 유일한 상속녀야. 이것은 글래디스 양이 그동안 간직해 온 지도 반쪽이야. 이게 바로 네가 이슬라 테소로의 상속권을 주장할 수 있는 증거지. 쉽지는 않겠지만, 얀 스벤손과 나는 네가 할아버지의 섬을 물려받을 수 있도록 최선을 다해 도울게.";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			Notification_Approve(true, "Helena");
			npchar.lastname = "Sharp";
		break;
		
		case "Helena_hire_3":
			dialog.text = "오... 우리 불쌍한 어머니! 언젠가 어머니의 무덤을 찾아가 그곳에서 영혼을 위해 기도할 수 있으면 좋겠어. 하지만... 잠깐! 그럴 리가 없어!";
			link.l1 = "무슨 일이에요, 샤프 양?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "집시 여인의 예언이 방금 현실이 되었어... 이제야 그 뜻을 완전히 알겠어.";
			link.l1 = "에? 무슨 예언?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", 순진하다고 생각할지 모르겠지만, 그래도 말할게. 내가 어릴 때 한 집시 여인이 내게 이렇게 말했어. '네 운명은 과부의 동전을 받지 않고, 죽은 자의 금화를 돌려주며, 어머니의 이름을 부르는 남자의 손에 달려 있다.'\n그땐 다 허튼소리라고 생각했는데, 어쩌다 보니 당신이 그 예언의 모든 조건을 다 이뤘어. 당신이 그걸 알았을 리가 없잖아!";
			link.l1 = "네 운명이라니... 글쎄, 어쩌면 네 말이 맞을지도 모르지. 실망시키지 않을게. 네 어머니의 무덤을 함께 찾아보자. 그리고 지금은... 헬렌 샤프 양! 출항 준비하고 늦지 마라!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "알겠어요, 선장님!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = "Captain "+pchar.name+"! 좋은 생각이 떠올랐어...";
			link.l1 = ""+npchar.name+"? 여기 안전하지 않아, 그리고 내가 배에 있으라고 했잖아...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = "샤를, 이 낡은 배에는 화약이 너무 많이 실려 있어서 한 번 터지면 섬 전체가 성 베드로의 문 앞까지 날아갈 거야! 내가 숨으라고 해도 소용없으니, 내 말 좀 들어!";
			link.l1 = "좋아, 빨리 말해!";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "코르벳과 프리깃이야. 저들은 Knive의 배를 적대적으로 여기지 않아. 그 방심을 역이용할 수 있지. 화약통 몇 개 챙겨서 도화선을 달고 배로 가자고\n우리가 가까이 접근해도 놔둘 거야. 그때 도화선에 불을 붙이고, 화약통을 한 척에 떨어뜨린 다음 최대한 빨리 도망치는 거지. 그러면 멋진 폭발을 구경할 수 있을 거야... 어때?";
			link.l1 = "즉석에서 만든 화선이라니... 정말 교묘하군! 네 계획은 미친 짓 같지만, 오히려 그래서 통할지도 몰라... 우리가 들키지 않고 충분히 가까이 접근할 수만 있다면.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "우리가 잃을 게 뭐가 있겠어 "+pchar.name+"? 한 번에 두 척을 상대하는 건 쉽지 않겠지만, 형세를 뒤집을 기회가 올 거야...";
			link.l1 = "좋아. 이제 시작하자! 얘들아! 화약통 세 개 가져와! 우린 여기서 당장 빠져나갈 거야! 네 상상력 정말 마음에 들어, "+npchar.name+"... 나 스스로는 이런 생각을 절대 하지 못했을 거야.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "예, 선장님, 무슨 일이십니까?";
			link.l1 = "잭맨의 배는 사보-마틸라 만에 있어, 중형 프리깃 '센튜리온'이야. 이 배는 원래 호크스의 소유였으니, 잭맨 선장실에 중요한 물건과 문서가 있을 거야... 반드시 승선해야 해.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "말처럼 쉽지 않아. 우리 폴라카로 그걸 어떻게 하겠다는 거야? 저쪽이 인원도, 화력도 우리보다 훨씬 세.";
			link.l1 = "네 말이 맞아. 잭맨 쪽이 우리보다 인원이 최소 두 배는 많고, 전부 검술에 능한 자들이야. 사전 포격 없이 그들을 공격하는 건 미친 짓이지. 그렇다고 오래 끄는 전투도 좋은 선택은 아니야. 그래서 어떻게 해야 할지 계속 생각하고 있었어.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", 아직 우리를 적으로 인식하지 못했어, 터크스에서 그 멍청이들처럼... 우리 수법을 다시 써볼 수 있겠네...";
			link.l1 = "헬렌, 내가 방금 말했잖아. 우리는 저 프리깃에 올라타서 수색해야 해. 그냥 날려버리는 건 선택지가 아니야.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "잠깐만, "+pchar.name+", 우린 그녀를 침몰시키지 않을 거야. 좀 색다르게 해보자. 잘 들어, 빈 럼통 몇 개에 화약이랑 산탄, 짧은 도화선을 채워 넣을 거야. 그다음 저 프리깃에 더 가까이 다가가서, 그 급조 폭탄들을 갑판 위로 던지는 거지.";
			link.l1 = "하! 너의 여성다운 기지가 또 한 번 나를 놀라게 하는군! 화선 대신 푸가스를 쓰자고? 그게 통할 거라 생각해?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "왜 안 되겠어? 저놈들 갑판이 우리보다 높긴 하지만, 도르래만 있으면 두세 명이 충분히 꽉 찬 술통을 들어 올려 던질 수 있어. 우리가 외치면 되지 - '나이브가 주는 공짜 럼주다!' 그러면 저놈들이 반응하기도 전에 술통이 터질 거야.";
			link.l1 = "폭발성 산탄이 갑판 위에 있는 그의 최정예 놈들을 갈기갈기 찢어 놓겠지... 젠장, 솔깃하게 들리네.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "쿼터데크에서 선미까지 한 번에 통 다섯 개를 던지자. "+pchar.name+", 우리는 기습의 이점을 가지고 있어. 녀석들은 아직 아무것도 눈치채지 못했지! 그리고 곧바로 우리가 배에 오르기도 전에 떠나버릴 거야.";
			link.l1 = "좋아, 해보자. 우리가 폭약통을 그들의 갑판에 올려놓기 전에는 절대 정체가 들키면 안 돼... 가까이 접근하는 것도 쉽지 않을 거야. 잭맨은 구울만큼 어리석진 않으니까.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "한번 걸어보자, "+pchar.name+"! 아까도 말했잖아, 우리 잃을 게 뭐가 있겠어?";
			link.l1 = "좋은 지적이야... 모두 대기해! 푸가스 준비하고 전투에 대비해!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "자, 내 사랑하는 캡틴... 이제 우리 서로 작별할 시간이야. 내 임무는 끝났고, 이제 이슬라 테소로의 해적 여왕이 되는 데 익숙해져야 해. 내가 삼촌의 뒤를 이을 만한 사람이 되길 바라. 도와줘서 고마워.";
				link.l1 = "그래, 너와 헤어지는 건 아쉽지만, 그게 바로 운명의 장난이지. 이제 내 배에서 일하는 것보다 훨씬 더 중요한 책임이 너에게 있잖아.";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "당신 배에 머물 수 있다면 정말 좋겠어. 당신 곁에... 하지만 그건 불가능해. 행복해야 해, 샤를. 그리고 그 여자는 반드시 당신에게 어울리는 사람이길 바라!";
					link.l1 = "미안해, Helen.";
					link.l1.go = "result_mary";
				} else {
					dialog.text = "정말 이상해, "+pchar.name+"! 나는 이제 막 한 섬의 주인이 되었지만, 이슬라 테소로의 여왕이 된 기분은 아니야... 새로운 브레더런의 수장이 나보다 식민지를 더 잘 다스릴 수 있겠지. 나는 아직 배워야 할 게 많아.";
					link.l1 = "걱정하지 마, 헬렌. 너는 스스로 잘 해낼 수 있는 여자잖아 – 네가 처음 배에 올랐을 때 나한테 그렇게 말했었지.";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "그래도 우리는 친구로 남을 거지, 그렇지?";
			link.l1 = "물론이지... 에렌, 우리는 이슬라 테소로에서 다시 만날 거야. 내가 너를 네 섬으로 데려다줄까?";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "네 말이 맞아... 봐, 네 배에서 항해하면서 내 몫의 전리품을 따로 챙겨뒀어. 이걸 받아, 내 제안을 거절하려고도 하지 마. 나는 네게 빚지고 싶지 않으니까.";
			link.l1 = "이봐, 잠깐만 기다려...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "무슨 말을 하려는지 알아. 그래, 네 도움이 이 보잘것없는 보물 상자보다 훨씬 컸지. 하지만 지금 내 손에 있는 건 이것뿐이고, 꼭 갚아야 해. 받아, 네가 직접 안 가져가면 네 선실에 두고 갈 거야.";
			link.l1 = "이제 혼자 항해할 생각이야? 내가 이슬라 테소로까지 데려다줄 수도 있는데?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("You have received a chest with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "그럴 필요 없어, "+pchar.name+". 내가 직접 섬에 갈 거야. 검과 권총도 있으니, 당분간은 그걸로 충분해... 내가 도착하면 이슬라 테소로의 여왕은 수입 걱정은 안 해도 될 거라고 확신해.";
			link.l1 = "예, 폐하. 새로운 삶에 행운이 있기를 바랍니다.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "그만해, 농담이라도. 나는 여전히 당신에게는 에렌이야. 하지만 그것만 말하려던 건 아니야. 나는 다시 아버지를 찾았어, 좀 이상하긴 했지만. 아버지는 영국 귀족으로서의 명예를 내 유산과 맞바꾸셨고, 그게 마음에 걸려. 영국 연방이 아버지를 쫓고 있고, 나는 당신까지 그러길 원하지 않아,\n "+pchar.name+", 그 일에 참여하기 위해서.";
			link.l1 = "정신 차려, 헬렌! 그는 강도이자 해적이야!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "해적이라고? 그리고 네가 뭔데 그런 말을 하는 거지? 그는 내 아버지고, 그게 내겐 전부야! 그리고 나는, 도적이자 해적인 아버지의 딸로서, 영국 법이 그를 어떻게 생각하든 전혀 신경 안 써. 내 아버지에게 조금이라도 해를 끼치려 한다면, 네가 나에게 해준 모든 좋은 일 따윈 다 잊어버릴 거야, 알아둬. 이걸 경고로 받아들여.";
			link.l1 = "그래? 사실 말인데, 아가씨, 좀 더 예의 바르게 구는 게 좋을 거다. 내가 그 강간범 도노반 놈 손아귀에서 네 예쁜 목숨을 구해줄 때나, 우리가 노획물 이익을 나눌 때는 내 해적 같은 태도에 대해 불평 한마디도 안 하더니!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "나... 미안해. 방금 한 말 취소할게, 용서해 줘. 내가 정신이 없었어... 그래도, 네 친구로 남고 싶어. 하지만 네가 내 아버지를 쫓기 시작하면 그건 불가능하겠지.";
			link.l1 = "알겠다. 하지만 감히 나를 협박하지는 마, 여자야. 내 배에서 함께 항해해 봤으니 이제쯤 알겠지, 나는 누구도, 아무것도 두려워하지 않아. 특히 여자에게서 무례함을 당하는 건 용납 못 해 – 해적 여왕이라 해도 마찬가지다. 내가 신사라 해도 인내심에는 한계가 있지. 이제 이 문제는 끝났다. 안녕히 가라. 행운을 빈다.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "고마워요... 언젠가 다시 만날 수 있겠죠, "+pchar.name+"...";
			link.l1 = "왜 안 되겠어? 앞으로도 이슬라 테소로에 여러 번 갈 거야. 거기서 보자... 잘 있어, 헬렌.";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но её не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашёл Мэри - выбирай, какая девушка милее
			dialog.text = "확실해. "+pchar.name+", 당신이 허락한다면 당신 배에 머물고 싶어요. 당신 곁에 있고 싶어서요...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(메리 선택) 헬렌, 넌 이해하지 못해. 네 앞에는 온전한 미래가 펼쳐져 있고, 걱정할 일은 하나도 없어. 내 앞에 있는 건 전쟁, 정치적 음모, 그리고 완전한 불확실성뿐이야. 넌 네 인생을 스스로 만들어야 해. 내 같은 방랑자는 그 안에 설 자리가 없어.";
				link.l1.go = "result_10";
				link.l2 = "(헬렌 선택) 내가 바라던 것보다 더 큰 일이야, 헬렌. 물론 너를 잃고 싶진 않지만, 네가 이슬라 테소로로 가는 게 너한테 더 나을 거야. 내 운명이 어디로 이끌릴지 누가 알겠어. 지금 내 앞에는 전쟁과 정치적 음모, 그리고 불확실함만이 기다리고 있어.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "내가 바랄 수 있는 것보다 더한 일이야, 에렌. 물론 너를 잃고 싶진 않지만, 네가 이슬라 테소로로 가는 게 너한테 더 나을 거야. 내 운명이 어디로 이끌릴지 누가 알겠어. 지금 내 앞엔 전쟁과 정치적 음모, 그리고 불확실함만이 기다리고 있어.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"! 내게 거짓말하지 마. 그냥 네가 원하지 않는 거잖아... 말해 봐, 그 여자가 누구야? 버려진 배들의 도시에서 온 그 빨간 머리 계집이겠지, 맞지?";
			link.l1 = "헬렌! 나는 네게 가장 좋은 게 뭔지 말해주려고 하는 거야! 어떻게 그걸 이해하지 못하겠어?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "아, 그래, 물론 그렇겠지... 그런데 그 여자가 어떻게 널 홀렸는데, 응? 걔가 *내가* 없는 뭘 가졌길래?! 정말 그렇게 대단해? 에이, "+pchar.name+"... 뭐, 그건 네 결정이니, 난 이제 내 섬으로 돌아갈 수밖에 없어. 너희 둘 사이에 끼어 있을 수는 없으니까\n지금까지 나를 위해 해준 모든 것에 고마워, 샤를. 네가 내가 만난 사람 중에 가장 좋은 남자야. 우리 앞으로도 친구로 지낼 수 있을까?";
			link.l1 = "물론이지... 에렌, 다시 이슬라 테소로에서 보게 될 거야. 내가 데려다주길 원해?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "필요 없어. 새 배를 살 거야. 당신 밑에서 일하는 동안 슈쿠너 한 척을 사고 장비를 갖출 만큼 돈을 모았거든. 다시 새 '레인보우'호를 타고 항해할 거야.";
			link.l1 = "기쁘구나, 헬렌. 그렇게... 알뜰하게 행동해줘서 말이야. 하지만 이슬라 테소로의 해적 여왕이 슬루프나 작은 배를 타고 다니는 건 어울리지 않아. 곧 너만의 프리깃을 가져야지.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "어쩌면, "+pchar.name+". 좋아. 조선소에 갈게, 하지만 먼저... 작별 키스 한 번만 해줘... 제발...?";
			link.l1 = "에렌...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться
		break;
		
		case "result_15":
			dialog.text = "우리가 만난 그 순간부터 내 운명은 당신과 얽혀 있었어. 그걸 아직도 모르겠어? "+pchar.name+"? 나는 세상 끝까지라도 당신을 따라갈 거야!";
			link.l1 = "그럼 네 아버지는? 로렌스 벨트로프? 그는 내 적이야...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "내 아버지는 션 맥아더였어. 나는 아버지를 사랑했고, 그의 죽음을 슬퍼했지. 내겐 오직 한 분뿐인 아버지였어. 그리고 그 해적... 그에 대해선 말하고 싶지도 않아.";
			link.l1 = "헬렌... 내 사랑하는 헬렌!";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", 예전부터 꼭 말하고 싶었어요. 내가 만난 사람 중에 당신이 가장 위대한 분이에요! 당신이 나에게 해준 일들은 평생 갚을 수 없을 거예요. 나는 당신 곁에 있고 싶어요. 영원히요. 당신이 원한다면 결혼하고 싶어요... 사랑해요.";
			link.l1 = "우리는 함께할 거야. 약속해!"; // а куда же ты теперь денешься :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "지금 당장 내 부탁 하나 들어주겠다고 약속해 줄래? 그리고 제발 웃지 마!";
			link.l1 = "약속할게, 내 사랑!";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "진짜 이름으로 불러 줘. 제발!";
			link.l1 = "사랑해, 헬렌 샤프.";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", 자기야... 안아줘! 이 순간을 너무 오래 기다렸어!";
			link.l1 = "에렌, 내 사랑...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// Квест Лонгвея "Путеводная звезда", начало 5 этапа
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! 정말... 대단했어! 어디도 가고 싶지 않아... 아침까지 여기 있자. 세상은 기다릴 수 있어!";
			link.l1 = "기다리게 두자, 헬렌!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
			npchar.SpecialRole = "fgirl";
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Выполнено требование для Дороже золота
			pchar.questTemp.GoldenGirl_Ready = true;
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "선장님! 잭맨이 죽었어요... 이제 제 가족은 드디어 안전한 건가요?";
			link.l1 = "그래, 에렌, 모두 무사해. 하지만 '센츄리온'이 침몰했고, 네 어머니의 무덤을 찾고 이슬라 테소로의 상속권을 증명할 수 있는 모든 문서도 함께 사라졌어... 에휴... 이제 나 혼자서 토르투가를 쳐들어가야겠군...\n";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", 그렇게 걱정하지 마. 우리가 할 수 있는 건 없어. 나도 신경 쓰지 마, 그 섬 없이도 괜찮을 거야. 지금까지 나를 위해 해준 모든 것에 고마워!";
			link.l1 = "...나를 두고 떠나려는 것 같네, 그렇지?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "네, 내 캡틴. 나는 슈너 한 척을 사고 장비를 갖출 만큼의 돈을 모았어요. 다시 내 '레인보우'호를 타고 항해할 거예요. 우리는 블루벨드에서 다시 만나겠죠... 이제 집으로 돌아가려 해요.";
			link.l1 = "음... 행운을 빌어, 헬렌!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "자, 내 캡틴... 우린 실패한 것 같아. 잘 있어. 난 집으로 돌아갈 거야. 당신 밑에서 충분히 돈을 벌어서 새 스쿠너를 살 수 있게 됐거든. 바다에서 다시 만나자!";
			link.l1 = "행운을 빌어요, Helen. 모든 일에 대해 미안해요. 안녕히 가세요.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "선장님! 잭맨이 죽었어요... 그럼 제 가족은 이제 안전한 거죠?";
			link.l1 = "그래, 에렌, 이제 안전해. 하지만 나는 기쁘지 않아. 너무 많은 시간을 잃었고, 이제 이슬라 테소로는 영국 식민지가 되었어. 너는 상속을 잃었으니, 내가 직접 토르투가를 공격해야겠군...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", 변호사가 너한테 뭐라고 했어?";
			link.l1 = "나는 너무 많은 시간을 허비했고, 이제 이슬라 테소로는 영국 식민지가 되었어. 너는 유산도 잃었으니, 내가 직접 토르투가를 공격해야겠군... 아아, 우리는 졌어.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "아니야, 자기야, 그건 안 될 거야.";
				link.l1 = "글쎄, 왜 안 되겠어?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", 오늘은 몸이 좀 안 좋아. 네 잘못 아니니까 미안해하지 마. 오늘은 그냥 하지 말자...",""+pchar.name+", 자기야, 요 며칠 너무 피곤했어. 솔직히 그냥 잠만 자고 싶어. 미안해. 다음에 하자.");
				link.l1 = RandPhraseSimple("좋아...","괜찮아. 원하는 대로 해...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", 분위기가 딱 좋으니, 가자!",""+pchar.name+"그래, 물론이지, 묻지도 따지지도 않아! 가자!");
				link.l1 = RandPhraseSimple("그래, 내 여자지...","헬렌, 정말 사랑스럽구나...");
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("정말 멋졌어, "+pchar.name+"!..","항상 그렇듯이 멋졌어요, 자기야..."),RandPhraseSimple("정말 멋졌어요, 샤를!","정말 즐거운 시간이었어, 자기야!"),RandPhraseSimple("당신과 함께라면 지루할 틈이 없어요, 내 캡틴!","정말 멋졌어, 자기야!"));
			link.l1 = RandPhraseSimple("사랑해...","항상 함께 있어서 좋아, 헬렌...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", 나도 항상 기쁘다는 거 알지... 하지만 지금은 때가 아니야 - 저 악당 티보를 도망치기 전에 잡아야 해.";
				link.l1 = "항상 옳군, 에렌...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "아니야, 자기야, 그건 안 될 거야.";
				link.l1 = "글쎄, 왜 안 되겠어?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", 오늘은 몸이 좋지 않아. 화내지 말아줘. 오늘은 그냥 넘어가자...",""+pchar.name+", 자기야, 요 며칠 너무 피곤했어. 솔직히 말해서 그냥 자고 싶어. 미안해. 다음에 하자.");
				link.l1 = RandPhraseSimple("좋아...","괜찮아. 원하는 대로 해...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", 사랑해! 가자!",""+pchar.name+", 아이 아이, 선장님! 가자!");
				link.l1 = RandPhraseSimple("너는 내 착한 아가야...","헬렌, 정말 아름다워...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "LoveSex_Room_Go");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("그래, "+pchar.name+"?","네, 내 캡틴?","듣고 있어. "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "이것 좀 봐요, 내 캡틴!";
				link.l1 = "이런, 힘이 대단하군! 시간을 허투루 쓰지 않았구나, Helen.";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "자기야, 네가 창녀들을 찾아가는 것에 대해서 말인데.";
				npchar.quest.refusesex = true;
				link.l1 = "뭐라고? 헬렌, 네가 완전히 오해한 거야! 나는 그냥...\n";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "헬렌, 나는 잃어버린 인디언 도시 타야살에 가려고 해. 거짓말하지 않을게: 이 여정은 정말 위험하고, 게다가 우상(아이돌)을 통한 순간이동도 포함되어 있어. 너... 나를 따라올래?\n";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "헬렌, 배에 대한 전체 보고를 해 줘.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "우리가 항구에 정박할 때마다 특정 물품을 사줬으면 해.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "당신의 명에 따라 도착했습니다, 선장님.";
				Link.l2 = "헬렌, 너에게 몇 가지 지시를 해야겠어.";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "웃긴다고 생각해?";
					link.l1 = "멋진 배지, 그렇지? 너를 위해 구했어, 에렌! 생각해 봐, 카리브에서 자기 여인에게 진짜 배를 선물하는 남자가 어디 있겠어, 응?";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "헬렌, 네 조언이 필요해.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "헬렌, 너에게 명령이 있어...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("헬렌, 우리 선실에서 단둘이만 같이 있어요... 몇 시간만이라도. 어때요?","자기야, 우리 둘이서 몇 시간만 오붓하게 보낼까? 그런 생각 어때?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("헬렌, 우리 방 하나 빌려서 둘이서만 몇 시간 같이 보내는 게 어때... 단둘이서. 어때, 마음에 들어?","자기야, 우리 다음 몇 시간을 단둘이 보낼까? 방을 하나 빌리자... 어때?");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "헬렌, 자기야, 선술집에서 함께 시간 좀 보낼 수 있을까?";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "헬렌, 네 숭배자 프란시스의 유언장을 찾은 것 같아. 그는 유산을 너에게 남겼어.";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "이 커틀라스는 이제 네 거라고 생각해. 블레즈는 네 이른바 삼촌이니까...";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "지금은 아무것도 없어, 헬렌.";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "샤를, 자기야, 어디 아픈 거야? 왜, 내가 밑으로 내려가서 창고 쓸고 쥐나 세라고 기대하는 거야?";
			Link.l1 = "알겠어, 미안해 자기야, 내 잘못이야...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "나도 백문의 대형 전열함을 갖고 싶어, 시속 20노트로 달리는 배 말이야. 나도 평생 너처럼 선장으로 살아왔어. 그러니 가서 그 빌어먹을 경리나 찾아가서 귀찮게 굴어.";
			link.l1 = "그래, 헬렌, 네 말이 맞아. 미안해.";
			link.l1.go = "exit";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "잘 듣고 있어.";
			Link.l1 = "우리의 승선 규정에 관해서라면...";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "당신이 지휘하는 그 배에 대해서...";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "아직 아무것도 없어.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "무엇을 원하시나요, 내 캡틴?";
			Link.l1 = "나는 네가 어디에도 승선하길 원하지 않아. 너랑 네 부하들 안전하게 지켜.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "기회가 오면 바로 적선에 올라타 줬으면 해.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "네, 내 캡틴?";
			Link.l1 = "승선한 뒤에 배를 바꾸는 일은 삼가줬으면 해. 저 배는 내게 너무 소중하거든.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "혹시 다른 배에 오를 일이 있으면, 그 배를 잘 살펴봐. 쓸 만한 배라면, 마음껏 네 것으로 가져도 돼.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "좋아, 생각해 볼게.";
			Link.l1 = "생각은 해보겠지... 그래, 내가 명령할 수 있기라도 한 것처럼 말이야.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "좋아, 생각해 볼게.";
			Link.l1 = "그녀가 생각해 보겠지... 그래, 내가 명령할 수 있는 사람이라도 되는 것처럼 말이야.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "좋아, 생각해 볼게.";
			Link.l1 = "생각은 해보겠지... 그래, 내가 명령할 수 있는 사람이라도 되는 것처럼 말이야.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "좋아, 생각해 볼게.";
			Link.l1 = "그녀가 생각해 보겠지... 그래, 마치 내가 명령이라도 내릴 수 있는 것처럼.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "명령이요?";
            Link.l1 = "여기 서 있어!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "나를 따라와, 뒤처지지 말고!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "화기의 탄약 종류를 변경하십시오.";
					Link.l3.go = "SetGunBullets";
				}	
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
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "바로 하겠습니다, 선장님!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "바로 하겠습니다, 선장님!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "여기 있었군! 드디어 찾았어... 정말 대단했어, 내 캡틴! 그렇게 지붕 위를 달리고 숨 막히는 높이에서 뛰어내리는 건 처음 봤어! 심장이 터질 뻔했다니까! 언젠가 당신의 이런 묘기 때문에 내가 죽을지도 몰라, 자기야... 어, 혼자가 아니네... 이 아가씨는 누구야?\n";
			link.l1 = "이분은 캐서린 폭스, 영국의 명성 높은 해상 보병 연대 '씨 폭스'의 지휘관인 폭스 대령의 딸이오. 우리는 그녀를 앤티가로 데려가는 중이오.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "그런가... 환영해, 폭스 양! 아니, 아니, 드 모르 선장의 팔을 잡지 말고, 혼자서도 잘 걸을 수 있잖아! 자, 이제 단정으로 가자 - 여기서 빨리 나가야 해."; 
			link.l1 = "하! 고마워, 헬렌! 너 없었으면 어쩔 뻔했어? 캐서린, 우리 따라와!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "드디어 깨어났네, 자기야! 기분은 어때? 나 정말 심장이 멎는 줄 알았어...";
			link.l1 = "헬렌, 무슨 일이야? 머리가 깨질 것 같아...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "우리가 선장실에 들어갔을 때, 당신은 바닥에 누워 꼼짝도 하지 않고 있었어요. 내 심장이 멎는 줄 알았다니까! 선원들이 당신을 들어 올려 우리 배로 끌고 왔죠—정말 아슬아슬했어요, 갑판에 쓰러져 있던 시체들이 다시 일어나기 시작했으니까요.  
정말 끔찍했어요! 신을 믿게 될 뻔했다니까요! 그 자들은 우리의 칼과 총알에도 전혀 반응하지 않았어요! 우리는 급히 밧줄을 끊고 도망치려 했지만, 그들의 배에서 날아온 일제사격에 우리 배가 크게 손상되어 조종을 잃고 말았죠. 그러더니 그들은 순식간에 돛을 올리고 사라져버렸어요.  
우리 배는 좌초했고, 폭풍이 배를 완전히 파괴하기 전에 이 해안으로 도망칠 수밖에 없었어요. 오늘 많은 좋은 사람들이 죽었지만, 결국 배는 살아남았죠... 내가 배를 버리라고 명령만 하지 않았더라면...";
			link.l1 = "헬렌, 네 잘못 아니야. 그게 옳은 판단이었어. 너 없으면 내가 어떻게 했을까?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "내가 널 배에 끌어올리고 해안까지 데려왔어. 넌 거의 죽은 것처럼 보였고, 심장만 아주 약하게 뛰고 있었지. 봐! 내 손이 아직도 떨리고 있어\n";
			link.l1 = "고마워요, 사랑. 당신에게 신세를 졌네요. 내가 여기 누워 있었던 게 얼마나 됐죠?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "하루 종일 네 상처를 씻고 붕대를 감아주고, 약도 먹이고, 럼주도 좀 부어 넣었어. 이제는 꼭 회복해야 해!";
			link.l1 = "이번엔 안 죽을 거야, 자기야. 하지만 몸이 좀 안 좋아서... 으윽....";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "말해 줘... 진짜 '플라잉 더치맨'이었어, 샤를? 왜 우리를 공격한 거지? 그리고 왜 다가올 때는 사격하지 않고, 배에 올라타자마자 바로 우리를 침몰시키려고 했던 거야?\n";
			link.l1 = "그들의 선장이 그 부적을 필요로 했어. 나는 그걸 투투아타파크라는 인디언 주술사와 이야기했지. 왜 그들이 그걸 필요로 했는지는 모르겠어... 하지만 그들의 우두머리가 부적을 손에 넣자마자 우리를 처리해 버렸어... 전능하신 하느님, 이게 무슨 끔찍한 악몽이람! 살아 있는 시체들이 선원인 배라니! 믿을 수가 없어...\n";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "그래, 이번엔 우리가 '플라잉 더치맨'을 만날 차례였지. 으으! 온몸에 소름이 돋는다! 다음에 들르는 항구에서는 교회에 가서 촛불을 켜고, 우리 주 예수 그리스도께 기적적으로 구해주신 것에 감사 기도를 올릴 거야. 젠장, 너무 고마워서 가톨릭 성인들한테도 기도할 판이야...\n";
			link.l1 = "곧 같이 갈게, 헬렌. 나도 고해성사 제대로 본 지 꽤 됐거든... 하지만 먼저, 저 마을로 돌아가야 해. 투투아타파크에게 모든 걸 말해야 해. 저주받은 그 배가 우리를 공격한 건 바로 그 부적 때문이야! 저 붉은 피부의 악마가 도대체 왜 그 산 자의 시체들이 그걸 필요로 했는지 짐작이라도 했으면 좋겠군.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "좋아. 하지만 조심해야 해 – 네 상처가 아직 다 낫지 않았으니까.";
			link.l1 = "하지만 네가 나 빨리 회복하게 도와줄 거지? 사랑해, Helen...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "나도 사랑해, 내 사랑...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", 한 번 말했잖아, 이제 우리 운명은 함께야. 네 운명이 곧 내 운명이야. 언제 출발하지?";
			link.l1 = "그 말을 들으니 정말 기쁘네. 거기로 가면 조금 있다가 말해줄게. 우리 준비 좀 해야겠어.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "준비됐어요, 내 캡틴! 지구 끝까지라도 따라갈게요!";
			link.l1 = "고마워요, 내 사랑...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "오, "+pchar.name+"! 반갑네! 무슨 일로 이슬라 테소로까지 온 건가?";
			link.l1 = "늘 그렇듯이, 일이지. 그냥 들러서 너도 보고 싶었어. 잘 지내고 있나, 헬렌?";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "우리 사랑하는 총독님께 무슨 일이 있나, 선장? 이번엔 누구 엉덩이를 걷어차야 하지? 스페인 놈들, 해적들, 아니면 더 골치 아픈 놈들?";
			link.l1 = "헬렌, 더 심각해. 훨씬 더. 총독이 값비싼 창녀를 만나러 가는데, 나는 구경거리로 따라가야 해. 총독은 애인에게 진짜 사략선장, 모험가, 바다의 개를 데려오겠다고 약속했거든. 결국 나는 지루한 대화, 터무니없이 비싼 와인, 따분한 귀족들 속에 끼게 생겼지.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "오히려 그 반대야, 상냥한 숙녀가 주최하는 즐거운 사교 모임에 초대받았지. 각하께서 갑자기 동행을 요청하셔서 놀랐지만, 솔직히 말하면 오랜만에 일에서 벗어나 쉴 수 있는 기회가 생겨서 기뻐.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "아이... 그러니까 무시무시한 샤를 드 모르 선장이 저놈들 구경거리로 원숭이처럼 차려입고 춤이라도 추겠다는 거야? 참 귀엽네! 더 좋은 생각이 있어. 그냥 닻 올리고 여기서 당장 벗어나자. 오래 기다린 휴가가 필요하다면, 이슬라 테소로로 가자. 거긴 언제나 우리를 환영해주지. 일광욕, 하얀 모래, 옛 친구들, 럼 펀치, 잡념도 잊고... 뭐든 다 할 수 있어.";
			link.l1 = "있지, 이 모든 게 정말 멋지게 들리긴 하는데, 나도 그러고 싶어... 하지만 나중에. 내가 총독에게 약속했거든, 이 일은 그 노인한테 정말 중요한 거라서...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "그래서 뭐? 네 고귀한 피가 그들에게 무슨 의미가 있다고 생각해? 나는 프랑스 혈통은 아니지만, 그들의 '상류 사회'가 어떤지 잘 알아. 그들에게 샤를 드 모르란, 사람들이 목숨을 맡기고 따르는 선장이 아니야. 그들처럼 신사도 아니지. 진짜 신사라면 바다에 나가 화약 연기 속에서 싸우지 않아. 샤를 드 모르는 그들의 식사에 그냥 호기심을 자극하는 장식품일 뿐이야. 애완 표범이나 멋 부린 집안 흑인처럼! 그냥 화려한 장난감이지! 언제부터 네가 이런 취급을 참고 견뎠어?!";
			link.l1 = "헬렌, 진정하게. 총독이 만족하고 우리 미래가 잘 풀릴 수 있다면 불편한 시선 몇 개쯤은 내가 감당할 수 있어. 힘 있는 친구가 있다는 건 좋은 일이야. 어쨌든, 이건 적함에 올라타는 것보단 훨씬 쉬운 일이잖아! 그리고 저 '쓸모없는 놈들'도 항상 그런 건 아니야. 상류층에도 괜찮은 사람들이 있지... 적어도, 그래야 한다고들 하니까.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "알겠어. (머리를 털며) 하지만 분명히 말해두지, 내가 화려한 드레스를 입는 일은 절대 없어. 억지로 데려가려면, 난 바지 차림으로 갈 거야. 카리브 해의 모든 귀부인들이 기절하든 말든 신경 안 써.";
			link.l1 = "억지로 시키려던 건 아니었어. 우리 둘 다 고생할 필요는 없잖아. 이 파티만 잘 넘기고 나면, 우리는 이슬라 테소로로 항해할 거야. 특별한 선물로, 내가 화물칸에 훌륭한 스페인산 마데이라 한 상자를 아껴 두었지...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "오호호, 샤를! 내가 그렇게 고귀한 분들 곁에 어울리지 못한다는 말이야? 바지 입은 여자가 네 밤을 망칠까 봐 걱정되는 거야? 흥미롭네. 좋아, 그럼 그렇게 해. 하지만 너도 잊지 말고 멋쟁이처럼 차려입어. 화려한 옷을 입은 원숭이도 기생의 마음을 흔들 수 있으니까. 공연 잘 즐겨!";
			link.l1 = ""헬렌, 잠깐만! 젠장... 여자들이란!"\n";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "그래, 우리도 좀 쉴 자격은 있지. 하지만 이런 일로 내가 드레스 같은 걸 입을 생각은 없어. 네 여자가 남자처럼, 선원처럼 입고 다닌다는 소문이 얼마나 멀리 퍼질 것 같아?";
			link.l1 = "아... 그건 별로 좋은 생각 같지 않아. 뭐라고 해야 할까... 여긴 남자들이 아내나 점잖은 숙녀를 데려오는 자리가 아니거든...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "하! 창녀들이랑 타락이라니! 정말 멋지네 - 그러니까 난교 파티에 가겠다는 거였군! 그럼 그냥 대놓고 말하지 그랬어? 내가 질투 많은 계집이 아니라서, 바로 여기서 총 쏘지 않는 걸 다행으로 알아. 적어도 지금은 말이야.";
			link.l1 = "헬렌, 제발, 나는 그냥 우리 총독을 따라가고 있을 뿐이야. 그가 부탁했고, 정말 끈질기게 졸랐어. 창녀 같은 건 절대 없어\n아, 말이 이상하게 나왔네... 내 말은 창녀랑 그런 짓을 한다는 뜻이 아니라... 젠장! 그냥 예의를 갖추러 가는 거야!";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "예의를 갖추러 간다고 멋지게 차려입으시죠, 드 모르 선장. 결국 상류층 모임이잖아요. 칼라랑 커프스도 없이 가면 완전한 스캔들이에요. 난교 파티라도 말이죠. 잘 즐기세요.";
			link.l1 = "헬렌, 기다려! 젠장... 여자란 말이지!";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "커프스랑 칼라, 선장님. 그리고 어쩌면 레이스도요. 다시 유행이라고 들었어요. 하지만 제가 뭘 알겠어요!";
			link.l1 = "오, 헬렌, 제발!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "이것 좀 봐! 우리 사랑하는 내 캡틴, 난장판 끝내고 집에 돌아왔네!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "이 동네 양반들은 아직도 자기네 새 원숭이를 마음에 들어 하더냐? 어젯밤 그 녀석의 활약이 전설적이었다고들 하던데! 배와 창녀를 걸고 내기하고, 귀족 도련님들에게 결투를 신청하고? 도대체 무슨 일이 벌어지고 있는지 좀 설명해 줄래?\n";
			link.l1 = "에렌, 설명하게 해! 그렇게 간단한 일이 아니야. 젠장, 미안해, 하지만 마담 보토의 집에서 밤을 보내게 될 줄은 정말 몰랐어. 거기서 그냥 잠만 잤어, 그래, 혼자였어, 맹세해! 그리고 그래, 카드 게임에서 프리깃함을 땄어. 그게 믿어지니?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "좋아! 너는 대단한 거짓말쟁이거나, 성인이거나, 아니면 바보겠네. 네가 따낸 창녀들과 배 이야기는 나중에 하자—지금은 결투에 대해 전부 말해봐. 그리고 왜 모두가 네가 왕세자에게 결투를 신청했다고 수군거리는지 설명해.";
			link.l1 = "왕세자는 아니고, 그냥 백작의 사생아이야. 꽤 영향력 있는 귀족, 드 레비 방타두르 백작의 아들이지. 있잖아, 내가 먼저 시작한 거 아니야! 그 녀석이 먼저 나한테 결투를 신청했거든. 이제 나는 그의 아버지 분노를 피하려면 너무 심하게 다치게 하지 않고 결투에서 이겨야 해.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "오, '고작 백작의 아들'이라고? 지금 진심이야, 샤를?! 그런데 이걸 어떻게 하자는 거야? 그자가 속이면 어쩔 건데? 널 죽일 수도 있잖아!";
			link.l1 = "이런 이유로 각하께서 나에게 고귀한 증인을 붙여주셨소. 나는 그들만 데리고 갈 것이오. 만약 일이 잘못되더라도, 결투 규칙과 법에 따라 모든 것이 진행되었다는 것을 증명할 수 있으니까. 내가 없는 동안 프리깃함을 잘 지켜주길 바라오.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "정확히 이해한 게 맞는지 확인 좀 하자... 너는 하루 밤낮을 통째로 사라졌다가 카드 게임에서 창녀 하나랑 프리깃함 하나를 땄고, 이제는 죽이면 안 되는 귀족 자식이랑 결투를 벌이려 한다는 거지. 그런데 *나는* 여기 앉아서 그냥 기다리기만 해야 해? 이 모든 걸 두고 내가 무슨 기분이어야 하냐고?!\n";
			link.l1 = "헬렌, 들어봐. 네가 나한테 화낼 만한 이유가 충분하다는 거 알아. 정말 미안해. 하지만 그게...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "있잖아, 나 이제 진짜 지쳤어. 그냥 네 할 일이나 하러 가! 나는 네 선실이나 쓸고 네 더러운 빨래나 할게! 이걸로 끝났다고 생각하지도 마. 끝나면 반드시 얘기할 거야. 네 새 프리깃은 내가 잘 돌볼 테니, 위대한 드 모르 선장님, 걱정 마시지. 아, 그리고 드 모르 선장님, 죽지 말라고... 왜냐면 내가 직접 죽일 생각이거든. 이제 실례할게, 내 방에 들어가서 네 선실에서 찾은 그 좋은 마데이라 한 병이나 마실 거야.";
			link.l1 = "헬렌, 그냥 내 말 좀 들어봐! 젠장... 또 시작이군!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "요즘 파리 유행은 신사라면 배나 여자를 돈 주고 사는 게 아니라 카드 게임으로 따내야 한다고 하더군! 게다가 제대로 멋을 부리려면, 그 전 주인과 결투까지 벌여야 한대. 도대체 이번엔 무슨 말도 안 되는 일에 휘말린 거야, 너?!\n";
			link.l1 = "헬렌, 그게 그렇게 간단하지 않아. 젠장, 미안해, 하지만 내가 마담 보토의 집에서 밤을 보내게 될 줄은 정말 상상도 못 했어! 어젯밤은 정말 지치고 거친 두뇌 싸움으로 변해버렸지. 그리고 그래, 카드로 피투성이 프리깃함 한 척을 땄어. 상상이나 가?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "아주 멋지네. 그럼 창녀도 같이 딴 거야? 그리고 네가 딴 프리깃함은—뭘 걸고 내기했지? 설마 우리 배를 건 건 아니겠지...";
			link.l1 = "어쩔 수 없었어. 봐, 이제 와서 중요하지 않아. 결국 내가 이겼으니까. 내 상대가 나에게 결투를 신청했고, 내가 속임수를 썼다고 비난했지. 그는 엄청나게 영향력 있는 귀족, 드 레비 방타뒤르 백작의 사생아야. 그러니까 내가 그를 죽이거나 심하게 다치게 하지 않도록 최선을 다해야 한다는 뜻이야.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "그 사람도 똑같이 할까? 제정신이야, 샤를? 다른 여자를 위해 네 배를, 네 목숨을 걸겠다고?! 그 여자가 정말 그럴 가치가 있어? 나는 너한테 아무 의미도 없는 거야?!";
			link.l1 = "헬렌, 질투할 이유 없어, 맹세해. 그냥 그렇게 된 거야. 내가 해야만 했고, 총독이 규칙에 따라 모든 일이 진행되도록 귀족 장교들을 증인으로 붙여줬어. 너나 우리 사람들 중 누구도 데려갈 수 없어. 내가 없는 동안 프리깃을 잘 부탁해.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "정말 대단하네! 처음엔 이상한 여자들이랑 난잡한 파티에 가더니, 다음 날 아침에 나타나서도 내가 뭐라 하지도 않았지. 그런데 이제는 카드놀이에서 우리 배를 거의 잃을 뻔했다가 창녀 하나를 땄다고? 그리고 이제 그 여자의 '명예'를 위해 귀족 자식이랑 결투까지 하겠다고? 그것도 죽일 수도 없는 놈이랑! 내가 이 모든 걸 어떻게 받아들여야 하니? 말해 봐.";
			link.l1 = "헬렌, 들어봐. 나한테 화낼 만한 이유가 충분히 있다는 거 알아. 하지만 내 말 좀 들어줘...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "있잖아, 나 이제 정말 지쳤어. 가서 네 그 빌어먹을 결투나 하고 와. 네 새 프리깃은 내가 잘 돌볼 테니, 위대한 드 모르 선장님, 걱정 마. 이제 실례하겠어, 내 방에 틀어박혀서 네 선실에서 발견한 그 훌륭한 마데이라 한 병을 마실 거야. 그런데 네게 무슨 일이라도 생기면, 맹세코 이 마을에 지옥불을 쏟아붓고 이 창녀촌이랑 네가 그렇게 사랑하는 각하의 궁전까지 다 무너뜨릴 거야!";
			link.l1 = "헬렌, 괜찮을 거야, 나만 믿어... 잠깐, 어디 가는 거야?! 젠장! 또 시작이네...";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "샤를, 설명 좀 해 줘야겠네. 대체 무슨 일이 있었는지 말해 줄래? 내가 제대로 감시를 세우지 않았고, 선원들은 술을 마시고 있었어... 그 틈을 타서 어떤 놈들이 우리 배를 습격해서 우리가 자는 사이에 우리를 묶었지. 그 더러운 자식들이 네가 날 구하러 어디까지 올 수 있을지 캐묻더라. 결국엔 날 창고에 가둬버렸어. 내가 얼마나 오래 기다렸는지도 이제는 모르겠어!\n";
			link.l1 = "그 자식이 내가 그에게 안긴 수치에 대해 복수하려고 했어. 네게 무슨 짓이라도 할까 봐 정말 걱정됐어! 무사해서 정말 다행이야!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "날 다시 데려오기 위해 뭔가 해야 했던 거지? 나쁜 짓, 맞지?";
			link.l1 = "중요한 건 네가 다시 내 곁에 돌아왔다는 거야. 내가 너를 지키지 못했어, 에렌. 정말 미안해! 네 마음속에서 나를 용서해줄 수 있기를 바랄 뿐이야!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "이미 했어. 내가 한 말을 곱씹을 시간이 많았거든... 나도 미안해, 샤를. 내가 그 후작과 네 일에 너무 감정적으로 굴지만 않았어도. 그날 밤 경계를 제대로 세웠을 거고, 내가 더 조심했을 텐데. 아! 난 정말 쓸모없는 여자야!";
			link.l1 = "그만 말해, 지난 일은 지난 일이야. 나는 너를 사랑해, 그리고 다시는 너를 떠나지 않을 거야. 약속해!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "내가 당신이 뭘 했는지 굳이 알 필요는 없겠지? 좋아, 다시 함께 있으니 그게 중요한 거야.";
			link.l1 = "당신에게 숨길 비밀은 없어. 다 말해줄게...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "엉망진창이네... 어쩔 수 없었던 건 알지만, 이걸 디 루 파크스랑 그 친구들에게 어떻게 설명할 거야? 이제 너도 범죄자인데!";
				link.l1 = "나는 그 대가를 치르기로 했지만, 사실 선택의 여지가 없었어. 걱정하지 마, 내가 반드시 방법을 찾아서 우리의 명예를 되찾을 거야. 만약 안 되더라도, 우리는 언제나 이슬라 테소로에서 환영받을 거야! 네가 함께라면 나는 뭐든 해낼 수 있어.";
			}
			else
			{
				dialog.text = "정말 대단한 이야기네, 샤를... 네가 어쩔 수 없었다는 건 믿어. 하지만 이제 어떻게 할 거지? 그 영국인이 모든 걸 바로잡을까, 아니면 전쟁이야? 혹시 바스테르에 같이 가서 그 자식이 사슬에 묶이는 걸 직접 보고 싶지 않아?";
				link.l1 = "알지, 에렌. 2주 전만 해도 절대 이런 기회를 놓치지 않았을 거야. 하지만 오늘은, 그 인간은 그냥 지옥에나 가라지! 이제는 그가 정당한 벌을 받든 말든 신경도 안 써. 우리가 다시 함께 있다는 것, 그게 전부야!";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "너도 알잖아, 내가 언제나 너와 함께할 거라는 걸. 하! 우리 둘이 이런 곤경에 빠진 게 처음도 아니잖아. 또 한 번 헤쳐나갈 수 있을 거야.";
				link.l1 = "맞아. 출항하자, 자기야! 지평선이 우리를 기다리고 있어!";
			}
			else
			{
				dialog.text = "네 생각 마음에 들어, 샤를! 이제 귀족은 그만: 프랑스든, 영국이든, 스페인 놈들이든 상관없어. 우리 이제 좀 쉴 자격 있지 않겠어!";
				link.l1 = "좋아. 이제 우리 둘뿐이야! 더 이상 총독이나 귀족 자식들은 없어!";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "예, 예, 선장님!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "정말 멋지게 들리네! 내가 가서 녀석들에게 닻 올릴 시간이 됐다고 말할게! 그리고 샤를...";
				link.l1 = "알고 있어, 헬렌, 나도 곧 합류할게.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "샤를, 결국 해냈구나! 포르투갈 놈들이 전부 말해줬어! 정말 대단한 이야기야!";
			link.l1 = "신이시여, 살아 있었군, 헬렌! 다시 만나게 되어 내가 얼마나 기쁜지 너는 모를 거야!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "그러고 보니 말인데. 나한테 뭔가 얘기해주겠다고 약속했지, 기억나? 뭔가 크고 복잡한 이야기라던데. 지금이 기회야, 선장. 도대체 무슨 일이 있었던 거야?!\n";
			link.l1 = "나는 당신을 사랑해, 에렌. 나머지는 중요하지 않아.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "그래, 그건 도움이 됐지, 하지만... 젠장, 나도 그래, 샤를. 나도 당신을 사랑해. 세상에, 당신이 너무 그리웠어!";
			link.l1 = "나도 그래. 나랑 같이 가, 오늘 밤 이 비참한 마을에 하늘이 무너져 내려도 널 두고 가지 않을 거야.\n다시는 널 떠나지 않을게. 절대로.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "정확히 무슨 일을 했는지는 모르는 게 낫겠지, 그렇지? 그래, 우리가 다시 함께 있다는 게 중요한 거야.";
			link.l1 = "당신에게 숨길 비밀은 없어. 다 말해줄게...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "믿을 수가 없네! 지금 나 때문에 프랑스랑 영국이 전쟁 직전이라고 말한 거야?";
			link.l1 = "아니야, 에렌. 내가 판단을 아주 잘못했기 때문이야. 하지만 널 반드시 데려와서 모든 걸 바로잡아야 했어.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "정말 감동적이고 낭만적인 이야기네. 나도 처음에 어떻게 시작됐는지 잊어버릴 준비가 다 됐을 정도야. 거의 다 됐지. 그런데 진지하게, 너를 체포한 이유가 그 빌어먹을 브리건틴의 이름을 포르투갈 놈들이 잘못 알려줬기 때문이란 말이야?";
			link.l1 = "정반대야, 제대로 된 걸 줬지! 도대체 어떻게 이런 일을 해낸 건지, 그리고 왜 그런 건지 정말 궁금해. 그런데, 그 사람은 지금 어디에 있지?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "그는 떠났어. 나를 여기 데려다주자마자 바로. 네가 이긴 그 창녀의 '환대'는 받고 싶지 않아서, 바르톨로메오에게 방을 빌려 달라고 했지. 그는 돈을 내고 아무 말 없이 사라졌어. 아, 잠깐만, 아니, 사실 네게 남긴 편지는 있었어!";
			link.l1 = "편지라고? 포르투갈인 바르톨로메오한테서 온 거야? 이건 처음이네. 뭔가 불길한데...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "좋아, 나는 여기서 네가 그걸 읽게 두고, 그동안 선원들에게 인사하러 갈게. 분명 걱정하고 있을 거야. 내가 그 우울하고 풀이 죽은 얼굴들이 그리울 줄은 몰랐지! 그동안 또 사고 치지 않도록 조심해!\n";
			link.l1 = "젠장... 아직도 내가 너를 데려왔다는 게 믿기지 않아!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "하얀 모래, 맑고 푸른 바다, 너와 나, 그리고 좋은 와인 – 샤를, 정말 낭만적이야! 우리 이런 산책 자주 같이 하자, 알겠지!";
			link.l1 = "마음에 들어서 다행이야. 이제 이런 시간을 더 자주 가져야겠어.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "샤를, 지금 뭐 하는 거야? 왜 무릎 꿇고 있어? 너무 갑작스럽잖아...";
			link.l1 = "에렌, 나는 당신을 사랑해. 그리고 내게 주어진 모든 날을 당신과 함께 살고 싶어. 그러니 지금, 이 바다와 하늘이 지켜보는 이 자리에서, 나는 당신에게 묻겠소 – 헬렌 비어트리스 샤프, 나와 함께 인간과 신 앞에 서서 죽음이 우리를 갈라놓을 때까지 함께해 주겠소? 나, 샤를 드 모르, 몽페르 기사로서 당신에게 청하오 – 나와 결혼해 주겠소?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "있잖아, 난 이런 격식 차리는 거 원래 별로 안 좋아해. 그래도 세상 끝까지 당신과 함께할 거야. 그리고 네 질문에 대한 답은... 아, 미안, 쏟아버렸네!";
				link.l1 = "신경 쓰지 마, 그냥 포도주일 뿐이고 이 셔츠도 원래 안 좋아했어...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "샤를, 물론이지! 그래, 그래, 또 그래!!! 하지만 우리를 먼지 쌓인 가문의 성에 데려가 평생 순무나 키우며 살게 할 생각은 아니겠지?";
				link.l1 = "음, 우리 집에도 성이 있긴 하지만, 먼지 쌓인 곳은 아니고 거기서 머물 생각도 없어. 우리의 삶은 자유, 그리고 손끝에 닿는 지평선이야!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "그럼 당신을 위해 건배를, 내 캡틴, 내 남편, 그리고 우리의 결혼을 위해!";
			link.l1 = "당신을 위해, 내 사랑! 그리고 우리 함께할 미래를 위해, 우리 앞엔 정말 많은 일이 기다리고 있어요!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "그럼 당신을 위해, 내 캡틴, 내 남편, 그리고 우리의 결혼을 위해 건배해요!";
			link.l1 = "너에게, 내 사랑! 그리고 우리 함께할 미래를 위하여, 우리 앞엔 정말 많은 일이 기다리고 있어!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "그러니까, 브누아 수도원장이 돌아왔고 우리 결혼식을 집전할 준비가 됐대. 하지만 미리 말해두겠는데, 그런 날이라도 난 드레스는 절대 안 입을 거야! 내가 바지 입고 가면 소란이 날까?";
			link.l1 = "헬렌, 어떤 옷을 입어도 난 당신을 사랑해, 그리고 사람들도 곧 괜찮아질 거야. 먼저, 손님들과 결혼식에 대해 당신과 상의하고 싶었어.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "그래, 한 가지 문제가 있어. 우리가 오늘을 함께 나누고 싶은 가장 소중한 친구들 대부분은 도시에 들어오는 것조차 허락되지 않을 거야, 교회는 말할 것도 없고. 그러니 여기서 중요한 사람들만 모아 결혼식을 올리고, 그다음에 이슬라 테소로로 가서 진짜 친구들과 제대로 축하하자. 어떻게 생각해?";
			link.l1 = "좋아! 베누아 아빠트에게 이야기할게. 하지만 초대장도 보내야 하고, 준비할 게 더 많아...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "진정해요, 선장님. 당신의 사랑스러운 미래 아내가 짐의 일부를 함께 질 테니까요! 내가 이슬라 테소로에서 모든 걸 준비하고 친구들에게도 편지를 쓸게요. 그러니 말해봐요, 얼마나 큰 결혼식을 원해요?";
			link.l1 = "너랑 나, 그리고 우리 가장 가까운 친구들만. 마르티니크에서 이런 공식적인 허례허식 다 끝나고 나면, 진짜로 서로 가까워지고 싶을 거야.";
			link.l1.go = "LongHappy_10";
			link.l2 = "모두 이 날을 기억해야 해! 모두 불러 모아! 빠지는 사람 없게 해!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "아늑하고 친근하게 – 내 마음을 읽었군! 샤프타운에 들러야겠어, 내가 모든 걸 준비할게. 럼주 오십 통과 와인 두 다스면 충분할 것 같아. 그리고 음식과 오락을 위해서는 30만 피스 오브 에잇이 필요해.";
			link.l1 = "다시 한 번 말해줘 – 왜 네가 배의 재정을 맡지 않는 거였지? 내가 다 처리할게. 수도원장님께 잠깐 들렀다가 바로 샤프타운으로 출항하자.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "그래, 진짜 바다늑대들처럼 파티를 열고 싶다는 거지? 좋아! 샤프타운에 가서 내가 전부 준비할게. 제대로 준비하려면 럼주 백 통에 와인 오십 통은 있어야 할 거야. 그리고 다른 비용도 최소한 오십만 피스 오브 에잇은 들겠지.";
			link.l1 = "해적 연맹 전부를 초대하겠다는 거야? 이런, 좋아! 내가 보급품을 준비할게. 수도원장님께 잠깐 들렀다가 샤프타운으로 출항하자.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "샤를, 내가 짐 싣는 건 알아서 할 테니, 그다음에 남작에게 초대장을 돌리고 선술집 주인과도 합의 볼게. 오래 걸리진 않을 거야.";
			link.l1 = "걱정 마, 내 사랑, 나는 돈 되는 일이나 하면서 시간을 보낼게... 아니면 그냥 모래사장에서 낮잠이나 잘까. 맙소사, 내 결혼식을 준비하는 것보다 토르투가를 습격하는 게 더 쉬울 줄은 정말 몰랐어.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "좀 쉬었어, 샤를? 좋은 소식과 나쁜 소식이 있어. 나쁜 소식부터 말하자면, 지난주에 현지인들이 너무 신나게 놀다가 그만 '올드 우드페커' 선술집을 홀랑 태워버렸어!\n좋은 소식은, 남작이 우리가 돌아올 때쯤이면 예전보다 더 크고 멋지게 다시 지어주겠다고 약속했어. 내가 준비는 다 해놨으니, 이제 출항할 수 있어.";
			link.l1 = "우리 결혼식이 끝나고 나서 마을에 이런 잿더미만 남기진 않길 바라. 정말 아쉽네, 난 '올드 우드페커'가 꽤 마음에 들었거든. 아늑하고, 친밀하고, 토사물과 밧줄 냄새가 은은하게 섞여 있었지! 뭐, 여보, 네 말이 맞아. 이제 슬슬 가야겠어.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "얀은 이미 글래디스와 함께 마을에 와 있어, 상상이나 해 봐! 내가 결혼식에 그들이 정말 올 거라고는 생각도 못 했어! 오, 맙소사! 우리가 그 끔찍한 인디언 사원 도시에 있었을 때도, 지금만큼 무섭지는 않았는데!\n";
			link.l1 = "다 괜찮아, 자기야, 정말 괜찮아. 나도 걱정돼 – 긴장하는 건 당연하지. 손님들이 이미 도착했으니, 베누아 신부님께 가서 예식이 언제 시작되는지 물어봐야겠어.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "오늘은 정말 길고 힘든 하루가 되겠네... 난 얀하고 글래디스를 보러 갈 거야.";
			link.l1 = "와줘서 다행이야. 스벤손 영감님은 너를 친딸처럼 아끼고, 맥아더 부인도 그 이상이지. 오늘 그분들이 여기 와 있어서 다행이야. 이제 가, 걱정하지 말고 – 모든 게 잘 될 거야.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "그래.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "그래.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "그래.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "나, 샤를 앙리 드 모르, 몽페르 기사로서, 너, 헬렌 비어트리스 샤프를 내 아내로 맞이하여, 오늘부터 앞으로 좋을 때나 나쁠 때나, 부유할 때나 가난할 때나, 병들 때나 건강할 때나, 죽음이 우리를 갈라놓을 때까지 함께할 것을 맹세하오. 하나님의 거룩한 법에 따라, 하나님의 면전에서 이 서약을 하오.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "나, 헬렌 비트리스 샤프는 당신, 샤를 앙리 드 모르를 남편으로 맞이하여, 오늘 이 순간부터 좋을 때나 나쁠 때나, 부유할 때나 가난할 때나, 아플 때나 건강할 때나, 죽음이 우리를 갈라놓을 때까지 함께할 것을 맹세합니다.\n하나님의 거룩한 법에 따라, 하나님의 면전에서 이 서약을 합니다.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "아멘.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "헬렌 비트리스 드 모르, 몽페르 부인이라니 - 아, 이 이름 참 마음에 들어요, 나의 사랑하는 남편!";
			link.l1 = "이보다 더 좋은 말은 못 들어봤어, 내 아내!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "있잖아 – 이게 아무것도 바꾸지 않을 거라고 생각했어, 어쩌면 정말 그럴지도 모르지 – 나는 예전부터 당신을 사랑했고 평생을 함께하고 싶었어. 하지만 오늘, 이 성스러운 예식... 정말 행복해, 샤를! 그 어느 때보다 더 행복해. 글래디스와 얀 좀 봐 – 둘 다 빛나고 있어! 주위에 기쁜 얼굴이 정말 많아! 그런데 – 이제 손님들과 어울리면서 축하 인사도 받아야지. 다 끝나면 돌아와, 잊지 마 – 우리 샤프타운에 가야 해.";
			link.l1 = "바로 할게, 자기야. 가기 전에 뽀뽀 한 번 해줘!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "안녕하세요, 남편. 벌써 손님들과 이야기했어요?";
			link.l1 = "아직 아니야, 참아 줘, 아내, 곧 돌아올게.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "그래, 이렇게 많은 축하 인사를 한꺼번에 들어본 건 처음이야. 그리고 있잖아, 대부분 진심이었던 것 같아!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "그래, 이 귀족들이 의외로 진심이더라 – 솔직히 말해, 나는 더 많은 거짓과 위선을 기대했었지. 아니면 내가 너무 기뻐서 아무것도 못 느끼는 걸지도 몰라. 하지만 어쨌든, 샤프타운에서 우리 친구들이 기다리고 있잖아! 언제 출항하지?";
			link.l1 = "지금 바로. 우리는 독수리의 날개를 타고 친구들과의 연회로 곧장 날아갈 거야. 내 아내여, 오늘 밤을 우리 선실에서 보내는 것, 괜찮겠지?\n";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "아, 그래요, 내 남편, 정말 낭만적이네요! 그리고 그렇게 움찔거리지 말아요, 이제 내가 당신을 사람들 앞에서 마음껏 키스할 권리가 생겼으니까요... 네, 이제 가도 돼요!";
			link.l1 = "항해사, 샤프타운으로 항로를 잡아라. 어떤 이유로도 우리를 방해하지 마! 유령 함대가 덮쳐와도 상관없으니!\n";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "오, 내 사랑하는 남편, 정말 행복해요! 오늘은 정말 멋진 날이에요...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "어서 가자, 샤를. 저 거짓말쟁이는 땅에 닿기도 전에 죽을 거야!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "괜찮아, 샤를, 정말이야. 네이선은 어때?";
			link.l1 = "피가 너무 많아... 대니, 저 사람 숨 쉬고 있어? 숨 쉬는 거 보여!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "더 빨리, 자기야, 시간 낭비하지 마!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "샤를, 괜찮아? 이런 피바람이라니! 미안해, 우리가 위층에 갇혀 있었거든. 저 놈들이 열두 명이나 있어서 먼저 처리해야 했어!";
			link.l1 = "괜찮아, 내가 처리했어. 자크와의 이야기를 드디어 끝낼 수 있어서 기뻐... 결국 그는 자기 몫을 받았지.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "좋아, 내 사랑, 여기서 마무리하고 돌아가자. 네이선 생각이 자꾸 나서 멈출 수가 없어. 그는 괜찮을까? 그가 나 대신 총알을 막아줬잖아!";
			link.l1 = "맞아, 자기야, 나도 걱정돼. 어서 가, 내가 바로 뒤따라갈게.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "마커스를 찾았어! 그는 화물창에 묶인 채로 의식을 잃고 있었어.";
			link.l1 = "살아 있어?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "걱정 마, 자기야, 타이렉스 남작은 우리 모두보다 오래 살 거야. 이제 막 깨어났는데 벌써부터 부산하게 굴고 있어. 럼주, 군도, 그리고 다리를 차례대로 찾으면서 말이야.";
			link.l1 = "저게 우리 마커스지! 우리가 여기 일 마치는 동안 잠깐 쉬게 두자. 그 다음에 해안으로 돌아가자.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "정말 미안해, 자기야... 먼저 우리 충직한 친구 티칭기투, 이제는 지노까지... 바르바존은 그동안 저지른 짓만큼 열두 번은 죽었어야 해!";
				link.l1 = "안타깝게도, 딱 한 번 그렇게 했어. 나도 기분이 좋진 않아... 하지만 우리가 이겼고, 그는 다시는 아무도 해치지 못할 거야.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "지노 일로 너무 마음이 아파, 샤를! 그 소식을 들었을 때, 믿을 수가 없었어! 당신은 괜찮아, 사랑?";
					link.l1 = "나도 믿을 수가 없어... 이렇게 끝나다니... 오늘이 이렇게 될 줄은 정말 상상도 못 했어.";
				}
				else
				{
					dialog.text = "앞으로 역사가들이 프라이버티어 만의 대전투에 대해 기록할까? 해안의 형제단 바론들이 공개적으로 맞붙은 그날 말이야 - 스페인 코스타 가르다 놈들은 감사의 눈물을 훔치고 있겠지! 하지만, 또 우리가 이겼어! 우리 친구들은 살아 있고, 적들은 모두 죽었으니 - 이 얼마나 영광스러운 결혼 선물이냐!";
					link.l1 = "그래, 정말 대단한 축하였지. 하지만 우리가 해냈어, 내 천사. 우리가 해냈어.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "가자, 대니가 마을 변두리에 집을 하나 구해놨어. 지금은 배로 돌아가고 싶지 않아, 청소가 끝날 때까지는 말이야. 앉아서 살아남지 못한 이들을 위해 한잔하자.";
			link.l1 = "그래, 헬렌, 가자.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "지노 일로 너무 마음이 아파, 샤를! 그 소식을 들었을 때 정말 믿을 수가 없었어! 너는 괜찮아?";
				link.l1 = "나도 믿기지 않아... 이렇게 끝나다니... 오늘이 이런 날이 될 줄은 상상도 못 했어.";
			}
			else
			{
				dialog.text = "호크 봤어? 지노가 '위험이 끝났다'고 했을 때 대니가 나를 내보내줬어. 모든 게 잘 끝나서 다행이야. 우리 친구들은 살아 있고, 적들은 죽었으니—이보다 더 영광스러운 결혼 선물이 또 있을까!";
				link.l1 = "나도 그래, 자기야. 그리고 우리가 이겼어. 바르바존은 죽었고, 남은 선원들을 모으려고 바론들이 모이고 있어. 싸움은 끝났어.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "샤를, 너 간신히 서 있는 것 같네. 그런데 내가 선술집에 들렀다가 바텐더한테서 들은 얘길 너 믿지 못할 거야.";
			link.l1 = "그래, 얀한테 들었어. 그도 거기 갔다 왔지. 내 생각엔 우리 친애하는 인디언이 전쟁길에 오른 것 같아. 사보-마틸라 만으로 한번 가보자. 몇몇 사람들이 그쪽으로 그가 떠나는 걸 봤대.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "맙소사! 바로 그거야, 티칭기투! 푸하하, 나 여기서 배꼽 잡고 웃고 있어! 우리 유럽인들도 저런 풍습 좀 받아들이면 안 될까?! 오, 샤를, 너는 지금 당장이라도 쓰러질 것 같아! 자, 다니가 이 근처 변두리에 집을 하나 구해놨어 – 좀 쉬어야지.";
			link.l1 = "앞장서... 저 해변에서 전에 잠든 적이 있는 것 같아.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = "... 괜찮아.";
			link.l1 = "좋은 소식이네.";
			link.l1.go = "exit";
			link.l2 = "정말이야?";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "그래.";
			link.l1 = "좋은 소식이네.";
			link.l1.go = "exit";
			link.l2 = "이봐, 뭔가 마음에 걸리는 게 있잖아!";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "나 완전히 괜찮으니까, 그냥 내버려 둬!\n샤를, 지옥에나 가버려! 감옥도 싫고, 너도 싫고, 이 빌어먹을 섬도 싫어! 당장 여기서 데리고 나가!\n미안해... 나 정말 감옥이 싫어, 건들지 마!";
			link.l1 = "미안해. 우리 모두 두려워하는 게 있지.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "아아아! 여기서 내보내 줘! 샤를, 뭐라도 해봐!";
			link.l1 = "정신 차려!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "내 캡틴, 적이 2층 갑판 선체를 뚫고 올라와서 승선대를 내렸어요. 배 전체에서 전투가 벌어지고 있고, 대부분의 포병들이 쓰러졌어요! 우리 선원들과 에르퀼을 구해야 해요! \n직접 가실 건가요, 아니면 제가 갈까요?";
			link.l1 = "이번엔 내가 직접 갈게, 헬렌! 네가 배를 맡아서 여기서 빠져나가!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "알겠어요, 내 캡틴. 절대 실망시키지 않을게요, 그리고 꼭 조심하세요!";
			link.l1 = "알고 있어, Helen. 너도 조심해!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "승리예요, 내 캡틴! 상륙 부대는 전멸했고, 적은 후퇴를 선택해 남쪽으로 향했어요. 배 상태는 양호해요. 선원들은 모두 살아 있습니다: "+GetCrewQuantity(pchar)+" 사람들. 보고 완료!";
			link.l1 = "고마워, 헬렌, 그리고 뭐...";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "벗겨 줘요, 승리자님. 당신의 상은 나를 마음껏 원하는 대로 하는 거예요!";
			link.l1 = "어...";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "가자!";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "오, 안녕, 에르퀼. 미안, 지금은 좀 곤란한 때에 찾아왔네! 그래도 네가 살아 있고, 또 남의 피에 흠뻑 젖어 있는 걸 보니 정말 반갑다. 너한테 딱 어울리는 모습이지, 그치!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "글쎄, 에렌, 너 정말 대단하구나!";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "아직 시작도 안 했어요, 내 캡틴. 우리 축하할까요?";
			link.l1 = "설득 따위 필요 없어!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "보지 마, 보지 마, 보지 마... 여긴 또 다른 세계야, 내 캡틴! 이럴 리가 없어!";
			link.l1 = "이제 여기가 우리 세상인 것 같아, 자기야. 그리고 네 말이 맞아, 머뭇거리지 말자...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "이 전염병 때문에 네 여자들이 힘들어하고 있는 것 같군, 로드리고. 뜨개질이라도 시켜서 바쁘게 해 줘!";
			link.l1 = "이 대화는 분명히 아무 소용도 없군. 우리 내일 교회에 가기로 했잖아. 기도하러... 물론이지.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "자랑스러워요, 내 사랑!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "그래, 샤를...";
			link.l1 = "또 무슨 생각해, 헬렌?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "카리브에서 가장 스캔들한 커플이 섬 두 개를 소유하고 있다니! 내 해적 소굴인 이슬라 테소라와 네가 약속받은 땅까지 - 문명이 결국 서인도에 닥치면, 그 두 곳이 얼마나 오래 버틸 수 있을 것 같아?\n";
			link.l1 = "우리 평생을 함께하기에 충분히 길지, 자기야. 그리고 그 다음엔? 그때 무슨 일이 일어날지는 우리가 어쩔 수 없어. 다른 사람들이 우리의 이야기를 전하겠지. 가장 중요한 건 지금 여기서 너와 내가 함께, 그리고 행복하다는 거야.";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "행복 얘기가 나와서 말인데... 이제 위층으로 올라가려 해. 촛불도 켜야 하고, 침대도 정리해야 하고, 어쩌면 일기장에 글도 좀 써야겠지...";
			link.l1 = "나는 여기서 좀 더 있다가, 곧 위로 올라가서 당신이랑 ‘침대를 만든다’는 걸 도와줄게.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "너무 오래 걸리지 마...";
			link.l1 = "";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "정말 그렇게 바쁜 거야? 아쉽지만, 이해해. 나도 다른 일로 시간을 보내면 되지.";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "기억해줘서 기뻐. 정말 고맙다는 말을 하고 싶었어. 매일 누군가가... 알잖아, 그런 데서 구해주는 건 아니니까. 술 한잔하러 가자. 내가 살게.";
			link.l1 = "헬렌... 글래디스가 뭐라고 할까?";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "아주 웃기네, 샤를. 가자, 그리고 나 좀 그만 귀찮게 해.";
			link.l1 = "이거 데이트야?";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "가고 있어, 짜증낼 필요 없잖아.";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "하하! 네가 바라는 대로 될 줄 알아? 내가 완전히 취해야만 그럴걸!";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "이제 좀 낫네.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "... 그녀는 미덕이 많았지만 술은 전혀 못 마셨지. 우리가 그렇게 만났어.";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "... 아버지께서 군 복무를 고집하셨어. 나도 결국 굴복해서 추천서를 들고 파리로 갔지. 하지만 지정된 주소에는 끝내 가지 못했고, 대신 화가가 되었어.";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "아, 이제 무슨 미덕을 말하는지 알겠네. 그녀 이름이 뭐였지?";
			link.l1 = "루루.";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "루루... 네 얘기 듣고 나니까 파리가 완전히 망가졌어. 원래는 호화롭게 사는 도시인 줄 알았는데, 그냥 거대한 고급 사창가처럼 들리잖아.";
			link.l1 = "너는 사창가를 비난하나?";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "네, 선장님, 그리고 저는 그런 곳을 찾는 남자들을 이해하지 못하겠어요.";
			link.l1 = "(잔을 응시한다)";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "(심하게 기침한다)";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "어... 사람마다 다르니까... 그런 거겠지?";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "(웃음) 하! 네 얼굴 좀 봤어야 했는데! 겁먹었어? 한 잔 더 하자! 파리 만세!";
			link.l1 = "파리로!";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "(웃음) 너, 너라고?! 예술가라고? 그러니까 영국 함대의 자랑이자 미남, 강간범이자 개자식 도노반이 파리 출신 예술가 손에 죽었다는 거야? 아, 네가 순백색 자보를 차고 승선했더라면, 지팡이로 그 쓰레기를 두들겨 팼으면 더 재밌었을 텐데!";
			link.l1 = "그래, 정말 안됐지. 그날따라 jabot이 세탁 중이었거든.";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "(웃음) 고마워요, 샤를. 오늘 밤이 앞으로 어떻게 흘러갈지는 모르겠지만, 이미 멋진 저녁이에요. 어쩌면 내 초상화도 그리게 해줄지도 몰라요. 하지만, 주의해요. 파리 아가씨들 그렸던 그 방식으로는 안 돼요!";
			link.l1 = "하! 내가 너를 그려주겠다고 동의해야 말이지.";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "실례해요, 내 캡틴, 당신의 모험담과 귀족... 양쪽 성의 기생들의 삶을 듣고 있자니. 상어가 나를 물어가라지, 당신이 그 시간에 더 가치 있는 일을 못 찾았다는 건 도저히 믿을 수 없어! 온종일 캔버스에 물감이나 바르고 아버지 돈이나 탕진했다고 감히 말하지도 마요. 그게 사실이었다면 우리랑 하루도 못 버텼을걸.";
			link.l1 = "나는... 다른 일에 몰두하고 있었어.";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "";
			link.l1 = "나는 궁정 생활과 군 복무를 병행했어. 하지만... 헤헤, 물론 아버지가 원하던 방식은 아니었지. 창문으로 몇 번 도망치고, 한 번 싸움질을 한 뒤에는 근위대랑 친구가 되었거든. 그리고 자연스럽게 많은 걸 배웠고, 몸도 단련됐지. 선배들은 나한테 맞는 법, 갑옷 입는 법, 검 다루는 법, 그리고 제대로 쉬는 법까지 가르쳐줬어. 마지막이 특히 내 취향에 딱 맞았지, 물론. 믿기 힘들겠지만, 아침부터 정오까지 검을 휘두르고, 정오부터 다음날 아침까지 술 마시는 걸 아무나 할 수 있는 건 아니야.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = "";
			link.l1 = "수도에서 평판도 안 좋고 주머니도 빈 귀족이 첫날부터 아버지의 추천서까지 잃어버렸을 때, 그게 쉬웠을 것 같아? 나 자신을 증명해야 했고, 아무도 날 우습게 보지 못하게 해야 했지. 집에서 배운 검술은 잊지 않았고, 삐딱하게 쳐다보는 놈마다 결투로 응수했어. 그러다 보니 점점 재미를 붙이게 됐지. 그래도 한 번도 사람을 죽인 적은 없었고, 나를 끝장낼 만한 노련한 검객을 만나기 전에 파리를 떠나는 데 성공했어.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = "";
			link.l1 = "묘지에서 시간을 많이 보냈어. 나쁘게 생각하지 마, 내 사교계에서는 그냥 유행하는 놀이였거든. 용기를 시험하려고 밤에 묘지에 가서, 울타리에 빈 병을 올려놓고, 시간 재면서 그걸 쏘곤 했지. 아침이 되면 탄환 백 발이랑 샴페인 한 상자를 허비하곤 했어. 지금은 그런 행동이 부끄럽지만, 그땐 이기면 두둑한 상금에 궁정 숙녀들의... 호의까지 받았거든. 뭐든 다 써먹었지—화약 혼합도 조금 만져봤고. 그런데 왜 우리 중 아무도 종이 탄약 만드는 법을 배우려 하지 않았는지, 그건 아직도 모르겠어.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "공부도 했고, 꽤 열심히 했지 – 소르본에 들어갈 뻔하기도 했어. 사무실에서 일하다가 지겨워져서, 결국 이것저것 다 해봤지. 선생님은 우리 아버지의 오랜 친구였는데, 이론보다 실전을 더 중시했어. 그래서 파리의 온갖 모습을 직접 보고, 도둑놈부터 귀족까지 별별 사람들과 얘기도 해봤지. 그 모든 경험이 여기서 다 쓸모가 있더라고.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "그리고... 그게 다야? 아직도 네 안에 뭔가 남아 있네, 내 캡틴. 네가 아직 스스로도 못 본 무언가가. 너를 위하여!";
			link.l1 = "좋은 건배다!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = "";
			link.l1 = "네 이야기 좀 들려줘, 헬렌. 내가 수도에서 겪은 모험 따위는 삼십도 안 된 여자가 백 명을 거느리고 슈쿠너를 지휘한 것에 비하면 아무것도 아니야.";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "서른도 안 됐다고, 그렇지, 샤를? 그렇게 대담하게 말했으니 다음 술값은 네가 내야 해! 내 부하들은 전부 죽었고, 나는 더 이상 스쿠너의 선장이 아니야. 솔직히, 내가 다시 배를 지휘할 수 있을지조차 모르겠어.";
			link.l1 = "미안해, Helen. 일부러 아픈 데를 건드리려던 건 아니었어. 그런데 왜 네가 선장으로서 끝났다고 생각하는 거야?";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "내 선원들은 다 죽었고, 다른 선원들은 날 절대 받아주지 않을 거야. 에이! 좋아, 내 캡틴, 당신은 당신 인생 이야기를 많이 해줬으니 이제 내 차례야! 진실은 이 잔 바닥에 있지 않으니, 이제 미스터리는 집어치우자고.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "내 경우는 특별해, 샤를. 내 아버지는 이 일대에서 손꼽히는 선장이셨고, 숲의 악마에게도 크게 신임받았지. 그의 선원들은 아버지를 숭배했고, 아버지는 나를 자기 목숨보다 더 사랑하셨어.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "이 중 하나라도 없었다면, 아버지는 나를 런던으로 보내 문명 속에서 살게 했거나, 아니면 어머니처럼 여기서 시들어가게 내버려 뒀을 거야. 처음엔 모든 게 잘 풀렸지. 나는 자유를 원했어, 진짜 자유를. 샤를, 충성스러운 선원들과 함께 전함을 능숙하게 지휘하는 것, 그게 바로 진정한 자유를 주거든. 아버지는 자신이 해줄 수 있는 모든 걸 내게 주셨어. 열두 살 때 아버지와 함께 바다로 나갔고, 처음 여섯 달은 선창에서 쥐를 쫓으며 보냈지. 그리고 나서야 선원들과 함께 일할 수 있게 허락받았어.";
			link.l1 = "션 맥아더가 너를 배쥐로 만들었다고? 미안해, 헬렌, 하지만 그건 돌이킬 수 없는 일이야! 선원들은 너를 어떻게 받아들였어?";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "음, 좋은 이야기거리로 좀 과장했을지도 모르겠네? 아버지의 선원들은 날 받아줬어. 아버지는 훌륭한 사람들을 모으셨거든. 하지만 그때 이후로 난... 선창이나 좁고 어두운 공간이 전부 무서워졌어. 하! 스벤손이 그 사실을 알고 아버지를 거의 죽일 뻔했지!";
			link.l1 = "그는 너에게 중요한 사람이야. 분명히 네 운명에 션 못지않게 큰 역할을 했지.";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "그래. 모든 바론들이 내 아버지에게 대놓고 바보라고 했지만, 내가 돛대 오르기에서 선원 기록을 깼을 때, 포레스트 데빌만은 아버지에게 인정을 표하고 악수를 해 주셨어. 그 순간은 평생 잊지 못할 거야: 선원들의 환호성, 그리고 어디를 봐도 끝없이 펼쳐진 바다의 수평선. 그리고 아버지의 그 인정하는 시선—직접 볼 수는 없었지만, 온 마음으로 느낄 수 있었어.";
			link.l1 = "내 승리는 과달루프로 가는 첫날, 내가 돛대에서 떨어지면서 끝나 버렸어.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1+" 내 키잡이 델뤽도 아주 의미심장한 표정을 지었어."}
			link.l1.go ="drinking_my_background_7";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "아하하! 상상할 수 있지! 걱정 마, 그건 오래전 일이야. 이제 너는 진짜 바다늑대잖아!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "우리의 승리를 위하여!";
			link.l1 = "들어라, 들어라!";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "... 그리고 나는 점차 계급이 올라가면서, 아버지와 장교들이 모이는 선장 회의에도 참석하게 되었어. 많은 걸 배웠지. 열다섯 살 때부터 군사 원정에 데려가더니, 첫 전투에서 사람을 죽였어. 정말 끔찍한 원정이었지; 월요일에 출항하는 게 아니었는데... 정말 그러지 말았어야 했어!";
			link.l1 = "열다섯 살에? 헬렌, 너 정말 나를 놀라게 하는구나.";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "무슨 일이 일어났는지도 제대로 이해하지 못했어. 네덜란드 상인에게는 선봉대가 있었지 - 바로 동인도 회사의 용병들이었어. 그 자들이 대담하게 나와서 우리 선미 갑판을 역습했지. 그런데 나는, 바보처럼, 내 목숨도 아랑곳하지 않고 금발 머리를 내밀었어. 바로 그 순간 권총 개머리판에 얻어맞았지. 하지만 그 직전에, 내 레이피어를 회사 놈 하나한테 꽂아넣는 데는 성공했어.";
			link.l1 = "맙소사, 그럼 션은 어쩌고? 그런 일 있었는데도 널 배에서 내쫓지 않은 거야?";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "내 아버지도 그 전투에서 멀쩡히 살아남은 건 아니었어, 그리고 내 멍청하고 깨진 머리를 보는 것도 그분께 전혀 도움이 안 됐지. 아버지는 서서히 기력이 쇠해졌고, 아마도 나 말고는 아무도 눈치채지 못했을 거야. 그리고 결국 돌아가셨어. 유언장에 따라 나는 레인보우호와 그 선원들, 그리고 1년 동안 배를 유지할 수 있을 만큼의 자금을 물려받았어.";
			link.l1 = "그리고 선원들이 너를 선장으로 받아들였어?";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = "우리는 동화 속에 살고 있지 않아, 내 캡틴. 아버지의 유언을 못마땅하게 여긴 이들도 있었지 – 상황이 좋지 않게 흘러갔어\n만약 무지개호의 선원 한 명이라도 내 지휘를 거부하고 떠났다면, 내 명성은 끝장이었을 거야. 하지만 스벤손이 나서서 모두를 바로잡아줬지. 그때는 아무도 대놓고 배를 떠나지 않았어... 그땐 그랬지. 7년 동안 나는 내 보물을 지휘하며, 숲의 악마를 위해 수상한 물건을 나르고, 보물을 찾아다니고, 살아 있었어... 하지만 이제, 그 모든 건 과거야.";
			link.l1 = "예전에는 아니었지. 하지만 나는 네가 다시 네 깃발 아래에서 항해할 운명이라고 믿어! 그걸 위해 한잔하자!";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "우리가 배는 되찾지 못할지라도, 네 레이피어는 아직 네 곁에 있잖아.";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "있잖아, 그렇게 말하니까 나도 믿게 되네. 마시자!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("Naval Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "하지만 내 레이피어가 나에게 행복을 가져다줄까? 그 답은 아마 이 머그잔 바닥 어딘가에 있겠지. 마시자!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("Personal Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "유럽에서의 당신 삶에 대해 생각해봤어요... 봐요, 당신은 도시 멋쟁이고, 나는 그냥 평범한 여자일 뿐이지만, 우리는 이미 세상에서 가장 위험한 곳에서 이름을 알렸잖아요.";
			link.l1 = "건배 제안 같네! 그런데 우리를 하나로 묶는 무언가가 있을까?";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "음, 나는 아버지의 어깨 위에 서 있지. 너는 어떤지 모르겠지만, 네 가족도 너에게 못지않은 영향을 주지 않았을까? 아직 네가 그걸 깨닫지 못했을 수도 있겠네?";
			link.l1 = "감옥에서 내 사랑하는 오빠를 꺼내고 나서 물어볼게.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "자, 이제 끝났어요, 내 캡틴. 서로 이야기 나눴으니, 이제 잘 시간이네요.";
			link.l1 = "흠, 오늘 밤이 이렇게 끝나길 바라진 않았는데.";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "밤은 아직 끝나지 않았어. 게임 하나 제안하지. 패를 잘 쓰면, 네 소원이 이루어질지도 몰라.";
			link.l1 = "우리 카드놀이 할 거야? 나도 끼워 줘!";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "진정해, 바다의 늑대. 너랑 스트립 포커는 안 할 거야.";
			link.l1 = "그래, 헬렌. 여기선 우리만의 시간이 전혀 없군.";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "그게 우리가 없는 유일한 건 아니야, Charles... 카드 게임은 아니지만, 걱정 마. 네가 이런 건 달인일 것 같으니까. '내가 한 번도 안 해본 것' 게임, 들어본 적 있어?";
			link.l1 = "익숙하네. 전생에서 들었던 것 같아. 그리고 자주 연주해?";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "항상 해보고 싶었지만, 같이 놀 사람이 없었어.";
			link.l1 = "우리 첫 술자리치고는 꽤 대담한 게임이네. 정말 괜찮아?";
			link.l1.go = "drinking_game_5";
			link.l2 = "그런데, 모두 어디 갔지? 우리 둘만 여기 있는 거야?\n";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "그래, 최근 일들 때문에 나도 좀 살아봐야겠어. 바보 같은 짓이라도 해보고 싶거든, 알지?";
			link.l1 = "아니, 항상 나쁜 결말이 나, 룸바.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "시작하자! 숙녀 먼저!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "다 집에 돌려보냈어 - 외부인들이 듣게 둘 필요 없으니까.";
			link.l1 = "아니, 항상 끝이 안 좋아, 룸바.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "가자! 숙녀 먼저지!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "아쉽지만, 네 말이 맞을지도 모르겠네. 그럼 한 잔 더 할까?";
			link.l1 = "시작하자! 숙녀 먼저!";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "내가 다 준비해뒀어 - 위층 방은 네 거야. 원래는 프랑스의 어떤 중요한 장교가 쓰고 있었는데, 숲의 악마 녀석들이 정중하게 비워 달라고 했지. 가서 좀 쉬어. 내가 널 이 상태로 거리에 내보내거나, 더 나아가 바다로 나가게 두진 않을 거야.";
			link.l1 = "네, 마님!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "하! 힉! 그럼 네가 먼저 시작하는 거네!";
			link.l1 = "조심해, 자기야! 흠. 선창에서 쥐를 쫓아본 적은 한 번도 없는데!";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "그런 거였어? 너랑 있을 땐 방심하면 안 되겠네! (술을 마신다)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "으으! 그 기억만 해도... 자, 각오해, 잘생긴이: 나는 아직 한 번도 돛대에서 떨어진 적 없어!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "잘했소! 내가 한 잔 올리겠소, 아가씨! (잔을 든다)";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "나는 미신을 믿어본 적이 없어.";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "그리고 네가 자신을 선원이라고 부르다니! 우리가 어떤 사람들인지 너도 잘 알잖아. 항해가 우리에게 무엇을 가져올지, 언제 어디서 육지를 볼 수 있을지, 아니면 아예 볼 수나 있을지 아무도 몰라. 지도나 항해 도구만으로는 답을 찾을 수 없어! 네 건강을 위하여! (술을 마신다)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "직접 그린 아가씨들은... 결과를 마음에 들어 했어?";
			link.l1 = "그림을 항상 좋아했던 건 아니지만, 음... 결과만큼은 늘 좋아했지.";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "샤를! 그때 우리가 만났다면, 난 너를 쏴버렸거나 몸값을 노리고 인질로 삼았을 거야. 그리고 참고로, 난 한 번도 붓을 들어본 적 없어.";
			link.l1 = "이봐! 뭐야, 그건 정말 진부하잖아. 헬렌 양, 내가 당신이 한 번도 해본 적 없는 것들을 나열하기 시작하면...";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "좋아, 알겠어, 정정당당하게 할게. 이제 네 차례야, 내 캡틴.";
			link.l1 = "(홀짝) 힉! 흠... 내 모델이 권총 손잡이로 내 머리를 때린 적은 한 번도 없었는데.";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "(홀짝) 으으. 우리 이 게임 완전히 잘못하고 있네, 자기야. 나는 같이 술 마시면서 서로 알아가는 줄 알았는데, 대신에 서로 쏘아붙이고... 그리고... 힉. 젠장!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "더 흥미롭게 만들어 보자! 그리고 가능하면 한 시간 전에 얘기했던 것 말고 다른 걸로 하자!";
			link.l1 = "술 마시고 난 뒤에 낯선 곳에서 깬 적은 한 번도 없어.";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "아야! 젠장, 샤를! (마신다)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "나... 힉... 믿을 수가 없어. 인정해, 잘못했어 - 작은 룸바가 술을 좀 마시긴 했지. 하지만 감옥에 들어간 적은 한 번도 없어!";
			link.l1 = "어떻게 한 거지...?";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "하하하! 마셔라, 마셔!";
			link.l1 = "이걸 후회하게 될 거야. (마신다)";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "어서 와, 내 사랑. 마지막 질문이자, 날 이길 수 있는 마지막 기회야!";
			link.l1 = "아니... 나... 바람 좀 쐬자.";
			link.l1.go = "drinking_game_enough";
			link.l2 = "나 술은 자주 마셔봤지만, 이런 식으로는 처음이야... 여자랑 이렇게 취해본 적은 한 번도 없어. 맹세코, 술 마시는 건 정말 큰 죄야...";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "에!";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "자, 잠깐만... 너 술 안 마시는 거야?";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "아-하-하! 정말 웃기네! 내 캡틴, 너 참 큰 꿈을 꾸는구나. 좋아... 힉!... 너도 알아둬...";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "나는 온통 남자들뿐인 선원들 사이에서 살아야 하는 불운을 겪고 있어, 늘 조심스럽게 행동해야 해. 나는 정직한 여자야.";
			link.l1 = "나, 나 정말 기뻐, 에-에렌.";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "내가 이겼으니 더 기쁘겠지! 하지만 솔직히, 나도 남자랑 이렇게까지 취해본 건 처음이야.";
			link.l1 = "(말없이 술을 들이킨다) 너를 위해. 축하해... 히끅...";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "이봐-이봐-이봐! 선장, 어디 가는 거야? 혹시 기분 상했어?";
			link.l1 = "나, 나 잠깐... 쉬어야겠어? 그냥 내 검 좀 찾으러 갈게...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "캡, 준비됐어? 이제 돌아갈 수 없어. 뭔가 잘못되면, 나랑 결혼해야 할 거야.";
			link.l1 = "휴! 숨 좀 돌리게 해 줘! 정말 이대로 해도 괜찮겠어, Helen?";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "그래, 젠장, 그리고 거기서 말뚝처럼 서 있지 말라고! 오늘 밤만이라도, 잠시라도 다 잊고 싶으니까!";
			link.l1 = "오늘 밤이 지나면 내가 오히려 도망치고 싶어질 것 같아. 우리 온 마을을 깨우기 전에 가자.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "캡, 열쇠 가져가서 위층으로 올라가. 거기 상자가 있을 거야; 스벤손이 가지고 있을 때 봤을 거다. 통 챙기고 바로 돌아와.";
			link.l1 = "잠깐만요, 자기야, 내가 왜 네 상사를 털어야 하지?";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "바보 같은 소리 하지 마. 난 어릴 때부터 여기 있었어. 주인이 돌아온다 해도 내가 알아서 처리하고, 너도 덮어줄 수 있어. 자, 이제 겁먹지 말고 물러서지 마!";
			link.l1 = "칼처럼 날카롭군, 진짜 밀수꾼이네! 잠깐만, 금방 끝낼게.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "알겠어?";
			link.l1 = "당연하지! 내가 비운 보물상자는 이번이 처음도 아니고, 마지막도 아닐 거야!";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "너 정말 자랑스러워! 하하! 일류 아일랜드 위스키, '부쉬밀스'야! 이런 술은 선술집에서도 안 내올걸.";
			link.l1 = "좋은 생각이긴 한데, 스벤손이 없어진 걸 눈치채지 않을까?";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "그 사람은 분명 눈치챌 거야, 하지만 자기가 마시지는 않아. 그 술은 해적 친구인 도드슨에게 선물로 주려고 아껴둔 것 같아. 그런데 도드슨은 사라졌거나 누군가를 죽였다는 소문이 돌아...";
			link.l1 = "정말 끔찍하군! 그런 재능이 헛되이 사라지면 안 되지. 통을 챙겨, 그리고 분위기 좀 바꿔보자!";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "잘 말했어, 캡틴. 그런데 한 가지 더 묻지. 혹시 그 상자에서 다른 것도 가져갔어? 솔직하게 대답해.";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "뭔가 가져갔지, 습관처럼 말이야, 알지.";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "아니. 내가 해적인지는 잘 모르겠지만, 도둑은 절대 아니야.";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				Notification_Approve(false, "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "왠지 너를 믿게 되는군... 내가 참 바보지!";
			link.l1 = "";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "가서 혹시라도 뭔가 가져간 게 없는지 확인해 봐.";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "이봐, 이봐, 자기야! 집중해! 바닷바람에 입맞춤한 내 얼굴, 여기 있잖아!";
			link.l1 = "휴, 그런데 네 복장 정말 대단하네! 천값은 엄청 아꼈겠는걸. 그리고 나는... 딸꾹! 별별 걸 다 봤거든! 그런데 이건... 이건 내가 본 것 중에 최고야.";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "다들 그렇게 말하지만, 이상하게도 난 너를 믿고 싶어져! 정말 진심이야?";
			link.l1 = "글쎄, 물론 당신의 몸매를 아주 돋보이게 해주긴 하지만...";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "아, 이제 네가 다 망쳐놨잖아!";
			link.l1 = "... 하지만 평민들 사이에서는 분명 경외심을 불러일으키겠지!";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "이런 더위에 평민이든 귀족이든 모두가 무거운 유럽식 옷을 입는 이상한 풍습이 정말 신기해 보여. 그래서 우리 마을이 더 우스꽝스러워 보이기도 하고... 나는 내 옷차림이 마음에 들어, 샤를. 이 옷을 입으면 내가 아름답다고 느껴지거든, 그리고 그건 여자에게 중요한 일이야.";
			link.l1 = "그 옷이 없어도 헬렌, 당신은 여전히 아름다울 거야.";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "조심해요, 내 캡틴! 그렇게 달콤한 말을 하면 가엾은 소녀가 타락할지도 몰라요!";
			link.l1 = "그녀가 반대하지 않으면, 나도 반대하지 않아.";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "히히! 다른 걸 물어보는 게 좋을 거야. 네가 호기심 많아질 때가 난 좋아.";
			link.l1 = "그럼 당신 의상에 대해 한 가지 물어볼게. 그런 차림으로는 바다의 사내들이 선장을 진지하게 보지 않을 것 같은데.";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "그리고 대체로 바다의 사내놈들이 여자를 선장으로 받아들일 리 없으니, 내 옷차림이 문제를 더 키우진 않았을 거야. 아니면, 아직 새 옷이라 그런지 문제를 일으킬 시간도 없었을지도 모르지. 이 옷, 내가 직접 바느질해서 만든 거야!\n아하하! 예전엔 나도 그런 걸 입었었지... 뭐라고 하더라? 우리 군인들은 아직도 그걸 입잖아! 으으... 지금은 그런 옷만 봐도 속이 울렁거려.";
			link.l1 = "제복?";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "아, 맞아, 제복이야! 빨간 제복! 저 남자가 입고 있는 것처럼.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "아, 미안해요, 소령님. 사과의 뜻으로 좋은 아이리시 위스키 한잔 대접할게요... 힉!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "샤를이 곤란해지진 않겠죠, 소령님? 제발 아니라고 말해 주세요, 네?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "정말 기뻐! 한잔하자!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "으, 이것 좀 봐!";
			link.l1 = "헬렌... 설마 그걸로 기분을 달래려는 거야?!.. 꿈도 꾸지 마! 다투라는 사람을 완전히 지배해서, 기운을 빼앗고, 의지를 짓밟아버려! 정신 차려보면 이미 산송장이 되어 있고, 곧장 진짜 시체가 되는 거야...";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "샤를, 하지만... 지금은...";
			link.l1 = "변명하지 마. 내가 심하게 군 건 미안하지만, 이건 장난이 아니야. 이건 내가 가져갈 거야. 도대체 무슨 생각을 한 건지 믿을 수가 없어... 자, 이거 마시고 정신 차려.";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "미안해, 샤를. 네 말이 완전히 맞아, 나도 알아. 잠깐 흔들렸을 뿐이야. 다시는 이런 일 없을 거야. 악마의 유혹에서 날 구해줘서 고마워...";
			link.l1 = "잊어버리자... 이제 말해 봐, 어떻게 해서 마을에서 존경을 받고, 주둔지 장교들과도 좋은 관계를 유지하면서, 원주민들과도 친구가 될 수 있었어?";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "스벤손을 존경하지, 그리고 그 존경심이 나에게도 조금은 옮아와. 우리 작은 마을은 전적으로 얀의 거래 덕분에 살아남고 있어. 그는 자신의 코코아 농장 수익 일부를 영국군과 나누고, 미스키토족은 삶 전체를 그에게 빚지고 있지.";
			link.l1 = "어쩌다 그렇게 된 거야?";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "카스티야인들이 지배하던 시절엔 인디언들을 크게 괴롭히지 않았지. 하지만 귀족 이달고들을 쫓아낸 뒤로 우리 사람들이 이 지역 숲을 장악하려 들었어. 그때 얀은 이 문제를 아주 단호하게 해결했지 – 심지어 사람들을 런던까지 보냈다니까! 물론, 그가 착해서 그런 건 아니야. 숲의 모든 덤불이 널 미워하는 곳에서 코코아를 채취하는 건 가망 없는 짓이거든. 그런데 지금은 인디언들이 얀의 밀수에 포르토 벨로에서 블루웰드까지 도와줄 뿐만 아니라, 자기네 숲도 푼돈에 베어내고 있어. 브라보, 숲의 악마, 브라보!";
			link.l1 = "그의 방식이 완전히 마음에 들지는 않는 것 같군요.";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "나는 미스키토 사람들을 사랑하고 존경해, 하지만 얀의 전략도 존중해. 우리는 동화 속에 살고 있지 않아, 내 캡틴.";
			link.l1 = "흠... 처음 봤을 때보다 스벤손과의 관계가 더 복잡한 것 같군...";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "네가 아는 것보다 더 그래. 그의 아내가 나한테 독하게 구는 데는 충분한 이유가 있어... 얀은 내가 열다섯 살쯤부터 나를 눈여겨봤거든. 무지개호 갑판을 동등하게 걷기 시작했을 무렵이었지, 그때 숲의 악마 머릿속에서 뭔가가 딱 맞아떨어진 모양이야... 하지만 내가 너무 많은 말을 했네, 내 캡틴. 이 주제는 더 파고들지 말자. 우리 후원자에 대해 험담하는 건 별로 품위 있는 일이 아니니까.";
			link.l1 = "그럼 화제를 바꾸자. 내가 말하려던 건, 당신이 이 무리에 분명 잘 어울리고, 그들도 당신을 자기 사람으로 여긴다는 거야.";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "나는 인디언, 집시, 그리고 다른 괜찮은 부랑자들과 함께 있는 게 훨씬 편하더라고. 엄마가 끓여주던 스튜, 해변 모닥불, 그리고 레인보우호의 승강구까지—내 나름대로 아늑한 세상을 만들었지, 선장. \n그런데 모든 걸 다 이해했다고 생각한 순간, 그 세상이 산산조각 나 버렸어.";
			link.l1 = "통이 거의 비었네... 마지막으로 한 잔 더 할까?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "정말 좋아요... 나랑 시간을 보내주기로 해서 기뻐요, 캡틴. 나한텐 정말 필요했거든요. 당신도 그랬으리라 믿어요.";
			link.l1 = "그래, 이렇게 편하게 쉬어본 건 정말 오랜만이야. 이건 오래 기억에 남을 거야!";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "지금쯤 나에 대해 별별 생각을 다 하고 있겠지. 나는 원래 성격이 아주 폐쇄적인 사람이야, 샤를. 그냥... 젠장, 그냥 살아 있다는 걸 느끼고 싶었어! 그냥 누군가와 이야기하고 싶었을 뿐이야!";
			link.l1 = "글래디스는? 얀은?";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "엄마는 울기만 하고, 얀은 이제 완전히 딴사람 같아. 내가 괜히 그렇게 느끼는 걸 수도 있지만, 이제 얀이 나를 부끄러워하는 것 같아? 미안해, 나... (훌쩍인다).\n이제 됐어, 이년아. 미안, 내가 좀 감정이 북받쳤어.";
			link.l1 = "사과할 필요 없어. 나는 모든 걸 이해하고 있어, 아니, 적어도 이해한다고 생각해.";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "이런 말을 하는 건 우리가 이제 막 만났기 때문이야. 나는 오랫동안 알아온 사람들에게도 이렇게 솔직하게 말하는 게 익숙하지 않아. 사람들은 나를 룸바라고 부르지, 내 성격 때문이라는데, 보다시피 그건 잘못 붙은 별명이야. 술은 다 떨어진 거야?";
			link.l1 = "조금 전이었는데, 벌써 새벽이 밝아오고 있어.";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "미안해요, 내 캡틴, 오늘 밤에 다른 기대를 했다면. 나... 나는 안 돼요. 오늘은 안 돼.";
			} else {
				dialog.text = "저녁 시간 고마워요, 캡틴. 누가 알겠어요, 어쩌면 또 이런 시간이 있을지도 모르죠.";
			}
			link.l1 = "물론이지, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "여기까지 데려다줘서 고마워요, 선장님. 둘러볼까요? 내 유산을 살펴보죠.";
			link.l1 = "여기 전에 온 적 없었어?";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "아니, 꽤 멀리 떨어져 있어. 게다가 나는 해적도 아니야. 이곳은 원래 별로 매력적인 곳도 아니었고, 블레즈가 죽은 뒤로는... 여기 오래 머무르는 게 좋지 않아.";
			link.l1 = "우린 안 그럴 거야. 벌써 너를 여기 데려온 걸 후회하고 있어.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "꼭 그랬어야 했나요, 선장? 왜 그렇게 싸우려고 서둘렀죠? 뭐, 승자를 탓할 순 없겠지. 자, 저택을 한번 둘러보자; 어차피 여기엔 더 볼 것도 없으니까.";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						Notification_Approve(false, "Helena");
					} else {
						dialog.text = "잘했어요, 내 캡틴. 싸움부터 벌이기 전에 현명하게 문제를 풀려고 하다니. 자, 저택을 한번 살펴보죠. 어차피 여기엔 더 볼 것도 없으니까요.";
					}
					
					link.l1 = "저기 해안에 끌어올려진 저 거대한 배는 어쩔 건데?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "그 바보들을 정말 능숙하게 속였어요, 내 캡틴! 진짜로, 나 웃음 터질 뻔했다니까요! 자, 이제 관저나 한번 구경해요; 어차피 여기엔 더 볼 것도 없으니까요.";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					Notification_Approve(true, "Helena");
					
					link.l1 = "저기 해안에 끌어올려진 저 거대한 배는 뭐야?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "잠깐만, 숨 좀 돌리게 해 줘! 정말 네가 그 찰리 프린스 맞아?";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					Notification_Approve(true, "Helena");
					
					link.l1 = "내 인생에도 그런 시절이 있었지, 그래. 감탄하는 거야?";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "그래, 네 말이 맞아. 나도 탐험해보고 싶지만, 솔직히 말해서, 샤를, 조금 두려워. 가자.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "세상에, 맞아! 나중에 꼭 전부 다 얘기해 줘야 해, 알았지? 난 들은 것밖에 없거든... 아주 외설적인 이야기들만!";
			link.l1 = "다 말해줄게... 거의 다지만.";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "기대하면서 기다릴게! 자, 저택을 한번 둘러보자. 어차피 여기엔 더 볼 것도 없으니까.";
			link.l1 = "저기 해안에 끌어올려진 저 거대한 배는 어쩔 거야?";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "비좁고 차가운 오두막에 말도 안 되는 요구들. 벌써부터 덫에 걸린 기분이야!";
			link.l1 = "지금까지는 그 잠재적인 재산이 마음에 들지 않는 건가?";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "아니, 샤를. 내가 너무 까다로운 걸지도 모르지만, 지금은 그 배가 내가 두려워하고 미워하는 모든 것의 상징이야. 언젠가 임대라도 할 수 있으면 좋겠는데... 그래도 그 돈을 어디에 쓸지조차 모르겠어.";
			link.l1 = "임대료의 가치를 얕보지 마. 나는 임대료를 내지 않지만, 종종 선원들 월급을 마련하려고 머리를 굴려야 해. 너도 새 배를 사게 될 거야, '레인보우 II'라니, 괜찮은 이름 아닌가?!";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "자기 자신에게 돈을 쓰는 방법은 많지. 우선 맞춤형 검과 훌륭한 와인 한 병부터 시작해 봐. 자신을 아끼는 거야, 헬렌. 그럴 자격이 있으니까.";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "고마워요, 내 캡틴. 그렇게 말해줘서 기뻐요. 두 번이나 듣게 되니 더욱 좋네요. 저를 정말 잘 아시네요.";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				Notification_Approve(true, "Helena");
			} else {
				dialog.text = "고마워요, 내 캡틴. 그렇게 말해줘서 기뻐요.";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "내가 그럴 자격이 있다고 생각해? 난 이런 사소한 것들에 돈을 써본 적이 없지만, 뭐든 처음은 있는 법이니까. \n바다를 잊게 만들려는 네 시도는 멈추지 않을 것 같네, 그치, 캡틴? 어쩌면 네 말이 맞을지도...";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				Notification_Approve(false, "Helena");
			} else {
				dialog.text = "내가 그럴 자격이 있다고 생각해? 난 이런 사소한 것에 돈을 써본 적이 없지만, 뭐든 처음은 있는 법이니까.";
			}
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "어쨌든, 검사는 끝났어. 여긴 값나가는 게 없는 것 같아 - 잡것들이 이미 다 털어갔고, 2층도 똑같은 상태일 거라고 확신해.";
			link.l1 = "헬렌, 마치 네가 달라진 것 같아. 지난번에 우리가 함께 있었을 때는... 글쎄, 좀 더 솔직했던 것 같은데?";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "아무것도 변한 건 없어, 내 캡틴, 하지만 불쌍한 소녀의 어깨에 짊어진 게 너무 많아, 하하! 기분 상하게 하려던 건 아니야. 지금은 그냥 생각할 게 많을 뿐이야. 인생에 이런 급격한 변화가 매일 일어나는 건 아니잖아. 그리고 우리에겐 아직 함께할 시간이 많이 남아 있어!\n";
				link.l1 = "그 말 들으니 기쁘네! 여기서 나가자.";
			} else {
				dialog.text = "많은 것이 변했어요, 선장님. 이제는 좀 더 성숙해져야 하고, 인생을 다르게 바라봐야 할 것 같아요. 이건 공주와 유산에 대한 동화가 아니라, 거대한 정치의 세계예요. 그리고 그 안에서 제 위치를 아직도 깨달아야 하죠. 우리 집안의 위치도 마찬가지고요.";
				link.l1 = "그게 해결돼서 다행이야. 이제 여기서 나가자.";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "네?";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "이봐, 아직 다 약탈당한 건 아니야! 봐, 에렌! 이 군도는 전설급인 것 같아. 여기 깡패들도 차마 집어 가지 못했나 봐.";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "아니, 아무것도 아니야.";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "이런 젠장, 이건... 블레즈 본인의 전설적인 커틀러스잖아! 해적들도 그를 너무 존경해서 죽은 뒤에도 집에서 이 칼만큼은 가져가지 않았지. 돈이랑 값나가는 건 다 챙겼지만, 교수대에 오를 놈들도 명예의 흔적쯤은 남아 있는 법이야...";
			link.l1 = "여기 누군가가 분명히 정리를 하고 있는 것 같아. 마치 주인이 다시 돌아올 것처럼... 이곳은 집이 아니라, 추모관이야!";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "예리한 관찰 고마워, 샤를. 너 때문에 이곳이 완전히 망가졌잖아, 하하!";
			link.l1 = "이 커틀라스는 이제 네 것이야. 블레즈는 네가 말하는 그 삼촌이지...";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "더 무섭게 만드는군요, 내 캡틴. 나... 나는 못 하겠어요. 그걸 받아들이면 내 지난 삶이 완전히 끝나버릴까 봐 두려워요.";
			link.l1 = "그렇다면 상속의 일부로 생각하지 말고, 잘생긴 남자가 주는 선물로 받아.";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "누구일까? 농담이야! 어두운 생각을 떨쳐줘서 고마워, 선장. 이 검에 걸맞은 사람이 되도록 열심히 훈련할게!";
			link.l1 = "헬렌, 너라면 최고의 무기를 가질 자격이 있어. 가자, 여기서 할 일 끝났어.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "이런 젠장, 이건... 바로 블레즈 본인의 전설적인 커틀라스잖아! 해적들도 그를 너무 존경해서 죽은 뒤에도 집에서 이 검만은 가져가지 않았지. 돈이랑 값나가는 건 다 챙겼지만, 장차 교수대에 오를 놈들도 명예의 흔적쯤은 남아 있더라고\n나... 나는 못 하겠어. 이걸 받아들이면 내 지난 삶이 완전히 끝나버릴 것 같아서 두려워.";
			link.l1 = "그럼 이건 유산이 아니라 잘생긴 남자가 주는 선물로 받아.";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "그게 누굴까? 농담이야! 어두운 생각을 떨쳐줘서 고마워, 내 캡틴.";
			link.l1 = "헬렌, 너라면 최고의 무기를 가질 자격이 있어. 마음에 들어 해서 기쁘네.";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "이 검에 어울리는 사람이 되도록 열심히 훈련하겠다고 약속할게!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "내 캡틴! 샤를!";
			link.l1 = "샤를리? 그건 처음 듣네! 반가워, 자기야.";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "나도 실수로 그랬어, 하! 너를 다시 보니 나도 기쁘네...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "자매애는 다 물 건너갔네! 내 캡틴, 나... 정말 걱정 많이 했고 너무 보고 싶었어!";
			link.l1 = "그래서 집에 그렇게 급히 돌아가야 했던 이유가 뭐였어?";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "아... 아, 맞다! 여기, 너에게 줄 작은 선물이 있어!";
			link.l1 = "부적이 세 개나... 에렌, 왜? 나를 따라오고 싶었던 거야?";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "이리 와, 이 바보야!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "이 순간 망치기만은 하지 마, 평생 이 순간을 꿈꿔왔으니까!";
			link.l1 = "안 할 거야, 헬렌.";
			link.l1.go = "after_kiss_a";
			link.l2 = "평생 나를 만나길 기다렸다고? 영광인데!";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "에렌, 저기... 정의의 섬에서 어떤 여자를 만났는데, 그리고...";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "그래, 맞아! 다 말해, 전부 다! 배에서 기다릴게, 캡틴!";
			link.l1 = "잠깐!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "바보야! 나를 화나게 하고 싶어? 좋아, 나 화났어! 하하! 당분간 배에 가 있을게, 대니가 더 놀리기 전에...\n";
			link.l1 = "잠깐!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "바보야! 내가 분위기 망치지 말라고 했잖아! 만났다고... 뭐, 만난 건 알겠는데 – 아직 손가락에 반지는 안 보이네. 하지만 그냥 넘어갈 생각 마. 배로 돌아오면 자세한 얘기 꼭 들을 거니까.";
			link.l1 = "잠깐!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "내 캡틴, 무슨 소식이죠? 창백한 얼굴만 봐도 그 변호사가 도와주기는커녕 또 골치 아픈 일만 떠넘겼다는 걸 알겠어요.";
			link.l1 = "맞아, 에렌. 록슬리가 엄청난 선금을 요구했고, 이 일 자체도 나한테 꽤 큰 돈이 들 거야. 이제 얀을 흔들러 갈 거야 – 더는 못 참겠어! 마치 해적단이 자기들 모든 비용을 나한테 떠넘기기로 한 것 같잖아!";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "악의는 없어, Charles. 저 사람들은 원래 그래 – 꼭 필요하지 않으면 손가락 하나 까딱 안 해. Jan도 분명 도와줄 거고, 나도 가만히 있진 않을 거야.";
			link.l1 = "알고 있어, 에렌. 무슨 생각이 있는지 말해 줘.";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "나는 예전에 얀을 위해 일했어 – 메인 전역에 귀한 목재를 밀수했지. 하지만 나는 수완 있는 여자라서, 그 많은 항해 중에 내 몫도 따로 챙겨뒀어.";
			link.l1 = "그런데 얀은 끝내 몰랐단 말이지? 영리하네!";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "난 좋은 재무관을 두고 있었어. 아무튼, 제법 많은 돈을 모았고, 여기서 멀지 않은 곳에 숨겨 두었지. 지금 얀한테 가는 거야? 그럼 산 후안 델 노르테에 들르자. 근처에 동굴이 있는데, 우리 둘만 들기엔 무거우니까 선원 몇 명만 도우면 돼.";
			link.l1 = "이미 다 알아챘군, 그렇지? 고마워, 헬렌. 시간 나면 꼭 들르겠어.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "내 캡틴, 소식이 뭐예요? 창백한 얼굴만 봐도 변호사가 도와주기는커녕 또 문제를 떠넘겼다는 걸 알겠어요.";
			link.l1 = "맞아, 헬렌. 록슬리가 엄청난 선금을 요구했고, 이 일 자체도 나한테 꽤 큰 돈이 들 거야. 이제 얀을 흔들러 가야겠어 – 더는 못 참겠어! 마치 해적단이 자기들 모든 비용을 나한테 떠넘기기로 한 것 같잖아!";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "동화 속에라도 있다고 생각했어? 걱정 마, 여기선 우리 모두 같은 처지니까 내가 도와줄게. 어차피 나도 상속받을 권리가 있잖아?";
			link.l1 = "그렇지... 무슨 생각을 하고 있는지 말해 봐!";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "산후안델노르테에 숨겨둔 게 있어. 근처에 동굴이 있는데, 우리끼리 다 나르지 않으려면 선원 몇 명만 모으면 돼.";
			link.l1 = "이미 다 알아챘군, 그렇지? 고마워, 헬렌. 시간 나면 꼭 들를게.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "여기가 바로 그곳이야, 샤를! 하지만 너 혼자 가야 해 – 나는 동굴이 정말 싫거든!";
			link.l1 = "나도 알아, 헬렌. 밀폐된 공간은 다 그렇지. 여기서 나를 기다려.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "문제가 생겼어! 병사 한 분대가 이쪽으로 오고 있는데, 분위기가 심상치 않아. 조심해, 샤를, 저들은 평범한 해안 경비대가 아니야 - 그들 중에 프랑스 장교도 있어! 제발, 제발 무모한 짓만은 하지 마!";
			link.l1 = "내가 언제 어리석은 짓을 한 적이 있지?!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "하, 두 번째 선택지가 더 매력적으로 들리네. 하지만 너무 자만하는 건 아니겠지, 샤를?";
			} else {
				dialog.text = "놀랍지도 않네, 샤를...";
			}
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "끝났어? 이제 내가 말할 차례야!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "내 이름은 헬렌 맥아더야! 선장, 당신은 내가 누구고 누구를 위해 일하는지 알잖아! 당신 부하들에게, 특히 저기 땅바닥에 누워 있는 멋 부린 바보에게, 오늘의 결과를 지금부터 내가 발표할 거라고 알려 줘!\n";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "항의? 네가 크롬웰한테 직접 편지를 써도 상관없어. 우선, 드 모르 나리는 오늘 명예를 잃지 않았어.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "둘째, 드 타반 대령은 한 소녀를 창녀라고 불렀다가 아주 화끈한 옷차림의 그 소녀에게 총을 맞았지.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "셋째, 당장 병사들을 철수시키고 있었던 일은 잊어라. 숲의 악마에게 이 소문이 들어가길 원하지 않는다면 말이지.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "질문이 없군. 좋은 하루 보내요, 캡틴.";
			link.l1 = "이런 맙소사, 헬렌, 너 완전히 불붙었구나!";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "나중에 보자, 샤를. 저들이 충격에서 회복하기 전에 여기서 나가자. 나도 온몸이 떨려. 블루벨드에서 이야기할까?";
			link.l1 = "동의해.";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "충격에서 저들이 회복하기 전에 여기서 나가자. 아직 아이언우드를 찾아야 하잖아, 기억하지? 블루웰드에서 이야기하자.";
			link.l1 = "이런 젠장! 축하 한마디도 없냐? 좋아, 가자.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "드디어, 집이네...";
			link.l1 = "무슨 일이 있었는지 어떻게 생각해?";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = "나는 결투를 이해하지 못하겠어. 남자들이 즐기는 오락거리라지만, 보통은 시체 둘로 끝나고, 운이 좋으면 더 많기도 하지. 그리고 명예라... 나는 명예란 끝까지 충돌을 피하려는 마음에서 비롯된다고 생각해. 명예가 진짜로 가치 있는 경우는 드물거든. 하! 내 말 좀 들어봐—이런 헛소리를 하고 있네!\n";
			link.l1 = "흥미로운 관점이군, 헬렌. 하지만 모두가 동의하진 않을 거야.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "네가 그들의 계략에 말려든 게 안타깝군. 대령은 분명히 집착에 사로잡혀 있었고, 나머지 사람들은 그냥 구경거리와 소문거리를 원했을 뿐이야. 뭐, 더 이상 상처 주진 않을게 – 오늘 하루면 이미 충분히 겪었으니까.";
			link.l1 = "그래, 결투가 끝나면 항상 허전함이 남지. 오늘은 모험도 이쯤이면 충분해. 이제 뭘 하고 싶어?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "으윽! 그냥 우리 자신이 자랑스럽다고 말하고 싶었어. 오늘 정말 용기를 보여줬어, 내 캡틴. 한 번쯤은 너를 휘두르고 싶어한 선원들의 히스테리에 휘둘리지도 않았고. 붉은 제복의 허세와 푸른 제복의 집착에도 굳건히 맞섰지. 대령은 분명 죽음을 원했던 것 같은데, 결국 부적절한 곳에 상처만 얻었네, 하하!";
			link.l1 = "고마워, 헬렌. 진짜 해군 장교처럼 우리를 재난에서 멋지게 이끌었어. 스스로 자랑스럽지?";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "그래, 그게 필요했어. 아쉬운 건 파란 제복이었다는 거지, 빨간 제복이었으면 더 좋았을 텐데. 그래도 그걸 입고 있던 녀석은 마땅한 대가를 치렀으니 다행이야.";
			link.l1 = "그 사람은 정말 별거 아니지, 인정해. 오늘은 모험도 충분했어. 이제 뭘 하고 싶어?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "집에 가려고 해, 내 캡틴. 내 모... 글래디스가 그리웠거든. 지금 집에 있어서 아쉽네, 아니었으면 너도 초대했을 텐데!";
			link.l1 = "정말 안타깝군!";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "너무 속상해하지 마. 곧이야, 내 사랑. 그동안에는...\n";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "음, 이건 처음 것보다 더 좋네. 기억나? 우상 옆에서 했던 거?";
				link.l1 = "그건 잊을 수 없는 일이야, 자기야.";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "이 순간 망치기만은 하지 마, 평생 이 순간을 상상해 왔으니까!";
				link.l1 = "안 할 거야, 헬렌.";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "평생 나를 만나길 기다렸다고? 영광인데!";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = "오! 정신 차려, 소녀야! 다음에 또 보자, 내 캡틴.";
			link.l1 = "그때까지 안녕, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "그래, 맞아! 곧 다시 보자, 내 캡틴.";
			link.l1 = "다시 만날 때까지, 에렌. 아, 맙소사, 정말 대단한 여자야...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "바보야! 나를 화나게 하고 싶어? 좋아, 나 화났어! 하하! 곧 다시 보자, 내 캡틴.";
			link.l1 = "다시 만날 때까지, 에렌. 아, 맙소사, 대단한 여자야...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "집으로 돌아갈게, 캡틴. 변호사랑 돈 문제는 이제 해결된 거지? 앞으로 험난한 일들이 기다리고 있으니, 이제부터는 괜히 문제 일으키지 말자. 어차피 문제는 우리가 가만히 있어도 찾아올 테니까.";
			link.l1 = "이런 젠장, 진짜야?";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "직설적으로 말해서 미안해, 캡틴. 내 운명도 지금 결정되고 있거든.";
			link.l1 = "알겠어, 최대한 품위 있게 처리해 볼게. 배에서 보자, Helen.";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "알겠어요, 캡틴!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "이제 뭐지? 내가 보여줄게.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "음, 이건 첫 번째 것보다 더 좋네. 기억나? 우상 옆에서 했던 거?";
				link.l1 = "그런 건 쉽게 잊을 수 없는 일이야, 자기야.";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "이 순간 망치기만은 하지 마! 평생 이 순간만을 상상해 왔으니까!";
				link.l1 = "안 할 거야, 헬렌.";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "평생 나를 만나기만을 기다렸다고? 영광인데!";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "그래, 맞아! 젠장, 깜짝 놀랄 일이군! 글래디스는 지금 집에 없어. 들어올래?";
			link.l1 = "나를 초대하는 거야? 그런데 뭘 하자는 건데?";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "아니, 에렌. 정의의 섬에서 또 다른 여인이 나를 기다리고 있어. 그녀에게 그런 짓은 할 수 없어.";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "다음에 보자, 내 사랑. 정말 그러고 싶은데, 오늘은 너무 힘들었어. 우리 나중에 만나서 못 만난 시간까지 열 배로 보상하자.";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "그래, 맞아! 젠장, 깜짝 놀랄 일이군! 글래디스는 지금 집에 없어. 들어올래?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "아니, 헬렌. 정의의 섬에서 나를 기다리는 여인이 또 있어. 그녀에게 그런 짓은 할 수 없어.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "다음에 하자, 내 사랑. 정말 그러고 싶은데, 오늘은 거의 죽을 뻔했어. 우리 나중에 만나서 못 만난 시간까지 열 배로 보상하자.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "나를 초대하는 거야? 그런데 우리가 뭘 하게 될까?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "바보야! 나 화나게 하고 싶어? 좋아, 나 정말 화났어! 하하! 이제 나한테 사과해야 해, 내 캡틴. 자! 글래디스는 지금 집에 없어. 들어올래?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "아니, 헬렌. 정의의 섬에 나를 기다리는 다른 여인이 있어. 그녀에게 그런 짓은 할 수 없어.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "다음에 보자, 내 사랑. 나도 정말 그러고 싶지만, 오늘은 정말 힘들었어. 우리 나중에 만나서 못 만난 시간까지 열 배로 보상하자.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "나를 초대하는 거야? 그런데 뭘 하게 될까?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "아, 내가 유혹의 기술이 부족하단 말이야? 그런데 그 여자는 능숙하다고? 그 여자가 누구지?";
			link.l1 = "그녀의 이름은 메리 캐스퍼이고, 나는 그녀를 사랑해.";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "빨간 제복 입은 그 빨간 머리? 빨간 제복이라니... 뭐, 신호가 필요했다면 이게 그거겠지. 인연이 아닌가 봐. 그리고 걱정 마, 캡틴. 내 선상 근무에는 아무 영향 없으니까.";
			link.l1 = "미안해, Helen.";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "오, 내 캡틴! 여자를 이런 상태로 두는 건 위험해요! 약속한 거 꼭 지켜야 해요, 그러니 이제 가요... 혼자 있고 싶고, 내 문제는 내가 스스로 해결해볼게요... 혼자서! 배에서 봐요!";
			link.l1 = "대단한 아가씨네!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "걱정 마, 내 사랑. 길을 잃으면 내가 안내해 줄게.";
			link.l1 = "그럼... 앞장서!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "아무 말도 하지 마요, 제발.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "... 물론 오늘까지 내가 이 주제에 대해 아는 거라곤 '레인보우' 선원들의 저속한 대화뿐이었지, 그걸 대화라고 부를 수 있다면 말이야, 물론.";
			link.l1 = "어땠어? 현실이 기대만큼 괜찮았나?";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "정말 즐거웠지만, 아직 완전히 다 경험한 것 같진 않아. 그리고 어떻게든...";
			link.l1 = "내가 보여줄게! 계속할까?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "아, 이제야 알겠어요! 정말 멋졌어요, 내 캡틴!";
			link.l1 = "솔직히, 너 때문에 깜짝 놀랐어!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "아하하! 그거 정말 웃기네! 이제 그녀는 귀에 밀랍을 틀어막거나 요새에서 제일 높은 망대로 달아나겠군!";
			link.l1 = "예상치 못했지만 정말 웃겼어, 아-하-하!";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "준비됐어, 내 캡틴?";
			link.l1 = "벌써?! 안 돼, 에렌, 제발 나 좀 봐줘. 글래디스가 갑자기 나타난 건 분위기에 전혀 도움이 안 됐어.";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "뭐, 어쩔 수 없지... 하지만...";
			link.l1 = "아니, 아니, 돛을 내리라고!";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "좋아, 그럼 잠시만이라도 함께 있자. 우리의 앞날은 너무나 흐릿하고 두렵지만, 오랜만에 처음으로 아무것도 두렵지 않아. 언젠가 또 다른 두려움이 스며들 수도 있겠지만, 오늘은 아니야. 오늘만큼은 아니야, 내 캡틴.";
			link.l1 = "오늘은 아니야, 내 사랑. 오늘은 아니야.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "말해도 되겠습니까, 선장님?";
			link.l1 = "그래, Helen?";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "나도 그 스네이크 아이를 알아. 괜찮은 사람이긴 한데 좀 별난 구석이 있지. 정체도 모를 일로 사람들을 자주 심부름 보내거든. 보아하니 너도 그 수상쩍은 영광을 누리게 된 모양이네.";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "맞아, 내가 그에게 부적 세 개를 가져다줘야 해, 그렇지 않으면 그가 나를 호크의 아지트로 데려다줄 수 없대. 그런데 웃긴 게 뭔지 알아? 그 부적들, 이미 내가 갖고 있었어! 어쩌면 그는 처음부터 그걸 알고 있었던 걸까?";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "맞아, 내가 그에게 부적 세 개를 가져다줘야 해. 그렇지 않으면 그가 나를 호크의 은신처로 데려다줄 수 없어. 지금은 어디서 그 부적을 찾아야 할지 모르겠고, 시간도 얼마 남지 않았어.";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "아, 정말 아쉽네! 등대지기들한테서 부적을 모으러 뛰어다닐 필요가 없었다니 다행이지만, 이번만큼은 내가 너에게 도움이 되고 싶었고, 내 실력을 증명하고 싶었거든.";
			link.l1 = "헬렌, 말도 안 돼. 나한테 아무것도 증명할 필요 없어.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "도와줄게! 사실, 이번만큼은 내가 너에게 도움이 되고 싶었어, 내 자신을 증명하고 싶었거든.";
			link.l1 = "헛소리 하지 마, 헬렌. 나한테 아무것도 증명할 필요 없어.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "그래도 도와주고 싶어. 자, 내 방 열쇠를 가져가... 아니, 내 방에 있는 상자 열쇠야! 별건 없지만, 너한테 도움이 될지도 몰라. 그리고... 샤를, 지금 웃음 터뜨리기만 해 봐!";
			link.l1 = "에헴, 그럴 생각은 없었어. 이런 것들에 관심이 있나?";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "나도 선장이자 뱃사람이야, 선장님. 우리 같은 일 하는 사람들은 행운의 여신을 내 편으로 만들기 위해 뭐든 해야 하지.";
			link.l1 = "고마워, 헬렌. 정말 고맙게 생각해.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "자기야, 선물 하나 줄게!";
			link.l1 = "알겠어, 저기 있네 – 서서 웃고 있잖아!";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "아, 아하, 그만해! 예전에 내가 이 근처 조선공에게 비단을 한가득 넘긴 적이 있어서, 지금은 그 사람이 내게 배 전체를 싹 고쳐주기로 빚을 진 셈이지. 원래는 그 일에 '레인보우'를 맡기려고 했는데, 결국 그렇게 되진 않았어. 그런데 네 배라면 그런 정비가 정말 도움이 될 것 같은데, 그렇지 않아?";
			link.l1 = "정말 훌륭한 선물이군, 에렌 – 너한테 딱 어울려!";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "마음에 들어서 기뻐. 언제든 그를 찾아가서 내가 보냈다고 전해. 최선을 다해 줄 거야.";
			link.l1 = "당연하지!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "말씀드려도 될까요, 내 캡틴?";
			link.l1 = "물론이지, 내 사랑.";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("당신의 여인이 당신을 그리워하며 관심을 원하고 있습니다. 그녀를 위해 방을 마련해 주시고, 시간을 좀 내어 주실 수 있을지 부탁드려도 되겠습니까\n","보고합니다: 현지 선술집의 침대에서 당신이 필요하답니다. 단 5분만 내주시면 되지만, 선원들은 좀 더 오래 머물러 주시길 바라고 있어요!","선상 반란입니다, 선장님! 저는 당신께 몰래 블랙 마크를 전달하라는 임무를 받았습니다. 지금 바로 저와 함께 가시죠!");
			link.l1 = "헤헤, 크흠! 네 부탁 들어주지, 샤프 경관!";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "오늘은 안 돼, 자기야. 지금은 일이 너무 많아.";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "오, 그럼 가엾은 내가 뭘 어쩌란 말이야, 응? 좋아, 내 사랑, 다음에 또 보자.";
			link.l1 = "";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "하! 두 번 말할 필요도 없어! 당연하지, 가자!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "지금 당장 너를 바다에 던져버릴 거야!";
			link.l1 = "이봐, 이봐, 이봐! 진정해, 자기야!";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "이리 와, 이 악당아!";
			link.l1 = "장난이었어, 에렌! 기분 상하게 하려던 건 아니었어!";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "정말이야? 참 장난꾸러기네...";
			link.l1 = "넌 세상에서 제일 아름다워, 그리고 미칠 듯이 사랑해!";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "꺼져, 샤를.";
			link.l1 = "";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "너야말로 제일 방탕한 여자지! 얀 덕분에 그나마 사람 구실하는 거나 다행인 줄 알아. 아니었으면 아직도 길가는 놈마다 다리나 벌리고 있었겠지!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "창녀 같으니! 가자, 샤를!";
			link.l1 = "";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "커틀러스가 내 손에 딱 맞아! 뭐라고 설명해야 할지 모르겠어... 난 항상 레이피어나 롱소드 같은 다른 칼들은 잘 못 다뤘거든. 그런데 이 커틀러스는 완전히 달라! 정말 놀라운 느낌이야! 고마워, 샤를!";
			link.l1 = "운명은 결국 우리를 찾아내지. 잘 됐구나, 헬렌!";
			link.l1.go = "exit";
			notification("Medium Weapons +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "네 얘기는 딴 사람한테나 해, 나한테는 안 통해. 내가 순진하게 사랑에 빠진 바보처럼 보여? 뭐, 사실 너한테 푹 빠진 건 맞지만, 바보라고 하기엔 좀 심하지\n 들어봐, 자기야. 네 마음대로 해도 돼. 하지만 나보다 나은 여자는 못 찾을 거라는 건 명심해. 기생집에서 그런 여자를 찾고 싶으면 마음대로 해. 하지만 그땐 내 인생에서 넌 영영 사라지는 거야.";
			link.l1 = "Helen, 나...";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "모든 걸 이해해, 샤를. 당신은 오직 나만 사랑하고, 그건 그냥 본능일 뿐이겠지. 내 본능이 뭔지 알아? 내 남자에게서 존중받는 거야. 여자란 사랑만으론 만족하지 못할 수도 있어, 자기야. 이번 오해는 일단 잊자. 하지만 내 말을 곰곰이 생각해 봐. 알겠지?\n";
			link.l1 = "좋아, 헬렌.";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "알잖아. 먼저 여자가 진정할 시간을 줘야지.";
			link.l1 = "하아...";
			link.l1.go = "exit";
		break;
		
		// Тайна Порт-Рояля
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "프랜시스... 기억나. 항상 내가 포트 로얄에 도착하길 기다렸지. 그는 정말 구제불능의 로맨티스트였어. 바다와는 거리가 먼 사람과 시간을 보내는 게 즐거웠어 – 그 모든 시와 세레나데들... 내겐 새로운 경험이었지. 내가 한 번도 알지 못했던 세상의 한 조각을 엿본 느낌이었어. 프랜시스는 부유했고, 똑똑했으며, 잘생겼지 – 정말 대단한 남자였어. 이곳의 어떤 여자라도 그의 관심을 받으려고 미쳐버렸을 거야. 하지만 그때 나는 레인보우를 지키는 일에 더 신경을 썼지.";
			link.l1 = "시인의 여린 영혼이 당신의 거절을 견디지 못한 것 같아요. 그가 보낸 모든 편지에는 오직 당신 이야기뿐이었고, 두 분이 만났던 장소들을 떠올렸어요. 원하신다면 그가 남긴 모든 것을 드릴 수 있어요.";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "그가 아팠다는 건 몰랐어. 지금 와서 생각하니 이 모든 게 참 어리석게 느껴지네.\n그의 유산 말인데... 이제는 유언장이나 상속 같은 건 지긋지긋해. 내 말 믿어, 난 필요한 건 다 가지고 있어 – 아니, 그 이상이야. 그건 네가 갖는 게 좋겠어.";
			link.l1 = "어찌 되었든, 그의 유산은 결국 당신에게 도움이 될 거야\n– 그러니까 나는 모르는 사이에 그의 마지막 소원을 이뤄준 셈이지. 참 기구한 이야기네.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}
