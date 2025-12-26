// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "뭐 필요한 거 있어?";
			link.l1 = "아니, 안 그래.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("너무 피곤해서, 벌써 쓰러질 것 같아...","이렇게는 더 이상 못 살겠어!"),RandPhraseSimple("이 일 때문에 죽을 것 같아.","경비들이 우리 모두를 죽이려고 해!"));				
			link.l1 = RandPhraseSimple("정말 안타깝군.","죄송합니다.");
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("이봐, 저리 가!","꺼져!"),RandPhraseSimple("뭐 원하는 거야?!","여기서 당장 꺼져!"));				
			link.l1 = RandPhraseSimple("음...","음...");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple("가서 농장 책임자를 귀찮게 해","노예들 방해하지 마, 이 친구야."),RandPhraseSimple("내 일은 이 게으른 놈들한테 동기부여를 해주는 거지.","젠장, 오늘도 너무 덥네, 여느 때처럼..."));
			link.l1 = RandPhraseSimple("그렇군...","정말이지...");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("Voice\English\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple("해적이다?! 저 놈을 잡아라!","그는 해적이다! 공격해!");
					link.l1 = RandPhraseSimple("해적이다. 그래서 뭐?","헤, 한번 해 보시지.");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("호호, 너는 그 깃발 아래에서 항해하고 있구나 "+NationNameGenitive(sti(pchar.nation))+"! 우리 지휘관께서 당신과 이야기하게 되어 기뻐하실 것 같소!","오, 오, 냄새가 나는군 "+NationNameAblative(sti(pchar.nation))+" 여기 있군! 첩자라니?! 이제 우리 사령관과 이야기할 시간이야.");
				link.l1 = RandPhraseSimple("먼저, 널 지옥으로 보내주지!","이제 내 칼날이 너와 대화할 시간이야!");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("Voice\English\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple("해적이다?! 저 놈을 잡아라!","그 자는 해적이다! 공격해!");
						link.l1 = RandPhraseSimple("해적이라고? 어디에?","헤, 한번 해보시지.");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("너는 누구고 여기서 뭘 원하는 거지?","멈춰! 여기에 무슨 일로 왔지?");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "이곳의 책임자를 만나 사업 이야기를 하고 싶소. 나는 무역 허가증이 있소.";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "이곳의 책임자를 만나 사업 이야기를 하고 싶소.";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
					if (IsCharacterPerkOn(pchar, "Trustworthy"))
					{
						link.l2 = "(믿을 만한) 존경하는 나리 여러분, 저는 공정하고 상호 이익이 되는 거래를 위해 왔습니다. 부디, 농장주를 만나게 해주십시오.";
						link.l2.go = "mtraxx_soldier_1";
						Notification_Perk(true, "Trustworthy");
					}
				}
				else
				{
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("너 누구야, 여기서 뭐 하려고 온 거지?","멈춰! 여기서 뭐 하는 거야?");
					link.l1 = "여기 책임자와 사업 이야기를 하고 싶소.";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = "면허증? 잠깐만... 하하, 이거 웃기네! 네가 누군지 알아. 넌 수배자야, 이 친구야! 네 목에 걸린 현상금이 엄청 크다고! 잡아라!";
				link.l1 = RandPhraseSimple("그렇다면 내 칼맛을 봐야겠군!","꺼져.");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("Voice\English\soldier_arest_1.wav");
				dialog.text = "어디 보자... 하! 네 면허가 만료됐군. 그러니 따라와, 내가 너를 사령관에게 데려가겠다...";
				link.l1 = RandPhraseSimple("젠장! 이제 내 칼맛을 볼 때가 됐군, 이 친구야.","그렇지 않을 것 같은데...");
				link.l1.go = "fight";	
				break;
			}
			dialog.text = "좋아. 들어와도 된다. 얌전히 굴고 노예들을 귀찮게 하지 마라.";
			link.l1 = "걱정 마, 친구.";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("Voice\English\soldier_arest_2.wav");
            dialog.text = "사업? 하하! 이거 웃기는군! 너한테서 나는 냄새가 "+NationNameAblative(sti(GetBaseHeroNation()))+" 천 리 밖에서 왔군! 이제 우리 사령관을 만날 시간이야.";
			link.l1 = "아니, 이제 내 칼을 맛볼 때가 된 것 같군.";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = "좋아. 들어와도 된다. 얌전히 있고 노예들에게 폐 끼치지 마라.";
			link.l1 = "걱정 마, 친구.";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = "어서 가, 얼른 비켜!";
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2") // belamour legendary edition 
			{
				dialog.text = "여기서 무슨 일이지, 나리?";
				link.l1 = TimeGreeting()+", 나리. 당신께 제안할 사업이 있소. 노예를 팔려고 하오. "+FindRussianQtyString(sti(GetSquadronGoods(pchar,GOOD_SLAVES)))+". 관심 있어?";
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = "여기서 무슨 일이지, 나리?";
			link.l1 = "그냥 돌아다니다가, 인사나 하려고 왔어.";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup") && bOk) //пробуем выкупить Красавчика
			{
				dialog.text = "또 왔군, 나리. 잘 지내나?";
				link.l1 = "당신에게 사업 제안을 하나 하지. 당신은 설탕과 카카오를 생산하잖아. 나는 당신의 물건을 사고 싶지만, 돈으로는 아니네; 내 물건을 교환품으로 줄 수 있지. 서로 거래를 해보는 건 어떻겠나?";
				link.l1.go = "mtraxx_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "또 만났군, 나리. 잘 지내시오?";
				link.l1 = "당신에게 사업 제안을 하나 하지. 당신은 설탕과 카카오를 생산하잖소. 나는 당신의 물건을 사고 싶지만, 돈으로는 아니오; 내 물건으로 교환할 수 있소. 서로 좋은 거래를 할 수 있지 않겠소?";
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = "또 만났군, 나리. 잘 지내나?";
			link.l1 = "고마워, 난 괜찮아.";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
			// belamour legendary edition возможность обмануть плантатора -->
			if(GetSquadronGoods(pchar, GOOD_SLAVES) >= 50 || CheckCharacterPerk(pchar, "Trustworthy") || ChangeCharacterHunterScore(Pchar, "spahunter", 0) <= -50)
			{
            dialog.text = "실망스럽겠지만, 나리, 지금은 노예가 필요하지 않소. 에두아르도 데 로사다 선장이 이미 지난 습격에서 사로잡은 해적들을 우리에게 넘겼소.";
			link.l1 = "여기에 해적들이 있다고? 여기서 어떻게 잠을 잘 수가 있지?";
			link.l1.go = "mtraxx_1";
			}
			else
			{
				dialog.text = "아, 그럼 어디 보자... 네 노예들을 사겠다. 그런데 네가 말한 그 사람이 아닌 것 같군. 이리 와, 내 사랑, 사령관 사무실로 같이 가자. 내가 틀렸다면 네 수고를 충분히 보상해 주지. 자, 실례하네. 경비병!";
				link.l1 = RandPhraseSimple("꿈이나 꿔라, 난 살아서는 절대 잡히지 않는다!”, “내 시체를 넘어가라!");
				link.l1.go = "mtraxx_fail";
			}
		break;
		
		case "mtraxx_fail":
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddQuestRecord("Roger_3", "27");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		break;
		// <-- legendary edition
		case "mtraxx_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "우리에겐 경비가 좋아서 폭동이 일어날 가능성은 낮아. 하지만 한 가지는 네 말이 맞아. 이 놈들은 정말 형편없는 일꾼들이지. 총독이 로사다 돈 나리에게 예의를 갖추라고 하지 않았으면 난 이놈들을 사지도 않았을 거야. 게다가, 그도 이놈들을 비싸게 부르지도 않았지.";
			link.l1 = "알겠습니다. 그럼 나는 로스-테케스로 항해해야겠군요... 나리, 당신의 플랜테이션을 좀 둘러보고 탐색해도 되겠습니까? 어쩌면 당신의 농산물을 좀 사고 싶을지도 모르니까요...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "상인인가?";
			link.l1 = "어떤 면에서는 그래. 나는 전문 상인은 아니지만, 괜찮은 거래를 그냥 지나치진 않아.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "흥미롭군. 좋아, 허락하마. 아이디어가 생기면 다시 오게.";
			link.l1 = "감사합니다, 나리. 그렇게 하겠습니다.";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = "왜 안 되겠소? 어떤 물건을 팔고 있소?";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "커피 500상자.";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "바닐라 500상자.";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "코프라 500상자.";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "커피 상자 500개라고? 오, 그래... 어디 보자... (계산 중) 네 커피와 맞바꿀 준비가 됐어 "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" 설탕 자루와 "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  카카오 상자들이네. 거래할래?";
			link.l1 = "흠... 더 좋은 조건을 기대했는데. 뭐, 상관없지. 거래하자!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(믿을 만한) 존경하는 나리, 감히 이의를 제기하겠습니다! 저는 최고의 품질을 가진 상품을 가져왔습니다. 제가 드리는 것과 나리께서 주시는 것, 각각의 가치를 저는 잘 알고 있습니다. 저는 나리 쪽에서 조금 더 많은 몫을 받을 자격이 있습니다. 그래도 이 거래는 나리께 충분히 이익이 될 것입니다 – 그 점은 나리도 잘 아시지요.";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_cinnamon":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = "바닐라 500상자라고? 오, 그래... 어디 보자... (셈하는 중) 네 바닐라와 바꿀 준비가 됐어 "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" 설탕 자루와 "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  카카오 상자들이야. 거래할래?";
			link.l1 = "흠... 더 좋은 조건을 기대했는데. 뭐, 상관없지. 거래하자!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(믿음직한) 존경하는 나리, 감히 이의를 제기하겠습니다! 저는 최고 품질의 상품을 가져왔습니다. 제가 드리는 물건과 나리께서 주시는 물건, 각각의 가치를 저는 잘 알고 있습니다. 저는 나리 쪽에서 조금 더 큰 몫을 받을 자격이 있으며, 그래도 이 거래는 나리께 충분히 이익이 될 것입니다 - 그 점은 나리도 잘 아시지 않습니까?";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_copra":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "코프라 500상자라고? 그래, 그래... 어디 보자... (계산 중) 네 코프라를 바꿔줄 준비가 되어 있지 "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" 설탕 자루와\n "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  카카오 상자들이야. 거래할래?";
			link.l1 = "흠... 더 좋은 조건을 기대했는데... 뭐, 상관없지. 거래하자!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(신뢰할 만한) 존경하는 나리, 감히 이의를 제기하겠습니다! 저는 최고의 품질을 가진 상품을 가져왔습니다. 제가 드리는 물건과 나리께서 주시는 물건, 각각의 가치를 저는 잘 알고 있습니다. 저는 나리 쪽에서 조금 더 많은 몫을 받을 자격이 있습니다. 그래도 이 거래는 나리께 충분히 이익이 될 겁니다 – 그 점은 나리도 잘 아시지 않습니까.";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_6":
            dialog.text = "훌륭하군! 우리 둘 다에게 이익이 되는 거래야! 언제 교환을 진행할까?";
			link.l1 = "먼저 물건을 준비해야겠군. 너도 마찬가지일 거라 믿어. 교환은 내일 저녁 네 시에 시작하자. 내 부하들이 해 지기 전에 상자를 가져다줄 거야.";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = "좋아. 그럼 내일 보자, 나리!";
			link.l1 = "또 보자...";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = "여기가 바로 그곳이오, 나리. 설탕이나 카카오가 필요하면 언제든 저를 찾아오시오. 언제든지!";
			link.l1 = "이번 거래가 이득이 된다면, 다시 만나게 될 거요. 이제 가봐야겠소, 나리.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_10":
            dialog.text = "안녕히 가시오, 나리!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
		
		case "mtraxx_soldier_1":
            dialog.text = "너는 상인처럼 안 보이는데, 이방인아. 허가증을 보여라.";
			link.l1 = "살려줘! 종이 한 장이 사람이 장사를 할 수 있는지 없는지 결정한단 말이야? 너무 비싸잖아! 나 이제 막 장사를 시작했는데, 벌써 내 인생의 열정이 됐어! 그냥 보내줘, 그러면 내가 주인한테 너희 둘 좋게 얘기해줄게.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_soldier_2":
            dialog.text = "입이 참 살아 있구나, 이 구두쇠야. 좋아, 가 봐라. 하지만 우리가 너를 추천했다고 꼭 두목에게 말하는 거 잊지 마라.";
			link.l1 = "물론입니다. 감사합니다.";
			link.l1.go = "plantation_exit";
		break;
		
		case "mtraxx_PlantVykup_2":
            dialog.text = "요즘 시세에 밝으시군요, 선장님! 겉으론 풋내기 같아 보여도 협상에는 소질이 있으십니다. 좋아요, 물건이 정말 일류라면, 당신을 위해 조금 더 얹어 드려야겠군요.";
			link.l1 = "물론이죠, 일급품입니다, 맹세합니다! 한 가지 더 있습니다, 나리. 당신에게서 뭔가 사고 싶습니다.";
			link.l1.go = "mtraxx_PlantVykup_3";
		break;
		
		case "mtraxx_PlantVykup_3":
            dialog.text = "오? 그게 뭔데?";
			link.l1 = "누군가를, 물건이 아니라. 당신 노예 중 한 명을 개인 하인으로 사고 싶은데, 가능하오?";
			link.l1.go = "mtraxx_PlantVykup_4";
		break;
		
		case "mtraxx_PlantVykup_4":
            dialog.text = "문제없어. 너한테 맞는 사람을 찾아줄게.";
			link.l1 = "나는 특정 노예에게 관심이 있소. 그 매력적인 얼굴을 가진 자 말이오—격식 있는 행사에 데려가도 부끄럽지 않고, 손님들에게 와인을 따라도 어울릴 만한 그런 사람이지. 자기 소개를 할 때 장 피카르라고 했소. 이미 서로 마음이 잘 맞았지.";
			link.l1.go = "mtraxx_PlantVykup_5";
		break;
		
		case "mtraxx_PlantVykup_5":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 70)
			{
				dialog.text = "그래, 장 피카르드에 대한 수요가 있어. 단순히 와인 서빙 때문만은 아니야. 영향력 있는 영국인이 이미 나에게 연락했지. 이름이 뭐더라... 패턴슨? 그가 나에게 편지를 전해줬어.";
				link.l1 = "하지만 Pattornson도 그의 의뢰인도 아직 나타나지 않았어. 나는 지금 당장 여기서 Jean을 사갈 준비가 되어 있지. 값을 말해봐 – 아가씨들이 기다리고 있으니!";
				link.l1.go = "mtraxx_PlantVykup_10";
				Notification_Skill(true, 70, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "아, 잘 통했군. 이해하네. 하지만 유감스럽게도 거절해야겠어 - 장 피카르는 팔 수 없어. 미안하네, 나리.";
				link.l1 = "오? 왜 그러지? 돈은 넉넉히 줄 생각이야. 원하는 값을 말해봐.";
				link.l1.go = "mtraxx_PlantVykup_6";
				Notification_Skill(false, 70, SKILL_COMMERCE);
			}
		break;
		
		case "mtraxx_PlantVykup_6":
            dialog.text = "값을 매길 수 없지. 이미 사겠다는 사람이 있어. 나는 그를 다른 이에게 주기로 약속했어. 더 이상 할 말 없어. 원래 거래로 돌아가서 거래를 마치자.";
			link.l1 = "흠, 원하시는 대로 하겠습니다, 나리.";
			link.l1.go = "mtraxx_PlantVykup_7";
		break;
		
		case "mtraxx_PlantVykup_7":
            dialog.text = "훌륭하군! 우리 둘 다 이득 보는 거래야! 언제 교환을 진행할까?";
			link.l1 = "먼저 물건을 준비해야겠군. 너도 그래야 할 거야. 교환은 내일 저녁 네 시에 시작하자. 내 사람들이 해 지기 전에 상자들을 가져다줄 거다.";
			link.l1.go = "mtraxx_PlantVykup_8";
		break;
		
		
		case "mtraxx_PlantVykup_8":
            dialog.text = "거래 성사됐군. 그럼, 내일 보자고, 나리!";
			link.l1 = "또 보자...";
			link.l1.go = "mtraxx_PlantVykup_9";
		break;
		
		case "mtraxx_PlantVykup_9":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup2 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_1");
		break;
		
		case "mtraxx_PlantVykup_10":
            dialog.text = "원하시는 대로 하겠습니다, 나리. 하지만 알아두십시오, 값이 비쌉니다. 오백 두블룬입니다.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "그건 문제없지 - 여기 있다. 훌륭한 개인 하인은 평범한 노예보다 훨씬 더 가치 있다는 거, 너도 잘 알잖아.";
				link.l1.go = "mtraxx_PlantVykup_11";
			}
			else
			{
				link.l2 = "값을 꽤 세게 부르셨군, 나리. 하지만 이 노예에 정말 관심이 있어. 여기서 기다려. Pattornson이 나타나면 Picard는 이미 팔렸다고 전해 줘 - 하하하!";
				link.l2.go = "mtraxx_PlantVykup_13";
			}
		break;
		
		case "mtraxx_PlantVykup_11":
            dialog.text = "맞아요. 내가 준비할게요. 피카르가 밖에서 당신을 기다릴 거예요.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "mtraxx_PlantVykup_12":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup3 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Maracaibo_ExitTown", "rld", "loc17", "Mtraxx_PlantPlantVykup_2");
		break;
		
		case "mtraxx_PlantVykup_13":
            dialog.text = "그가 전액을 가지고 온다면 내가 그를 돌려보낼 리 없지. 그러니 서두르시오, 선장.";
			link.l1 = "곧 돌아올게.";
			link.l1.go = "mtraxx_PlantVykup_14";
		break;
		
		case "mtraxx_PlantVykup_14":
            DialogExit();
			NextDiag.CurrentNode = "mtraxx_PlantVykup_15";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
		break;
		
		case "mtraxx_PlantVykup_15":
            dialog.text = "장 피카르를 위한 금을 가져왔소, 선장? 시간이 촉박하오.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "그건 잘 알고 있소. 자, 여기 금화다. 내 새 하인이나 내놓으시오.";
				link.l1.go = "mtraxx_PlantVykup_16";
			}
			else
			{
				link.l2 = "아직 모으고 있어 - 그렇게 비싼 값을 매긴 건 바로 당신이잖아, 나리.";
				link.l2.go = "mtraxx_PlantVykup_14";
			}
		break;
		
		case "mtraxx_PlantVykup_16":
            dialog.text = "저는 누군가가 하인을 얻는 데 이렇게 많은 돈을 쓰는 건 처음 봅니다. 하지만 당신의 옷차림을 보니, 이런 호화로운 거래에 익숙한 분이신 것 같군요. 제 부하들에게 알리겠습니다. 피카르가 출구에서 당신을 기다릴 것입니다.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
	}
} 
