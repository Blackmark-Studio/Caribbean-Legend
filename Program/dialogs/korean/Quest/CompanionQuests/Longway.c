void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "무슨 일이십니까?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "exit";
		break;
		
		// Квест "Путеводная звезда"
		// Этап 0, ПРОЛОГ
		case "PZ_Alonso_1":
			dialog.text = "실례를 무릅쓰고 선실에 들어왔음을 용서해 주십시오, 나리 선장님. 하지만 이건 매우 중요한 일입니다.";
			link.l1 = "그랬으면 좋겠군, Alonso. 너희 모두가 여길 자기 집처럼 막 들어오면 곤란해질 거야. 그래서, 무슨 일이야?";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "당신의 사물함이 뒤져진 것을 발견했습니다.";
			link.l1 = "뭐?! 잠깐만... 그걸 어떻게 알아낸 거지? 그리고 다들 내 선실에서 뭘 하고 있었던 거야?";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "당신이 밖에 나가 있을 때마다, 가령 마을에 있거나 침상에서 쉬고 있을 때, 우리는 가끔씩 당신 방을 청소합니다. 전혀 눈치채지 못하셨나요? 아니면 그냥 잊으신 건가요?";
			link.l1 = "아, 맞다. 이제 가도 된다.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "찰스 선장님, 보세요! 누가 당신 큰 서랍을 뒤졌어요.";
			link.l1 = "뭐라고? 언제 그걸 알아챘지? 누가 그런 짓을 했는지 아나?";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "얼마 전, 내가 당신을 뵈러 오던 길이었습니다. 그것이 누구인지는 영혼들도 침묵하고 있습니다.";
			link.l1 = "멋진 솜씨로군, 티칭기투. 이제 실례하겠소, 혹시 빠진 게 있는지 확인해야 하니.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "이봐, 선장, 뭐 보고 있어? 누가 네 물건 뒤졌어. 나도 눈치챘다니까.";
			link.l1 = "너였던가? 어차피 나는 프랑수아만큼 후하게 돈을 주는 것도 아니지.";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "헤, 내가 도둑이라면 굳이 말하겠어? 값진 것들 챙기고, 깔끔하게 정리하고 갔겠지. 이런 난장판은 내 방식이 아니야.";
			link.l1 = "인정하기 싫지만, 네 말이 맞아. \n자, 클로드, 비아냥은 나중에 해라. 도둑이 뭘 훔쳐갔는지 확인해야겠어.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "선장님, 오늘 누군가 당신의 사물함을 뒤진 것 같더군요. 눈치채지 못하셨습니까?";
			link.l1 = "뭐라고? 나는 항상 사물함을 확인하는 것도 아니고, Folke, 선실에만 있는 것도 아니야. 솔직하게 말해 봐 - 너지? 또 실수해서 우리가 마지막으로 육지에 있었을 때 은행 대출을 더 받은 거 아니야?";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "전혀 아닙니다, 선장님. 제 주머니나 사물함에 선장님의 물건은 아무것도 없습니다. 앞으로도 절대 그럴 일 없을 겁니다.";
			link.l1 = "나는 정말 아니길 바란다. 너는 가도 된다 - 나는 뭐가 빠졌는지 확인해 볼게.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			AddDialogExitQuestFunction("PZ_OsmatrivaemSunduk_0");
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "샤를 드 모르, 맞지?";
			link.l1 = "네 얼굴을 보니 이미 답을 알고 있는 것 같군. 그래서, 원하는 게 뭐지?";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "네 머리.";
			link.l1 = "흥미롭군요! 이 대화의 시작이 마음에 든다고 솔직히 말씀드려야겠네요. 하지만 더 나아가기 전에, 적어도 제가 누구에게 잘못을 저질렀는지는 알려주실 수 있겠습니까? 어쩌면 협상할 수도 있을 텐데요.";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "우리는 아마추어가 아닙니다, de Maure 나리. 우리가 말해도 당신에게 아무런 도움이 되지 않을 겁니다 – 우리 고용주는 이미 군도에서 떠났으니까요. 당신은 그들에게 해를 끼칠 수도, 사과를 전할 수도 없습니다. 우리는 이미 대가를 받았으니, 이제 약속을 지킬 차례입니다.";
			link.l1 = "이미 돈을 받았으면, 왜 피를 더 흘려야 하지?";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "우리는 아마추어가 아니야. 우리는 우리의 평판을 소중히 여겨.";
			link.l1 = "이번에는 그 기대를 충족시키지 못할 것 같군.";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "그건 두고 보자. 우리가 끝내면 저 놈 시체를 뒤져라! 뭐든 찾으면 다 불태워!";
			link.l1 = "뭘 태우라고?..";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "가면 쓴 자가 한 말... 설마...?";
			link.l1 = "무슨 일이야, 롱웨이? 현상금 사냥꾼들이 나를 쫓아온 게 이번이 처음도 아닌데, 네가 유난히 신경 쓰는 것 같군.";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "롱웨이는 누가 이 자들을 당신에게 보냈는지 안다고 생각합니다, 나의 주 선장님.";
			link.l1 = "제가 알아야 할 무언가 있습니까?";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "이게 로덴부르크 나리의 방식이오 - 자신을 도운 자들 중 너무 많은 것을 아는 이들을 제거하는 것이지.";
			link.l1 = "정말로... 그 가면 쓴 남자가 자기 고용주가 최근에 군도에서 떠났다고 했지. 그게 바로 루카스가 계획하던 거야! 우리, 더 많은 공격을 예상해야 한다고 생각해?";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "무엇이든 대비하는 것이 현명하지요, 나리 선장.";
			link.l1 = "현명한 말씀이군요. 그렇게 하겠습니다. 하지만 루카스는 뭘 노렸던 거죠? 그가 내가 뭘 가지고 있다고 생각했던 걸까요? 생각나는 것 있습니까, 롱웨이?";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "음-음, 롱웨이는 그게 뭔지 전혀 모르겠소.";
			link.l1 = "안타깝네. 하지만 좋아, 여기서 나가자.";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			ReturnOfficer_Longway();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// Этап 1, ВЕРНЫЙ КЛЯТВЕ
		case "PZ_Longway_11":
			dialog.text = "나리 선장님, 롱웨이가 드릴 말씀이 있습니다. 매우 중요한 일입니다.";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "무슨 일이오, 롱웨이? 루카스의 작별 인사가 걱정되는 것이오, 아니면 뭔가 새로운 걸 알아낸 것이오?";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "물론이지! 무슨 생각이야?";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "유감스럽지만, 아니오.";
			link.l1 = "그럼 뭔데, 롱웨이?";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "롱웨이는 말할 수 없습니다. 하지만... 떠날 허락을 구하고 싶어 합니다.";
			link.l1 = "떠난다고? 영영? 왜, 롱웨이? 네 선장으로서 이유를 알아야 할 권리가 있어.";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "맞습니다, 나리 선장. 하지만 롱웨이는 일꾼도 아니고 하인도 아닙니다. 스스로 돕겠다고 온 것이고, 떠날 때도 마찬가지로 자신의 의지로 떠날 수 있습니다. 영원히 그런 것은 아니오 - 처리해야 할 중요한 일이 있습니다. 그 일이 끝나면 롱웨이는 다시 돌아오기를 바랍니다.";
			link.l1 = "무슨 일인가? 말해 보게. 내가 선장이 아니라도, 그동안 함께 많은 일을 겪어온 사람으로서 말일세.";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "롱웨이가 할 수 있는 말은 오래전에 맹세를 했다는 것뿐이오.\n이제 그 맹세를 지킬 때가 왔소.\n그렇지 않으면... 롱웨이의 삶에는 아무 의미도 없소.";
			link.l1 = "맞아, 롱웨이. 너는 죄수가 아니고, 나는 간수가 아니야. 자유롭게 가도 돼. 행운을 빈다.";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "가도 되지만, 적어도 어디로 가는지 말해 줘. 내가 너무 많은 질문 없이 도와줄 수도 있어.";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "나도 중요한 임무가 있어. 내 형제를 구해야 해. 그러려면 모든 사람이 필요해, 롱웨이, 너도 포함해서. 네가 없으면 우리는 해낼 수 없어.";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "내 동정심이나 의무감을 이용하려 들지 마시오. 나는 완벽히 이해하고 있소. 맹세를 해본 적 있소, 나의 주군 선장?";
			link.l1 = "물론이지. 그러니 있는 그대로 전부 말해 봐. 내 부하들과 내가 반드시 도와줄 테니까.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "롱웨이는 못 해. 그냥... 못 해. 이건 커다란 미스터리, 그리고 내 것이 아니라서 말할 수도 없어.";
			link.l1 = "유감이군. 우리 사이에 신뢰가 있다고 생각했는데. 이제 넌 배를 떠날 수 없어 - 모든 장교들이 내 편이거든.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "맞아, 롱웨이. 너는 죄수가 아니고, 나는 감옥지기가 아니야. 자유롭게 가도 돼. 행운을 빈다.";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "그렇게 하면 안 돼!";
			link.l1 = "유감이지만, 할 수 있어, 롱웨이. 이제 네 임무로 돌아가.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "이렇게 쉽게 날 보내줄 줄은 몰랐소. 감사합니다, 나리 선장.";
			link.l1 = "아, 별거 아니오. 그런데 말씀해 주시오 - 일이 끝나면 어디서 당신을 찾을 수 있겠소?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "롱웨이는 아무리 말하고 싶어도 정말로 말할 수 없습니다. 하지만 롱웨이는 정의의 섬 나리께서 도우려는 마음을 고맙게 생각합니다.";
			link.l1 = "그렇다면 그렇게 하시오. 맹세를 다 이루고 나면 어디에서 그대를 찾아야 하오?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "나는 한 달 안에 내 일을 끝낼 생각이오. 그 후에 롱웨이는 바세테르 선술집에서 당신을 일주일 더 기다릴 것이오.";
			link.l1 = "뭐, 네가 뭐라 하든, 친구야. 작별은 아니야. 바세테르에서 다시 보자.";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "오, 안녕하세요, 선장님.";
			link.l1 = "네 미소가 마음에 안 들어, 나리.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "저는 참담합니다. 당신이 마침내 자유로워졌다는 소식을 전하러 왔습니다. 하지만 이 호화로운 선실에 좀 더 머무르고 싶으시다면, 얼마든지 그러셔도 됩니다.";
			link.l1 = "전혀요. 그럼, 롱웨이가 잡혔나요? 어디에 있죠? 감방 중 하나에 있나요?";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "다른 세상 같았더라면, 그는 우리 누구와도 말하지 않고 곧장 전투에 들어갔을 겁니다.";
			link.l1 = "젠장! 그냥 그 자를 생포할 수도 있었잖아.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "어떤 사람들은 붙잡는 것보다 죽이는 게 훨씬 쉽다는 거, 모르나? \n우리가 당신한테 아무런 원한도 안 품고 있다는 걸 다행으로 알아야 해. 당신네 중국인이 또 한 번 학살을 저질렀고, 그를 상대하려면 명사수 몇 부대가 더 필요했으니까.";
			link.l1 = "그래요, 정말입니다. 그 점에 대해 감사드립니다.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "그런데, 그가 당신 친구였으니 말인데, 우리가 그의 시신에서 서류 몇 장을 발견했소. 무슨 문서인지는 잘 모르겠더군. 당신이 더 잘 알겠지. 피로 덮이지 않은 부분에는 뭔가 알아볼 수 없는 글씨가 적혀 있었소.";
			link.l1 = "그건... 젠장. 돌려줘서 고맙다. 잘 가, 장교.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "우리와 함께 가시오, 사령관께서 당신과 이야기하고 싶어 하신다.";
			link.l1 = "제 추측이 맞다면, 이것이 제가 중국인을 찾는 일과 관련이 있습니까?";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "직접 보게 될 것이오, 나리.";
			link.l1 = "제가 뭔가 죄를 지었다는 겁니까?";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "전혀 아닙니다. 아무도 당신을 체포하거나 구금하려는 게 아닙니다. 지금은요. 제가 사령관께서 당신과 이야기하고 싶어하신다고 말했을 때, 그 말 그대로의 의미였습니다.";
			link.l1 = "아, 그래...";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "아이디어 있어? 이 누런 피부의 사내는 정말 치명적으로 위험해. 우리 말고도 여기에 파견된 조가 처음이 아니야. 명령은 명령이지만, 제대로 된 계획 없이 들어가서 멍청하게 죽고 싶진 않아.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "그 자는 저 안에 혼자 있고, 나는 당신과 함께 있어. 내가 상대할 테니, 너희는 나를 엄호하는 데 집중해. 우리는 해낼 거야.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "하나 있지. 너희 모두 여기서 죽게 될 거야.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "걱정 마, 우리는 그냥 그와 얘기만 할 거야.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "미안하지만, 오늘 너희 모두 죽게 될 거야. 그리고 그 죽음은 중국인의 손에 의한 것이 아니야.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "그래서 현상금 사냥꾼은 아니란 말이지... 하지만 설령 그렇다 해도, 넌 그 빌어먹을 중국놈의 친구잖아!";
				link.l1 = "맞아. 어차피 널 없애야 했으니, 피할 수 없는 일을 미룰 이유는 없지.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "무슨 말이야?! 도와주겠다고 약속했잖아!";
				link.l1 = "당신은 어차피 우리에게 평화로운 출구를 주지 않았을 거라고 생각해. 개인적인 감정은 아니야.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "나도 그렇게 믿고 싶군.";
				link.l1 = "난 더한 것도 겪어봤다. 중국인 한 놈쯤이야 우릴 끝장내지 못해. 가자, 이놈들아!";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "만약 대화가 계획대로 풀리지 않으면 어떻게 하시겠습니까?";
				link.l1 = "그건 싫지만, 그렇다면 나도 스스로를 지켜야겠지. 가자.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "나리 선장?! 롱웨이는 당신이 저들과 함께 있다는 걸 믿을 수 없소!";
			link.l1 = "아니야, 롱웨이, 난 그냥 얘기하러 온 거야! 네가 생각하는 그런 게 아니야!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "그럼 혼자 왔겠지. 네가 이 병사들 도움으로 나를 공격하려고 내 경계를 풀려고 하는 거잖아!";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "할 수 있다면 했겠지. 내가 아니었으면 벌써 너를 공격했을 거야. 진정하고, 우리 얘기 좀 하자, 그치?";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "헛소리 집어쳐! 내가 원했다면 넌 이미 죽었어. 무기 내려놔, 그리고 얘기하자. 이건 네 선장의 명령이다.";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "예. 롱웨이가 당신을 믿습니다, 나리 선장.";
			link.l1 = "자, 이제 좀 낫군. 이제, 말해봐...";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "나리, 무슨 일입니까? 이건 대체... 감동적인 재회라도 되는 겁니까? 당신은 우리와 함께 그 중국 야만인을 제거하기로 했던 것 아닌가요?";
				link.l1 = "그래, 나다. 나는 저자를 데리고 간다. 이제 이 살육은 끝날 거다. 너는 사령관에게 우리가 함께 저자를 죽였다고 전해라. 약속하지?";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "잘했어요, 선장님! 그가 무기를 내려놨어요. 당신이 우리와 함께 있어서 든든하군요. 이제 그를 사령관에게 데려갑시다.";
				link.l1 = "내가 왜 그래야 하지? 나는 롱웨이의 행동에 대해 금화로 벌금을 냈어, 그것도 넉넉하게. 네 동료 장교들이 증인이었으니, 그들이 확인해 줄 거야. 지휘관이 내 부하를 데리고 배로 돌아가도 된다고 허락했어.";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "사령관은 이 피 묻은 금에 질렸을지 몰라도, 나는 아니야. 그 피투성이 동굴에서 그가 죽인 놈들 중엔 내 친구들도 있었지. 게다가, 우리가 그 중국인을 죽인다고 해도 그가 신경이나 쓸지 의문이군.";
			link.l1 = "정말 알고 싶은 거야? 그리고 네 친구들이 죽은 일에 대해서도... 그 뻔뻔한 도적 무리에 대해 들어본 적 있지? 분명 그놈들 짓이었을 거야.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "롱웨이, 네가 그들이 주장하는 것만큼 많은 병사들을 죽인 건 아니지, 그렇지?";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "맞습니다, 나리 선장. 롱웨이가 그 무리를 봤습니다. 그들이 롱웨이를 눈치채지 못하게 동굴 더 깊은 곳에 숨어 있었지요. 그리고 롱웨이는 도적들과 군인들 사이에서 말다툼, 욕설, 싸움 소리가 들리는 것도 들었습니다.";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "보이시죠? 다 맞아떨어져요. 롱웨이는 성질이 좀 있지만, 정직한 사람이에요. 우리는 떠날 거예요. 우리를 건드리면 당신들 제복에 수치를 안기게 될 거예요. 안녕히 계세요, 신사 여러분.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "말도 안 돼, 나리! 저 자식이 우리 사람들을 잔뜩 죽였는데, 이제 와서 그냥 넘어가자고?! 우리랑 같이 그 놈을 죽이든가, 아니면 제발 방해나 하지 마!";
			link.l1 = "유감이지만, 내가 끼어들어야겠소. 정말 미안하오.";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "그냥 대화하려는 거였다면, 무장 해제하라고 하지 않았겠지. 하지만 호랑이는 발톱을 감추고 있어도 여전히 호랑이야. 너는 이미 오래전에 롱웨이를 배신하기로 마음먹었겠지-거짓말할 필요 없어. 방어해라, 선장!";
			link.l1 = "젠장!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "그 사람하고 어떻게든 통과했다니 믿기지 않아! 그런데, 왜 그가 너를 선장이라고 불렀던 거야?";
				link.l1 = "겉보기보다 더 복잡해, 친구. 네 지휘관을 안심시켜야 했거든. 중요한 건 결과잖아, 그렇지? 그리고 결과는 롱웨이가 죽었고, 내가 그 일에 네게 도움을 줬다는 거야.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "네가 있어도 소용없었어 - 그래도 우리를 덮쳤지. 젠장할 야만놈...";
				link.l1 = "그 사람에 대해 그렇게 말하면 안 돼. 그는 화가 나서, 내가 너와 함께 있다고 생각해서 우리를 공격한 거야.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "아마도. 그렇다면, 안녕히 계시오, 나리. 우리가 직접 사령관에게 중국인이 드디어 죽었다고 전하겠소.";
				link.l1 = "좋아요, 고마워. 잘 있어라, 얘들아.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "화가 났든, 야만적이든, 그게 뭐가 달라지겠어 - 저 자식이 먼저 우리 사람들을 많이 죽였고, 피를 처음으로 흘린 건 그놈이야.";
				link.l1 = "무언가가 그를 그런 상태로 몰아넣었겠지. 하지만 그 일에 너무 집착하지 맙시다. 나는 이만 가보겠소, 당신도 적당할 때 사령관에게 돌아가시오. 그럼 이만.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "정의의 섬?";
			link.l1 = "그래! 너를 찾으려고 온 동네를 다 뒤졌어, 롱웨이. 네가 마을을 꽤 뒤흔들었더라. 할 얘기가 많으니, 당장 배로 돌아가자.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "저기다!";
			link.l1 = "손님이 온 것 같군. 조금 늦을 것 같아.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "더 온다!";
			link.l1 = "고집 센 놈들이네, 그건 인정하지. 여기선 너무 노출돼 있어. 동굴로 가자. 거기서 방어하기가 더 쉬울 거야.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "여기서 영원히 머물 수는 없어.";
			link.l1 = "이 모든 일이 벌어진 후에 네가 제일 먼저 할 말이 그거야, 롱웨이? 이제는 무슨 일이 벌어지고 있는지 설명할 때가 되지 않았다고 생각하지 않아?";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "나리 선장님, 롱웨이...";
			link.l1 = "하지만 네 말이 맞아 - 여기 머물 수는 없어. 또 다른 무리가 오기 전에 움직이자. 배가 출항하면 그때 얘기하자.\n";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "백인들의 교활함과 악의에는 한계가 없소.";
			link.l1 = "이봐, 나도 백인이라고! 게다가 네가 그들의 친구와 동료 병사들을 죽였잖아 – 그들이 화낼 권리 충분히 있어.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "용서하시겠습니까, 나리 선장?";
			link.l1 = "용서하네, 롱웨이. 그리고 사람을 피부색으로 판단하지 말라고 권하고 싶네. 자네야말로 그걸 가장 잘 알 테지. 방해를 받았군... 어디까지 이야기했더라...?";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "선장님! 뒤에요!";
			link.l1 = "아, 오늘은 제대로 대화도 못 하게 하겠군...";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "알겠습니다, 나리 선장.";
			link.l1 = "좋아, 하지만 여기서 오래 머물지 말자. 너랑 나, 할 얘기가 많아. 따라와. 배로 돌아가자.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
		
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "정의의 섬, 정말 당신이십니까...?";
			link.l1 = "그래, 롱웨이. 괜찮아?";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "롱웨이는 괜찮소. 감사합니다. 하지만, 선장님! 저것을 보시오!";
			link.l1 = "동굴로 달려가, 서둘러! 거긴 방어하기 좋은 위치야!";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "롱웨이가 아직도 군인들이 오고 있는지 확인할 거야.";
			link.l1 = "같이 가자 - 우리 힘만으론 주둔군 전체를 막아낼 수 없어.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "예, 나리 선장님?";
			link.l1 = "우리가 할 이야기가 많소. 이제 나를 따라오시오 - 즉시 닻을 올려야 하오.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// Этап 2, СТРАНИЦЫ ИСТОРИИ
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "다시 한 번 도와주셔서 감사합니다, 나리 선장님. 궁금한 점이 많으시겠지요.";
			link.l1 = "그건 아주 약하게 말한 거야. 왜 그 병사들을 죽였지? 넌 재미로 사람을 죽이지 않아. 나 그건 알아.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "아니, 롱웨이는 그렇지 않소. 병사들이 롱웨이를 막으려 했고, 감옥은 선택지가 아니었소. 그자들은 중국인 말은 듣지 않소—오직 백인만이 그런 예우를 받지.";
			link.l1 = "그 자들도 다른 백인들 말 잘 안 듣는 경우 많지요, 하지만 무슨 말인지는 알겠소. 그래도, 도시 한복판에서 소 잡듯이 학살하다니? 바스테르에서 뭘 하고 있었던 거요?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "백인들은 내 말을 자주 듣지 않을 뿐만 아니라, 때로는 아예 말조차 하지 않소. \n그리고 입을 열 때면, 경비병을 부르기 위해서지. \n롱웨이는 자신의 피부나 눈을 선택하지 않았지만, 자신이 누구인지 자랑스럽소. \n병사들이 조롱하고 위협할 때, 롱웨이는 지치고... 분노하오.";
			link.l1 = "이제부터 함께 일하자. 사람들은 보통 경비병을 부르지 않고 나한테 말을 걸지... 대부분은 그래. 그런데 진심으로, 네 임무에 대해 말해 봐. 내가 도와줄게.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "부디, 나리 선장님, 롱웨이를 이해해 주십시오. 그는 이 일을 혼자 하겠다고 맹세했습니다.\n그를 몰아붙이지 마십시오. 그 정도는 롱웨이에게 빚진 셈입니다.";
			link.l1 = "진심으로 감사하지만, 그때 나는 직접 반 메르덴을 처리할 수 있었소. 하지만 우리는 처음부터 서로 빚을 졌지—내가 당신의 체면을 살려줬고, 당신은 내 목숨을 구했으니. 이제 내가 또다시 당신을 구했소.";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "흠... 맞아요, 나리 선장. 롱웨이는 백인들 중에서 당신이야말로 진정한 친구라고 믿고 있어요. 예전에 한 번 그렇게 생각한 적이 있었지만, 그땐 참혹하게 속았지요. 존 머독 기억나시나요? 요한 반 메르덴은요?";
			link.l1 = "반 메르덴을 언급하다니 참 이상하군요. 최근에 누군가 내 눈앞에서 그의 기록 보관소에서 몇 장을 찢어갔습니다.\n그 일이 당신 사건과 관련이 있었습니까? 도둑을 찾았나요?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "제가 했습니다. 도둑은... 롱웨이였습니다. 그는 정말 죄송하다고 합니다, 나리 선장님. 그때는 당신을 완전히 믿을 수 있을지 몰랐답니다.";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "우정에 대해 말하면서 내 뒤에서 내 것을 훔쳐? 이번이 처음이자 마지막이야, 롱웨이. 알겠어?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				Notification_Reputation(false, 61, "low");
			}
			else
			{
				link.l1 = "그런데 어떻게 해낸 거지, 롱웨이?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				Notification_Reputation(true, 61, "low");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "롱웨이 이해했소. 진심이오.";
			link.l1 = "그러길 바란다. 이제 어떻게 이런 삶을 살게 되었는지 말해라 - 누구에게, 언제, 어떤 약속을 했는지.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			Notification_Approve(false, "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "예, 나리 선장님\n롱웨이는 자신에게 남은 가장 중요한 생존자, 창싱을 찾으려 합니다.";
			link.l1 = "창싱, 그가 네 가장 친한 친구야?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "당신의 친절 덕분에, 다른 선원들도 금방 나에게 익숙해지고 신뢰하기 시작했습니다.";
			link.l1 = "그래, 알겠어. 칭찬 듣는 건 별로 안 좋아하는구나. 그래도 수고했어, 롱웨이... 네가 네 난입으로 남긴 엉망진창을 제대로 치웠다면 말이지.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "그래. 하지만 그럴 시간 없어.";
			link.l1 = "그런 것 같진 않네. 하지만 다시는 그러지 마, 그치? 필요한 거 있으면 그냥 말해. 나 믿어도 돼. 이제, 네 맹세에 대해 말해봐.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "물론입니다, 롱웨이는 자신의 짐을 나리 선장과 기꺼이 나누려 합니다.\n롱웨이는 자신에게 남은 가장 중요한 생존자, 창싱을 찾으려 합니다.";
			link.l1 = "창싱, 그 사람이 네 가장 친한 친구야?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "창싱은 내 가족, 내 누이야. 몇 해 전에 사라졌지. 그녀를 찾으려고 롱웨이는 그녀의 행방을 알 만한 자들을 찾아다닌다.";
			link.l1 = "이게 반 메르덴의 기록 보관소와 무슨 관련이 있지? 네 누이의 실종과도 연결되어 있는 거야?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "맞아요. 모든 것이 연결되어 있죠. 롱웨이와 요한은 내가 이 군도에 오기 훨씬 전, 당신들이 포르모사라 부르는 땅에서 여러 해 전에 만났어요.";
			link.l1 = "서로를 그렇게 오랫동안 알고 지냈다고? 그리고 판 메르덴이 관련되어 있었다고? 대단한 이야기네! 그 사람이 네 여동생 실종과는 어떤 관련이 있었던 거야?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "그는 내가 아주 나쁜 자들을 찾는 데 도와주었소—백인들의 기준으로도 악랄한 자들 말이오. 올리베이로 페르멘텔로스, 안톤 판 디멘, 그리고 요프 판 데르 빈크.";
			link.l1 = "이름을 보아하니, 한 명은 포르투갈인이고, 나머지 두 명은 네덜란드인입니다.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "네, 맞아요. 하지만 수색은 성공하지 못했어요. 롱웨이는 하늘의 인도를 조용히 기다렸죠. 그래서 당신이 반 메르덴의 기록을 손에 넣었을 때, 저는 그것을 연구하기로 결심했어요. 올리베이로에 대한 첫 언급이 나온 페이지를 발견하자마자, 그걸 찢어내고 선실에서 도망쳤어요.";
			link.l1 = "모든 것이 마침내 이야기 속에 맞아떨어진다.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = "하지만 이야기는 이제 막 시작됐습니다.\n나리 선장, 롱웨이의 수색이 처음부터 어떻게 시작됐는지 듣고 싶으십니까?\n앉아서 들을 준비가 되셨습니까?";
			link.l1 = "바로 그래서 당신을 선실로 부른 거요. 계속 하시오.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "중국인들은 여기 들어올 수 없다. 여기는 체면 있는 사람들이 오는 점잖은 곳이지, 너 같은 자들이 올 곳이 아니다.";
			link.l1 = "질문이 하나 있습니다. 그것만 묻고 가겠습니다.";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "먼저 제대로 말하는 법부터 배워라! 내가 말했지-너 같은 놈은 여기서 환영받지 않는다고.";
			link.l1 = "Oliveiro Fermentelos는 어디에 있지? 말해 주면, 바로 떠나겠다.";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "너도 귀가 멀었나? 내 인내심을 시험하지 마라, 아니면 이 방 전체가 곧 노란 내장 냄새로 가득 찰 테니.";
			link.l1 = "내 민족은 수천 년 동안 이곳에서 살아왔소. 여기는 우리 섬인데, 우리가 평범한 선술집에도 들어갈 수 없다니?";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "오, 큰소리치는군? 그 말로 목이 달아날 수도 있겠어. 나가!";
			link.l1 = "...";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "네 큰 문제에 대해 들었어, 내 작은 친구야. 너무 시끄럽게 굴지 말았어야지—이름도, 장소도 다 틀렸잖아.";
			link.l1 = "이 남자에 대해 뭔가 아시오?! 말해 보시오!";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "진정해, 이봐.";
			link.l1 = "죄송합니다.";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "네 사과는 필요 없어. 하지만 돈은 필요하지. 그러면 도와줄 수도 있지. 나는 마르셀로 슐테야. 너는? 돈 있지?";
			link.l1 = "내 이름은 창 투다. 돈은 있다. 그걸로 충분한가?";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "(휘파람) 에스쿠도, 페소, 길더, 두블룬... 그리고 너희들이 쓰는 이상한 동전도 좀 있네. 이 정도면 충분해. 그치, 충충? 그 남자에 대해 알아볼 수 있는 건 알아볼게. 걱정 마, 난 거의 매일 여기 있으니까 네 돈은 안전해. 매일 들러봐, 분명 다시 마주칠 거야.";
			link.l1 = "바라지요. 더 이상 가진 돈이 없습니다...";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A few days have passed,"+ NewStr() +"April 4, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "아, 창창! 벌써 와 있었군.";
			link.l1 = "창투다.";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "상관없어, 친구야.";
			link.l1 = "올리베이로가 어디 있는지 알아냈습니까?";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "아니, 전혀 모르겠어.";
			link.l1 = "내 돈!";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "그렇게 예민하게 굴지 마! 내가 아무것도 알아내지 못했다면 감히 다시 너한테 다가왔겠어? 네가 찾는 걸 아는 사람을 소개해 줄 거야. 운 좋은 줄 알아, 그 사람은 너희 아시아인들을 아주 좋아하거든. 하인도 있고, 심지어 하녀들도 있어. 네 더러운 언어도 배우고 있지. 이름은 요한 판 메르덴이야. 관저 근처 2층 집에서 널 기다릴 거야.";
			link.l1 = "감사의 말씀을 드립니다.";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "당신이 창창 맞지? 들어와, 부끄러워하지 말고.";
			link.l1 = "창투다.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "그런가요? 사과드립니다. 그 마르셀로와 그의 농담 퍼레이드란... 안타깝게도 당신 문화에 관심을 가지는 이가 너무 적군요. 단지 언어가 다르고, 눈매가 다르다는 이유로 말입니다. 하지만 당신은 똑똑하군요. 흑인들과는 다르게, 헤헤헤.";
			link.l1 = "(만다린어로) 밀수업자가 거짓말한 게 아니었군-정말로 교양 있는 분이시네. 그리고 정말로 우리 말을 할 줄 아시오?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "제 문화에 대해 따뜻한 말씀 해주셔서 감사드립니다. 당신이 요한 판 메르덴 맞으신가요?";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "오... 몇 마디밖에 이해하지 못했소. 아직 배우는 중이오. 네덜란드어로 계속해 주겠소?";
			link.l1 = "원하시는 대로. 당신이 Johan van Merden입니까?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "그래, 청투, 그게 나다. 올리베이로 페르멘텔로스를 찾고 있다 들었지. 어디 있는지 알지만, 먼저 말해라-왜 그를 찾는 거지? 네 대답에 따라 내 대답도 달라질 거다.";
			link.l1 = "그자는... 내 마지막이자 가장 소중한 가족, 내 여동생 창싱을 납치했소.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "그럼 실망시켜야겠군, 창 투. 이제 그녀에게는 아마도 희망이 없을 거야. 부유한 플랜터에게 노예로 팔렸거나, 아니면 사창가에 팔렸을 가능성이 높아. 어느 쪽이든, 네가 그녀를 구할 수는 없을 거다.";
			link.l1 = "나는 창싱이 아직 살아 있다고 믿소. 올리베이로가 그녀를 탐냈지. 그녀는 당당하게 거절했소. 내가 집에 없을 때 그는 그녀를 납치했소. 그리고... 우리 부모님을 죽였소.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "저... 정말 미안해. 만약 그렇다면, 창싱-맞지?-아직 살아 있을지도 몰라. 이렇게 하자: 올리베이로가 지금 정확히 어디에 있는지 알아볼 시간을 좀 줘. 일주일 정도면 될 거야. 그때 다시 만나자. 도시 성문 밖에서 만나-여기서 누가 널 지켜보고 있을지 아무도 모르니까. 난 익숙한 것 이상으로 엮이고 싶지 않아, 이해해 주길 바란다.";
			link.l1 = "저는... 저는 정말 깊이 감사드립니다, van Merden 나리. 다음에 또 뵙기를 고대하겠습니다.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A week has passed,"+ NewStr() +"April 11, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "안녕, 청투. 네 눈에서 불꽃이 보이는구나. 소식이 있긴 한데, 좋은 소식은 아니야.";
			link.l1 = "어떤 소식이든 저에게는 지극히 중요합니다. 부디 말씀해 주십시오, van Merden 나리.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "그래... 페르멘텔로스는 한 달쯤 전에 바타비아로 떠났어. 그에 대해 내가 가진 유일한 단서지. 좋은 소식은, 그자가 거기서 한동안 머물 계획이라는 거야. 지금 가면 잡을 수 있을 거야. 나쁜 소식? 그는 총독 안토니 판 디멘의 절친한 친구야. 네가 그에게 가까이 가는 건 불가능할 거다.";
			link.l1 = "이 소식이면 충분합니다. 미천한 저의 감사를 드립니다, van Merden 나리. 저는 곧바로 떠나겠습니다.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "뭔가 네가 그렇게 말할 것 같아서, 너와 창싱에게 좀 더 공평한 기회를 주려고 했어. 내 오랜 친구 올리버 트러스트에게 편지를 썼지. 그는 바타비아에서 가게를 운영해. 나한테 신세를 진 사람이니, 너를 도와줄 거야.";
			link.l1 = "나... 무슨 말을 해야 할지 모르겠어...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("Вы получили письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "간단히 “고맙다”면 충분해. 도시에서 올리베이로를 못 찾겠으면, 모닝 스타를 찾아봐. 그의 배를 통해서라면 언제든 그를 추적할 수 있어. 행운을 빌어, 친구여—너와 네 여동생 모두에게 필요할 테니.";
			link.l1 = "진심으로 감사드립니다, van Merden 나리.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Batavia,"+ NewStr() +"May 29, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "너는 누구지, 여기서 뭐 하는 거야? 나는 너희 같은 족속과는 거래하지 않아.";
			link.l1 = "당신에게 줄 편지가 있습니다.";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "아, 전령이군! 오늘은 편지를 기대하지 않았는데. 여기 있어! 내가 확인해 볼게.";
			link.l1 = "당신이 올리버 트러스트요? 반 메르덴이 저를 당신에게 보냈소.";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "나 글은 읽을 줄 알아. 원래라면 널 내쫓았겠지만, van Merden 같은 자들은 거절을 모르는 법이지. 드디어 van Diemen과의 결판을 낼 때가 왔군.";
			link.l1 = "내 목표는 페르멘텔루스야. 반 디멘은 어때?";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "그건 네가 알 바 아니다. 내가 이렇게라도 도와주는 걸 감사히 여겨라. 이제 잘 들어, 내가 이 일이 잘못됐다고 판단하기 전에. 페르멘텔로스를 나는 안다. 그는 한동안 여기 있었지만, 이제 더 이상 여기 없다. 모닝 스타는 몇 주 전에 떠났다. 언제 돌아올지는 신만이 알겠지. 그러니 네 목표가 바뀌었다. 이제 네 목표는 페르멘텔로스의 친구다...";
			link.l1 = "... 판 디멘.";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "그래. 그것도 알고 있군? 요한이 말해줬나? 오, 반 메르덴... 넌 참 대담한 놈이야. 하지만 이미 반 디멘에 대해 안다면, 그의 높은 지위도 알겠지? 총독에게 어떻게 접근할 생각이지? 설마 그의 관저를 습격할 생각은 아니겠지!";
			link.l1 = "Chang Tu는 숙련된 전사다.";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "실력 있는 전사라, 그렇소? 이제 우리 모두 엉켜버린 거 알지? 그리고 자네가 붙잡히면 나는 어떻게 되는 거지? 자네와 내 안전을 위해 도와줄 수밖에 없겠군. 그리고 Van Diemen은 저택에 머무는 것 외에도, 도시 밖 농장과 그의 정부 Vette에게 정기적으로 들르지.";
			link.l1 = "저를 도와주겠다고 하셨지요.";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "모든 사람에게는 열정이나 취미가 있어야 한다고 생각해. 나는 희귀하고 값비싼 무기를 수집하지. 어떤 것은 역사가 있고, 어떤 것은 없지만, 항상 치명적이야. 내 수집품이 자네의 성전에 도움이 될 수 있지. 그러니 말해보게, 어디에서 반 디멘을 습격할 계획인가?";
			link.l1 = "(거처) 좋은 무기가 이렇게 많으니, 내가 제일 좋은 칼을 가져가겠다. 이 칼만 있으면 창투는 백인들 사이에서 무적이 될 것이다.";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = "(플랜테이션) 플랜테이션 길목에서 매복하겠소 - 놈들은 도망칠 곳이 없을 거요.";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "(안주인) 안주인 쪽에는 사람이 많지 않을 테니, 경비들도 제때 반응하지 못할 거야.";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом...
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "좋은 선택이오! 감탄했소. 제대로 활용하려면 좋은 화기가 필요하오. 말해보시오, 창투, 사거리가 얼마나 되오?";
			link.l1 = "솔직히 말해서... 너무 멀면 안 돼, 반드시 놓치지 않아야 하니까."
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance1";
			link.l2 = "나는 멀리서 공격하겠소 - 내 적은 어디서 내가 공격했는지도 모를 것이오.";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification(GetConvertStr("Sniper", "AbilityDescribe.txt")+" Unlocked", "Longway");
			SetCharacterPerk(pchar, "Sniper");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("Вы получили башенный мушкетон");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "grapeshot");
			
			dialog.text = "알겠습니다. 그렇다면, 이걸 받으십시오! 고대 포르투갈산 타워 블런더버스입니다. 대구경 탄환을 쏘지요. 이런 무기는 이제 구세계에서도 더 이상 만들지 않습니다.";
			link.l1 = "어렸을 때 하나 본 적 있어...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "그래서, 그걸 쓸 줄 아시오?";
			link.l1 = "아니...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "명심하세요, 교환식 장치는 시간이 지나면서 녹슬었어요.\n기름으로도 고칠 수 없어요 – 완전히 망가졌거든요.\n장전을 하기가 어렵지만, 지금 해봅시다.\n잘 보세요 – 이렇게 약간 힘을 주어야 해요.\n하지만 너무 세게 하면 부러질 수 있으니 조심하세요.";
			link.l1 = "이렇게?";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "정확합니다.";
			link.l1 = "알겠습니다. 정말 감사합니다!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("Вы получили двуствольный штуцер");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "bullet", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "bullet");
			
			dialog.text = "진정한 예거군! 조심하게, 이건 선물이었네. 무기가 화려하면서도 치명적인, 드문 경우 중 하나지. 더블 배럴 사냥용 라이플이야! 들기엔 무겁지만, 다루긴 쉽지. 아직 쏘는 법은 익혔나?\n";
			link.l1 = "알겠습니다. 정말 감사합니다!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = "경비병들에 대해선 맞는 말이지만, 위험을 과소평가하지 마시오. 반 디멘은 도시에서 오른팔인 요프 반 데르 빈크 없이 절대 움직이지 않소.";
			link.l1 = "그래서, 그들이 베트와 함께 있는 건가...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("Naval Skills +", "Longway");
			notification("Rat Wolf Unlocked", "Longway");
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "뭐라고? 하! 상상력이 참 풍부하구나, 차이나맨! 안툰은 겁쟁이고, 반 데르 빙크는 누가 그들의 '사적인 시간'을 방해할까 봐 그를 지키고 있지.\n요프는 항상 두꺼운 참호 갑옷을 입고 다녀. 대부분의 냉병기로는 뚫을 수 없어. 그래서 너도 특별한 게 필요하지. 이 레이피어를 가져가. 길고, 다른 칼보다 튼튼하며, 좋은 검처럼 무게감도 있지.";
			link.l1 = "갑옷 입은 적과 싸우려고 레이피어를...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("Вы получили асоледу");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "갑옷 자체를 노리지 마. 이건 에스톡이 아니야. 틈새나 약한 부위를 노려, 사타구니, 겨드랑이, 목 같은 곳 말이야. 상대를 지치게 하고, 네가 주도권을 쥐어. 요프는 무거운 도끼도 쓰니까, 그의 공격을 막으려 하지 말고 피하는 게 좋아\n혹시 빈틈을 못 찾을 경우를 대비해서 이 블런더버스를 가져가. 보통은 산탄이 들어가 있지만, 널 위해 강철 화살 세트도 준비해 뒀어.";
			link.l1 = "머스킷에 쓸 화살...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("Вы получили бландербуз");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "특이하지? 옛것과 새것이 섞여 있어. 한 손으로 쏘게 설계됐지만, 너무 무거우면 두 손을 써. 많은 사람들이 그렇게 해\n그리고 여기, 이 등나무 갑옷을 입어 봐. Joep의 흉갑보다는 가볍지만, 그래도 꽤 보호가 돼. 저자의 도끼가 제대로 박히게 두지 마. 밀라노 갑옷도 그런 무기 앞에선 버티지 못할 거야. 이해했어?";
			link.l1 = "네, 이해했습니다. 고맙습니다, Trust 나리!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили кожаный корсет");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "자신만만하군, 그렇지? 내가 내 수집품 이야기를 너무 일찍 꺼냈던 걸지도 모르겠군. 하지만... 이미 각오했잖나. 대낮에 저택을 공격하다니, 대담한 짓이야. 누구도 예상 못 했겠지. 이 검이 자네에게 딱 맞을 거다. 세상에서 가장 좋은 건 아니지만, 찌르고, 베고, 찍는 데는 완벽하지.";
			link.l1 = "클레왕! 이 칼을 알아보겠어. 이웃 섬 사람들은 종종 이런 걸 쓰지.";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification(GetConvertStr("TannedLeather", "AbilityDescribe.txt") +" Unlocked", "Longway");
			SetCharacterPerk(pchar, "TannedLeather");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "전에 이런 걸 써본 적 있나? 좋아. 시간이 별로 없고, 상대해야 할 적은 많을 거야. 자, 이것도 가져가. 세 개의 총열이 달린 권총이야. 아름답게 장식되어 있지. 지금 내 앞에서 장전해. 나중엔 그럴 시간이 없을 테니까. 그리고 이 결투용 조끼도 입어. 가볍고, 네게 필요한 속도를 줄 거고, 어느 정도 보호도 해줄 거야.";
			link.l1 = "감사합니다, Trust 나리!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили клеванг");
			//Log_Info("Вы получили трёхствольный дробовик");
			//Log_Info("Вы получили жилет бретера");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "잠깐, 아직 끝난 게 아니오. 당신이 살아남는 것이 우리 모두에게 이익이오. 이 약을 받아두시오, 전투 후에 상처를 치료하는 데 쓰시오. \n그리고 이 엘릭서도 가져가시오. 맛과 냄새는 끔찍하지만, 몸속의 어떤 독도 다 없애주오. 요프 판 데르 빙크, 반 디멘의 경호원 놈이 무기에 그 더러운 걸 바르거든. 건방진 자식이지, 그러니 이걸로 당신이 유리할 거요.";
			link.l1 = "제가 당신께 충분히 감사드릴 수 있을지 모르겠습니다, 트러스트 나리...";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("Вы получили 10 лечебных зелий");
			//Log_Info("Вы получили противоядие");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "네가 나한테 해줄 수 있는 최고의 감사는, 만약 잡히더라도 날 밀고하지 않는 거야.\n뭐, 대부분의 경우 넌 그냥 그 자리에서 죽임을 당하겠지만.\n그래도 혹시 살아남는다면, 반 디멘에게 네 죽음은 내 덕분이라고 전해 줘. 할 수 있겠어?";
			link.l1 = "문제없습니다. 다시 한 번 감사드립니다, 트러스트 나리. 안녕히 계십시오!";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "멈춰! 어디 가는 거냐, 차이나 놈?";
			link.l1 = "관저로.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "그건 수사적인 질문이었어, 천재야. 누가 너 같은 놈을 거기에 들여보내 줄 거라고 생각하지?";
			link.l1 = "나는 반 디멘 나리와 볼 일이 있다. 지나가게 해 주시오.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "총독의 이름을 알고 있군? 좋아... 무슨 일로 왔는지 말해 봐. 내가 전해주고 답을 가져오지.";
			link.l1 = "내 대화는 반 디멘 나리와만 하는 거다. 그분이 나를 기다리고 있어. 비켜라, 아니면 후회하게 될 거다.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "그래, 그래, 눈 찢어진 놈아, 잘난 척하지 마라. 내 방식대로 하든가 아니면 아무것도 없어.";
			link.l1 = "그럼 내 방식대로 하겠소.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "망할 촌놈! 누가 너를 고용했지? 내가 그놈보다 더 많이 줄 테니!";
			link.l1 = "너희 백인들은 금밖에 모른다. 용들이 너희 족속을 저주하길 바란다. 나는 정보를 얻으러 왔지만, 너희 사람들이 나를 들여보내주지 않는다.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "뭘 원하지?!";
			link.l1 = "페르멘텔로스. 지금 그는 어디에 있지?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "올리베이로? 그런데 대체 왜 그 자를 찾는 거야? 난 아무것도 말 안 해!";
			link.l1 = "그 자는 내 가족을 죽이고 내 여동생을 납치했다. \n내 충고를 듣지. 말을 시작하는 게 좋을 거다. \n자네를 위해서 하는 말이야.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "나한테 뭘 할 생각이지? 곧 주둔군 전원이 여기로 올 거야.";
			link.l1 = "린치라는 걸 들어본 적 있소? 내 문화에서 쓰는 형벌이오. '천 번의 칼질로 죽음'을 뜻하지.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "나에게 그렇게 많은 상처를 입힐 시간도 없을 거다, 이 멍청한 놈아!";
			link.l1 = "그건 비유적인 표현이야. 형리란 놈은 상처를 하나씩 내지. 아니면 몸의 일부를 잘라내기도 하고. 우리가 할 수 있는 만큼, 시간이 허락하는 만큼 계속하지. 네가 입을 열지 않는 한 말이야.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Joep";
			sld.lastname = "van der Vink";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "아-아-아!!! 멈춰! 멈추라고, 이 더러운 짐승아. 말할게, 다 말할 테니까. 제발 멈춰. 조에프! 드디어! 그동안 대체 어디서 뭐 한 거야?!";
			link.l1 = "정말 안 좋은 때군...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "Antoon? 지금 당장 의사를 봐야 해. 여기 일 끝나는 대로 데려다줄게. 이봐! 너 뭐 하는 짓이야, 이 비열한 도살자 놈아?!";
			link.l1 = "노란 도살자? 그거 마음에 드는군. 하지만 내가 꼭 알아야 할 질문이 하나 있는데, 아무도 대답하려 하지 않아...\n";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "무슨 질문?!";
			link.l1 = "Oliveiro Fermentelos는 어디 있지? 그것만이라도 말해 줄 수 없나?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "나는 페르멘텔루스 따위는 신경도 안 써! 누가 너한테 돈이랑 정보를 줬지?!";
			link.l1 = "올리버 트러스트. 그런데 그가 전해달라고 했소, 당신의 죽음은 그의 덕분이라고.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "신뢰?! 하하하하하하하! 그 구두쇠 놈, 우리가 그의 플랜테이션을 빼앗았다고 복수할 수 있다고 생각했나? 내가 너를 처리하고 나면 곧 그의 가게와 목숨도 가져가 주지.";
			link.l1 = "내 시간을 낭비하고 있군.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = "(만다린어로) 그럼, 매복하기 좋은 장소를 찾아보자.";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "(만다린어로) 이 녹슨 걸로는 가까이 가야 해. 빠른 일제 사격, 날카롭고 무자비하게. 공포와 혼란이 나머지를 처리해 줄 거야.";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "(만다린어로) 바로 여기. 처음엔 나를 보지도 못할 거야. 최고의 전투란 시작되지 않는 전투... 아니면 피 한 방울 적게, 빠르게 끝나는 전투지.";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "더러운 짐승 같으니... 도망친 노예지? 어떻게 그런 무기를 손에 넣었지? 누가 널 고용했나...?";
				link.l1 = "시간 없어! 올리베이루 페르멘텔루스가 어디 있는지 말해, 지금 당장!";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "헤헤헤, 웃기군... 시간이 없어 - 피가 배에서 쏟아지고 있어. 지옥에서 불타라, 이 이교도야...";
			link.l1 = "(만다린어로) 안 돼!!!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "(만다린어로) 왜, 왜, 왜?! 이제 내가 어떻게 페르멘텔루스를 찾아야 하지?!";
			link.l1 = "하지만 먼저, 나는 숨어야 해 - 누군가 이미 이 피바다를 보고했을 테니까...\n";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = "힉! 중국인이라니! 네가 여기 초대될 줄은 몰랐지. 구경하는 거 좋아하나 보군, 헤헤.";
			link.l1 = "여긴 왜 이렇게 사람이 많지...? 그리고 너는 누구야?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "내 옷차림을 보고도 나를 못 알아보겠어? 그리고 총독께 말할 때는 말조심해! 힉!";
			link.l1 = "그렇다면, 당신이 반 디멘 나리로군요. 무례를 용서하십시오. 여기서 무슨 축제가 열리고 있는 겁니까?\n";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "맞아, 내 착한 친구, 달리 방법이 있겠어! 여장 퍼레이드다! 하하하! 나쁘지 않네, 촌놈! 루터스라면 베트의 드레스를 입고 싶어 죽을걸, 하하하!";
			link.l1 = "루터스?..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "저런 한심한 남편 말이오, 자기 귀한 마누라가 다른 놈과 잠자리를 할 때 옷장 속에서 훔쳐보는 걸 좋아하지. 부인은 신경도 안 쓰더군!";
			link.l1 = "";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "그치, 베트, 내 사랑? 헤헤.";
			link.l1 = "(만다린어로) 대체 여기서 무슨 일이 벌어지고 있는 거지...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = "힉! 네가 방금 뭐라고 한 건 모르겠지만, 네 눈빛이랑 말투 보니까 내 말에 동의하는 거 맞지! 반 한은 진짜 변태야. 그런데 넌 뭐야? 일꾼이냐? 베트가 널 초대한 거야?";
			link.l1 = "나...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "여기 일꾼을 들이는 건 베트조차도 지나친 짓이야. 이 자는 분명히 길을 잃었고, 잘못된 곳에 온 거지. 이봐, 너. 여기서 나가. 그리고 본 건 전부 잊어버려. 네 주인은 누구냐? 우리가 그와 연락할 거고, 너희 둘 다 입 다문 대가를 받게 될 거다. 운이 좋으면 대륙에 있는 가족에게 돌아갈 수도 있겠지. 대답하고 꺼져.";
			link.l1 = "사실, 나는 일 때문에 여기 왔어.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "헤, 사업이라. 여기서 “사업”을 하는 건 미네르 판 디멘뿐이야. 나는 그 양반을 너 같은 자들로부터 지키는 게 일이지. 그리고 루터스는... 그냥 루터스답게 굴 뿐이고. 아니면... 베테가 정말 너를 여기 초대한 거냐?\n";
			link.l1 = " 아니, 나는 여기...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "내 사랑하는 베테가 정말 이런 누런 놈을 여기로 불렀겠어?! 당장 꺼져!!!";
			link.l1 = "그 비참한 머저리...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "아무도 너한테 말 안 해. 입 다물어. 자지나 자존심 있는 척하지 마.";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "간, 간통남이라고?! 아니야, 나는 그녀를 나 자신보다 더 사랑해. 하, 너 같은 멍청한 중국인은 그런 걸 이해 못 하겠지!";
			link.l1 = "(만다린어로) 미친 자식.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "꼬꼬꼬꼭?! 괜찮아! 그래! 다른 남자들이 내 사랑스러운 베테에게 더 큰 쾌락을 준다는 것, 그거면 됐지!";
			link.l1 = "내 고향에서는 이렇게 말하지. 남자는 손가락 하나만 남아도 여전히 남자라고. 네가 진짜 남자라면, 그 뜻을 알 텐데.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "나는 물론 그를 초대한 적 없어. 하지만, 알잖아, 꽤 괜찮은 사람이야. 너희 모두 떠난 뒤에도 남아 있을지도 몰라. 우리 집 개랑은 이미 해봤지만, 이런 건 한 번도 안 해봤어...\n";
			link.l1 = "닥쳐라, 남자들이 말하고 있잖아, 창녀야! 여기서 짐승은 너 하나뿐이야. 나는 일 때문에 왔다. 올리베이로 페르멘텔로스를 찾고 있다. 너희가 그의 친구들이겠지. 혹시 그가 어디에 있을지 말해줄 수 있겠나, 반 디멘 나리?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "Antoon, 그 자가 나를 모욕했어! 모욕했다고! 그냥 넘어갈 생각 아니지?!";
			link.l1 = "...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "헤헤, 미안하다, 친구야, 하지만 아가씨가 화났거든. 내가 예의범절 좀 가르쳐줘야겠어. 첫 번째 교훈이다.";
			link.l1 = "하지만 올리베이로를 찾는 내 수색에 도움을 줄 수 있겠습니까?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "죽은 일꾼에게는 아무 소용도 없지.";
			link.l1 = "(만다린어로) 모두 지옥에나 떨어져라...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);	//Нужно ещё раз, а то не бежит
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "(만다린어로) 젠장! 아무것도 배우지 못했어!";
			link.l1 = "(만다린어로) 나는 오늘을 절대 잊지 않을 거야... 경비병들이 오기 전에 여기서 나가야 해. 이 미친 집에서 들리는 소음 따위엔 그놈들이 신경도 안 쓰겠지만...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "(만다린어로) 신들이 오늘을 저주했소! 내가 그의 졸개를 처리하는 동안 반 디멘이 피를 흘리며 죽어갔소...!\n";
			link.l1 = "(만다린어로) 경비병들이 오고 있어. 여기서 싸워서 나가야겠어.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Formosa,"+ NewStr() +"26 July 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "오, 창창이잖아! 이번엔 무슨 일로 도움이 필요하니, 내 작은 친구?";
			link.l1 = "장투야... 무슨 뜻이오?";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "나에 대한 경멸이 줄줄 흐르고 있군, 그렇지? 필요하지 않았다면 여기 오지도 않았을 테지.";
			link.l1 = "반 메르덴이 어디 있는지 아시오? 그가 마을에 있소? 집에는 없더군. 그와 이야기해야 하오.";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "남자가 하루 종일 집에 틀어박혀서 노란 피부의 한 남자가 나타나기만을 기다릴 순 없지. 그도 섬에서 할 일이 있어. 오늘 밤엔 다시 마을로 돌아올 테니 걱정 마, 창창!";
			link.l1 = "감사합니다. 안녕히 가십시오.";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "이봐, 눈 찢어진 놈! 이 시간에 뭔 급한 일이라도 있나? 이 시각엔 멀쩡한 사람들은 다 자고 있거든.";
			link.l1 = "그럼 너는 어때?";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "잘 말했다! 우리는 지금 순찰 중이다! 듣자 하니, 노랗게 생긴 놈 하나가 마을을 어슬렁거리며 신을 두려워하는 사람들을 귀찮게 하고 있단다.";
			link.l1 = "누구인지 말씀해 주시겠습니까?";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "이제 그만 말하자 - 벌써 늦었고, 나도 슬슬 졸리기 시작하네.";
			link.l1 = "곧 당신의 잠은 영원해질 것이다.";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "창투, 괜찮아?";
			link.l1 = "머르덴 나리! 당신 덕분에 저는 괜찮습니다. 당신은 무사하십니까? 그게 가장 중요한 질문입니다.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "항상 남을 생각하는구나, 그렇지? 나도 그래. 네가 저들에게 공격당하는 걸 보고도 그냥 있을 수 없었어, 네가 잘 처리할 거란 걸 알면서도 말이야. 네 질문에 답하자면, 난 괜찮아, 그냥 좀 피곤할 뿐이야. 다리가 약간 후들거려. 괜찮다면 안으로 들어가자. 거기서 이야기하자.";
			link.l1 = "물론이지요, van Merden 나리, 어차피 여기는 나리의 집이니까요.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "이제 우리는 서두르지 않고, 평온하고 조용하게 이야기할 수 있소. 말씀해 보시오, 무엇이 그대를 내게로 이끌었소, 창투?";
			link.l1 = "맞습니다, van Merden 나리. 저는 방금 바타비아에서 돌아왔고, 그리고...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "잠깐. 혹시 불쌍한 창싱인가...?";
			link.l1 = "아니요, 전혀 아닙니다! 제발 아니길 바랍니다. 하늘이 아직도 그녀의 운명을 저에게 숨기고 있습니다. 그리고 페르멘텔루스에 관해서는... 그는 바타비아에 없습니다. 판 디멘은 아무런 도움이 되지 않았습니다.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "그럴 리 없지, 그는 올리베이로와 오랜 친구니까. 영국인들 말로는, 친구이자 범죄의 동료라더군. 그가 쓸만한 정보를 줄 리 없으니 놀랄 일도 아니지.";
			link.l1 = "그래, 너와 트러스트 덕분에 나는 강력한 무기를 손에 넣었어. 반 디멘을 습격해서 그를 심문하고 페르멘텔루스가 어디 있는지 알아내려고 했지. 하지만 아무것도 알아내기도 전에 그가 죽어버렸어...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "인상적이군. 이제야 사람들이 항상 아는 것을 말하고 싶어하지 않는다는 걸 깨달았나 보군. 그러니 다른... 설득 방법도 있다는 거지, 그렇지 않나. 네가 네 여동생의 죽음을 알게 돼서 그렇게 날뛰는 줄 알았네. 그런데 지금은 왜 나를 찾아왔지? 나는 이미 말했잖나, 페르멘텔루스가 어디로 가는지 모른다고. 가끔 바타비아에 들르는 것 말고는 말이야. 반 디멘이 사라졌으니, 마지막 실마리도 사라진 셈이지.";
			link.l1 = "하지만 당신은 많은 것과 많은 사람을 알고 있지요. 또 한 번 도와줄 수 있을 거라 생각했습니다. 예전처럼 페르멘텔루스에 대해 물어봐 줄 수도 있지 않을까요. 당신은 나를 잘 대해준 첫 번째 백인이었어요. 첫 번째... 백인 친구였지요.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "그거... 감동적이군.";
			link.l1 = "Mynheer van Merden, 왜 웃고 계십니까...?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "어? 아, 미안하네, Chang Tu. 나이가 들어서 그런지 괜히 감상적이고 우울해지는군. 이 미소는 진심이야 - 숨길 수가 없었네. 나를 친구로 생각해줘서 기쁘네. 우리가 친구라면, 나 역시 가끔 자네의 도움을 기대하겠네. 그 대신 Fermentelos 일은 내가 꼭 도와주지. 걱정 마 - 자네를 함정에 빠뜨리려는 건 아니니까.";
			link.l1 = "흠, 어떻게 도와줄까?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "우리가 마지막으로 만난 이후로, 나는 당신의 언어와 문화, 특히 의학에 대한 공부를 더 깊이 했소. 때때로 나에게 특정 유물 명판을 구해다 주었으면 하오. 그 대가는 다른 일처럼 넉넉히 지불하겠소. 그리고 가끔은 중국어로 대화 연습도 함께 했으면 하오. 하인들에게 부탁하기는 부끄럽지만, 친구라면...\n";
			link.l1 = "창투가 최선을 다하겠습니다, 반 메르덴 나리.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "좋아. 우리 앞에는 먼 길이 남아 있네, 친구. 아주 먼 길이지. 하! 자네에게 좋은 위장 이름이 될 것 같군. 내 업에 유용한 연습도 되고. 네덜란드어로는 “Lange Afstand”라고 하지. 영어로는 “Long Way.” 자네는 어느 쪽이 더 마음에 드나?";
			link.l1 = "나는 영어 버전이 더 마음에 든다. 롱. 웨이. 롱웨이. 내 언어로도 꽤 잘 어울리는 이름이다. 들어주셔서 감사합니다, 반 메르덴 나리. 롱웨이는 나리의 말씀을 기다리며 언제든 도와드릴 준비가 되어 있고, 요청도 충실히 이행하겠다.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// Этап 3, СЛЕД ЗВЕЗДЫ
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "기록 보관소 말인데요, 주군 선장님, 그걸 가지고 계십니까? 저에게 필요한 건 그것뿐입니다 – 암호는 이미 외워두었으니.";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("All Skills +", "Longway");
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingL", 50);
				AddCharacterExpToSkill(npchar, "FencingS", 50);
				AddCharacterExpToSkill(npchar, "FencingH", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);	
				
				link.l1 = "그래, 언젠가 쓸모가 있을지도 모른다고 생각해서 간직해 두었지.";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "유감이지만, 아니오. 그게 자네의 마지막 희망이었나, 누이를 찾는?";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "롱웨이는 대인 선장님께서 신경 써주셔서 매우 기뻐합니다. \n아직은 희망이 남아 있습니다. 과들루프에서 새로운 실마리를 찾았습니다.";
			link.l1 = "좋아, 그럼. 거기서 무슨 일이 있었는지 말해봐.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "현명한 결정이었습니다. 어쩌면 그 안에서 장싱을 찾는 데 도움이 될 만한 무언가를 발견할 수 있을지도 모르겠군요.";
			link.l1 = "그게 가장 이상적이겠군. 지금 바로 살펴보자.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "그래, 함께 살펴보자. 연도는... 1637년. 안톤 판 디멘이 팔았어... 팔았어...";
			link.l1 = "노예들, 맞지?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "내 민족의 여자들, 부유한 백인들에게 팔려갔소.";
			link.l1 = "끔찍하군.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "정의의 섬 선장님, 놀라지 않으시는군요. 그 여자들의 운명이 전혀 마음에 걸리지 않으십니까?";
			link.l1 = "롱웨이, 물론 나도 진심으로 괴롭네. 나도 이 더러움을 속속들이 봤으니까. 하지만 나는 언제나 여성의 편이었어… 솔직히 말하면 여자들에게 좀 약하기도 하고. 반 디멘을 죽인 건 잘한 일이야. 그 자는 그럴 만했지. 또 할 말 있나?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "반 디멘은 완전히 신뢰하는 자들과만 일했지 - 그의 오른팔인 요프 판 데르 빙크, 그리고 저주받은 올리베이로 페르멘텔로스. 그리고... 그리고...";
			link.l1 = "무슨 일이야? 얼굴이 하얗게 질렸는데, 롱웨이.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "요한 반 메르덴...";
			link.l1 = "정말 유감이야. 끔찍하긴 한데, 그런데 왜 그렇게 놀라는 거지? 아까는 페르멘텔루스에 관한 모든 페이지를 다 찢어버렸다고 했잖아. 그때 반 메르덴에 대한 언급은 못 봤어?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "롱웨이가 급해서 이 중요한 조각을 놓쳤던 게 분명해.";
			link.l1 = "알겠습니다. 준비되면 계속 찾아보고 지금 당장 쓸 수 있는 건 뭐든 찾아봅시다.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "페르멘텔루스가 자기 부하들을 보내 여인들을 사로잡고, 그들을 바꿔치기하며 기록을 없앤다고 쓰여 있소. 그 다음에는 메르덴이 그들을 바타비아로 보내면, 반 데르 빈크와 반 디멘이 우리 여인들을 백인 남자들에게 팔았다고 하오. 내가 이 사실을 좀 더 일찍 알았더라면...";
			link.l1 = "결국, 모두가 함께 일한 거군요. 자책하지 마, 롱웨이. 네가 알 수 있었던 게 아니야. 기록보관소는 최근에야 네 손에 들어왔잖아. 다른 건 없어?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "그래. 그 짓을 거의 십 년이나 계속했지. 수많은 여자들이 가족을 잃고, 명예를 잃고, 희망마저 잃었어...\n하지만 페르멘텔루스가 반 메르덴과 손을 끊었지. 그게 그가 나를 도운 유일한 이유야 – 그자는 오직 옛 동업자를 없애고 싶었을 뿐이거든.";
			link.l1 = "여기에 그들의 더러운 짓에 대한 다른 기록도 있습니까?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "반 메르덴의 어두운 생각이 또 드러나는군. 그는 반 디멘이 자기 돈을 빼돌리고 있다는 걸 알아냈지. 그래서 나를 바타비아로 보냈어. 내가 거기서 죽기를 바라면서, 동시에 반 디멘도 나와 함께 죽기를 바랐던 거야.";
			link.l1 = "차갑지. 하지만 믿을 수 없을 만큼 영리해.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "더 끔찍할 수도 있었지. 반 메르덴이 자기 집에 그 깡패들을 보내 나를 죽이려고 했어. 내가 혼자서 그들을 이길지도 모른다는 걸 깨닫고 나서야 비로소 도와주려고 나섰지.";
			link.l1 = "그 자는 모든 걸 다 계산해 뒀지, 의심할 여지 없이.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "내가 살아 돌아온 뒤, 그는 내가 그의 진짜 속셈을 알아채고 복수하러 온 줄 알았던 모양이오. 우리가 대화할 때, 그는 탁자 밑에서 총을 겨누고 있었소. 그런데 내가 그를 내 첫 번째 백인 친구라고 부르자... 그는 거의 웃음이 터질 뻔했지...\n";
			link.l1 = "정말 끔찍하군, 롱웨이. 우리가 친구라 여겼던 자들이 내내 우리 등 뒤에서 비웃고 있었다는 걸 깨닫는 건 참 쓰라린 일이야.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "롱웨이는 이 군도에 도착하기 직전, 오래전에 어떤 것을 배웠소. 나는 포르투갈 놈들에게 붙잡혀 교수형을 당할 뻔했소. 로덴부르크 나리께서 내 목숨을 구해주셨지.";
			link.l1 = "그렇게 해서 그의 밑에서 일하게 된 겁니까? 루카스도 포르모사에 있었습니까?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "그래, 맞아. 그리고 그 사람만이 아니야 - 반 베르크도 마찬가지지. 반 메르덴이 나한테 로덴부르크에게 날 살려두라고 조언한 사람이 바로 그라고 말했어. 그런데 얼마 후에 롱웨이가 수상한 경로로 들은 바로는, 사실 나를 쫓아온 포르투갈 놈들을 보낸 게 요한이었다더군. 그땐 믿지 않았는데... 이제 와서 생각해보니, 사실일지도 모르겠어...";
			link.l1 = "역겨워.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "그래도 그날 내 마음에 의심이 자리잡았소. 그래서 정의의 섬 나리와 반 메르덴이 서로 맞섰다는 소식을 들었을 때, 롱웨이는 나리의 친절을 기억하고 나리 편에 섰소.";
			link.l1 = "그게 옳은 결정이었어, 롱웨이. 헤, 결국 이 모든 시간 동안 네 첫 진짜 백인 친구는 나였던 거네.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "그런 셈이군요, 나리 선장. 이제야 알겠습니다. 판 메르덴은 저에게 친구라고 했지만, 사실 롱웨이는 그저 다른 일꾼들보다 조금 더 쓸모 있는 존재였을 뿐입니다\n그게 전부입니다. 나머지 쪽지들은 회계와 판 베르크, 로덴부르크 사이의 거래 내역에 관한 것입니다.";
			link.l1 = "알겠소. 이제는 그대가 과달루프에서 무슨 일을 했는지 말해줄 때가 되었소.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "나는 샛별을 찾고 있었소. 찢겨진 기록지 중 한 장에 마지막으로 샛별이 세인트 크리스토퍼 근처에서 목격됐다고 적혀 있었소.";
			link.l1 = "왜 거기로 가야 하죠? 우리는 과들루프에서 만나기로 했고, 나는 거기서 당신을 찾았어요.";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "세인트 크리스토퍼는 반 메르덴의 정보원 중 한 명인 조르주 그라벨의 본거지이기 때문이오. 조르주는 내가 아직 요한을 위해 일한다고 믿고 있소. 게다가 그라벨은 한때 반 메르덴에게 중대한 죄를 저질렀지. 그리고 롱웨이가 그걸 은폐하는 데 도왔소.";
			link.l1 = "그게 무슨 죄였소?";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "그건 중요하지 않아. 중요한 건 조르주가 롱웨이에게 빚을 졌다는 거지. 그래서 나는 그라벨이 보조 신부로 일하는 교회에 갔어. 정의의 섬 선장 나리, 더 들을 준비가 되었나? 좀 산만해 보이는데.";
			link.l1 = "미안, 잠깐 딴생각했어. 그래, 해, 롱웨이.";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Capsterville,"+ NewStr() +"St. Christopher Island.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "좋아, 아직 늦지 않았군. 여기서 더 오래 있고 싶진 않으니까, 알지! 이번엔 무슨 일이야, 롱웨이?";
			link.l1 = "말투를 바꿔라, 그라벨. 조직에서 네 도움이 필요하다.";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "고백하자면, 그들로부터 오랫동안 아무 소식도 듣지 못했습니다. 나를 잊어버린 걸까요?";
			link.l1 = "내가 그들에게 상기시켜 줄 수 있소. 어쩌면 당신이 한 일을 반 메르덴 나리께 말씀드리면 되겠군.";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "알았어, 알았어, 그렇게 화낼 필요 없잖아! 내가 뭘 해주면 되지?";
			link.l1 = "나는 모닝 스타에 대한 정보가 필요해. 뭐든지 좋으니 알아낼 수 있는 건 다 가져와. 많으면 많을수록 좋아.";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "물론이지만, 시간이 걸릴 거요! 최소 이틀은 필요하오!";
			link.l1 = "왜 이렇게 오래 걸려?";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "보통은 헌금함에서 돈을 꺼내 내 정보원들의 입을 풀게 하지. 하지만 최근에 도둑을 맞았네! 신부님께서 곧 새로운 헌금 모금을 알리시겠지만, 우리 지붕도 고쳐야 해 - 지금 물이 새고 있거든! 지붕을 고치려면 헌금이 많이 필요할 거야.";
			link.l1 = "이틀. 여기서 영원히 머물 수는 없어. 그럴 시간 따윈 없어. 롱웨이는 인내심으로 유명하지 않지. 반 메르덴 나리는 더더욱 아니고. 아니면 내가 그걸 상기시켜줘야 하나, 그라벨?";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "내 손이 닿지 않는 일은 어쩔 수 없어! 내가 할 수 있는 건 하겠어. 하지만, 네가 그 도적놈들을 찾아서 우리 기부금을 되찾아온다면 훨씬 더 빨리 알 수 있을 텐데!";
			link.l1 = "생각해 볼게. 너는 수색을 시작해. 이틀. 더는 안 돼. 같은 시간, 같은 장소에서 만나.";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A Day Later..."+ NewStr() +"In Search of the Church Robbers.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "이런, 이게 누구야! 우리 섬에 눈이 가늘은 사내라니! 주인들한테서 도망치는 거냐? 실례가 안 된다면, 누구한테서 숨고 있는 거지?";
			link.l1 = "나는 자유인이다.";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "하! 그래, 그렇겠지. 하지만 네 몸도 튼튼하고 머리도 좋아 보여, 비록 눈이 좀 찢어졌지만 말이야. 우리 패거리에 들어올래? 어차피 갈 데도 없어 보이는데, 안 그래?";
			link.l1 = "롱웨이는 당신이 그를 동료로 삼는 것보다 약탈하는 데 더 관심이 있다고 생각합니다.";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "헤, 운이 좋다고 생각해. 우리 최근에 마을 교회를 털었어, 믿기지 않지?\n왜냐고? 도둑놈한테서 훔치는 건 진짜 도둑질이 아니거든.";
			link.l1 = "널 쫓아다닐 생각은 없었지만, 그래도 널 찾아서 다행이야.";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "우릴 사냥하러 온 거야? 아, 그럼 넌 도망친 일꾼이 아니라 용병이군. 그럼 네겐 안 좋은 소식이겠네.";
			link.l1 = "정확합니다.";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "젠장... 왜 바로 날 죽이지 않았지? 나한테 뭘 원하는 거야? 감옥에 끌고 가려는 거야?";
				link.l1 = "나는 그거에 관심 없어. 그냥 금을 어디에 숨겼는지만 말해.";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");	
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "헤... 이 노란 피부의 개자식아...";
			link.l1 = "롱웨이의 인내심이 바닥나고 있다. 어차피 내가 알아낼 거다. 네가 얼마나 더 고통받을지가 문제일 뿐이지.";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "좋아, 알겠어... 동굴에 있어. 전부 거기 있어. 돈은 네 거야. 제발... 제발 나만 죽이지 마, 알겠지?";
			link.l1 = "나는 고통이 전혀 없을 거라고는 말하지 않았소...";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = "(만다린어로) 여기 도적들의 은신처야.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "(만다린어로) 많아요!";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "(만다린어로) 발소리가 들린다...";
			link.l1 = "(만다린어로) 여기 또 다른 사람이 있어...";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "우리가 대체 여기서 뭘 하고 있는 거지? 이제 아무도 남지 않았어 - 도둑놈들은 전부 처리했잖아.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "그게 바로 요점이야, 멍청아! 놈들이 다시 올 거고, 우리가 제대로 환영해 주지.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "주변을 좀 둘러볼게. 누가 숨어 있는지 확인도 할 겸. 어차피 심심하거든...";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "(만다린어로) 병사들아! 참으로 불행하구나... 이제 나는 어찌해야 한단 말인가?";
			link.l1 = "(만다린어로) 나는 이 돈이 하얀 군인들보다 더 필요해! 이 돈 없이는 절대 안 떠나!";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "아, 롱웨이 나리, 돌아오셨군요!";
			link.l1 = "물론이지. 의심이라도 있었나? 조르주, 모닝 스타에 대해 뭔가 알아낸 게 있나?";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "네, 나리. 무거운 갤리온선이라고 합니다. 선장은 스페인 사람이라던데요...";
			link.l1 = "그자는 포르투갈 놈이오. 너희 백인들은 서로 구분도 못 하잖소.";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "아, 맞다. 내 실수야. 아무튼, 그가 갤리온을 상인선처럼 보이게 하려고 대포는 소구경으로 바꾸고 승무원도 줄였다는 걸 알아냈어. 대신 창고를 확장해서 가득 채웠지. 너무 무거워서 겨우 항해할 수 있을 정도야.";
			link.l1 = "그래서 그는 새 삶을 시작하기로 한 거군. 좋아. 이제, 그를 어디서 찾을 수 있지?";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "그건 더 까다롭지. 그는 우리 식민지와 영국 식민지 사이를 끊임없이 오가지만, 항상 바람이 센 섬들 사이에서만 움직여. 하지만 지금은 많은 양의 와인을 싣고 바스테르로 향하고 있다는 걸 알아냈어.";
			link.l1 = "거기로 빨리 가는 방법을 알아내야 해.";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "그건 자네 사정이지, Longway 나리. 내 문제도 충분히 많아... 저 빌어먹을 지붕이나 고쳐야 하거든.";
			link.l1 = "걱정 얘기가 나와서 말인데, 그 교회 도둑놈들 내가 찾았소. 여기 헌금 돈 돌려주오. 지붕이나 고치시오 - 당신네 신이 지붕도 없이 계시는 건 좋지 않으니.";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "정말 고마워요, Longway 나리! 당신이 그렇게 해줄 줄은 전혀 몰랐어요.";
			link.l1 = "나도 그렇게 생각하지 않았어. 하지만 그 이틀 동안 뭔가 해야만 했지.";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "그래서 과들루프로 가야 한다고? 그쪽으로 가는 배를 찾아줄게. 곧 소식이 있을 테니 기다려!";
			link.l1 = "도움이 되겠군요. 고마워요, Georges.";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("The Next Morning..."+ NewStr() +"Capsterville", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "조르주와 아는 사이인가요? 그가 이걸 전해 달라고 했어요.";
			link.l1 = "쪽지입니까? 감사드립니다. 어떻게 그게 저를 위한 것임을 아셨습니까?";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "진심이야?";
			link.l1 = "아, 맞다.";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "(편지를 읽는다) 롱웨이 나리, ‘프로방스’ 피나스는 내일 아침 바스테르로 출항합니다. 선장 마티외 트뤼니는 선술집에서 찾을 수 있습니다. 반 메르덴 나리께 안부 전해 주십시오. - 조르주 그라벨.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "여기서는 너 같은 놈들한테 술 안 판다. 그리고 벼룩 때문에 불평 듣기 싫으니까 방도 안 빌려준다.";
			link.l1 = "술도, 방도 필요 없어. 그리고... 롱웨이에게 벼룩 따윈 없어.";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "내가 그걸 어떻게 알겠어? 좋아, 말해 봐. 뭐 원하는데? 그럼 꺼져.";
			link.l1 = "알겠습니다. 저는 마티외 테뤼니 선장을 찾고 있습니다. 아무리 찾아도 보이지 않네요. 어디에 있는지 아십니까?";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "그는 지금 자기 배를 출항 준비하느라 근처 상점에서 바쁘게 움직이고 있어. 그런 일은 너 같은 중국인하고 잡담하는 것보다 훨씬 중요하지. 하지만 넌 그걸 전혀 모르는 모양이군.";
			link.l1 = "사실, 나는 예전에... 아니다. 지금은 중요하지 않아.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = "뭘 원하지, 차이나맨? 바쁜 거 안 보여? 내 배를 준비해야 해.";
			link.l1 = "Mathieu Terugny 선장?";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "이제 더 이상 웃기지도 않군. 너 같은 놈이 어떻게 나를 아는 거지? 누가 널 보냈나?";
			link.l1 = "걱정할 필요 없어. 바스테르로 항해한다는 소문을 들었어. 나를 승객으로 태워줄 수 있겠나? 돈은 내겠네.";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "점점 더 재밌어지는군. 나는 바스테르가 아니라 생피에르로 가는 길이지만, 잠깐만 돌아가면 돼. 그거면 충분하지, 널 배에 오래 태울 필요가 없으니까. 오천 페소다. 세 시간 후에 출발한다. 부두에서 돈 내. 나는 상인이지만 흥정은 없어. 알겠지?";
			link.l1 = "네. 감사합니다. 부두에서 뵙겠습니다, Terugny 선장.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "결국 나타났군, 짱깨. 네놈 같은 족속에게 자진해서 진짜 돈을 주는 사람은 없을 거라 생각했지.";
			link.l1 = "오천 페소, 당신이 요구한 그대로요. 출항할 준비가 되었습니까?";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "아니, 아니! 내가 오히려 너한테 그걸 물어봐야지. 하지만 준비된 것 같군. 가자. 너는 단정을 저어야 해. 그리고 제대로 된 선실은 기대하지 마! 우리가 이렇게 우회하는 건 전적으로 너 때문이야.";
			link.l1 = "위로는 필요 없어. 그냥 거기로 데려가.";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "...그래서 롱웨이는 모닝 스타가 정확히 어디로 향하는지 알아내지 못했어.";
			link.l1 = "그래, 네가 왜 그런 엉망진창에 휘말렸는지 알겠어.";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Helena";
			else sStr = "Alonso";
			dialog.text = "과달루프 해역에서 브리그선을 봤어. 아마 반텐일지도 모르지. 알아볼게. 자, 이제 가도 된다, 롱웨이. 가져와라\n " + sStr + ".";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "내 캡틴, 모두 괜찮아요? 롱웨이가 당신이 필요하다고 해서 바로 왔어요.";
				link.l1 = "나는 그냥 모든 걸 맞춰보려는 중이야. 우리가 섬 근처에서 봤던 그 브리그 이름, 기억나?";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "저를 찾으셨습니까?";
				link.l1 = "그래. 최근에 본 브리그 기억하지? 그 배의 위치와 이름을 알아내.";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "기억은 나지만, 갑자기 브리그에 왜 관심이 생긴 거지? 알아내려면 시간이 좀 걸릴 수도 있어.";
			link.l1 = "헬렌, 그냥 해 줘, 제발. 그리고 그래, 오래 걸릴 수도 있다는 거 알아. 기다릴게.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "아니, 확인 안 했어. 왜? 중요한 거야?";
			link.l1 = "음. 더 알아봐 줄 수 있어? 지금 그들이 어디에 정박해 있는지 알아야 해, 아직 과들루프 해역을 떠나지 않았다면 말이야.";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "물론이지. 미리 말해두지만, 좀 오래 걸릴 수도 있어. 내가 작은 배랑 몇 명 데리고 갈게, 그치, Charles?";
			link.l1 = "물론이지, Helen, 고마워. 기다리고 있을게.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "나리 선장, 부르셨습니까?";
			link.l1 = "그래, Alonso. 우리가 Longway를 데리러 돌아갈 때 섬 근처 해역에서 브리그 한 척을 지나쳤지. 혹시 그 배 이름을 봤나?";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "아니오, 제 일은 신병들을 감시하고 선상 돌격대에 참여하는 것입니다.\n게다가 저는 망원경도 없고, 그와 그렇게 가까운 사이도 아니었습니다.";
			link.l1 = "맞아. 그래도 알아봐야 해. 끝내.";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "예, 선장님. 반나절이면 할 수 있을 것 같습니다.";
			link.l1 = "서둘러. 내가 기다릴게.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("Five hours later...", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "모든 걸 배웠어요. 내가 없는 동안 별일 없었나요, 내 캡틴?";
				link.l1 = "그래, 괜찮아. 고마워, 헬렌. 말해 봐.";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "휴, 돌아왔어. 네 브리그를 찾았어.";
				link.l1 = "돌아오셨군요. 그녀의 위치와 이름은 무엇입니까?";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "반텐. 그 이름, 당신에게 의미가 있지 않소? 지금 그녀는 등대에 있고, 선원 몇 명이 상륙했소. 우리가 그 배를 공격할 건가?";
			link.l1 = "아니, 누가 상륙했는지 정확히 알아내야 해. 우리는 육로로 등대로 가자. 이미 지체된 걸 생각하면, 이제는 항구를 떠날 때야. 외진 곳에 닻을 내려야 해. 캡스터 해변이 좋겠어. 서두르자, 헬렌.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "음, 브리그 이름은 반텐이고, 등대에 정박해 있어. 선원 몇 명이 거기 상륙했지. 이제 어떻게 할 거야?";
			link.l1 = "알아내려면 등대까지 들키지 않고 가야 해. 그건 걸어서만 할 수 있지. 우리 배는 안전한 곳에 정박해야 해. 캡스터 해변은 어때?";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "좋은 생각이야. Charles, 등대로 같이 가길 원해?";
			link.l1 = "배를 옮기는 동안 생각해 볼게 - 너는 이미 충분히 지쳤으니까.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "끝나자마자 바로 돌아왔소, 선장 나리.";
			link.l1 = "아주 좋다. 보고하라, Alonso.";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "브리그는 아직 섬 앞에 있어. 정확히는 등대 근처야. 선미에 적힌 이름은 반텐이야. 그들 선원 몇 명이 상륙했어.";
			link.l1 = "잘했어, Alonso. 즉시 닻을 올릴 수 있도록 선원들을 준비시켜.";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "너도 승선 준비할 거야?";
			link.l1 = "아직 아니야. 그들의 선장이 등대로 간다면, 우리가 바다에서 공격하면 도시로 숨을지도 몰라. 우리는 먼저 캡스터 해변으로 가서 우리 배를 확보한 다음, 걸어서 등대로 접근하자.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "정의의 섬, 저기 보십시오! 등대 안에 누군가 있습니다.";
			link.l1 = "좋아, 제시간에 도착했어! 서둘러서 놈들을 잡자. 오늘은 Alonso가 할 일이 많겠군.";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "하지만 그 과정에서 죽으면 어떻게 하죠?";
			link.l1 = "무엇을 제안하시겠습니까?";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = "우리는 조용히 숨어들어가 먼저 그들의 대화를 엿듣는다.";
			link.l1 = "창문에서 들키지 않고 할 수 있을지 의심스럽군. 그래도 한번 시도해 보지.";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "HiddenImmortality");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "내가 한 말을 생각해 보시오. 곰곰이 생각하시오. 돈은 문제가 아니오 - 물론 어느 정도 한계는 있지. 하지만 그 한계조차도 자네에겐 금산처럼 보일 것이오 - 그 중국인은 반드시 죽어야 하오! 전에 그를 잡으라고 사람들을 보냈지만 소용없었소. 하지만 이번에는, 자네 부하들과 힘을 합친다면...\n";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "봐, 우리를 지켜보고 있어! 저 자야! 저 자랑 그 빌어먹을 선장 놈이야!";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "빌어먹을 더러운 아시아 놈... 네 탓에 내가 얼마나 많은 걸 견뎌야 했는지 알아? 그런데 이제, 그 모든 대가로 내가 죽게 생겼군...";
				link.l1 = "우리 의사에게 모시고 가겠습니다, 사령관 나리. 누구와 이야기하고 있었는지 말씀해 주십시오 - 매우 중요한 일입니다.";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "그의 이름은... 요프 판 데르 빙크, 그는... 크하...";
			link.l1 = "...";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "죽었네... 그래도 이름은 알게 됐군. 롱웨이...?";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "그럴 리가 절대 없어...";
			link.l1 = "롱웨이, 얼굴이 좀 창백해 보이네.";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "롱웨이는 10년 전에 반 데르 빈크를 확실히 죽였다고 생각했지\n저놈들이 도망친다! 그 배, 빠르군!";
			link.l1 = "그래, 훌륭한 브리그지... 우리한텐 불행하게도 말이야. 우리가 제때 배에 도착한다 해도, 우리가 돛을 올리고 바람을 잡을 때쯤이면 저놈들은 이미 사라지고 없을 거야.";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "이게 끝일지도...";
			link.l1 = "아니야, 롱웨이. 내 말 들어. 그들이 군도에 머물 생각이라면, 언젠가는 반드시 마주치게 돼 – 세상은 좁고, 특히 카리브 해는 더 그렇지. 우리가 다시 그들의 흔적을 찾는 순간, 나는 모든 걸 제쳐두고 쫓아갈 거야. 그건 꼭 약속할게. 내 말 들었지?";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "네, 나리 선장님. 감사합니다.";
			link.l1 = "고개 들어, 롱웨이. 서둘러 배로 돌아가야 해. 사령관의 죽음이 곧 큰 소문이 될 거야.";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			ReturnOfficer_Longway();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// Этап 4, Обманчивая Звезда
		case "PZ_PoterpKrushenie_1":
			dialog.text = "나리! 잠깐만요! 선장이십니까?";
			link.l1 = "어쩌면. 어떻게 알아챘지? 그리고 뭘 원하는 거지?";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "여긴 산과 울창한 정글밖에 없어. 도시로 가는 길도 없고. 그런데 네가 여기 있네.\n단순히 구경하러 온 건 아니겠지?";
			link.l1 = "좋은 관찰이군. 하지만 아직도 당신이 원하는 게 뭔지 말하지 않았소.";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "아, 맞다! 선장님, 우리 배가 바로 이 만 앞바다에서 암초에 부딪혔어요. 우리만 살아남았어요...";
			link.l1 = "미안하오. 어디로 모셔가길 원하시는 거지, My Lord Captain?";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "아이... 우린 문제 일으키지 않을 거야, 맹세해. 벨리즈에만 내려주면, 그다음부터는 우리가 알아서 할게.";
			link.l1 = "멀지 않지? 그렇다면, 배에 타.";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "미안하지만, 나는 반대 방향으로 가는 중이오.";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "감사합니다, 선장님! 당신이 아니었으면 우리가 얼마나 오래 여기 갇혀 있었을지 아무도 모릅니다.";
			link.l1 = "정말이군. 시간 낭비하지 말자!";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "하지만 벨리즈는 이렇게 가까운데! 금방 다녀올 수 있잖아, 그치?";
			link.l1 = "나는 급해. 돌아갈 여유 없어.";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "짧은 항해라도 안 돼요? 벨리즈까지만이라도요? 제발요, 선장님, 우리를 여기 버려두지 마세요!";
			link.l1 = "좋아, 이거 후회하지 않길 바란다. 모두 승선해!";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "그게 인생이지. 좋은 하루 보내, 친구들.";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "다시 한 번 감사드립니다, 선장님! 우리는 그저 평범한 선원들이라 드릴 수 있는 게 많지 않습니다.";
			link.l1 = "그래도 적어도 너무 멀리 돌아가진 않았군.";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "당신의 건강을 위해 술잔을 들고, 교회에서 당신을 위해 촛불을 밝히겠소.";
			link.l1 = "그거라도 없는 것보단 낫지. 건배하자, 이 녀석들아!";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "들었어? 드디어 그 놈을 잡았대! 이제 우리 바다는 드디어 안전해졌어!";
			link.l1 = "그게... 좋은 소식인가요? 그런데 누구를 잡았다는 거죠?";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "바람잡이 매튜 러터, 그 자신이군!";
			link.l1 = "나는 잘 모르겠어 - 그가 뭘 했지?";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "모른다고?! 흠, 분명히 영국인은 아니구나, 딱 봐도 알겠어. 그는 '갈매기'라는 배를 타고 우리랑 스페인 놈들을 수년째 약탈해온 해적이야.";
			link.l1 = "영국 놈들이랑 스페인 놈들 둘 다 약탈한다고? 그거 참 드문 일이군.";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "정말이지. 해안 경비대도 그를 잡지 못했지만, 결국에는 자기 분수를 넘어서다가 당했지. 믿기 힘들겠지만, 어떤 이상한 상선에게 패배했다고 하더군.";
			link.l1 = "재미있군. 그 상인에게 뭐가 그렇게 이상했지?";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "글쎄, 그건 그냥 호위도 없는 거대한 둔한 갤리온 한 척뿐이었어! 하지만 그 미친 선장 덕분에, 루터는 오늘 마지막 노래를 부르게 될 거야 - 곧 교수형을 당하거든. 구경하러 와야 해!";
			link.l1 = "할 수도 있겠지만, 지금은 처리해야 할 다른 일이 있어.";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "나리 선장님!";
			link.l1 = "스페인 상인이 대담한 해적을 이긴다니... 너도 롱웨이가 생각하는 그걸 떠올리고 있지?";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = "샛별...";
			link.l1 = "아마도 저런 상인 선장은 이 군도 전체를 통틀어도 또 없을 거요.";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "우리는 즉시 그를 찾아야 해!";
			link.l1 = "맞아. 하지만 항구에 무거운 갤리온은 안 보여. 윈드백이 교수형 당하기 전에 한번 말이나 해보자. 그 별명을 얻을 만한 놈인지 직접 보자고.";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			ReturnOfficer_Longway();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "그 자 아직 살아 있나? 우리가 그와 얘기할 수 있나?";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "뭐? 아, 그래. 그는 살아 있어 – 처형은 아직 안 일어났거든. 가서 그와 이야기해도 돼 – 요즘 들어 그 어느 때보다 말이 많아졌지. 하지만 최근엔 헛소리만 늘어놓고, 주로 혼잣말만 해. 바람쟁이는 미쳐버렸어... 그의 끝없는 수다에 우리 모두가 미치기 전에, 내가 그놈을 교수대에 매달 날이 기다려져.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "감사합니다.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			ReturnOfficer_Longway();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Matthew";
			sld.lastname = "Lutter";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "그가 내 보물을 훔쳤어!";
			link.l1 = "매튜 러터?";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "내 보물은 이제 그 자에게 묶여 있어, 알겠어, 그 놈에게! 우리가 할 수 있는 건 아무것도 없어! 뭘 원하는 거야?! 우리한테서 또 뭘 빼앗아가고 싶어? 남은 건 아무것도 없어! 그녀는 죽을 거야! 아니면 더 끔찍한 일이 벌어질 거야!";
			link.l1 = "누가 죽는다고? 무슨 보물? 됐어, 그건 네 잘못이야 - 네가 그 갤리온을 공격했지, 걔네가 먼저 한 게 아니잖아.";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "아니야! 그 반대였어! 젠장할 이달고 놈! 우리가 이렇게 된 건 다 그 자식 때문이야! 우리한테 바로 달려들어서 코앞에서 쏴버렸지! 그리고 그녀를 우리에게서 빼앗아 갔어!\n";
			link.l1 = "정말인가? 놀랍지도 않군. 그 자에 대해 더 말해줄 수 있나? 그리고... 뭘 가져갔지? '그녀'는 누구지?";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "아-아-아!!! 아-아-아-아!!!";
			link.l1 = "알겠소, 내 시간이 헛되이 낭비되고 있군...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "선장님, 허락해 주신다면... 루터! 나가! 여기까지야, 친구.";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "선장님, 소타와 루터에 대해 더 알아봐야 합니다. 주변에 물어봅시다.";
			link.l1 = "좋은 생각이야, 롱웨이. 어차피 그 소리치던 남자한테서 얻은 건 별로 없었으니까.";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "하지만 소타부터 시작하는 게 낫겠어.";
			link.l1 = "그래, 우리가 찾는 자가 바로 저놈이야. 가자.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "그놈들은 아무것도 몰라!";
			link.l1 = "당연하지. 하지만 이제 우리 스스로 생각할 만큼은 충분히 알게 됐어. 내가 들은 바로는, 소타가 받은 전략 물자를 곧 팔아넘기려고 할 거라고 하더군.";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "정확해!";
			link.l1 = "그를 포트 로얄이나 캡스터빌로 가는 길에서 가로막아야겠소. 문제는 그가 어디로 향하는지, 우리가 어디서 그를 덮쳐야 할지요. 아니면 바다 한가운데서 그를 붙잡게 될지도 모르겠군.";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "안 돼! 롱웨이가 말한 건... 페르멘텔로스는 노련한 선장이야. 망망대해에서 싸우면 승패를 알 수 없어. 항구에서 기습하면 우리가 이길 확률이 더 높아.";
			link.l1 = "맞아요, 아마도. Matt와 그 사이에 무슨 일이 있었든, Sotta는 위험한 자이고 절대 과소평가해선 안 돼요.";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "우리도 기다릴 수 없어!";
			link.l1 = "또 맞았군, 롱웨이. 그럼 지금 바로 닻을 올리고, 다음 행동을 계획하자.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "정의의 섬, 모닝 스타가 항구에 들어왔소!";
			link.l1 = "그래, 이미 눈치챘어.";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "계획이 뭐지?";
			link.l1 = "아직 결정하지 않았어. 요새의 대포 아래에서 저들을 승선시키려는 건 자살 행위야. 그리고 설령 그들의 중무장 갈레온을 빼앗는다 해도, 그 배로는 도망칠 수 없어. 롱웨이, 네 생각은 어때?";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "그래. 안전한 만에 닻을 내리고, 밤의 어둠을 틈타 보트를 타고 갈레온에 접근할 수 있겠지.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "하프 문 만은 어쩌지, 롱웨이?";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "포틀랜드 코브가 괜찮을 것 같아. 충분히 가깝고 비교적 안전하지. 어떻게 생각해?";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "좋은 선택이오.";
			link.l1 = "좋아, 그걸로 정해졌군. 우리가 빠뜨린 건 없나?";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "그렇지 않다고 생각합니다, 나리 선장님. 우리는 그저 철저히 준비만 하면 됩니다.";
			link.l1 = "틀림없이.";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "Half Moon Bay");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "Portland Cove");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "너 도대체 누구야, 무슨 일이야? Holmes 나리!";
			link.l1 = "Holmes 나리는 더 이상 여기서 일하지 않습니다. 그리고 우리는 모든 해치를 단단히 봉쇄했습니다. 그러니 한동안 방해받지 않을 겁니다, Fermentelos 나리.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "뭐라고? 페르멘텔로스? 내 이름은 에드가르도 소타야!";
			link.l1 = "응, 그 얘긴 전에 들었어. 네 진짜 이름이 올리베이로가 아니라는 거 우리도 다 알아.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "페르멘텔루스가 죽었어!";
			link.l1 = "다시 생각해보니, 당신은 정말 너무 어려 보여. 분명히 10년 전에 모닝 스타의 선장이었을 리가 없지. 그럼, 올리베이로에게 무슨 일이 있었던 거지?";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "우린 그 자를 처리했어. 그냥 우리가 치워야 할 또 다른 문제였지 - 네 옆에 서 있는 그 놈처럼 말이야.";
			link.l1 = "음, 당신이 페르멘텔로스가 아니라면, 그래도 우리 질문에 답할 수 있을지도 모르겠군. 내 친구에게서 그가 데려간 사람을 찾고 있어.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "난 아무 말도 안 할 거야! 그 사람은 이 일로 절대 날 용서하지 않을 거야.";
			link.l1 = "지금은 우리가 너를 용서할지 걱정하는 게 좋을 거다...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "드디어 저 자식이 죽었군...";
			link.l1 = "맞아요. 그런데 당신은 누구십니까, 부인? 저 자가 억지로 잡아두었나요? 유감입니다; 끔찍한 고초를 겪으셨겠군요...";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "저는 아나벨 루터예요. 그리고 신께 감사하게도, 별로 고생하지는 않았지만, 걱정해 주셔서 고마워요, 나리...?";
			link.l1 = "샤를 드 모르 선장. 뤼테르라고 했소...";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "아, Matt에 대해 들어봤겠지? 가엾은 바보... 나는 그의... 동반자였어.";
			link.l1 = "당신의 상실에 애도를 표합니다, 루터 부인. 이제 과부가 되셨군요. 실례가 안 된다면, 결혼 전 성씨가 무엇이었는지 여쭤봐도 될까요?";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "나는 그런 이름 없었소. 나를 좀 더 잘 보시오. 내 불쌍한 어머니는 해적들에게 잡힌 피부가 검은 노예 소녀였소. 내 아버지가 누구였는지 아무도 몰랐으니, 제대로 된 이름조차 주지 않았소.";
			link.l1 = "그때 아무도 너를 건드리지 않은 이유가 뭐지? 오해하지 마, 그런 일이 없어서 다행이야. 하지만 그래도... 이상하잖아.";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "맞아. 하지만 사물은 제대로 불러야 해. 나는 귀하게 자란 귀족 여자가 아니야; 나는 노예의 딸이야. 무거운 대화 때문에 기절하지 않아.";
			link.l1 = "음, 저도 응석받이 같은 건 질색이오. 하지만 계속 말씀하시지요. 왜 선원들이 그 노예 소녀의 딸에게는 손도 대지 않았소? 당신은 아버지가 누군지도 모르고, 그 사람도 신경 쓰지 않는 것 같았는데.";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "그렇지 않은 것 같군. Matt에 대해 알고 있다면, 그가 한동안 Levasseur 밑에서 일했다는 것도 알고 있나?";
			link.l1 = "그래, 내가 아침별을 찾으면서 그 이야기를 들었어. 그런데 그게 이 일과 무슨 상관이 있지? 전부 말해 줘, 제발.";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "아직도 이해 못 하겠나? 혹시 레바쇠르의... 취향에 대해 못 들어봤나?";
			link.l1 = "나는 못 봤어, 하지만 그게... 무슨 상관이 있지?";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = "아, 다 말해줘야 할 것 같군요. 너무 예민하다면 앉으세요, 나리. 사실은, 그 사람이 여자들과 많이 자고 다니는데, 그리고...";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "그의 아내도 그리 멀지 않은 곳에 있고, 거의 누구와도 잠자리를 같이하지.";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "이런.";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = " 글쎄, 다들 그러잖아... 남편이 그러면 아내도 그렇다고. 하지만 아니야, 그는 분명 그보다 훨씬 더 나아갔을 거야.";
			link.l1 = "얼마나 멀지?";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "여기서 비꼬는 말은 쓸데없소, 나리. 우리가 무슨 이야기를 하는지 전혀 모르시잖소.";
			link.l1 = "알았어, 알았어, 미안해. 계속해, 제발.";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "그건 단순히 배우자를 속이는 게 아니야. 그는 여자들을 그들의 의사와 상관없이 데려가. 그리고 그건 한 번의 학대가 아니야. 그는 소녀들을 납치해서 자기 소유의 와인 저장고 중 한 곳에 가둬 둬.";
			link.l1 = "그래서 그자는 노예 소녀들을 정기적으로 들여온다는 거야? 그리고 네가 그중 하나가 될 뻔했단 말이지?";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "후자에 대해서는 네 말이 맞아. 하지만, 안타깝게도 첫 번째는 아니야. 그자는 노예가 필요하지 않아. 르바쇠르는 미쳤어, 자기만의 방식으로. 내 매트와는 달라. 프랑수아는 여자를 완전히 소유하고 싶어 하지, 몸과 영혼 모두를. 물론 사랑 때문이 아니었지. 그는 자유로운 여자들의 의지를 꺾는 게 목적이었어. 시간이 흐르면서 그들의 눈빛, 행동, 말투가 변하는 걸 지켜보는 걸 즐겼지...\n";
			link.l1 = "역겨워...";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "이미 좀 속이 안 좋으시죠. 이제 그 여자들에게 어떤 일이 있었을지 상상해 보십시오. 이 모든 이야기를 들었습니다, 그리고 매트한테만 들은 게 아닙니다. 레바쇠르는 한때 포르투갈 귀부인도 가졌었지요...";
			link.l1 = "넌 시선을 피하고 조용히 있었지. 전부 말해. 나는 구세계에서도, 군도에서도 온갖 걸 다 봤어. 이제는 아무것도 놀랍지 않아.";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "멈춰, 그녀에게 무슨 일이 있었는지 알고 싶지 않아. 그 여자들이 그의 손아귀에서 너무 오래 고통받지 않았길 바랄 뿐이야.";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "하지만 이런 일은 들어본 적도 없으시겠지요. 그리고 부디 직접 보게 되는 일도 없기를 바랍니다. 그녀는 여전히 자존심을 잃지 않은 채, 꺾이지 않은 상태로 그에게 끌려갔습니다. Matt가 내게 말하길, Levasseur의 놈들이 그녀의 남편이 캄페체 근처의 농장을 빼앗긴 뒤 토르투가까지 가는 내내 그녀를 능욕했다고 합니다. 그 남편은 그 괴물들이 두 무릎에 총을 쏜 뒤 출혈로 죽었습니다...\n";
			link.l1 = "강인한 여자군... 하지만 당신이 말했잖아, 르바쇠르는 자기 마음에 든 여자는 보통 건드리지 않는다고.";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "그가 특별히 지목한 자들은 건드리지 않았소. 하지만 레온티나 나리는 선물이었지. 그들에게는 뜻밖이면서도 기쁜 선물이었소. 그래서 그들은 마음껏 탐닉했지...";
			link.l1 = "알겠습니다...";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "내 생각에... Matt는 Francois가 아끼는 놈들 중 하나가 되었던 것 같아. Levasseur의 비밀 연회 중 하나에 초대받았지... 연회 도중, 해적 한 놈이 여자들이 부족하다고 불평했어. 그러자 Levasseur가 웃더니...\n";
			link.l1 = "그리고 나서? 무슨 일이 있었지?";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "...그러고 나서 그녀가 끌려 나왔소. 목줄에 묶인 채로! 두들겨 맞고, 등에 상처가 나고, 눈가리개와 재갈까지 물린 채였지. 재갈을 벗기자, 그녀가 한 말은...";
			link.l1 = "끔찍한 일이었겠지, 내 생각엔. 그녀가 가진 모든 저주를 퍼부었나?";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "만약에... 도냐 레온티나는 그저 속삭였지, '제 주인께서 무엇을 원하십니까?'";
			link.l1 = "토할 것 같아. Matt가 그 후에 그녀에게 무슨 일이 있었는지 말해줬어?";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "물론 살해당했지. 하지만 르바쇠르 손에 죽은 건 아니야. 그는 그녀를 길 잃은 개처럼 내팽개쳤어. 그의 선장 중 한 명이 그녀를 쏘아 죽였지. 죽기 전에, 그녀는 단 한 마디만 남겼어...";
			link.l1 = "저주인가? 기도인가?";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "아니. '감사합니다...'";
			link.l1 = "그런 고통 끝에 죽음에 감사하게 되다니... 그녀가 얼마나 끔찍한 일을 겪었을지... 그리고 그 괴물의 소굴에서 그녀와 같은 고통을 당한 이들은 또 얼마나 많을지...";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "레바쇠르는 특히 노예들과 피부가 어두운 여자들을 경멸했어\n그는 그들에겐 부술 게 없다고 말했지\n그들은 그와 오래 버티지 못했고, 인디언들도 마찬가지였어\n특히 고집 센 몇몇을 제외하고는 말이야\n하지만 야성이나 반항도 답이 아니었지\n그는 너무 빨리 비위를 맞추려는 자들도, 너무 오래 저항하는 자들도 죽였으니까";
			link.l1 = "끔찍하군요... 말해 보시오, 르바쇠르가 아시아 여자들을 데려온 적이 있소?";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "아니, 적어도 내가 들은 바로는 없어. 나에 관해서라면... 그가 흑인 여자를 좋아하지 않는다고 이미 말했잖아. 그래서 Matt가 Francois 밑에서 일할 때는, 나랑 대놓고 토르투가 거리에서 다녔어. 한 번은 나를 관저에도 데려갔지.";
			link.l1 = "하지만 르바쇠르는 어차피 당신을 자기 노예로 만들고 싶어했지...";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "정말 그래... 왜 그가 나를 그렇게 좋아했는지 모르겠어... Matt가 알게 됐을 때, 그는 소식을 듣자마자 섬에서 도망쳤어. 다시는 토르투가로 돌아오지 않았지. 약간 미친 구석이 있었을지도 모르지만, 나를 사랑했어. 그는 나를 자신의 보물이라고 불렀어...";
			link.l1 = "그래서 그가 소타가 자기 보물을 빼앗아 갔다고 말했을 때 그 뜻이었군!";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "헤, 그 사람이 그렇게 말했다고? 아, 매트... 하지만 우리는 함께 늙을 운명이 아니었던 것 같아. 레바세르가 여자를 노리면, 그 여자가 누구든, 어떤 대가를 치르든 반드시 손에 넣으려 했지. 소타는 그의 선장 중 한 명이었고, 명령대로 행동했어.";
			link.l1 = "알겠어. 그럼 이제 어떻게 할 생각이야, Annabel?";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "도망쳐야 해. 레바쇠르의 부하들이 날 찾지 못하는 곳으로. 이름을 바꿔야 해. 변장해야 해...\n";
			link.l1 = "성공하길 바랍니다. 행운을 빕니다, Annabel.";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "통행을 마련하려면 돈이 필요하실 겁니다. 이것을 받으십시오. 여기 만 페소가 있습니다.";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "돈만 조금 있어서는 부족할 거야. 어두운 피부의 소녀, 그것도 혼혈이라면 도와주려는 사람이 많지 않아. 자, 여기 금화 백 닢이야 - 배를 찾아서 숨어.";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "당신도요! 안녕히 가세요, 선장님.";
			link.l1 = "안녕히 계십시오.";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "저... 무슨 말을 해야 할지 모르겠어요. Matt 말고는 아무도 저한테 이런 친절을 베푼 적이 없었어요.";
			link.l1 = "어쩌면 그게 신호일지도 몰라. 결국 어딘가에서 행복하게 늙어갈 거라는. 잘 가.";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "맞아요. 정말 고마워요. 평생 기도할 때마다 당신을 기억할게요.";
			link.l1 = "감사합니다. 순풍을 빕니다.";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "저 자... 아니, 이제 더 이상 인간이 아니야. 짐승이지. 괴물이야. 여인들을 저렇게 고문하다니...";
			link.l1 = "네가 무슨 생각하는지 알아, 롱웨이. 하지만 들었잖아 – 저자는 노란 피부의 여자를 한 번도 가져본 적 없대.";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "하지만 그는 그 무리를 전부 알고 있었어! 반 데르 빈크, 페르멘텔로스, 소타... 그의 일지에서 우리가 막 읽었잖아. 만약 그 '그녀'가... 바로 그녀라면?";
			link.l1 = "누가 알겠어... 페르멘텔로스에게 복수를 다짐한 여자라면, 그렇게 생각하는 것도 무리는 아니지. 하지만 올리베이로에게 인생이 산산조각 난 여자라면 누구든 될 수 있어. 꼭 네 여동생일 필요도 없고, 꼭 황색 피부의 여자일 필요도 없어.";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "...이걸 시도하는 걸... 거부하시는 겁니까, 나리 선장님? 마지막 순간에 와서...요?\n";
			link.l1 = "아니, 롱웨이. 하지만 그걸 어떻게 상상하는 거지? 레바쇠르가 우리 질문에 답할 가능성은 거의 없어. 그리고 이렇게 토르투가에서 돌아다니는 건 너무 위험해.";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "그럼 어떻게 하자는 겁니까?";
			link.l1 = "기다리자. 우리는 르바쇠르가 네 누이 같은 여자를 좋아하지 않는다는 걸 알고 있어. 그러니 지금은 자원을 아껴두자. 인내와 힘이 필요해. 프랑수아는 만만한 상대가 아니야, 특히 그의 '거북이' 때문이지. 하지만 스벤손의 도움을 받으면 우리가 원하는 방식으로 그와 대화할 수 있어. 네 누이를 찾는 걸 도와주겠다고 약속했으니, 반드시 지킬 거야. 나를 믿겠어, 롱웨이?\n";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "흠... 알겠습니다, 나리 선장님. 하지만 롱웨이가 당신께 한 가지 더 부탁이 있습니다.";
			link.l1 = "무슨 일이야? 또 혼자서 가려고 하는 건 아니지? 지난번엔 그리 잘 끝나지 않았잖아.";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "전혀 아닙니다, 나리 선장. 이제야 깨달았습니다. 안타깝게도, 저 같은 자가 백인들이 지배하는 세상에서 혼자 할 수 있는 일은 아무것도 없다는 것을요. 롱웨이가 요청합니다. 캡스터빌에 정박해서 조르주 그라벨에게 쪽지를 전해 주시고, 준비하시는 동안 무슨 정보든 알아봐 달라고 부탁해 주십시오.";
			link.l1 = "현명한 생각이군, 롱웨이. 그렇게 하자.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "정의의 섬, 롱웨이가 여쭤볼 것이 있습니다...";
			link.l1 = "편지 쓰는 걸 잊었나요? 그냥 그라벨에게 직접 말하면 됩니다.";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "아니요, 편지는 이미 준비됐어요. 하지만 롱웨이가 혼자서 마을을 돌아다니지 않는 게 좋겠다고 했어요. 나리 선장님... 조르주에게 이 편지를 대신 전해주실 수 있나요? 부탁드려요?";
			link.l1 = "내가 심부름꾼처럼 보여? 아니면 여기 선장이 너야?";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "정의의 섬...";
			link.l1 = "하하하, 그냥 농담이야, 롱웨이! 네가 말한 그 그라벨이 어디 있는지 다시 한 번 알려줄래?";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "그는 교회에서 일한다.";
			link.l1 = "알겠어, 내가 처리할게.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// Этап 5
		case "PZ_Mary_Sharptown1":
			dialog.text = "찰스, 내 사랑하는 찰스, 무슨 일 있어? 걱정돼 보이고... 피곤해 보여, 그치?";
			link.l1 = "아니야, 아니야, Mary, 난 괜찮아. 그냥... 내 이 토르투가 일 말이야. 또다시 막다른 길에 다다른 것 같아서 그래... 그리고 그 Sharp의 유언장도 정말 나를 지치게 했지, 정말이지. 하지만 괜찮아.";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "뭐? 무슨 의뢰? 그리고 그게 샤프랑 무슨 상관이야? 아무것도 이해가 안 돼!";
			link.l1 = "질문이 너무 많군, Mary. 여기는 그런 얘기를 할 곳이 아니야.\n선술집 방에서 이야기할까? 네가 좋아하는 대로, 남의 눈과 귀에서 멀리 떨어져서 말이야.\n지난 1년 동안 내가 뭘 했는지 다 얘기해주지.";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "좋아! 하지만 경고해 두지, 뭔가 숨기고 있다면...\n";
			link.l1 = "절대 안 돼! 가자, 어차피 시간도 남잖아...\n";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "이상하지 않나, Charles? 분명 이 섬이 내 소유라고 하는데, 전혀 내 것 같지가 않아.";
			link.l1 = "그렇게 생각해?";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "오, 그 미소 좀 봐... 여자 다루는 법은 잘 아는구나. 그런데 왜 그래? 얼굴이 완전 엉망이야!";
			link.l1 = "왜요? 이게 제 평소 얼굴입니다. 아주 잘생겼죠.";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "찰스, 당신 목소리에서 들려요 - 요즘 많이 침울하셨군요.";
			link.l1 = "요즘 할 일이 너무 많아, 특히 롱웨이 때문에. 정말 지쳤어. 하지만 이제 포기하기엔 너무 늦었어, 특히 그와 아버지께 약속까지 했으니까.";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "이해가 안 돼... 롱웨이가 이 일과 무슨 상관이야? 그리고 무슨 약속을 했다는 거야?";
			link.l1 = "이야기를 하려면 선술집에서 방을 빌려서 합시다. 다른 사람들 없는 곳에서요.";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "좋아, 가자. 어차피 할 일도 없으니, 적어도 같이 시간을 보낼 수 있잖아.";
			link.l1 = "앞장서, 자기야!";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "서로의 품에 안겨 얼마나 달콤하게 잠드는지 보시오! 참 아름답군!";
				link.l1 = "질투나?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "일어나요! 잘 잤어요, 사랑꾼들?";
				link.l1 = "좋아, 물어봐 줘서 고맙군. 그리고 너희들은 어떻게 잤나?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "그건 좀 어리석은 질문 아닌가요?";
				link.l1 = "그래. 그리고 그건 네가 한 정말 어리석은 짓이야. 이유를 알고 싶나?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "샤를 드 모르, 자네 말이 아주 날카롭다고들 하더군.";
				link.l1 = "내 혀만 그런 게 아니야. 알고 싶어? 그런데 말해 봐, 왜 우리가 잘 때 공격하지 않았지?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "그건 왜입니까?";
				link.l1 = "아침에 Mary를 화나게 하면 안 돼. 곧 그 이유를 알게 될 거야.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "간단해! 어두워서 말이지, 누가 여자였는지 구분할 수가 없었거든.";
				link.l1 = "개자식.";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "너희랑 달리, 난 여자라고 안 무서워해. 그런데 말이지 - 얘들아, 저 여자를 멀쩡히 데려가라. 아니면 위그노 놈이 우리를 여자 만들어버릴 거다!";
				link.l1 = "후... 누구?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "적어도 난 사내답게 생겼지. 얘들아, 금발은 살아서 잡아라 - 위그노 놈이 그녀를 기다리고 있다.";
				link.l1 = "후... 누구?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "저 사람이 누구야, Charles? 저 위그노 놈은 도대체 누구지? 정말... 맞는 거야?";
				link.l1 = "하나뿐이야, Mary. 그리고 우리 어서...\n";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "샤를... 방금 뭐였지? 위그노라고? 내가 생각하는 그 사람 맞아?";
				link.l1 = "유감이지만 그래, 헬렌. 우리는...";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "저 소리 들려? 누가 오고 있어, 그치? 아마 이 죽은 놈들의 친구들이겠지.";
				link.l1 = "그럼 그들도 곧 따라가게 될 거야. 준비해...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "저 소리 들려? 발소리야.";
				link.l1 = "정말 그렇소. 내 뒤에 서시오.";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "정의의 섬, 아가씨 " + sStr + ".";
			link.l1 = "롱웨이?! 네가 우리 방에 그냥 들어올 수 있다고 생각해? 만약 우리가...?";
			link.l1.go = "PZ_Longway_62";
			
			//заранее создаём заглушку для корабля
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "음, 실례합니다, 나리 선장. 그렇게 바쁘셨다면 문을 닫으셨을 거라 생각했습니다. 하지만 롱웨이는 문이 열려 있는 걸 발견했지요.";
			link.l1 = "부서졌지, 열리지 않았어. 그런데 말이야, 내 친구, 왜 이렇게 빌어먹게 침착한 거지? 바닥엔 시체들이 널려 있고, 우린 무장을 했는데, 넌...";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "뭐, 난 익숙하니까.";
			link.l1 = "그치? 이건 반박할 수 없지? 그런데 정말로, 여기 오는 길에 싸우는 소리 못 들었어? 이 놈들이 네 눈앞에서 선술집으로 들어가서 계단을 올라가는 것도 못 봤단 말이야? ";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "아닙니다, 나리 선장. 여기 올라오는 길에 홀에서 낯선 사람은 보지 못했습니다.";
			link.l1 = "그건 정말 말도 안 되는 우연이군. 그래서, 뭘 원하는 거지, 롱웨이?";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "긴급히 배와 선원이 필요합니다, 나리 선장님.";
			link.l1 = "뭐? 왜? 드디어 창싱의 흔적을 찾은 거야? 그렇다면, 지금 당장 같이 가자.";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			dialog.text = "장싱이 아니에요, 유감스럽게도. 그게 아니라... 요프 판 데르 빈크입니다. 조르주 그라벨이 전갈을 보냈고, 저는 마을을 거닐다가 그걸 받았어요, 당신은... 그 아가씨와 쉬고 있을 때 말이죠.";
			link.l1 = "그래, 정말 푹 쉬었어, 그건 분명히 말할 수 있지. \n하지만 왜 지금 우리가 헤어져야 하지, 롱웨이? 우리가 해야 할 중요한 일도, 죽여야 할 위험한 놈들도 아주 많잖아.";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "반 데르 빙크는 르바쇠르만큼 위험하지 않아. 게다가, 나는 이미 그를 한 번 쓰러뜨렸지. 그리고 다시 쓰러뜨릴 거야. 이번에는 확실히 죽었는지 확인하기 위해서지. 우리 모두가 그에게 소중한 시간을 허비하는 건 원치 않아. 너는 토르투가에 가서 우리가 필요한 것에 대해 중요한 사람들에게 물어봐. 반 데르 빙크는 내가 직접 잡을 거야. 나리 선장, 이 일에 시간을 낭비할 가치가 없어. 나도 한때 선장이었으니, 내가 알아서 할 수 있다네.";
			link.l1 = "흠, 일리가 있군, 롱웨이. 반 데르 빈크가 그렇게 위험하진 않을지 몰라도, '반텐'은 군도에서 가장 빠른 배 중 하나야. 아무 배로나 쫓을 수 있는 게 아니지. 그리고 선원들은? 혼자서 이렇게 빨리 사람들을 어떻게 모을 생각이지?\n";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "나는 그곳을 잘 알고 있고, 거기서 동인도회사의 지위도 있소. 아니, 적어도 조르주와 했던 것처럼 그렇게 속일 수는 있지. 그 회사... 로덴부르크 나리는 급하게 싸울 인원, 질문하지 않는 전문 선원들이 필요할 때 그들의 서비스를 이용했소.";
			link.l1 = "고용할 수 있는 선원들이라... 그런 게 있는 것도 이해가 가는군. 그리고 비용은 얼마나 드나?";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "이천오백. 즉시, 바로 지금.";
			link.l1 = "그게 다야? 선술집에서 정규 선원 전원을 구하려면 그 정도로는 어림도 없어, 특히 큰 배라면 더더욱. 로덴부르크와 그의 수하들은 특별한 곳에서 특별한 가격을 받는 모양이야.";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "저는 두블룬을 말한 겁니다, 나리 선장님.";
			link.l1 = "뭐라고?!";
			link.l1.go = "PZ_Longway_70_4";
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "제 말 제대로 들으셨죠, 나리 선장. 중요한 일입니다. 하찮은 일로 그런 큰 금액을 요구하지 않았을 겁니다.";
			link.l1 = "그래, 들었어. 하지만 아직도 믿기지가 않아. 정말 특별한 가격이라니. 페소도 받나?";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "그래... 백인들한테서 말이야. 롱웨이는 그 부분에서 힘들어할 수도 있겠지만... 내가 충분히 강하게 부탁하면 설득할 수 있을 것 같아. 방법은 항상 있으니까.";
			link.l1 = "그래, 그거라도 있군. 그런데 그건 선원들 몫일 뿐이지... 그리고 당신은 또 배로 가야 하잖아. 아마 그것도 무슨 '특별한 장소'에 있겠지? 그게 우리한테 얼마나 들지 묻기도 두려워...";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "그렇지 않습니다, 나리 선장. 선원들은 자기 배와 함께 옵니다.";
			link.l1 = "하지만?";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "'메이펑' 말입니다. 저 배는 결정적인 변수가 될 수 있습니다. 군도에서 그보다 빠른 배는 없습니다. 그리고 그 배는... 내 것이었으니, 내가 잘 압니다. 저에게 빌려주시겠습니까, 나의 주군 선장님?";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "여기 있다. 이천오백 더블룬이다. 반 더 빈크의 목을 순금 쟁반에 올려 가져오기만 하면 된다, 하하하하!";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "나는 그렇게 많은 두블룬을 가지고 다니지 않아, 롱웨이. 그리고 배에도 그만큼 있을지 의심스럽군—네가 말하는 건 산더미 같은 금이잖아. 하지만 페소라면, 물론이지. 삼십만이면 네가 필요한 만큼이야.";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "있잖아, 롱웨이... 네가 지금 나한테, 그냥 평범한 깡패 하나랑 싸우려고 공성 함대를 무장할 만큼의 돈을 내라는 거냐?!";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
				
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "오... 롱웨이가 진심으로 감사드립니다, 나의 주군 선장님! 하지만, 그래도 '메이펑'은 어떻게 하시겠습니까?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "그 여자 말인가? 친구야, 여기 오는 길에 머리라도 다친 거야? 지금 우리 함대에 있잖아!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "생각 좀 해봐야겠어, 롱웨이. 반 데르 빙크를 잡을 시간, 얼마나 남았지?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "정의의 섬 선장 나리, 약간 실수하셨소. 이백오십만 페소가 되어야 하오.";
			link.l1 = "나는 아니오; 그건 샤를 드 모르가 친구들에게 도움이 필요할 때 적용하는 특별 환율이오, 하하. 내가 더 얹어 주는 거니 모든 것에 충분할 거요.";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "대단히 감사합니다, 나리. 선장님... 하지만, '메이펑'은 어떻게 하실 겁니까?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "그 여자는 어쩌라고? 내 친구야, 오는 길에 머리라도 부딪혔나? 지금 우리 함대에 있잖아!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "생각할 시간이 필요해, 롱웨이. 반 데어 빈크를 잡을 시간이 얼마나 남았지?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "다른 방법이 없습니다, 나리 선장님, 진정하십시오...";
			link.l1 = "오, 아직 시작도 안 했어. 자, 이렇게 하자. 오만 페소. 그 정도면 조선소에서 브리그 한 척을 사고, 전투 준비까지 하고, 선원도 고용할 수 있지.";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // Лонгвэй будет на бриге
			Notification_Approve(false, "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "하지만, 나리 선장. 백인 선장에게는 그 정도면 충분할지도 모르지! 하지만 모두가 롱웨이와 거래하려 하진 않을 거야. 내게 뭔가를 팔기 전에, 아주 힘든 흥정을 하려 들 거야!";
			link.l1 = "그러니, 설득을 잘 해 보라고! 처음 네가 내놓은... 제안을 보니 흥정에는 꽤 능숙한 것 같군. 아직도 여기 있나? 이 돈을 받아서 어서 가. 네 말대로 그렇게 급하다면서!";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "예, 예, 나리 선장님...";
			link.l1 = "나를 그렇게 쳐다보지 마. 토르투가에서 나중에 보자. 행운을 빌지.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "크흠, 아닙니다, 나리 선장. 물론 기억하고 있습니다. 롱웨이는 단지 당신이 그녀를 저와 나눌 준비가 되었는지 여쭤본 것뿐입니다.";
			link.l1 = "그렇소. 결국, 반 데르 빈크도 우리 명단에 있는 다른 자들과 마찬가지로 당신 누이의 불행에 깊이 연루되어 있소. 그러니 그를 잡는 것이 정말 중요하오. 내가 메이펑의 지휘를 맡기겠소.";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "믿을 수가 없습니다... 감사합니다, 나의 주군 선장님!";
			link.l1 = "아, 별거 아니야. 원래 네 배였으니, 난 항상 그걸 기억할 거야. 자, 가. 그 개자식 죽여. 난 토르투가로 간다.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			Notification_Approve(true, "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "시간이 없습니다, 나리 선장. 허비할 시간이 없소 - 창싱이 우리 도움이 필요할지도 모릅니다...";
			link.l1 = "그건 알고 있어, 롱웨이. 그래도, 우리에게 반 데르 빈크를 잡을 시간이 정확히 얼마나 남았지?";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "몇 달 정도지 - 그는 그 정도 기간 동안 정기 항로를 따라 다니다가 한동안 사라져. 그게 그의 방식이라고 그라벨이 편지에서 내게 알려줬어.";
			link.l1 = "좋아. 그럼 배로 가자...";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "두려우나 준비를 지금 바로 시작해야 하겠소, 나의 로드 캡틴. 내가 메이펑을 손에 넣는 즉시 곧바로 시작할 수 있도록 말이오.\n미리 선원들과 협상해야 하오. ";
			link.l1 = "그래서 어디서 만나는 거지?";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "여기 있습니다. 하지만 편하시면 조선소에서 만날 수도 있습니다.";
				link.l1 = "왜 나만 여기서 돈만 있으면 전투원들로 가득한 선원들을 고용할 수 있다는 걸 몰랐던 거지?";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "그 용병들은 원래 이슬라 테소로에 거처가 있었지만, 여기로 쫓겨왔소.";
				link.l1 = "이해가 가는군. 그럼 라 베가에서는 어디서 널 찾아야 하지?";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "아는 자가 극히 드물기 때문이오. 그리고 그 중에서도 손댈 수 있는 자는 더더욱 적지. 로덴부르흐 나리만이 오랜 세월 그들의 유일한 손님이었소.";
			link.l1 = "알겠어. 좋아, 롱웨이. 거기서 보자.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "선술집이지요, 나리 선장님. 제가 또 어디에 있겠습니까?";
			link.l1 = "그래, 맞아. 그럼 나중에 보자, 롱웨이! 몸조심해.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "정의의 섬 선장님, 선원들이 준비를 마쳤음을 알려드립니다. 마지막으로 처리해야 할 일이 하나 남았습니다. '메이펑'은 어떻게 하시겠습니까?";
			link.l1 = "지금까지는 너에게 어울릴 만한 배를 제대로 고르지 못했군, 롱웨이.";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "War schooner";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "Brig";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "Corvette";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "Polacre";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "Xebek";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "Brigantine";
				link.l2 = "'" + sStr + "'는 당신 것입니다.";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "'메이펑'은 어쩌고? 내가 그녀를 그냥 썩게 놔둘 줄 알았나?";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "내가 너를 위해... 특별한 배를 준비했어, 롱웨이. 빠른 배지. 그리고 메이펑보다 더 치명적이야. 전쟁 갤리온, '플라잉 하트'야.";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "롱웨이, 너는 제벡을 좋아하지. 폴라크르는 어때? 특히 이 배, '토레로' 말이야. 물론 경주용으로 만든 건 아니지만, 꽤 강력하지.";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "고백하자면, 언젠가 이게 쓸모 있을 거라고는 생각 못 했소. 이 갤리온, 어떻게 생각하시오? 위대한 '엘 카사도르'요!";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			
			// а теперь хором, дети: ненавижу костыли, ненавижу костыли, ненавижу костыли, нена... помогите!!!
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "이건 '메이펑'이 아니오, 나의 주군 선장님! 메이펑에 무슨 일이 생긴 것이오?";
			link.l1 = "롱웨이! " + sStr + " 위험해! 네 여동생도 마찬가지야! 그런데 이런 배가 없다고 짜증을 내고 있다고?! 누구라도 이런 배를 가지면 기뻐할 거야! 이 배를 네 지휘 아래 두고, 반 더 빈크에게 네가 어떤 사람인지 보여 줘.";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "좋아... 하늘이 내게 행운을 내려주길 바란다. 토르투가에서 당신에게도 같은 행운이 있기를 바라네. 안녕히 계시오, 나의 주군 선장.";
			link.l1 = "확신해. 안녕, 롱웨이.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "음, 아닙니다, 나리 선장님. 물론 기억하고 있습니다. 롱웨이는 그저 선장님께서 그녀를 저와 나눌 준비가 되었는지 여쭤본 것뿐입니다.";
			link.l1 = "그렇소. 결국 반 데르 빙크도 우리 명단에 있는 다른 자들만큼이나 당신 누이의 불행에 깊이 관여했으니, 반드시 잡아야 하오. '메이펑'의 지휘를 맡기겠소.";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "믿을 수가 없습니다... 감사합니다, 나리 선장님!";
			link.l1 = "아, 별거 아니야. 그 배는 원래 네 배였지, 나는 그걸 항상 기억할 거야. 자, 가. 그 개자식 죽여버려. 난 토르투가로 간다.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "저... 저는 이걸 지휘할 수 없습니다, 나리 선장님. 롱웨이는 아직 자기 목숨과 영혼, 그리고 제정신을 아끼고 있습니다.";
			link.l1 = "하하하, 롱웨이! 설마 네가 그렇게 미신을 믿는 줄은 몰랐어. 그래도 저주는 풀렸으니 이제 두려워할 필요 없어.";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "아... 하지만 반 데르 빈크가 그걸 알고 있을까? 그 배를 보는 순간 겁먹은 토끼처럼 도망칠 거야.";
			link.l1 = "그 말이 맞아. 좋아, 다른 걸 찾아보자.";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// если "Тореро" у ГГ
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				Notification_Approve(true, "Longway");
			}
			
			dialog.text = "내가 직접 선장일 때 폴라크레를 몰아본 적은 없어. 배는 흥미롭지만, 지금은 힘이 아니라 속도가 가장 중요해.";
			link.l1 = "그건 맞지만, 그래도 폴라크 선이잖아. '반텐'만큼 빠르진 않지만, 저 배들이 못 잡는 각도에서 바람을 탈 수 있어. '메이펑'조차도 못 했던 것보다 더 말이지. 그러니 그걸 잘 활용해.";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "그래도... '메이펑'이 더 나았소... 아깝게도 당신이 그 배를 썩히게 했군, 나의 주인 선장. 토르투가에서 행운을 빌지.";
			link.l1 = "당신도요, 롱웨이. 고마워.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// если "Эль Касадор" у ГГ
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				Notification_Approve(true, "Longway");
			}
			
			dialog.text = "군도에서 가장 특이한 갤리온일지도 모릅니다, My Lord Captain. 제가 다룰 수는 있지만, '반텐'보다 느립니다...";
			link.l1 = "글쎄, 지금 조프랑 요트 경주하는 건 아니잖아?";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "뭐든 말씀대로 하시지요. 하지만 '메이펑'이 더 나았소... 아깝게도 그 배를 썩히게 두셨군요, 나리 선장. 토르투가에서 행운을 빕니다.";
			link.l1 = "당신도요, 롱웨이. 고마워.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "걱정해 주셔서 감사합니다, 나리 선장님. 하지만 서둘러 주십시오 - 시간이 많지 않습니다.";
			link.l1 = "알아. 하지만 헛수고하고 싶진 않지, 그치? 좋아, 제대로 된 배를 구해줄게.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "거의 다 왔네, Charles. 어디서부터 시작할지 정했나? 어쩌면 거리의 사람들에게 물어보는 게 좋을지도 모르겠군...\n";
			link.l1 = "어쩌면 그럴지도. 하지만 우리를 위한 게 아니야, 나를 위한 거지. 헬렌, 넌 배에 남아.";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "샤를, 물론이죠, 저 악당들과 그들이 한 말 때문에 아직도 불안합니다. 그래서 선원들 보호 아래에 있는 게 당연하다고 생각해요... 하지만 당신이 혼자서 그 괴물의 소굴로 들어가는 걸 보면, 제 마음이 더 불안해져요.";
			link.l1 = "알겠어. 하지만 일이 잘못되면, 네가 안전하다는 걸 알면서 혼자 도망치는 게 훨씬 쉬워. 명령이야, 헬렌. 여기서 나를 기다리고 너무 걱정하지 않으려고 해봐.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "여기가 토르투가야, Charles, 그치? 어떤 문을 두드리면서 그 뚱뚱한 당나귀가 나한테 뭘 원했는지 물어볼 생각에 못 참겠어...";
			link.l1 = "바로 그래서 네가 배에 남는 거야, 내 사랑.";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "말도 안 돼! 내가 너 혼자 상륙하게 둘 것 같아?";
			link.l1 = "레바쇠르가 그의 용병들이 실패한 일을 직접 끝내기로 마음먹는다면, 우리는 반격할 기회조차 없을 거라고 생각해. \n나는 그를 불필요하게 자극하고 싶지 않아, 특히 내 목표가 그가 아니라 요프 판 데르 빈크이기 때문에.";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "그래서 이제 내가 갇힌 거네, 그치?";
			link.l1 = " 명령하는 게 아니야, 부탁하는 거야, Mary.";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "그 더러운 섬의 뒷골목에서 당신에게 무슨 일이 생기면 어쩌죠?";
			link.l1 = "그럼 나도 영웅 흉내는 내지 않을게. 그리고 네가 안전하다는 걸 알면 더 빨리 달릴 수 있을 거야. 그러니까 배에서 기다려 줘. 제발, 무슨 일이 있어도 절대 상륙하지 마.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "누구요? 해변을 건너와서 그냥 이야기나 하려고 온 건 아니겠지.";
			link.l1 = "맞아. 샤를 드 모르. 로베르 마르텐?";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "샤를 드 모르? 젠장, 수상한 일에만 나 끌어들이지 마라. 그래, 나다. 그래서, 뭘 원하는 거지?";
			link.l1 = "조프 판 더 빈크와 친구라고 들었는데, 그리고...";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "누가 그렇게 말했지? 놈의 배를 갈라버릴 거야. 뭐, 우리는 그냥 아는 사이일 뿐이야. 그가 당신을 건드렸다고 해서 나는 문제에 휘말리고 싶지 않아.";
			link.l1 = "헤, 친구를 그렇게 쉽게 포기하는구나...";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "그렇게 생각하지 마. 난 너를 두려워하지 않아. 하지만 왜 굳이 애를 쓰거나 문제를 만들려고 하지? 네가 들은 것만큼 나는 Joep를 잘 알지 못해. 그 사람을 찾고 있는 거야?";
			link.l1 = "그래, 뭐 그런 셈이지. 그가 이미 토르투가를 떠난 건 알지만, 그에 대해 더 알아두면 나쁠 건 없잖아. 어디를 다녔는지, 누구와 얘기했는지 같은 거 말이야. 도와줄 수 있어?";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "어차피 당신에게 도움이 되지 않을 테니... 왜 안 되겠소? 그는 사창가에 있었소. 그 사창가 말이오. 당신이라면 갈 수 있을 것 같아서 말해 주는 거요.";
			link.l1 = "새로운 사창가? 이제 하나로는 부족해?";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "글쎄, 새롭진 않지만 아는 사람은 많지 않아. 그리고 살 수 있는 사람도 드물지. 이제 네 차례가 온 것 같군. 하지만 경고하지 - 두블룬만 받아. 은화 내밀면 엉덩이에 발길질이나 맞을 거야.";
			link.l1 = "그럴 줄 알았지. 그런데 그 매음굴이 어디라고 했지?";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "기둥 있는 그 건물 알지? 바로 거기야. 그리고 거기 여주인도 끝내주지! 피부가 노랗고, 정말 예쁘다니까! 허, 벌써 군침 흘리는구나, 응?\n";
			link.l1 = "헤헤, 뭐, 그런 셈이지. 고마워, Rober. 오늘은 너한테 문제 없을 거야 - 나한테 큰 도움이 됐으니까.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "드디어 돌아왔네, Charles! 나는 정말 어쩔 줄 몰랐어, 그치!";
			link.l1 = "금방 올게, Mary. 잠깐 처리할 일이 있어... 궁금해하지 마, Longway 일 때문이야. 근처 사창가에 들러야 해.";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "혼자 상륙하게 두지 말았어야 했는데. 모자를 안 써서 머리가 뜨거워졌든지... 아니면 머리를 부딪혔겠지, 그치?";
			link.l1 = "Mary, 내 말 들어. 이 선술집 주인이 롱웨이의 누이일 수도 있어. 확실히 하려면 내가 직접 봐야 하는데, 그게 내가 할 전부야. 안에 들어가지 않으면 그럴 수 없어. 하지만 네가 괜한 오해는 하지 않았으면 해.";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "정말 나에게 거짓말하는 거 아니지, Charles?";
			link.l1 = "Mary, 이렇게 생각해 봐... 사랑하는 사람에게 이런 경고를 하는 남자, 들어본 적 있어...?";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "거기서 멈춰, Charles. 그런 생각조차 하고 싶지 않아. 나는 너를 믿고 신뢰해. 그리고 네가 꼭 필요한 시간 이상으로 거기 머무르지 않길 바란다.";
			link.l1 = "단 1분도 더 안 걸려, 자기야, 약속해. 금방 들어갔다가 나올 거야, 곧 알게 될 거야.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "찰스! 예상보다 훨씬 빨리 돌아왔군요. 그런데 무슨 일이 있었던 겁니까? 안색이 좋지 않네요... 요프 판 더르 빈크에 대해 뭔가 알아냈습니까?";
			link.l1 = "아직 아니오. 몇 가지는 알아냈지만, 더 알아보려면... 나는 창관에 가야 하오. 물론, 당신이 생각하는 그런 이유는 아니오.";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "술집이요? 이런 곳이 뻔한 것 말고도 뭔가를 제공하는 줄은 몰랐소.";
			link.l1 = "나는 주인하고 얘기 좀 해야 해, 그게 다야.\n그리고 그냥 평범한 사창가가 아니야. 소문에 따르면—여긴 아주 비싼 곳이고, 상류층만 들어갈 수 있다더군...";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;
				
		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "그럼, 너한테 딱 맞겠네, 자기야. 아, 농담이야. 그래도 네가 거기 가는 건 썩 내키지 않아. 하지만...";
			link.l1 = "나는 정말로 롱웨이 일로만 가겠다고 약속해. 그곳의 주인이 그의 누이일 가능성이 꽤 있어. 오래 머물지 않을 거야.";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;
		
		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "원하시는 대로 하세요. 그런 일에 대해 저에게 알릴 의무는 없으시죠. 저도 다른 남자와 잠자리를 하지 않겠다고 약속한 적 없습니다. 그런데도 저는 그렇게 하지 않아요. 그건 당연한 일이라고 생각하니까요.";
			link.l1 = "다른 상황이었다면 당신을 데려갔을 텐데, 하지만...";
			link.l1.go = "PZ_HelenaTortugaCabin_15";
		break;
		
		case "PZ_HelenaTortugaCabin_15":
			dialog.text = "고맙지만, 됐어. Charles, 걱정하지 마. 나 바보 같은 질투쟁이 여자는 아니야. 음, 질투는 좀 나지만, 바보는 아니거든. 그리고 난 네 말을 믿어. 내가 멍청하지 뭐!";
			link.l1 = "고마워, 헬렌. 금방 돌아올게.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "오, 우리 업소에 새로운 얼굴이군요? 환영합니다, 나리. 음식, 숙성된 와인, 뜨거운 목욕—이 모든 것이 당신을 기다리고 있습니다. 우리 중 한 명과 시간을 보낼 여유만 있다면 말이지요.";
			link.l1 = "환대해 주셔서 감사합니다, 아가씨. 하지만 그게 제가 여기 온 이유는 아닙니다. 저는 누군가를 찾고 있습니다...";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// Убираем Мартэна с Маяка
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "오직 마음으로만 올바르게 볼 수 있다네. 본질적인 것은 눈에 보이지 않지.";
			link.l1 = "아름답군요. 그런 대사는 처음 들어봅니다.";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "여기서는 교육도 받아. 그냥 인형이 아니야. 여주인께서 우리 업소에 꼭 필요하다고 생각하시거든.";
			link.l1 = "여주인! 내가 찾는 사람이 바로 그 사람이야. 노란 피부라고 들었어. 말해 봐, 정말이야? 그런데 이름이 뭐지?";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "사실이야. 하지만 그 여자는 많은 백인 여자들보다 사업 수완이 더 뛰어나. 이름은 벨 에투알이야. 이제 그만 얘기하지.";
			link.l1 = "말이 충분하다고 하셨습니까? 나는 이야기를 하러 온 사람입니다. 질문 몇 개만 더 하고 떠나겠습니다.";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "그럼 이 집에 무슨 이득이 있겠소? 여기선 몸값이 아니라 시간값을 받지. 이야기하고 싶으면, 얼마든지. 하지만 돈은 선불이오. 그리고 방에서, 남의 귀를 피해 속삭일 거요. 거기서 뭘 하든 난 상관없소 - 촛불을 켜고 기도만 해도 상관없지. 어떤 손님은 시를 쓰는 걸 도와달라고 했고, 또 어떤 이는 자기 고민을 털어놓으며 나를 좋은 친구라 불렀소. 그리고 또 다른 이는... 그냥 촛불만 켜달라고 했지, 그 다음엔...";
			link.l1 = "글쎄, 알고 싶지 않아. 최근에 이미 불쾌한 소식을 들었거든. 내가 얼마를 내야 하지?";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "이백오십 두블룬이다. 흥정은 없다. 우리가 빈털터리 사기꾼이라는 걸 알게 되면, 미련 없이 내쫓는다. 그리고 돈은 많지만 욕심 많은 놈이면, 값을 올린다 – 어차피 내게 되어 있으니까.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "자, 여기 250골드다.";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "와, 여기 자메이카의 그 창관보다 더 비싸네. 금 가져온 다음에 다시 와도 돼?";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "좋아요. 어디서부터 시작할까요? 저녁 식사, 촛불은 켤까요 말까요, 목욕, 아니면 대화부터?";
			link.l1 = "시간이 많지 않으니, 바로 질문부터 하겠다. 앞장서라.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "물론이죠. 인내는 기녀의 미덕 중 하나입니다. 거지를 내쫓는 건 쉬운 일이지만, 부유한 신사인 당신이 돈을 가지러 가거나 심지어 빌리게 두는 건 전혀 다른 문제죠.";
			link.l1 = "창녀의 미덕이라... 아이러니하군. 금방 돌아오지.";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "돌아오셨군요, 나리! 그래서, 당신은 누구요? 부유한 신사입니까, 아니면 허세꾼입니까?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "물론이죠, 나는 부유한 신사입니다, 아가씨. 여기 당신의 금화가 있습니다 - 모두 이백오십 두블룬이에요. 굳이 세어볼 필요 없습니다.";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = "아직 부족하지만, 좀 참아 주시오.";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "여기서는 계산하지 않아. 흠, 동전 몇 개가 휘고 부서진 것 같네 - 여주인께서 그걸 별로 좋아하시진 않겠지만, 적어도 전부 진짜 금이야.";
			link.l1 = "참... 우아한 사람이군.";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "맞아요. 에투알 부인은 부드럽고 자상할 수도 있고, 엄격할 수도 있고, 무자비할 수도 있죠. 그래서 우리 같은 사람들은 숫자에 들지도 못해요. 주인마님은 항상 바로 대가를 받는 건 아니지만, 결국엔 반드시 자기 몫을 챙기죠. 금이 아니면 피로라도요. 어떤 환락의 집이든 보호자와 후원자가 필요해요. 그리고 우리 집의 보호자들은 그 위상에 걸맞은 사람들이죠.";
			link.l1 = "돈은 냈으니, 안내해.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "그래서, 무슨 질문이 있습니까, 나리? 당신의... 호기심을 만족시켜 드리겠습니다.";
			link.l1 = "무엇이 제 관심을 끄는지 아십니까, 아가씨 - 당신의 주인, 에투알 부인입니다.";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "그녀에 대해 뭐라고 말할 수 있을까요? 우리에게조차 여전히 수수께끼입니다.\n우리의 안녕과 건강, 안전을 신경 쓰긴 하지만, 우리 누구와도 어울리거나 가까워지지는 않습니다.";
			link.l1 = "아마 긴 대화를 좋아하지 않는 것 같군요. 말해보시오, 그녀가 말할 때 억양이 있소?";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "아니오, 왜 그렇게 생각하십니까? 그녀가 피부가 노랗다고 해서요? 그녀는 순수한 프랑스어를 구사하고, 여러 다른 언어도 할 줄 압니다. 그리고 어떤 주제든 손님이나 잠재적 이해관계자와 한 시간 동안 대화를 나눌 수 있습니다.";
			link.l1 = "그렇습니까. 흥미롭군요... 지금 그녀가 여기 있습니까? 그렇다면, 그냥 들어가서 그녀를 직접 보겠습니다. 더 이상 당신의 정말... 값비싼 시간을 낭비하지 않게 해 드릴 테니, 다시 일로 돌아가시지요.";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = "돌아갈 만한 곳이 많진 않소 – 하지만 우리 여주인은 이곳을 군도 최고의 장소로 만들겠다는 목표를 가지고 있지. 상인도, 귀족도, 아니면 그저 교양 있는 사람이라도 부끄러워하지 않고 올 수 있는 그런 엘리트 장소 말이오 – 왜냐하면 우리는 육체 그 이상을 제공하니까.";
			link.l1 = "하지만 그리 성공적이지는 않잖아, 그렇지?";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "어떻게 말해야 할지... 그녀는 우리 한 사람 한 사람을 단순히 상품으로 보는 게 아니라, 일종의 프로젝트로 여깁니다. 값비싼 옷, 약, 교육까지—우리 모두에게 투자하지요. 만약 우리가 구세계의 대도시에 있었다면, 그녀는 분명 성공했을 겁니다! 하지만 여기서는... 아무리 재능 있는 상인이라도, 물건 값이 너무 비싸서 아무도 살 수 없다면 아무 소득도 얻지 못합니다. 우리가 가격을 낮춘다 해도, 언젠가는 결국 망하게 되어 있지요.";
			link.l1 = "유감이군요. 그럼 지금 당신의 여주인은 어디에 있습니까?";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "여기서 우리는 지금까지 꽤 괜찮은 삶을 살고 있어, 분명히 말할 수 있지. 그만큼 얻고 지키기 위해 대가를 치러야 하고, 그녀의 기준을 맞추는 것도 쉽지 않아...\n그 여인 말인데, 에스파뇰라로 갔어. 우리 모두를 포르토프랭스로 옮기는 가능성에 대해 논의하러 말이지. 결국 그곳이 더 많은 교역로가 모이는 곳이니까, 우리의 무역도 거기서는 가만히 정체되어 손해만 보는 일은 거의 없을 거야. ";
			link.l1 = "그래? 레바쇠르가 이곳의 안정을 위해 투자한 것 아니었나?";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "별로 많진 않았어. 그가 우리한테 와서, 가끔씩 자기 집에 들르기만 하면 크게 투자하겠다고 했지. 하지만 그 숙녀분이 단호하게 거절했어. 너무 단호해서 각하께서도 잠시 당황하셨지. 그런 모습은 그녀도, 그분도 처음 봤어.";
			link.l1 = "헤헤, 저것 좀 봐. 저 여자가 뭔가 아는 것 같군... 용감하네, 아주 용감해.";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "있잖아? 그런데 이렇게 잘 얘기하고 있으니까, 한 가지 더 말해줄게. 근데 이건 정말 큰 비밀이니까 아무한테도 말하지 마!";
			link.l1 = "오, 아니오, 마드모아젤. 부디 안심하십시오. 저는 당신의 아가씨께 어떤 해도 끼칠 생각이 없습니다. 계속 말씀하십시오.";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "나는 네가 그녀를 해칠 수 있을지조차 모르겠어, 왜냐하면 벨 에투알은 매일 펜싱을 연습하고, 이 도시 전체에서 그녀와 맞설 만한 상대가 없거든. \n포르토프랭스뿐만 아니라, 그녀는 직접 마커스 타이렉스에게 투자를 제안할 계획이야! 아니, 정확히는 그에게서 대출을 받으려는 거지. 상상이 가?";
			link.l1 = "그래, 그리고 오늘은 펜싱을 자주 연습하는 또 다른 여성과 아주 힘든 대화를 하게 될 것 같은 예감이 들어... 자, 이야기해줘서 고마워, 마드모아젤. 좋은 하루 보내고, 손님들도 넉넉하길 바라.";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "감사합니다. 그런데 왜 그리 서두르시나요? 이미 전부 지불하셨고, 우리 대화도 그리 오래되지 않았잖아요. 게다가, 나리께는 뭔가 세련된 기운이 있어요. 우리 집에 드문 부자들과는 전혀 다른 뭔가가요. 진짜로 서로의 시간을 즐겨볼까요?";
			link.l1 = "있잖아... 도대체 왜 이러지? 왜 내가 이걸 원하지 않는 척, 스스로에게 거짓말을 하고 있는 거지? 너 같은 여자와의 기회는 정말 드물잖아.";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "아, 유감이지만 아니오, 아가씨. 나는 여기 대화하러 왔을 뿐이오. 게다가... 나를 기다리는 이가 있소.";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "그런 게 누굴 막은 적 있던가요. 그렇다면, 존경을 받아 마땅하십니다, 나리. 당신의 '누군가'를 위해 진심으로 기쁩니다.";
			link.l1 = "다시 한 번 고마워요, 아가씨. 안녕히 가세요.";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "고마워요. 우선 뜨거운 목욕 같이 할래요?";
			link.l1 = "두 손 다 찬성입니다.";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "정말 마법 같은 경험이었어요, 나리. 남자가 나를 이렇게 놀라게 할 줄은 몰랐어요. 여자를 기쁘게 하는 법을 정말 아시는군요...";
			link.l1 = "여자에 따라 다르지.";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "후회하십니까?";
			link.l1 = "지금은 절대 아니오. 안녕히 계시오, 아가씨.";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // флаг того, что секс был (понадобится для диалога с Тираксом)
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "어디 보고 다니는 거야, 가짜놈!";
			link.l1 = "입 조심해!";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "나는 까마귀를 세고 있는 당신과 달리, 앞을 보고 가고 있었소.";
			link.l1 = "찾으려고만 했다면 돌아갈 수도 있었겠지, 안 그래?";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "내가 왜 너를 돌아가야 하지?!";
			link.l1 = "도시 밖에서 누가 누구에게 무엇을 빚졌는지 알아보는 게 좋겠소.";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "음-음, 아니오. 당신 나리께서 하찮은 남자의 의도치 않은 손길에 그렇게까지 역겨워하실 줄은 몰랐소.";
			link.l1 = "다시 말씀해 주시겠습니까?";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = "흠, 미안하오. 밀치려던 건 아니었소.";
			link.l1 = "이제 좀 낫군.";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "네가 삼십 분만 늦었어도, Charles, 내가 이 더러운 소굴을 대포알로 박살냈을 거야, 그치! 찾던 거 발견했어? 저 사람이야, Longway의 여동생? 봤어?";
			link.l1 = "쉬, Mary, 그렇게 말하지 마. 아니, Chang Xing을 만나지는 못했어...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "그럼 대체 왜 그렇게 오래 걸린 거야?! 거기서 뭘 하고 있었던 거지?";
			link.l1 = "걱정하실 필요 없습니다. 알아낼 수 있는 모든 것을 알아낸 즉시, 약속드린 대로 그곳을 떠났습니다.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "그냥 말해, 그치!";
			link.l1 = "지금은 주인이 토르투가에 없어. 이곳에서는 그녀의 서비스 수요가 적은 편이야. 그녀는 값비싼 옷을 입은 교양 있는 숙녀들만 고용하고, 그들은 대금도 금으로만 받거든...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "너도 그놈들에게 돈을 줬어?!";
			link.l1 = "그 사람들이 아니었으면 나랑 말조차 안 했을 거야.\n저런 태도로는 손님이 많지 않은 것도 당연하지.\n마담은 더 부유한 손님을 끌어들이려고 장사를 포르토프랭스로 옮기기로 했어.\n하지만 돈이 많이 부족한 게 분명해, 마커스 타이렉스에게 대출을 부탁하려고 하니까...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "그가 그녀를 아는가?";
			link.l1 = "라 베가에 도착하면 알게 되겠지. 그리고 쓸데없는 말로 시간 낭비하지 말고 서두르면, 그 아시아 여자를 잡을 수 있을 거야, 누구든 간에.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "그 창녀촌에 갈 필요는 없었어, Charles. 우리가 조금만 더 노력했다면 선술집이나 거리에서도 이 모든 걸 알아낼 수 있었을 거야, 그치?";
			link.l1 = "다음번엔 네 예쁜 빨간 머리에 쓸데없는 생각 안 하게 내가 데려갈게, 알겠어? 이제 본론으로 들어가자.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "오, 내가 좀 늦었네, 그치! 자, 기다려 봐, 이 악당아...";
			link.l1 = "Mary, 도대체 여기서 뭐 하는 거야?! 배에 있으라고 했잖아!";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "내가 네가 창녀들이랑 노는 걸 막지 않을 거라고?! 변명할 생각도 하지 마, Charles! 선원들이 거기서 너를 봤어, 그치! 어떻게 그럴 수가 있어?!";
			link.l1 = "내 생각도 그랬어. 차라리 그들을 데리고 갔어야 했나 봐, 내가 뭘 하고 있었는지, 아니, 사실 아무것도 안 하고 있었다는 걸 직접 보게 말이야... 그랬으면 괜히 소란 피우지도 않았을 텐데...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "우리 아이들이 거짓말한다고 몰아세우는 거야? 네가 저지른 짓을 생각하면, 네가 더 짐승 아니냐?";
			link.l1 = "나는 그들에게 그저 비할 데 없는 어리석음만을 탓하고 있소. 상황도 제대로 파악하지 못하고, 당신은...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "오-오, Charles, 내가 그 구멍에 제때 도착했다면 네놈이랑 네 창녀들이 내가 상황을 어떻게 이해했는지 절대 마음에 들어하지 않았을 거야. 하지만 운이 좋군 – 이 빌어먹을 배를 나 혼자 노 저어야 했으니까...";
			link.l1 = "힘든 육체노동이 쓸데없는 생각을 없애준다고들 하지. 하지만 너는 아직도 잡생각이 많으니, 다시 노를 저어야겠군.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "나 안 움직여, 그치!";
			link.l1 = "Mary, 여기서 Levasseur의 부하들 앞에서 이런 얘기 안 할 거야. 진정하고, 주위를 잘 살펴보고, 스스로 판단해. 지금은 때도, 장소도 아니야.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "지옥이나 가라. 아직 내 짐이 선실에 남아 있거든... 하지만 내가 다시 노를 젓게 될 거라고는 생각하지 마, 그치! 너한테도 귀족의 피가 조금은 남아 있을 테니까!";
			link.l1 = "나는 악당이고 짐승이야, 기억하지? 배에서 내가 어떤 놈인지 보여주지. 하지만 먼저 거기까지 가야 해. 그러니 네 애원은 소용없어.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "네가 온 선원들 다 비웃게 만들었어, 그치!";
			link.l1 = "글쎄, 어쩌면 너한테도 그랬을 거야. 저런 구경은 정말 오랜만이었으니까. 이제 화가 좀 가라앉았으니, 무슨 일이 있었는지 말해줄게.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "찰스, 이제 모든 걸 다 들었어. 나에게 딱 한 가지만 묻고 싶어. 내가 너에게 충분하지 않았던 거야? 내게 뭐가 부족했던 거야?";
			link.l1 = "실례지만, 질문으로 답하겠소: 내가 당신이 나를 믿지 못할 만한 이유를 준 적이 있었소? 응? 난 그런 기억이 없소. 그러니 숨 좀 고르고 내 말 들어보시오. Joep van der Vink에 대해 알아낸 건 별로 없었소. 그가 사창가에 갔다는 것뿐이오. '노래하는 까마귀' 근처가 아니라, 부두 근처에 있는 다른 곳이었소. 나도 전엔 몰랐소... 하지만 우리 선원들은 이미 당신에게 다 알려줬더군. 물론, 그들이 거기 가는 건 허락되지 않았겠지만...\n";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "어떤 사창가가 뱃사람들을 못 들어오게 해, 그치?";
			link.l1 = "비단을 두른 여인들이 머릿속에 바람만 가득한 게 아닌 그런 사창가지. 그리고 그들의 봉사는 오직 금화 두블룅으로만 값을 치러야 해. 아무나 멋대로 정한 게 아니라, 그곳의 신비로운 여주인 벨 에투알의 명령이지.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "수상하네, 그치?";
			link.l1 = "그것만이 아니야. 그녀는 아시아인이야.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "아시아인? 토르투가의 그 사창가 마담 말인가?";
			link.l1 = "장싱일 수도 있습니다. 그래서 제가 거기에 갔던 것입니다 - 제 눈으로 그녀를 직접 보고 싶었으니까요. 그게 전부입니다.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "그녀는 어떤 사람이야?";
			link.l1 = "모르겠소. 그녀는 거기 없었으니, 나는 다른… 별과 이야기를 나눠야 했소.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "그 여자도 아시아 사람이었어, 그치?";
			link.l1 = "아니, 그녀는 백인이었어. 그녀가 말하길, 벨 에투알이 요즘 잘 안 돼서 포르토프랭스로 옮기기로 했다고 하더군. 그곳 사람들이 더 부유하니 당연한 선택이지. 마담이 에스파뇰라에서 장사를 열려면 대출이 필요해서, 타이렉스에게서 돈을 빌릴 생각인 모양이야. 그러니 우리가 라 베가로 서두르면 마르쿠스가 그녀를 만나기 전에 가로챌 수 있어.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "나는 그 여자든 마커스든, 다른 누구든 전혀 신경 안 써, 그치? 찰스, 딱 한 가지만 말해 줘. 그 여자의 사창가에 있는 여자들 중 누구랑 같이 있었어?";
			link.l1 = "그런 건 필요 없어, Mary. 난 너만 있으면 돼, 세상에서 제일 멋진 여자잖아. 왜 네가 그걸 모르는지 이해가 안 돼.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "사실 진실을 알아내는 건 정말 쉬워, 그치? 히히. 아무하고도 안 놀아봤으면 지금 엄청 힘이 넘칠 거 아냐. 그걸 지금 확인해볼 거야, 그치!";
			link.l1 = "Mary, 제발..";
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					Notification_Perk(true, "Medic");
					dialog.text = "(건강 양호) 으윽... 거짓말 아니었네, Charles, 그치...";
					link.l1 = "나는 당신을 속일 필요가 없소, 나의 소중한 이여...";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					Notification_Perk(false, "Medic");
					dialog.text = "찰스, 너... 진심이야?! 그게 뭐였어?";
					link.l1 = "아, 이 더위는 정말 힘드네요. 에헴.";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "으윽... 거짓말은 아니었네, Charles, 그치...\n";
				link.l1 = "나는 너를 속일 필요가 없어, 나의 소중한 이여...";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "하지만 그 조각배 타던 기억은 오래도록 잊지 못할 거야!";
			link.l1 = "하!";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "지금까지 한 번도 불평한 적 없었잖아, 그렇지?";
			link.l1 = "피투성이 섬을 네가 한 번 뛰어다녀 봐라...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "그리고 그 창관들, 그치! 너 정말로...\n";
			link.l1 = "Mary, 미안해.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "뭐?! 그럼 너는...\n";
			link.l1 = "그건 전혀 미안하지 않아. 젠장. 그러니까, 난 너 말고는 아무도 없었어, 말했잖아. 그냥... 마음이 놓이지 않았을 뿐이야, 그게 다야. 그게 쉽지 않거든, 라 로슈의 대포들이 널 노려보고 있는데 말이야.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "그럴듯한 변명이네, Charles. 좋아, 믿어줄게. 이번만... 하지만 아직도 너한테 화났다는 거 알아, 그치!";
			link.l1 = "당신의 용서를 꼭 받겠어요, 약속합니다.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "그래, 바람둥이. 뭘 알아냈는지 말해 봐. 내 호의를 걸 만큼 가치가 있었어?";
			link.l1 = "당신이 농담하는 건지 진심인 건지 정말 모르겠군요. 그래도 결국엔 도움이 됐어요 - 비록 제가 그 여주인을 직접 보진 못했지만요.\n그녀는 아시아인이고 이름은 벨 에투알이에요 - 멋진 별이라는 뜻이죠. 물론 진짜 이름은 아니지만...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "그래서 그걸 알아내려고 창관에 간 거야? 여관에서는 알아볼 수 없었어?";
			link.l1 = "이곳에 대해 마을에서는 별로 말하지 않아. 왜일까? 좋은 질문이지. 직접 벨 에투알에게 물어봐도 돼 – 그녀는 에스파뇰라로 갔거든.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = "토르투가는 그녀에게 부족했나?";
			link.l1 = "여기서는 장사가 잘 안 되는 것 같군요. 그녀는 평범한 항구 여인들을 고용하지 않고, 값비싼 옷을 입고 교양 있는 숙녀들만 고용하네요.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "그 사람들이 왜 그런 짓을 하겠소?";
			link.l1 = "그것도 좋은 질문이군. 아무튼, 우리 작은 새는 포르토프랭스로 날아가기로 했어, 드 뮈삭의 영지지. 하지만 이 일을 위한 자금은 다름 아닌 타이렉스에게서 빌리기로 했어.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "이 이야기가 빨리 끝났으면 좋겠어. 시간 낭비하지 말고 라 베가로 바로 항로를 잡자.";
			link.l1 = "그렇게 하겠소.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "참 용감한 사람이군, Charles. 그 점은 인정하지. 아무 일도 없었던 것처럼 이렇게 태연하게 나타나다니.";
			link.l1 = "아마 선원 중 누군가가 떠벌렸겠지? 아무런 맥락도 없이 말이야. 사실 아무 일도 없었어—적어도 네가 생각하는 그런 일은 아니야.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "부정하지 않아서 다행이야, Charles.";
			link.l1 = "나는 모든 걸 말하려고 했어, 헬렌.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "하지 마, Charles. 세부사항에는 별로 관심 없어. 하지만 이유는 궁금해. 말해 줘, 나한테 무슨 문제가 있는 거야?";
			link.l1 = "이유부터 말씀드리겠습니다. 토르투가에는 매음굴이 두 곳 있다는 걸 알게 되었습니다.\n하나는 잘 알려져 있습니다. 다른 하나는... 사람들은 존재를 알지만, 말하려는 이가 거의 없습니다. 그곳은 아시아 여자가 소유하고 있습니다...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "즉흥적으로 지어내는 건가?";
			link.l1 = "내가 대체 왜 그런 짓을 해야 하지, 헬렌?! 네가 못 믿겠으면, 그곳에 가서 직접 확인해 봐!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "첫째, 당신이 상륙하지 말라고 했으니 내가 거길 갈 방법이 없어. \n둘째, 내가 누군지 대체 뭘로 보고 그래?! 그런 데 근처엔 절대 안 가! \n셋째... 그냥 계속 해.";
			link.l1 = "좋아. 나는 직접 마담 에투알을 내 눈으로 보기 위해 거기로 가기로 했어. 그게 내 유일한 의도였어, 젠장!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "그런가요. 그녀를 만났습니까?";
			link.l1 = "아니. 그녀는 에스파뇰라로 갔어. 여기서는 일이 잘 풀리지 않아서, 포르토프랭스로 가서 운을 시험해 보기로 했지. 거기서는 그녀의 업소에서 일하는 비단옷을 입은 교양 있는 숙녀들이 토르투가보다 더 많은 이익을 가져다줄 수 있으니까...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "차려입고 교육도 받았다고? 와, 인생이란 참 별일이 다 있구나. 하지만 그 사람들은 있는 그대로를 좋아해야 해.";
			link.l1 = "헬렌, 그만해. 내가 네 불신을 살 만한 짓은 아무것도 안 했어.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "맞아요. 만약 나를 속이려 했다면 이렇게 침착하지 않았겠지요. 하지만 계획을 미리 말해줬어야 했어요, Charles.";
			link.l1 = "맞아, 자기야. 하지만 시간을 좀 아끼려고 했어. 내 실수야.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "좋아. 이제 어떻게 할까, Port-au-Prince로 항로를 잡을까?";
			link.l1 = "라 베가. 놀라지 마, 헬렌. 벨 에투알 부인은 상황이 좋지 않아. 장사를 포르토프랭스로 옮기려고 돈이 필요해서 마르쿠스에게 빌리기로 했지. 우리가 서두르면 거기서 그녀를 잡을 수 있어. 그러니 한순간도 낭비하지 말자.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ_1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ_1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				ReturnOfficer_Mary();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				ReturnOfficer_Helena();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "너 같은 놈이랑 네 졸개들이 우리를 이겼다니, 믿을 수가 없군!";
			link.l1 = "너...";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "오, 나를 알아보는군?";
			link.l1 = "우리가 만난 적 있습니까?";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "뭐?! 지금 장난치는 거야, 씨발?!";
			link.l1 = "내가 만나는 모든 미개한 쓰레기들을 다 기억할 수는 없지. 누가 널 우리를 죽이러 보냈는지 말하는 게 좋을 거다. 아니면 그냥 너를 처리하고 싶었던 걸지도 모르지?";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "너 같은 놈한테는 아무 말도 안 해. 네가 얼마나 잘난 척하는지 보이네! 여기서 잠깐 쉬고 나서도 그 잘난 자존심 계속 지킬 수 있나 보자.";
			link.l1 = "안됐군. 넌 역겹지만, 그냥 다른 섬에다 버릴 수도 있었지. 이제 내가 할 수 있는 건 너를 저편으로 보내는 것뿐이야.";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // флаг - абордаж был
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "저를 부르셨습니까, 선장님?";
			link.l1 = "그래, 친구. 피해 상황 보고해.";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "거센 폭풍이 몰아치고 있어. 배가 삐걱거리며 부서질 듯 흔들리고, 심하게 요동치고 있어.";
			link.l1 = "그래, 나도 알아챘어. 티칭기투, 내 친구. 나와 \n " + sStr + " 상륙하겠다. 너는 여기서 지휘를 맡아라. 즉시 수리를 시작해라 - 폭풍이 가라앉을 때까지 조선소에 가는 건 소용없다. 게다가, 우리도 오래 머물진 않을 거다.";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "내가 모든 걸 더 좋아 보이게 만들겠어.";
			link.l1 = "좋아, 고마워. 그럼 아무 걱정 없이 마을로 간다.";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "나리 선장님? 영광입니다. 하지만 이런 때에는 보통 알론소를 부르시지 않으셨습니까? 실례가 안 된다면, 무슨 일이라도 있으신지요?";
			link.l1 = "응, 다 괜찮아. 하지만 우리 알론소는 뭐든 고치는 것보단 부수는 쪽이 더 어울려. 모든 의미에서 말이야. 배 상태가 얼마나 심각해?";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "알론소라면 우리가 침몰하지 않아도 형편없다고 할 거야. 수리를 언급했으니, 시작할까?";
			link.l1 = "그래, 할 수 있는 만큼 해. 하지만 대대적인 장기 작업은 기대하지 마. 내가 마을에서 볼일만 끝나면 곧 닻을 올릴 거니까. 나랑\n " + sStr + " 거기 없을 테니, 무슨 일이 생기면 네가 직접 모든 결정을 내려라. 모든 일에서 알론소의 말을 따르도록 해.";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "명령대로 하겠습니다, 나리 선장님.";
			link.l1 = "편히 있어.";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "안녕하십니까, 나리! 포르토프랭스에 오신 것을 환영합니다.";
			link.l1 = "좋은 하루입니다, 나리. 당신은 누구시고, 이 환대는 무슨 이유입니까? 이 비와 폭풍이 지난 뒤라 긴 대화를 나눌 기분은 아니오.";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "Чанг";
			sld.lastname = "Шин";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "아, 당신의 시간을 많이 빼앗지 않겠습니다, 드 모르 나리.";
			link.l1 = "내가 너를 아는가?";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "오, 아니오, 하지만 이 군도 전체가 당신이 누구인지 다 알고 있습니다. 아, 실례했습니다! 앙리 티보, 당신을 위해 봉사하겠습니다. 저는 무삭 나리의 전령입니다. 그분께서 당신의 배를 발견하자마자, 저에게 가능한 한 가장 따뜻하게 환영하라고 명령하셨습니다, 나리.";
			link.l1 = "음, 이제 많은 게 이해가 되는군. 만나서 반갑소, Thibaut 나리.";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = ""저도 반갑습니다, 드 모르 나리! 저를 따라오시지요. 이런 악취 나는 선술집에 귀하 같은 분과 그의 아름다운 동행이 갇혀 있을 이유가 없지요. 각하께서 도성 안에 집을 마련해 주셨고, 저에게 모든 면에서 도와드리라고 지시하셨습니다. 나중에 푸앵시 각하께도 각하의 안부를 꼭 전해 주시기 바랍니다."\n";
			link.l1 = "사실, 제 용무는 은밀한 일입니다. 있잖습니까, Thibaut 나리, 제 생각에는...";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "Charles. 나는 거의 아무것도 부탁하지 않고, 방해하는 일도 드물지만, 저들의 제안을 받아들일 수 있을까? 비에 젖는 게 지긋지긋해. 게다가 속도 메스껍고 어지러워.";
			link.l1 = "헤헤, 정말 비 때문이라고 확신하나?";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "입 다물어, Charles! 아무튼, 나는 쉬고 싶어. 큰 침대에서, 파도도 없이.";
			link.l1 = "좋아. 우리 몸을 말리고, 잠깐 쉬었다가, 바로 다시 일에 돌아가자.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "이 집에서 좀 쉴 수 있을까? 몸이 좋지 않고, 나도... 피곤해, Charles. 그치?";
			link.l1 = "Mary, 얘야, 이해는 하지만 우리 선술집에 가는 게 어때. 이 모든 게 뭔가 수상쩍지 않아, 그치?";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "나한테 무슨 일이 일어나겠어? 여긴 토르투가조차 아니잖아.";
			link.l1 = "그게 저를 두렵게 합니다.";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "제발? 뭐든지, 내가 방 안에 방어선을 구축할게-그때처럼 말이야, 그치? 누구보다 나를 잘 아는 사람은 너잖아, Charles, 그러니까 내가 할 수 있다는 거 알지.";
			link.l1 = "알겠어, 알겠어. 이번엔 그때처럼 되지 않길 바랄 뿐이야.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "마음이 바뀔 줄 알았소, 나리! 걱정에 대해서는 충분히 이해하오. 하지만 보시다시피, 푸앵시 각하와 총독은 오랜 친구지라, 당신은 우리 마을에서 환영받는 손님이오, 드 모르 나리!";
			link.l1 = "아, 그래... 그럼, 우리를 그 집으로 데려가시오.";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "물론이지요, 나리! 저를 따라오시지요.";
			link.l1 = "감사합니다.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "나리, 총독께서 기다리고 계십니다. 가능한 한 빨리 오시라고 하셨습니다 - 개인적으로 말씀 나누고 싶으시답니다.";
			link.l1 = "그가 이미 알고 있나?";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // флаг для разговора с губернатором
			
			dialog.text = "물론, 그는 알고 있지! 그래서 너를 기다리고 있는 거야. 네 사랑하는 이가 달콤하게 잠들도록 두고, 너는 드 뮈삭 나리에게 가 보라고. 폭풍 따위가 유명한 샤를 드 모르를 막을 수는 없겠지? 하지만 각하께서는 알다시피 약속들 사이에 내줄 시간이 별로 없으시거든...";
			link.l1 = "음, 그건 사실이죠, Thibaut 나리.";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "길을 안내해 드리겠습니다, 선장님.";
			link.l1 = "오, 명예 호위까지 붙었군... 그럼, 앞장서 보시지.";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "나리 선장님!";
			link.l1 = "롱웨이! 배로! 지금 당장!";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "하지만 나는 창싱을 봤어!";
			link.l1 = "뭐라고?! 어디서? 언제? 그녀가 네 배에 있나?";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "안 돼! 여기 도시에서 롱웨이가 멀리서 그녀를 봤어. 따라잡을 시간이 없어 - 그녀가 막 출항한 갈레온에 승선하고 있어!\n";
			link.l1 = "우리가 갤리온을 따라잡을 거야! 그런데 말해 봐 - 본 적 있어? " + sStr + " 어디든?";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "안 돼! 무슨 일이라도 있었어?";
			link.l1 = "그래, 뭔가 일이 생겼어! 그녀가 위험해! 레바쇠르의 조카를 봤나? 이름은 앙리 티보! 성질 더럽고, 깡마르고, 머리 길고, 우스꽝스러운 콧수염 달린 젊은이야!\n";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "(만다린어로) 웃긴 콧수염 얘기는 필요 없소, 선장님...\n(서툰 프랑스어로) 나 그 사람 봤소! 그와 용병들도 같은 갈레온에 탔소.";
			link.l1 = "즉시 추격합시다!";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "배가 심하게 망가졌습니다, 나리 선장님!";
			link.l1 = "난 신경 안 써! " + sStr + "의 목숨이 위태로워!";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "내... '당신의 메이펑'이 우리를 이끌 거예요!";
				link.l1 = "아, 그녀는 분명히 올 거야! 서둘러!";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "우리를 자살 공격에 내몰지 마십시오. 전에 저에게 주신 그 배를 사용하십시오!";
				link.l1 = "좋은 생각이야, 롱웨이! 서두르자!";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			AddDialogExitQuestFunction("PZ_Longway_78");
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "또 너냐... 거절하고 네 여자를 다른 놈한테 넘겼어야 했는데, 그랬어야 했어.";
			link.l1 = "그 여자는 어디 있지?! 말해! 아니... 입 다물어. 네놈은 밧줄에 묶여 창고 안에서만 말하게 될 거다! 들리나?!";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "...";
			link.l1 = "그녀의 칼이다. 지금 당장 노래하지 않으면, 내가 그 칼로 널 산산조각낼 거야.";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "너... 너 완전히 미친 거 아니야!..";
			link.l1 = "이제 내 불쾌한 면을 보게 될 거요...";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "그게 다야?";
			link.l1 = "다시 묻겠소! 어디에 있지 " + sStr + "?! 중국 여자는 어디 있지?! 앙리 티보는 어디 있지?!";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "(피를 뱉으며) 네 주먹, 여자애처럼 약하군.";
			link.l1 = "이년아! 네 입에서 나오는 말 하나하나 전부 두들겨 패서 뽑아내주마!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "한심하군. 그래도... 말해주지. 왜 안 되겠어, 하하. 다들 다른 배에 있어. 토르투가로 가는 길이지. 이미 늦었어.";
			link.l1 = "그녀 머리카락 한 올이라도 떨어진다면...";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 1.00, 5.13, 7.23);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "그게 누구 잘못인데?! 네가 에드가르도 소타를 죽였잖아! 르바쇠르가 평생 처음으로 여자를 탐냈는데, 바로 손에 넣지 못했지! 우리 선원들이 그의 직접 명령을 처음으로 어긴 거야! 그 자는 악마만큼이나 무서울 수 있어...\n";
			link.l1 = "그럼 내가 악마보다 더 무서워져서, 내가 알고 싶은 걸 말하지 않으면 너한테 개인 지옥을 보여줄 거야, 알겠어?!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			else link.l1.go = "PZ_RobertMartin_Helena_1";
			//if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "네 슬픔 따위엔 관심 없어 – 어차피 난 죽은 목숨이니까, 네 미친 눈빛을 보니 알겠군. 그래도 한 가지는 인정하지, 드 모르.";
			link.l1 = "무슨 헛소리를 하는 거야?";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "르바쇠르는 금발을 좋아하지. 하지만 나는 언제나 빨간 머리가 더 좋았어, 바로 너처럼 말이야, 헤헤헤... 아주 매운 맛이네, 네 여자는!";
			link.l1 = "맞아, 오늘 하루도 못 넘길 거야...";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "나는 네가 뭘 원하는지 전혀 신경 안 써. 하지만 레바쇠르가 뭘 원하는지는 알려주지. 예쁜 금발 아가씨들, 하하하하하하하하! 먼저, 그자가 그녀를 가졌지...";
			link.l1 = "아-악!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "비명을 지르며 맨손인 남자를 두들겨 패는 것뿐이군. 한심하군. 그게 네가 할 수 있는 전부지. 넌 졌어, 드 모르! 네가 진짜로 진 순간이 언제인지 알고 싶나, 이 한심한 놈아?\n";
			link.l1 = "깨우쳐 봐라. 하지만 내가 감탄하지 않으면, 네 손가락 하나를 잃게 될 거다. 아니면 귀, 아니면 그 썩은 이빨을 그 더러운 입에서 뽑아낼 수도 있지. 아니면 또 다른 뭔가일지도. 선택은 네 몫이다...";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 0.66, 5.00, 8.26);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "헤헤, 난 네가 모르는 걸 가지고 있지. 네가 레바쇠르가 그 늙은 여우 푸앵시가 자기한테 무슨 음모를 꾸미는지 몰랐을 거라고 생각하냐? 프랑수아는 다 알아, 전부 다! 심지어 형제단의 대귀족들도 그에게 감히 맞서지 못하지. 그런데 너, 똑똑한 척하는 놈이 감히 덤볐군. 하지만...\n";
			link.l1 = "뭐라고?! 이 지랄 더 끌 생각 마!! 당장 말해, 아니면 네 손가락 하나씩 부러뜨릴 거야!";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "하하, 용감한 드 모르 선장! 뭐, 좋아. 나랑 앙리, 그리고 그 노란 피부 여자가 여기서 널 없애기로 했지. 그리고 타이렉스 탓으로 돌려서, 브라더후드의 늙은 바보들이 또 서로 전쟁을 벌이게 만들 생각이었어! 아니면 드 뮈삭일 수도 있지—그 자식은 남의 일에 참견하기 바쁘니까... 다들 내가 갤리온을 몰고 다닌다고 비웃었지만, 네 고물배랑 달리 내 배는 폭풍도 거뜬히 견뎠지.";
			link.l1 = "그만! 레바쇠르는 희생자들을 어디에 가두는가?";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "그래서 그의 비밀 장소, 지하 감옥에 대해 아는군? 아, 그래, 그는 진짜 던전 마스터지, 하하하! 하지만 정말로 그에게 도전할 수 있겠어? 난 의심스럽군. 그 괴물을 쓰러뜨리고 싶다고? 그럼 네가 직접 괴물이 되어 봐. 프랑수아가 그 여자애들을 부수듯이, 네가 날 부술 수 있는지 보자. 곧 네 여자도 그렇게 부서질 테니까...\n";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "알로오온소오!!!";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "귀찮게 하지 말라고 했잖아, 젠장!..";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "허락해 주십시오, 나리 선장님.";
			link.l1 = "롱웨이? 무엇을 허락하라는 거지?";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "백인들은 육체를 고문하지. 내 부족은 먼저 비참한 영혼을 괴롭혀야 한다는 걸 안다네, 조금씩, 끊임없는 고통으로 미치게 만들어야 하지. 그냥 덥석 잡아서 고문하는 건 안 되네. 언제나 특별한 방식이 필요하지. 여기선... 린치가 필요하다네.";
			link.l1 = "린치?";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "예, 나리 선장님. 천 번 베어 죽이는 형벌이지요.";
			link.l1 = "미쳤어?! 머리라도 다친 거야? 무슨 죽음 타령이야?! 먼저 저놈 입을 열게 해야 해!";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "롱웨이는 알고 있소, 나리 선장. 무엇을 해야 하는지 알고 있소. 이 개자식이 내게 전부 말하게 될 거요. 시간만 주시오...";
			link.l1 = "시간? 시간?! 좋아... 해. 제발, 부탁이야, 그놈한테서 전부 다 뽑아내 줘, 전부 다!";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_LongwayKazn_3_1", -1);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "날 죽여, 그냥 죽여 줘, 제발... 더 뭘 바라는 거야?!";
			link.l1 = "더 이상 할 말 없어. 입 다물고 죽어.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "깔끔한 사격이었소, 나의 로드 캡틴. 내가 된다고 했지 않았소.";
			link.l1 = "그래. 잘했어. 그럼 이제 지하 감옥으로 가자. 모든 돛을 올려라! 토르투가로 향한다. 그리고 만약 내 머리카락 한 올이라도 다치면, 이 피투성이 도시엔 신의 자비도 없을 거다. " + sStr + " 머리...";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			AddQuestRecord("PZ", "39");
			pchar.questTemp.PZ_FlagMartinInfo = true;
			AddDialogExitQuestFunction("PZ_FinalKaznOnShip_DlgExit");
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "세상에... 그런 모습이나 목소리는 처음 봤고 들었소, 선장 나리.";
			link.l1 = "알론소, 이제 네 차례다! 어서 해봐, 성스러운 종교재판이 위그노와 그 졸개들에게 어떻게 하는지 보여줘... 나는 지켜볼 테니... 그 다음엔 네 마음대로 해도 돼.";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "알겠소, 선장 나리...";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "오래 걸리지 않을 겁니다, 선장 나리...";
			link.l1 = "제발, 하시오!";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			//LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "일어나, 이 쓰레기 같은 놈아. 일어나라고 했잖아!";
			link.l1 = "죽었습니까? 죽었다고요?!";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "그런 것 같아, 선장...";
			link.l1 = "도대체 무슨 짓을 한 거야?!";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "이 멍청이가 이렇게 약골일 줄 누가 알았겠어! 바지에 오줌까지 쌌다니까, 더러운 놈! 젠장, 불까지 피울 필요도 없었잖아...";
			link.l1 = "너… 좋아, 저 놈은 물고기 밥으로 던져버려. 토르투가로 항로를 잡아. 필요하다면 저곳을 벽돌 하나하나 뜯어낼 거야—먼저 라 로슈, 그리고… 그리고 만약 내가 그녀를 살아서 못 찾는다면, 신이시여, 나를 도와주소서…";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			AddQuestRecord("PZ", "38");
			AddDialogExitQuestFunction("PZ_FinalKaznOnShip_DlgExit");
		break;
		
		case "PZ_Norman1":
			dialog.text = "드디어. 이제 이 왕좌는 내 것이다. 이 바위 위에 나는 세울 것이다...";
			link.l1 = "이게 대체 뭐야... 진짜로?";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Shark";
			
			dialog.text = "... 내 교회다. 나는 이제 로마의 교황이다. 하나님의 집에서 맹세하지 마라!";
			link.l1 = "그리고 저는 이렇게 생각했는데... 자, 성하, 충실한 신도에게 어디에 있는지 말씀해 주시겠습니까\n "+ sTemp +" 지금인가?";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "그는 신성한 사명을 수행하러 떠났어. 새로운 십자군 전쟁이라고 해도 되겠지. 악인들에게서 돈을 빼앗아 내게 가져올 거야.";
			link.l1 = "당신에게, 맞지. 언제 돌아온다고 했어?";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "한 달 후쯤. 어쩌면 조금 더 늦을 수도 있지. 나는 우리 무리의 다른 이들과 함께 그의 귀환을 기다리고 있어.";
			link.l1 = "그래서 정말로 바다에 있군. 네가 걸린 그 무언가가 옮기기 전에 떠나는 게 좋겠어.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "나는 그들 모두를 성스러운 불길로 정화할 것이다...";
			link.l1 = "네 머리는 좀 정화가 필요하겠군...";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// ох, какой же костыль, м-м-мать...
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "with Marcus";
					else sTemp = "with Steve";
					
					dialog.text = "찰스! 무엇을 도와드릴까요?";
					link.l1 = "안녕, 헬렌! 나 할 말이 있어 "+ sTemp +". 위층에 있습니까? 아니면 선술집에 있습니까?";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
					else sTemp = "Steve";
					
					dialog.text = "찰스! 그리고... 아, 정말 반가운 손님이군요. 두 분께 무엇을 도와드릴까요?";
					link.l1 = "안녕, 헬렌. 어디에 "+ sTemp +"?";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
				else sTemp = "Shark";
				
				dialog.text = TimeGreeting() + ", Charles. 무슨 일로 여기 오셨습니까?";
				link.l1 = TimeGreeting() + ", 헬렌. 나는 찾고 있어 "+ sTemp +". 그가 어디 있는지 아십니까?";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "그는 나가셨는데, 오래도록 돌아오지 않을 것 같아요\n정확히 말하면 바다로 나가셨거든요.";
			link.l1 = "젠장. 무슨 일이라도 있었나? 언제 돌아온다고 했어?";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "그가 그러진 않았지만, 별일은 아니야 – 평소처럼 좋은 단서를 잡았거든. 보통 한 달, 길어도 두 달이면 돌아와. 나도 알아, 가끔은 나 역시 배 갑판이 그리워지니까...\n";
			link.l1 = "언제든 바다로 나갈 수 있어. 언젠가 같이 하면 좋을 텐데 - 너는 '레인보우'호에서, 나는...\n";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "그럴 수도 있겠지. 하지만 네... 여자친구가 달가워하지 않을 거야. 그리고 나는 들러리가 되고 싶지 않아.";
			link.l1 = "에헴, 미안해, 헬렌. 기분 상하게 하려던 건 아니었어. 이야기 나눠줘서 고마워. 나중에 보자.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steve";
			
			dialog.text = "Charles, 돌아오셨군요. 또 도와드릴 일이 있습니까?";
			link.l1 = "아니요, 고마워요, 헬렌. 그냥 확인하고 싶었어요\n "+ sTemp +" 나타났어.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			else sTemp = "Steven";
			
			dialog.text = "저를 찾으러 오셨다면 놀랄 일이군요. 그리고\n "+ sTemp +", 그는 바다에 나가 있어.";
			link.l1 = "오, 정말이야? 언제 돌아온다고 했어?";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "분명히 저 자는 이 오물통을 운영하는 데 지쳐서, 자기가 아직도 배의 선장이라는 걸 스스로 상기해야 하나 봐. 처음 있는 일도 아니야. 보통 한 달, 길면 한 달 반쯤 지나서 돌아오지.";
			link.l1 = "젠장, 그 남작들이 항상 그렇게 가만히 있는 건 아니었군? 고마워, 헬렌. 잘 가.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steven";
			
			dialog.text = ""+ sTemp +"아직 돌아오지 않았어, Charles";
			link.l1 = "알겠소, 그냥 확인해 본 거요.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "그는 자유인이지, 그렇지 않아? 원하면 언제든 바다로 나갈 수 있잖아.";
			link.l1 = "물론 할 수 있지. 그래서, 그는 어디에 있지?";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "the Shark";
			
			dialog.text = "하지만 Charles, 그가 섬에 없다면 스페인 놈들을 약탈하러 간 게 분명하군. 이제, 실례하겠소, 할 일이 많으니. 가끔 들르시오 - 보통, the "+ sTemp +" 한 달쯤 후에 돌아오는데, 가끔은 좀 더 늦기도 합니다.";
			link.l1 = "좋아, 헬렌, 고마워. 우리는 계속 바쁠 거야.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "지금은 기분이 아니야. 나중에 다시 오는 게 어때, Charles?";
			link.l1 = "알겠어, 헬렌. 귀찮게 해서 미안해. 몸조심해.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "우리는 자리에 있습니다, 나리 선장님. 길을 기억하십니까?";
				link.l1 = "물론이지, 롱웨이. 저주받은 지하감옥에서 그걸 잃어버리지 않기만을 바라자고...\n";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "우리는 자리에 있습니다, 나리 선장. 계획이 있으십니까?";
				link.l1 = "아직 작업 중이야... 왜, 뭔가 생각난 거라도 있어?";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//На 6 эпизод даём Лонгвею бессмертие
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "글쎄, 우리가 장싱으로 서두르면...";
			link.l1 = "롱웨이... 네가 얼마나 누이를 보고 싶어하는지 이해하지만\n " + sStr + " 지금 그녀는 진짜로 목숨이 위태로워, 이건 비유가 아니야! 네가 알아야 할 건, 그녀를 구하는 게 최우선이라는 거야!";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "나리 선장, 당신이 내가 지난 10년 동안 겪어온 일들을 정말로 이해한다고는 의심스럽소. 내가 지금 겪고 있는 고통도 마찬가지요.";
			link.l1 = "있잖아, 어떻게 보면 맞아. 내 오빠가 감옥에 갇혀 있어. 아직까지는 해를 입히지 않았지만, 언제든지 그들이 원하는 대로 할 수 있어.";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "하지만 만약 그분이 혼자라면 어디로 가겠습니까 " + sStr + " 누가 구출이 필요했지?";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "한 군데가 있어... 한 사람이 있어... 하지만 그 일로 신경 쓰지 마, 롱웨이 - 그건 내가 직접 처리해야 해.";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "사실, 어디로 가야 할지조차 모르겠어. 함부로 여기저기 기웃거리다간 눈에 띄게 되고, 그러면\n " + sStr + " 확실히 끝장났어. 그래서... 나도 잘 모르겠어.";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "뭐? 왜?";
			link.l1 = "거긴 아무나 들여보내 주지 않아. 상류층 모임이란 말이야, 젠장. 그러니 내가 혼자 들어갈게. 그동안 넌 네 여동생한테 가. 최대한 빨리 합류할게. 행운을 빌어, 롱웨이!";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "예! 고맙습니다, 나리 선장님. 당신께도 행운이 있기를!";
			link.l1 = "아, 고마워요 - 오늘은 정말 필요했어요. 우리 모두 그렇죠.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "나리 선장님...";
			link.l1 = "신경 쓰지 마. 롱웨이, 네 여동생에게 가자. 지금 흩어지면 우리 둘 다 죽는다. 서둘러 네 여동생에게 가서 르바쇠의 소굴이 어디인지 알아보자. 그 다음엔 다시 함께 움직이자. 지금은 네 도움이 절실하다. 너무 늦지 않았길 바란다.";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "늦지 않을 것입니다, 나리 선장. 더 이상 지체하거나 말다툼으로 시간을 낭비하지 맙시다. 창싱으로 갑시다!";
			link.l1 = "맞아요, 서두르죠.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "도대체 어디로 가는 거야? 저 문이 어디로 통하는지나 알고 있는 거냐?";
			link.l1 = "나는 아주 잘 알고 있소. 나는 심심풀이로 가는 것도, 훔치러 가는 것도 아니고, 볼일이 있어서 그리로 가는 것이오.";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "무슨 용건이오? 레바쇠르 부인은 지금 자리에 없소. 게다가, 그분은 유부녀요. 아무나 그 집 근처를 어슬렁거리는 건 옳지 않소.";
			link.l1 = "결혼했지, 그치? 그래도 가끔씩 연회도 열잖아? 사적인 연회도 포함해서 말이야. 지금이 딱 그런 때거든. 그녀가 나를 기다리고 있어, 나 지금 급하다고.";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "그랬다면 그녀가 나에게 경고했을 거야.";
			link.l1 = "나는 특별한 손님이지 - 알릴 필요 없는 그런 종류 말이야.";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "예, 그분께서 나를 총살하라고 명령하실 만한 손님이지. 아니면 그 여인께서 직접 내 가죽을 벗기실지도 모르고.";
			link.l1 = "나는 마르셀린 부인 댁에 전에 묵은 적이 있소. 걱정 마시오, 병사. 그 후로 아무 일도 일어나지 않을 것이오.";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "하지만 물론이지, 눈 감고 아무나 들여보내는 게 바로 도시 경비대의 일이니까.";
			link.l1 = "이딴 데 신경 쓸 시간 없어, 이 고집 센 놈아...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "너...";
			// начинаем проверять результат прохождения "Почти как дома"
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// поделили алмазы и "охладили трахание, углепластики" (с)
				case "Fuck":
					link.l1 = "아, 네, 부인. 당신의 기사, 다시 만나 뵙게 되어 기쁩니다. 저를 보고 놀라신 것 같군요. 이 만남의 기쁨이... 서로 같지는 않은가요?";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// поделили алмазы, без трахания и углепластиков
				case "NoFuck":
					link.l1 = "네, 맞아요. 지난번에 말씀하신 대로 제가 이 섬에서 가장 잘생기거나 훌륭한 남자는 아닐지 몰라도, 적어도 정직한 사람이라는 건 아시잖아요. 제 말 좀 들어보세요, 부인. 오래 걸리진 않을 겁니다... 귀중한 시간을 많이 뺏지 않겠습니다.";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "сошлись вот где-то посередине" (с)
				case "Deception":
					link.l1 = "제발 조용히 하시오, 부인. 그 소리 좀 그만 지르시오. 나는 당신이 기사님을 속이고 용의 보물을 훔쳐 달아난 것에 대해 복수하러 온 게 아니오. 그리고 분명히 말하지만, 내가 당신을 죽이고 싶었다면 그냥 총을 쏘고 도망쳤을 것이오. 여기는 토르투가니까! 하지만 당신도 이미 내가 그런 짓을 할 사람이 아니라는 걸 알고 있겠지.";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "아, 이런! 그냥... 아니, 아무것도 아니에요! 있잖아요, 나쁜 사람들이 저에 대해 더러운 소문을 퍼뜨리고 있어요. 저는 불쌍한 여자일 뿐이고, 누군가를 해칠 수도, 적에게서 스스로를 지킬 수도 없어요. 게다가, 그 일도 너무 오래됐고요... 당신이 나쁜 마음으로 저를 찾아온 줄 알았어요. 좋은 뜻이 아니라서요. 제가 틀려서 다행이에요. 주위에 악의적인 사람들이 가득하니, 정말 살기 힘들어요.";
			link.l1 = "어떻게 내가 그럴 수 있겠어? 그런 얘기를 들었다 해도 한 마디도 믿지 않았을 거야. 하지만 네 말이 맞아 - 널 보기 위해서만 여기 온 건 아니야. 그래도 이렇게 만나서 기뻐. 좀 이상하게 들릴지 모르지만... 이번에는 네 기사가 네 도움이 필요해, 부인.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "그리고 당신이 생각보다 훨씬 더 예민하군요. 하지만 당신도 결점이 없는 건 아니에요, 드 모르 나리 - 저는 당신이 좀 더... 세련됐을 거라 기대했어요. 사실... 원래부터 이랬던 건지, 아니면 이 군도가 이미 당신을 타락시킨 건지 모르겠네요. 숙녀에게 말하는 법을 다시 배워야겠어요. 하지만 당신 말이 맞아요 - 당신은 정직한 사람이에요, 다만... 단순하죠.";
			link.l1 = "그리고 당신은 자존심 강하고 앙심 깊은 여자요. 당신의 눈빛, 말, 그리고... 행동이 그걸 다 드러내지. 그러니 나를 이해할 수 있는 사람이 있다면, 바로 당신이오. 내가 한때 당신을 이해했던 것처럼. 그러니 더 이상 과거에 머물지 맙시다. 도와줄 수 있겠소, 부인?\n";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "오... 그때 내가 당신에게 불친절했던 건 인정해요. 하지만 그건 내가 당신을 완전히 믿지 못해서였을 뿐, 다른 이유는 없었어요! 당신이 내게서 다이아몬드를 모두 빼앗아 갈 수도 있었잖아요? 아니면 하인들에게서 내가 남편 것을 훔쳤다는 걸 들었다며 남편을 데려올 수도 있었고, 당신이 그 일에 관여하지 않았다고 부인할 수도 있었죠? 결국 모두가 그의 환심을 사려고 하지, 저 같은 가난한 여자를 신경 쓰는 사람은 없으니까요... 이제야 내가 당신을 오해했다는 걸 알았어요. 제 사과를 받아주세요... 나의 기사님.";
			link.l1 = "지금 그들이 진심인지 아닌지 모르겠습니다. 하지만 상관없습니다. 당신의 도움이 필요합니다, 마르셀린 부인. 이것은 생사가 걸린 문제입니다. 제발 거절하지 마십시오.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "제 도움이요...? 제가 이 마을의 마지막 여자가 아닌 건 분명하지만, 여러분이 생각하는 것만큼 영향력이 크진 않아요. 저는 다스리는 여왕이지, 통치하는 여왕은 아니에요. 하지만 말씀은 들어드릴게요. 제 미천한 존재가 무엇을 도와드릴 수 있을까요?";
			link.l1 = "이런 말씀 드리기 불편하신 거 압니다만, 부인, 저는 당신 남편을 찾고 있습니다. 가능한 한 빨리요. 사실은...";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "이게 농담이오? 그가 지금 관저에 없다고? 그럼 업무 때문에 나가 있는 거겠지. 나는 도와줄 수 없소, 드 모르 나리.";
			link.l1 = "당신은 시선을 돌렸지. 당신도 알고 있어. 나도 알아. 나는 그저 거기에 가야만 해. 제발 이 지하 감옥 이야기를 처음 듣는 척하지 마. 당신이 모를 만큼 어리석진 않으니까.";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "아, 이 대화 때문에 내 머리에 흰머리가 하나 더 늘 것 같아. 이미 첫 주름도 충분한데 말이야. 도대체 우리 모두에게 무슨 짓을 하고 있는 거야, 프랑수아...\n";
			link.l1 = "회색 머리카락 한 올쯤은 당신의 고귀함을 더해줄 뿐, 아름다움을 빼앗지 않아요. 하지만 착하고 순진한 아가씨가 당신 남편 손에 넘어갔어요. 이제 그녀는 아름다움도, 건강도, 심지어 목숨까지 잃을 위험에 처했어요!...! 그곳에 갇힌 자들이 어떻게 되는지 당신도 잘 아시잖아요. 제발 부탁드립니다, 부인. 마르셀린... 당신의 기사에게 힘을 주세요.";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "이젠 내 기사도 아니잖아, 그치? 됐어, 나 바보 아니야. 하지만... 도와줄게, 드 모르. 어차피 이 일은 영원히 계속될 수 없었어. 언젠가는 세상에 드러났을 거고. 지금 내게 중요한 건, 제때에, 제대로 빠져나가는 거야. 그리고... 내 ‘남편’이 네... 지인에게 저지를 짓 때문에 너를 영원한 고통에 빠뜨릴 순 없어.";
			link.l1 = "이제 나는 더 이상 당신의 기사일 수 없소, 부인. 하지만 당신도 처음부터 내 여인이었던 적은 없었소. 그럼에도 불구하고, 나는 평생 당신께 감사할 것이오. 그런데 여기가 어디요?";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "좋아, 네 말을 믿겠네, Charles. 도시 지하감옥에 있네. 막다른 골목 중 하나에 큰 통이 있고, 그 옆에서 이 괴물의 소굴로 이어지는 통로가 시작되지. 나는 안을 들여다보지 않았네. 아주 오래전에 단 한 번 그를 따라갔을 뿐이야. 그리고 그 불쌍한 존재들의 인간 같지 않은 비명을 들었을 때, 나는 두려움에 사로잡혔지.";
			link.l1 = "오늘 많은 생명을 구하셨습니다, 부인. 제 소중한 사람뿐만 아니라 앞으로 당신 남편에게 희생될 수도 있었던 모든 이들까지도요. 감사합니다.";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "아, 이런 공허한 말은 그만두시오, 나리. 당신은 내게 너무 많은 것을 요구했소. 그리고 나는 큰 위험을 감수했소. 이제 당신의 새로운 용의 소굴로 가는 모험을 반드시 성공시키시오... 나의 기사여.";
			link.l1 = "최선을 다하겠습니다. 안녕히 계세요, Marceline.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "그래서, 당신은 도둑인가요, 나리...? 우리는 이런 식으로 새 여자를 들이지 않아요; 우리 모두 자발적으로 여기 온 사람들이에요.\n당신과 당신의... 공범은 나가 주셔야겠어요. 그리고 이 아가씨는 내가 치료받게 할 거예요 - 그렇지 않으면, 당신을 당국에 신고할 겁니다!";
				link.l1 = "우리는 산적이 아니오. 하지만 이 아가씨는 그 누구와도 맞설 수 있소. 허세로 칼을 차고 다니는 게 아니오. 그녀는 다쳤을 뿐이오. 이 사람은 내 친구이자 당신 주인 아가씨의 오라버니이기도 하오. 그러니, 그녀를 만나게 해주시오.";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "다시 뵙게 되어 반갑습니다, 나리! 하지만 아시다시피 저희는 여기서... 천한 손님은 받지 않습니다. 보증을 받았고 돈을 냈다 해도 마찬가지입니다. 특히 누런 피부의 일꾼이나 흑인 노예는 더더욱 안 됩니다. 유감이지만, 당신 친구분은 나가셔야 하겠습니다.";
				link.l1 = "네 주인 앞에서 그런 말 하지 마라. 저 여자도 누런 피부잖아. 그리고 이 사람은 일꾼이 아니라 그녀의 오빠다. 가족 상봉에 끼어들 생각은 아니겠지?";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "시간이 갈수록 점점 더 악화되고 있소. 처음엔 미친 노란 노동자, 이제는 당신까지. 아니오, 나리, 우리는 강제로 끌려온 여자들에게 돈을 주지 않소; 여기 있는 이들은 모두 자발적으로 온 사람들이오.";
				link.l1 = "이 소녀를 내가 구했으니, 이제는 자기 격에 맞지 않는 곳에서 일하게 두지 않을 거야. 노동자라니, 그게 무슨 말이지?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "오, 나리, 정말 때가 안 좋군요! 오늘은 더 이상 손님을 받지 않습니다 - 여기서 무슨 일이 일어났는지 직접 보실 수 있을 겁니다.";
				link.l1 = "그래서 내가 여기 있는 거요. 이 모든 걸 꾸민 건 노란 피부를 가진 사내였지, 그렇소?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "네, 나리, 노동자였습니다! 무슨 말을 하는지 거의 알아들을 수 없었어요! 그 거지꼴 사내가 들이닥쳐서 아가씨를 만나게 해달라고 요구했죠. 자기 말로는 그녀의 오빠라고 하더군요. 우리가 사람들을 불렀지만...\n";
			link.l1 = "그에게는 아무런 장애가 아니지. 그다음엔 어떻게 됐지?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "알고 보니, 그는 거짓말을 하지 않았어. 그 여인이 우리에게 나와서 그를 알아봤지. 사실, 그들은 아직도 그녀의 호화로운 방에서 이야기를 나누고 있어.";
			link.l1 = "그 자 머릿속에 뭐가 들어 있는지는 아무도 모르지. 그래도 우린 저 안으로 들어간다 - 필요하다면 그녀를 구해낼 거야. 소란 피우지 마라 - 이곳 명성만 망칠 테니까.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "맞습니다, 나리. 그가 그 숙녀의 오빠라고 했습니다.";
			link.l1 = "그리고 그를 들여보내지 않았군...";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "당연히 아니지! 그 숙녀는 아주 고운 옷차림에 말투에도 사투리가 없었어, 저 노동자와는 달랐지. 우리가 그를 쫓아내려 했더니, 그 자가 경비병들을 모조리 쓰러뜨렸어, 상상이 가?";
			link.l1 = "쉽게 상상할 수 있지. 그런데 지금 그는 어디에 있지?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "그와 그 여인은 아직도 뭔가를 이야기하고 있는데, 우리가 무슨 말인지 알아들을 수 없어. 아마 자기들만의 언어로 말하는 것 같아.";
			link.l1 = "내가 그들에게 가겠소. 아마도 당신의 부인께서 도움이 필요할지도 모르지. 경비병은 부르지 마시오 - 이 일이 퍼지면, 다시는 아무도 당신 집 문을 두드리지 않을 것이오.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "오라비? 그 아가씨는 품위가 있지만, 그 ‘오라비’라는 자는 그런 말조차 아깝지. 저 하층민으로 아가씨를 혼란스럽게 하거나 속이려 들 필요 없어. 저 자를 데리고 나가라.";
			link.l1 = "나는 그들이 오래전에 서로를 잃었다고 말했잖아. 그는 그냥 더 불운할 뿐이야. 우리는 우리 시간을 위해 직접 업소에 돈을 낼 거야. 지금 바로 여주인에게 알려.";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = "그 여자에게 네가 경계할 만한 이유는 없다. 그리고 나는 네 끈질김이 마음에 들지 않는다. 얘들아! 저 일꾼을 내쫓아라! 그리고 그 잘못된 주인도 함께!";
			link.l1 = "젠장! 창녀 주제에 이렇게 오만하다니!";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "말도 안 돼! 당신 일행 같은 수상한 사람들 틈에 아가씨를 혼자 두라고? 당신 혼자 들어간다면 모를까, 나리. 그리고 당신... 친구들은 밖에서 기다리게 하시오 - 여긴 체면을 중시하는 곳이니까.";
			link.l1 = "왜 그녀를 걱정하는 거야? 모두가 그녀가 토르투가에서 손꼽히는 검객 중 한 명이라는 걸 알잖아.\n그리고 내 친구들은 이 마을 사람들보다 훨씬 더 괜찮은 사람들이야.";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "얘들아! 여기 부상당한 산적이랑 더러운 일꾼이 있어! 우리 여주인님께 뭔가를 원한대! 처리해!";
			link.l1 = "이 무슨 집념이람, 젠장...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// итак, снова проверка по результатам прохождения. Лонгвэй с нами, тян ещё в пыточной
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "당신이 샤를 드 모르지요? 그리고 이분은... 오.";
				link.l1 = "그리고 당신이 바로 벨 에투알이군요. 아니면 창싱이라고 불러야 할까요? 그리고 그래요, 이 사람이 바로 당신의 오빠예요. 그는 십 년이 넘도록 당신을 찾아 헤맸죠. 그와 나는 당신에게 묻고 싶은 것이 아주, 아주 많아요. 그리고 시간이 많지 않아요.";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// пришли с Лонгвэем и тян
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "이런, 살아남으셨군요. 방어자가 꽤 괜찮네요, 비록 조금 늦긴 했지만요. 지금 당신 옆에 서 있으면서 자신을 내 보호자라고 여기는 사람보단 훨씬 낫죠. 하늘이 당신을 돌보는군요, 사랑스러운 아가씨.";
				link.l1 = "이미 알고 있다는 게 보이네. 그거면 더 좋아, 설명할 필요 없으니까. 그런데 말해 봐, 창싱, 뭐가 그렇게 웃긴 거지? 다른 여자들이 고통받는 걸 보는 게 즐겁나? 어차피 네가 그들을 팔잖아.";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// Лонгвэй с нами, тян на небесах
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
				dialog.text = "샤를 드 모르, 맞지? 나를 찾는다고 들었어. 그래서, 무슨 일로 왔나? 지난번에 우리 집에서 받은 서비스가 마음에 안 들었나?";
				link.l1 = "방금 당신의 또 다른 가게에서 왔소, Chang Xing. "+ sStr +", 내 연인은 죽었어. 그리고 당신도 그 일에 한몫했다는 걸 알아.";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "창싱... 그 이름을 들은 지 오래됐지. 정말 오랜만이야. 백인들... 너희는 항상 급하더라. 가족 상봉도 좀 느긋하게 하면 어때? 뭐, 난 상관없어. 남에게 기대는 건 오래전에 그만뒀으니까. 왜 아무 말도 안 해, 내 오라버니? 네 친여동생을 만나서 기쁘지 않아? 그렇게 집요하게 나를 찾아다녔으면서.";
			link.l1 = "우리에겐 더 급하고 중요한 일이 있다. 네 여동생과 이야기해, 롱웨이. 하지만 우리가 아직 가야 할 곳을 잊지 마라. 서둘러야 해. 그리고 나도 그녀에게 물어볼 게 있다.";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "(만다린어로) 롱웨이, 그렇지? 이름 빼고는 별로 변한 게 없구나... 창 투.";
			link.l1 = "(만다린어로) 하지만 많이 변했구나, 누이야. 무슨 일이 있었던 거지? 네 눈빛은 한때 한낮의 태양처럼 따스했는데, 지금은 차갑고 멸시밖에 담지 않았어. 그리고 네 목소리는? 네가 웃을 때 그 은방울 소리를 듣는 걸 정말 좋아했었지... 그런데 이제는 겨울의 고앙고보다 더 차가워. 그리고 그놈들의 옷을 입고 있구나. 네가 한때 페르멘텔로스에게 납치당했던 사람이면서, 이제는 네 손으로 여자들을 팔고 있어.";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "너는 나를 훈계하러 온 거냐? 예전에 군도에서 제일 악질인 로덴부르크 밑에서 일했던 주제에? 내가 너에 대해 몰랐을 거라 생각했나? 나는 항상 알고 있었다. 내가 왜, 어떻게 변했는지 네가 판단할 일이 아니야, 착각에 빠진 내 형제여.";
			link.l1 = "그러니까 내가 알아보게 해 줘, Xing! 그리고 나에게 말해 줘. 네가 내가 군도에 있다는 걸 알았다면, 왜 이 많은 세월이 지나도록 나를 만나고 싶어하지 않았던 거지? 나는 너를 찾는 데 내 평생을 바쳤는데...";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "왜냐하면 당신도, 하늘도 나를 가장 끔찍한 운명에서 지켜주지 않았으니까. 그때 깨달았지. 이 세상에서 누구도 누구를 필요로 하지 않아. 우리는 오직 자기 자신만 믿을 수 있을 뿐이야. 좋아, 알고 싶다면 말해주지. 하지만 그의 언어로 말할 거야. 그도 듣고 싶어할 테니까. 프랑스어 이해하지? 투, 너도?";
			link.l1 = "(엉터리 프랑스어로): 응, 그 말 할 줄 알아.";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "하하하, 오, 하늘이시여! 당신 발음 정말 끔찍하군요. 하지만 그건 당신 잘못이 아니에요 - 프랑스어 발음과 글쓰기는 정말 어렵거든요.";
			link.l1 = "이제는 웃는 소리도 달라졌구나, 누이여...";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			ReturnOfficer_Longway();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "내 사랑하는 오빠가 내가 그동안 어떻게 지냈는지 알고 싶어 하네. 너도 듣는 게 좋을 거야 – 네가 말했듯이 궁금한 게 있다면서. 그러니 걱정하지 마 – 프랑스어로 전부 이야기해 줄게.";
			link.l1 = "요점만 말해 줘. 롱웨이가 자기 인생 이야기를 해줬을 때 몇 시간이나 걸렸거든. 그리고 난 지금 급하니까.";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "참을성 있게 기다리시오. 나는 이 모든 걸 1년 넘게 혼자 감췄소. 그리고 방해하면, 그 어떤 질문에도 대답하지 않을 것이오.";
			link.l1 = "좋아... 그럼 계속해.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "예의는 어디에 두고 왔나, Charles de Maure? 자네가 예의 바르기로 소문난 신사요, 여인들의 모범이라 들었는데. 그냥 소문이었나? 실제로는... 형편없군? 내가 그럴 줄 알았지. 그리고 자네가 틀렸어 - 난 남자든 여자든 똑같이 증오해. 사실 난 아무도 믿지 않고, 궁금해하지도 않고, 아무 기대도 없어. 만약 자네를 붙잡을 수만 있다면 기꺼이 자네의 불알을 으깨버릴 거야. 하지만 이렇게 오랜만에 내 진짜 이름을 듣는 건... 조금은 상쾌했군.";
			link.l1 = "나는 숙녀들을 위한 남자지, 너 같은 마녀를 위한 남자는 아니야. 그리고 어차피, 네가 내가 가장 아끼는 사람을 괴롭히는 일에 연루된 걸 생각하면, 뭘 기대했겠어? 나도 너한테 뭔가를 저지르지 않으려고 간신히 참고 있는 거야. 그 중에서도, 그를 위해서 말이야. 롱웨이는 내 친구야. 그리고 너는 그의 가족이지. 그는 10년이 넘도록 너를 찾아 헤맸어. 그는 너와 대화할 자격이 있어.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "참 감상적이군. 그리고 내가 전혀 신경 쓰지 않는다는 게 참 슬프지. 하지만 이제는 그렇게 쉽게 도망칠 수 없을 거다, 투. 네가 죽인 죄도, 그리고 너희 모두가 한 번 늦었던 죄도 용서하지 않을 거야. 하지만 알아야 할 건... 그래, 넌 알 자격이 있겠지. 네가 알던 나는 이런 사람이 아니었으니까, 형제여.";
			link.l1 = "무슨 일이 있었든... 너에게는 언제나 선택이 있었어, 창싱.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "넌 아직 젊어서 세상이 어떻게 돌아가는지 모르는구나, Charles de Maure. 인생에는 진짜 선택이 하나뿐이지. 살거나 죽거나. 너도 모든 걸 아는 게 좋을 거야. 그러니 내 이야기를 프랑스어로 해주지. 그 언어 할 줄 알지, Tu?";
			link.l1 = "억양이 좀 있지. 하지만 아주 잘 알아들어. 시작해도 돼.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "그리고 그동안 어디 있었지? 에스파뇰라는 하루 이틀 거리밖에 안 돼. 그녀의 죽음도 네 탓이야. 그리고 너, 너도 마찬가지야. 십 년이 넘게 늦었잖아. 우리의 구원자, 우리의 보호자라더니. 여자는 스스로를 지키는 법을 빨리 배울수록 좋아. 어떤 여자는 때맞춰 배우고, 어떤 여자는 못 배우지. 그리고 어떤 놈은 그걸 깨달을 머리조차 없어.";
			link.l1 = "다음에 하는 말 한마디 한마디 조심해라. 네 형제이자 내 친구를 위해서만 아직 널 갈기갈기 찢지 않은 거다. 그가 널 위해 어떤 고통을 겪었는지 너는 전혀 모른다.";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "그가 내가 겪은 일과 비슷한 고통을 겪어봤을 거라고는 전혀 생각하지 않습니다.";
			link.l1 = "그러니 말씀해 주시오.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "글쎄요, 뭐라 해야 할지, 그때 나는 젊고, 어리석고, 순진했지요. 그리고 편협했어요. 투가 이미 내 부모님과 나를 죽인 올리베리오 페르멘텔로스에게 내가 어떻게 납치당했는지 이야기했나요?";
			link.l1 = "맞아요.";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "그가 나에게 구애하고 자신의 감정을 고백했어. 하지만 나는 거절했지. 그때 우리 가족을 학살하고 나를 납치했어. 그리고 그다음엔...\n";
			link.l1 = "짐작할 수 있소.";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "그랬으면 좋겠어. 그러자 그는 다시 한 번 내게 자신의 감정을 고백했어, 뜨겁게 울면서, 그게 유일한 길이라고 했지. 내 가족이 절대 내가 그와 함께 가는 걸 허락하지 않을 테니까.";
			link.l1 = "광기...";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "헤, 그때 이후 내 인생 전체를 설명할 수 있는 한마디군. 나는 또다시 그를 거부했어. 그리고 한동안은 계속 그렇게 흘러갔지. 하지만 분명히, 그게 영원히 계속될 수는 없었어. 나는 완전히 그의 손아귀에 있었으니까.";
			link.l1 = "정말로 그런 일이 있었던 겁니까?";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "물론이지. 그는 나를 힘으로, 거칠고 무자비하게 데려갔어. 강간범들은 신경도 안 쓰겠지만, 그가 예전에 나에게 자신의 위대한 사랑을 눈물로 고백했던 거 기억나? 푸훗! 사랑 따위는 이미 사라졌더군. 그리고 이 모든 일은 매일 반복됐어, 마치 일상처럼. 처음엔 소리치고 저항했지만, 곧 그만뒀어... 어차피 아무 소용도 없었으니까...";
			link.l1 = "하지만 페르멘텔루스는 마땅한 대가를 치렀고, 당신은 결국 여기 오게 되었군요. 어떻게 된 일입니까?";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "글쎄, 얼마 안 가서 그는 나한테 질려버렸지. 웃기지 않아? 그는 내 부모님과 투의 부모님을 죽이고, 나를 납치해서, 매번 나를 능욕하다가, 결국엔 버렸어. 이 군도에 와서는 나를 레바쇠르에게 노예로 팔아넘겼지.";
			link.l1 = "그런 일은 내 원수에게도 바라지 않아. 그런데 어떻게 살아남았지? 애초에 어떻게 자유의 몸이 된 거야? 내가 들은 바로는, 르바쇠르는 자기 은신처에서 여자를 절대 내보내지 않았다고 하던데. 항상 처리해버렸지.";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "지금은 이렇게 된 거요. 그때의 르바쇠르는 달랐소. 아니, 그는 항상 짐승이었지. 하지만 처음에는 가끔 현지의 젊은 식민지 사람들을 납치해서 지하실에서 능욕하고, 입막음 비용을 피하려고 거의 바로 처리해 버렸소. 그 시절엔 며칠 이상 붙잡아 두는 일은 드물었지. 하지만 나와는, 처음부터 달랐소.";
			link.l1 = "네가 노예였으니까, 맞지?";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "정확합니다. 르바쇠르가 진정으로 원한 것은 단순한 육체적 쾌락이 아니었소. 피해자들에 대한 일시적인 권력의 쾌감조차 아니었지요—결국 그는 섬 전체를 지배하고 있으니까요. 하지만...\n";
			link.l1 = "... 그들이 부서지는 모습을 지켜보는 쾌락이지 - 그들의 의지, 그들의 표정, 그들의 목소리, 그들의 행동까지.\n";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "그래. 준비를 잘 해왔군, 선장. 하지만 그런 면에서, 나는 그에게 아무 재미도 주지 못했어 - 페르멘텔로스가 이미 부서진 나를 데려왔으니까. 그리고 르바쇠르는 나를 아름답다고 생각하지 않았어 - 그는 아시아 여자를 좋아하지 않거든. 이상하게도, 이게 내게 너무 큰 영향을 줬어. 내가 매력 있다는 건 알지만, 진짜 아름답다고는 생각하지 않아. 누가 그렇게 말해도 믿지 못하겠어. 지금도 운동하고, 비단을 입고, 좋은 향수를 뿌려도 마찬가지야. 고문하는 자의 인정을 바라는 건 아니지만...\n";
			link.l1 = "그럼, 다시 묻겠소 – 어떻게 살아남았소? 그 자는 여자가 지겨워지면 곧바로 처분하지. 자네 말대로라면, 자네는 처음부터 그에게 지겨운 존재였을 텐데.";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "처음부터 내가 그를 지루하게 했다는 사실이 영향을 미쳤겠지. 그리고 내가 노예였다는 사실도. 어디 갈 수도, 아무 말도 할 수 없었으니까. 수천 년 동안 노예 소녀들은 그렇게 취급받아 왔어. 그는 나와 함께 보내는 시간을 자기한테 ‘재미있게’ 만들 방법을 생각하기 시작했지.";
			link.l1 = "아마 그의 중독이 지금의 형태로 태어난 것도 그런 이유겠지.";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "맞아요. 처음엔 구타, 침 뱉기, 그리고 온갖 모욕이었죠. 내 외모와 출신, 내 피까지 조롱당했어요. 그리고 첫 고문이 시작됐죠 - 칼, 집게, 프라이팬... 그래서 이렇게 온몸을 가리는 옷만 입는 거예요. 내 몸 전체가 흉터와 화상, 훼손으로 뒤덮였으니까요. 그래서 다시는 남자 앞에서 옷을 벗을 생각도 없어요. 절대 다시는요. 그때서야, 페르멘텔로스에게 납치당했을 때 이미 깨달았어야 했던 걸 비로소 알게 됐죠.\n";
			link.l1 = "그게 뭐였지?";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "더 이상 무력한 꼭두각시로 남지 않겠다는 뜻이오. 오히려 내 삶을 내가 통제해야 한다는 것이오. 내 경우에는, 여자가 자신의 삶을 바꾸려면 주변 남자들을 지배해야만 한다는 사실을 깨달았소.";
			link.l1 = "르바쇠르를 통제할 수 있다고는 말 못 하겠소.";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "그리고 그대가 틀린 말 하는 것도 아니오. 하지만 조심스럽게 그 자에게 영향을 줄 수는 있소. 르바쇠르는 처음부터 완전히 복종하는 것도, 반박이나 애원하는 것도 똑같이 증오하오. 아첨도 마찬가지요—자기가 얼마나 더러운 인간인지 스스로 알고 있기 때문이오. 나는 이 사실을 곧바로, 참으로 고통스러운 대가를 치르고 깨달았소. 하지만 또 한 번의 고문과 폭력이 끝나고 그 자가 모든 것에 만족했을 때, 부드럽게 말을 건넬 수 있었소. 나는 귀족의 피는 아니지만, 지능이 모자라진 않소.";
			link.l1 = "무슨 이야기를 나누었습니까?";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "내가 그의 흥미를 끌었지. 고문에 대한 아이디어를 제안하고, 어떤 고문 도구는 쓰지 않는 게 좋고, 어떤 것부터 시작하는 게 좋은지 조언했어. 처음엔 당연히 그 모든 걸 나한테 시험했지. 하지만 그 다음엔... 자기만의 뒤틀린 방식으로 나를 존중하기 시작했어. 그의 머릿속엔 도대체 무슨 일이 벌어지고 있는 걸까? 그가 왜 그렇게 됐는지 알아보려고 했는데, 또다시 나를 반쯤 죽도록 때렸어. 그리고는 개인 의사를 데려왔지.";
			link.l1 = "그게 내가 이미 들은 것보다도 더 이상하고 역겹군.";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "그는 더 이상 나에게 자신을 바치라고 요구하지 않았어. 나를 제자라고 불렀지. 하지만 항상, 자기 작품으로서 나는 완전히 실망스럽다고 말했어. 아마도 나를 긴장하게 하려고 그랬던 것 같아. 그래서 그는 나에게 펜싱과 언어를 가르치기 시작했어.\n비록 나를 지하실에 가뒀지만, 값비싼 드레스는 그의 아내가 아니라 내가 다 받았지.";
			link.l1 = "정말 대단한 사업이지요. 여기를 운영하는 당신의 방식과 뚜렷한 유사점이 보입니다.";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "그건 생각 못 했네, 흠. 그리고 네가 하는 비유는 마음에 안 들어. 나는 내 여자 직원들을 고문하지 않아. 내 손님들에게도 그렇게 못 하게 해. 그 여자들이 싫고, 그들의 아름다움이 부럽긴 해도 말이야. 그리고 나랑 그 돼지랑은 아무런 공통점도 없어, 그걸 기억해.";
			link.l1 = "그래서 이 사창가는 어떻게 손에 넣으셨습니까?";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "레바쇠르에게서지. 한동안 그는 나를 자기 집에 두었어. 가끔씩은 이런저런 여자애를 어떻게 부러뜨릴지 조언을 구하기도 했지. 결국 나는 그에게 특별한 존재였으니까, 비록 그는 절대 인정하지 않겠지만. 내가 처음이었으니까. 나는 전부 봤어.";
			link.l1 = "누가 누구에게서 배웠더라?";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "나는 그런 사람이 아니야! 나는 모든 걸 손쉽게 얻은 자들을 진심으로 증오해! 그건 불공평하잖아! 이 사창가는 내 생각이었어! 내 일꾼들은 상인, 관리, 귀족의 딸들이야. 가끔 르바쇠르와 어울리게 된 아이들이지. 내가 그들에게 나를 달라고 부탁했어. 비밀 지하실에서의 고문과 굴욕은 한 가지야. 하지만 그런 애들에게 창녀로서 대중 앞에 나서게 하는 건 전혀 다른 일이야!";
			link.l1 = "당신네 여자 일꾼들이 그렇게 굴욕적이고, 비참하며, 부서진 모습이라고는 말하지 않겠소.";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "그들이 왜 조용히 있는지 알지. 레바쇠르나 나라도 그들이 입을 열면 무슨 짓을 할지 아니까. 하지만 네 말도 일리가 있지. 포도주, 음식, 비단, 매일 고문당하지 않는 생활... 많은 이들이 나를 구원자처럼 여기기 시작했어. 멍청한 놈들! 여기 있는 게 싫은 자들은 몇 안 돼. 그중 몇몇은 무거운 마음으로 내보냈지. 그럴 때면 그는 웃으면서, 내 돈 문제가 해결되면 언제든 그들을 다시 데려가도 된다고 하더군. 하지만 난 항상 거절했어. 적어도 그럼 그들이 쓸모없이 지하실에서 죽는 대신 금을 가져올 테니까. 그들에게는 너무 쉬운 탈출구가 될 테니.";
			link.l1 = "모두가 굴욕을 느끼진 않았다는 게 참 안타깝군, 신성한 종교재판소보다 더 끔찍한 수도원을 네 창녀굴 같은 황금 새장으로 바꿨는데도 말이야...";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "나를 심판하는 건가? 나는 단순히 살아남는 것만이 아니라 성공적인 무역을 이루고 싶었어. 비록 자신도 모르게였지만, 르바쇠르는 내게 감사했지. 더 이상 노예가 아니었음에도, 그는 나를 놓아줄 수 없었어. 나는 여전히 그를 위해 일해야 했고, 그의 졸개들을 도와야 했지. 특히 그 깡마른 조카놈, 나를 볼 때마다 군침을 흘렸지만 감히 덤비거나 막말을 하진 못했어. 역겨웠지. 알겠나, 그는 나를 실망이라 불렀지만, 나는 티보와 마르텐 둘을 합친 것보다 더 쓸모 있었어. 나는 그의 명령으로 그들과 자주 동행했지, 그때 포르토프랭스에서처럼.\n";
			link.l1 = "그 모든 것이 많은 것을 설명해 주는군...";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "맞아. 들어봐. 나는 네 연인을 고문하지 않았어. 이 두 손으로는 어떤 여자도 고문한 적 없어, 가끔 레바쇠르에게 조언을 해준 적은 있어도. 하지만 이왕 말이 나온 김에...\n";
			link.l1 = "뭐라고?";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "아시다시피, 르바쇠르는 때때로 토르투가에서 잠깐 모습을 드러낸 어떤 소녀를 데려오라고 요구하곤 합니다. 그리고 그 소녀는 곧 섬을 떠났지요. 혹은 누군가가 그를 놀라게 하려고, 혹은 그의 환심을 사기 위해 낯선 여자를 끌고 오기도 합니다. 저 역시 그런 경우였습니다. 당신의 사랑하는 이를 납치한 건 제 생각이었습니다.";
			link.l1 = "방금 뭐라고 했지...?";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "At first, we were considering capturing that blonde who used be so close to you. But since she is untouchable now, and because we have already promised him a girl, you redhead had to do.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "I heard rumors about your gorgeous companion who never leaves your side. Considering Levausser's love for blondes, I had very little trouble selling him this idea.";
			dialog.text = "소타, 그 놈의 개, 원래는 루터의 아내인 물라토 여자를 그에게 데려오기로 했지. 그런데 네가 소타를 죽였으니, 큰 놈한텐 물라토 여자가 없게 됐어. 르바쇠르는 미쳐 날뛰었지. 티보, 마르텐, 심지어 나까지 다 두들겨 맞았어. 누가 더 미웠는지 모르겠어: 또다시 날 패버린 그 놈인지, 아니면 그 꼴을 만든 너인지...\n "+ sStr +"";
			link.l1 = "그러니까 그 사람 때문도 아니군... 당신이 한 짓이야.";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "나는 당신의 용서를 바랄 생각조차 없고, 게다가 필요하지도 않소. 피를 원한다면, 피를 보게 될 것이오. 그리고 당신은 그것을 몹시 후회하게 될 거요. 하지만 이해라면 거절하지 않겠소. 지난 십 년 만에 처음으로 그게 필요할지도 모르겠군. 내가 한 일은 그저 언젠가 토르투가에서 벗어나기 위해 최선을 다한 것뿐이오. 나에게 물어볼 것이 있소, Charles de Maure?";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "하지만 너도 납치에 가담했지. 그리고 레바쇠르가 피해자들을 어디에 가두는지 알고 있잖아. 어디인지 말해. 만약 최악의 일이 아직 일어나지 않았다면, 너에게 복수하지 않는 걸 진지하게 고민해 보겠다.";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "음, 드디어 모든 게 맞춰지고 있군...";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "내가 거기 있었으니 아는 거다.\n그리고 내가 그 자와 서로 병적으로 집착하는 사이라고 생각한다면, 그건 큰 오해다.\n누군가 그 돼지를 꼬챙이에 꽂아버리는 걸 본다면 나는 기쁠 거다.";
			link.l1 = "시간 없어, Chang Xing. 어디 있지?";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "도시 거리 아래에 있는 그 지하 감옥을 알고 있나? 바로 거기로 가게 될 거야.\n막다른 골목 중 하나에 큰 와인 통이 있는데, 그 옆에서 그의 쾌락실로 통하는 비밀 통로가 시작되지. 그자는 가끔 그 방을 그렇게 부르더군.";
			link.l1 = "이제야 모든 게 드디어 맞춰지고 있군...";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "잘됐군. 이제 나가. 수년 만에 이렇게 말할 수 있어서 좋았지만, 네가 내 모든 비밀을 알고, 나에게 무슨 일이 있었는지까지 아는 걸 깨닫자니 역겹기만 해. 이제 널 보는 것만으로도 분노가 치밀어. 아, 그리고 투는 내 곁에 남는다.";
				link.l1 = "왜 그렇습니까?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "아마 내가 그의 가족이기 때문일까? 그리고 네 옆에서 그가 어떤지 내가 보니까 그래 - 두들겨 맞고, 비참하게 중얼거리기만 하면서, 아직 언어도 제대로 익히지 못해서 말도 제대로 못 하는 모습이야. 그런데 그는 너랑 친구라고 했어. 네가 그에게 어떤 영향을 줬는지 뻔히 보여. 적어도 나는 그를 제대로 된 남자로 만들어 줄 거야.";
			link.l1 = "그리고 정말로 자신이 만족스러운가? 그를 무엇으로 만들 셈인가? 생명을 거래하는 잔혹하고 씁쓸한 괴물로 만들 것인가?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "정의의 섬 선장님, 제발 멈추십시오. 제 누이를 그냥 내버려 두시길 부탁드립니다. 그리고... 저는 그녀 곁에 남겠습니다.";
				link.l1 = "너... 뭐라고? 롱웨이... 하지만 왜? 그녀가 어떤 괴물이 됐는지 안 보이냐?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "너도 다르지 않잖아? 시간이 지나면서 변했지. 더 나빠졌어. 처음엔 예의 바르고 이해심도 있었지. 그런데 점점 무례해졌고, 로덴부르크보다도 더 심해졌어. 그리고 내가 반 데르 빈크를 쫓으려면 좋은 배가 필요하다고 했을 때, 넌 고물이나 던져줬지!";
				link.l1 = "롱웨이...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "나는 바다로 나가 이 모든 세월을 오직 내 여동생을 찾고 구하기 위해 보냈소. 그리고 이제 그녀는 여기 있고, 안전하오. 내 사명은 끝났소. 그리고... 내 이름은 창투요. 롱웨이라는 이름은 배신자 반 메르덴이 내게 붙여준 것이오, 혹시 잊었을까 봐 말해두오. 하지만 창투는 자유로운 사람이오. 창투의 긴 여정도 마침내 끝났소.";
			link.l1 = "그 여자는 널 로덴부르크처럼 하인으로 만들 거야. 가족이라는 이유로 널 옥죌 거고. 그리고 나와 \n " + sStr + " 이렇게 많은 고통을?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "지금은 당신이 창투를 압박하고 있소. 제발, 저를 놔주시오. 저는 너무 지쳤소. 당신은 좋은 분이오, 선장 나리 - 하늘도 증명할 것이오. 하지만 당신은 제 가족이 아니오. 그녀가 가족이오. 내가 남지 않으면, 이 모든 세월이 헛된 것이 되고 말 것이오. 이제 나는 그녀의 길잡이 별이 되어, 꺼져버린 불씨를 다시 밝혀주겠소 - 모든 것을 태우는 불길이 아니라, 따뜻하고 위로가 되는 불로.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "흠, 네 말이 맞아. 내가 지금 너무 몰아붙이고 있을지도 모르겠네. 뭐, 난 항상 널 존경해왔어. 오랫동안 기다려온 네 여동생과의 재회를 기원할게. 하지만 경고하는데, 그녀와 함께라면 평안을 찾지 못할 거야.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "지금 나를 떠나면 안 돼! 아직 내가 구해야 할 사람이 있어 " + sStr + " 르바쇠르에게서! 나 혼자 거기로 가길 바라? 도와줘, 롱웨이. 그러면 널 풀어줄게. 약속할게.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "내가 알아서 할 수 있어. 이제 더 이상 나 걱정하지 않아도 돼. 고마워.";
				link.l1 = "네 여동생께서는 우리가 평화롭게 헤어지기로 한 것에 화가 난 것 같군.";
			}
			else
			{
				dialog.text = "알아내실 겁니다, 나리 선장. 제가 본 사람 중에 가장 총명하신 분이니까요. 여자만 괴롭히는 그 벌레쯤이야 쉽게 처리하실 수 있겠지요. 부탁드립니다, 억지로 시키지 마십시오. 제 여동생은 저와 할 이야기가 산더미입니다! 그리고... 제 이름은 창투입니다.";
				link.l1 = "지금 나를 떠나면, 나를 배신하는 거라는 걸 알지?! 특히 그녀 곁에 남는다면 말이야 - 이 모든 걸 시작한 그 여자와 함께!";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "두려워 마십시오, 선장님. 저에 대해 무례하게 말하더라도, 저는 그녀의 오라비이자 마지막 남자 혈육입니다. 가셔도 됩니다. 그녀가 당신을 죽게 두지 않겠습니다. 안녕히 가십시오.";
				link.l1 = "작별이오... 창 투.";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//Мирно разошлись
			}
			else
			{
				dialog.text = "나는 할 말은 다 했소. 안녕히 계시오, 선장. 그리고 행운을 빕니다. 창 투는 언제나 자유인일 것이오. 그걸 잊지 마시오.";
				link.l1 = "이게 내가 모든 걸 포기하고 당신의 수색을 도왔더니 돌아오는 대가란 말입니까?! 저들이 지금 하고 있는 짓이... " + sStr + " 지금이냐?! 넌 배신자야, 창투. 그리고 넌 그렇게 죽을 거다, 둘 다, 이 빌어먹을 뱀들아!";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "내 이름은 창투다. 롱웨이는 죽었다. 네가 그를 죽였지. 이제 더 이상 너는 내 선장이 아니다. 그리고 이제 네가 죽을 차례다. 내 가족은 마침내 평화를 찾을 것이고, 우리의 별은 밤하늘에서 밝게 빛날 것이다.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "(신뢰) (지도력) 롱웨이... 창 투. 멈춰. 내가 너에게 완벽한 선장은 아니었다는 거 알아. 하지만 정말로 이렇게까지 나를 죽이고 싶어? 우리가 함께 겪은 모든 일들 이후에? 처음엔 로덴부르크, 이제는 네 여동생을 찾는 일까지.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				Notification_Perk(true, "Trustworthy");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "롱웨이, 나는 네 가족도 아니고 보모도 아니야. 나는 네 선장이야. 명령을 내릴 뿐이지, 내가 너를 실수로 모욕했는지 고민하지 않아. 그런데 넌 마치 오랜 부부처럼 요구를 해대고 있군, 맙소사...\n";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "그래. 이제 알겠군. 너도 결국 자기밖에 모르는 썩어빠진 인간이야... 롱웨이. 네 누이처럼 말이지. 내 가족은 오늘을 살아남을 거다. 네 가족은... 못 버틸 거다. 지옥에나 떨어져라!";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "만약 선택이 당신과 내 가족 사이라면, 아무리 힘든 선택이어도 나는 여전히 가족을 택하겠소.";
			link.l1 = "네가 그토록 오랜 세월 동안 그녀를 찾아 헤맬 때 손가락 하나 까딱하지 않은 가족? 아, 그런데 이제야 때가 됐다고? 나는, 너를 돕기 위해 내 모든 걸 내던졌지. 네가 지금 여기 서 있는 것도 그 결과야. 젠장, 나는 그 여자보다 네 가족이야, 내 친구!";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "맞으십니다. 언제나 맞으십니다. 용서해 주시겠습니까, 나의 주군 선장님?";
			link.l1 = "용서할 일은 없어! 한 가지는 네 말이 맞아 – 나는 항상 네가 받을 만한 선장이 아니었지. 이제 우리 서로 비긴 셈이네. 그런데 앞으로 널 뭐라고 부르면 좋겠어? 롱웨이? 아니면 창투?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "롱웨이로 하시지요. 이미 그렇게 불리우는 것에 익숙해졌으니.";
			link.l1 = "그럼 모든 다툼은 잊고, 다시 한 번 배에 오신 걸 환영하오, 롱웨이.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "너! 무슨 소리야?! 왜 멈췄어?! 죽여! 저 자에게 넌 평생 일꾼일 뿐이야! 네 가족은 나, 오직 나뿐이야!";
			link.l1 = "그녀 정말 화가 나 있지, 롱웨이? 이제 넌 그의 가족이 아니야, 싱. 롱웨이가 군도에 도착했다는 걸 알았을 때도 모른 척하기로 했을 때 이미 끝난 거야. 우리 간다.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "저 인간 안에 뿌리박힌 노예 근성을 뽑아낼 진짜 기회 따윈 애초에 없었던 것 같군. 내가 그를 구할 수 없어. 그렇다면 너희 둘 다 내가 직접 죽이겠다.";
			link.l1 = "여기서 구원받을 수 없는 건 바로 너야. 있지, 내가 너한테 너무 이해심 많고 관대했어. 하지만 이게 훨씬 낫지. 롱웨이조차도 네가 얼마나 뱀 같은지 이제는 알게 된 것 같아. 그는 네 죽음을 그리 슬퍼하지도 않을 거야.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "지금 농담할 때가 아니야! 네 두려움과 실패를 농담 뒤에 숨기고 있군! 그럴수록 내 확신만 더해질 뿐이다. 방어해라, 드 모르! 창 투는 너를 절대 용서할 생각이 없다.";
			link.l1 = "이렇게 끝나서 유감이오. 하지만 그게 당신이 원하는 길이라면, 그대로 두겠소. 그런 경우라면, 나 역시 자비 따위는 베풀지 않겠소.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "찰스, 들어봐...";
				link.l1 = "에렌?";
			}
			else
			{
				dialog.text = "찰스, 롱웨이, 멈춰...";
				link.l1 = "헬렌, 지금 내 뒤로 오는 게 좋겠어. 혹시 저들이 우리를 공격할지도 모르니, 네가 그러면 내가 더 안심이 될 거야.";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "너무 피곤해서 거의 서 있을 수도 없어. 그냥 여기서 나가고 싶어. 롱웨이가 오고 싶지 않으면 억지로 배로 끌고 가지 않을 거지? 내가 항해사이자 일등항해사가 되어줄게, 내 캡틴. 그리고 바라건대, 네가 가장 신뢰하고 사랑하는 사람이기도 하고. 게다가, 롱웨이 말도 맞아 – 우리는 그의 가족이 아니잖아. 그녀가 그렇지, 좋든 싫든.";
				link.l1 = "하지만 그녀는 어쩌고? 네가 고문당한 것도 다 그녀 때문이야. 모든 게 그녀의 생각이었지. 그리고 널 납치한 것도 바로 그녀야.";
			}
			else
			{
				dialog.text = "하지만 안 그럴 거잖아, 그치? 그냥 지금 떠나자, 그게 다야. 우리가 그를 위해 한 모든 일에도 불구하고 그가 우리를 이렇게 생각한다면, 그의 마음을 바꾸려고 해도 소용없어. 말보다 행동이 더 중요하니까. 그가 자기 누이와 남고 싶다면, 그냥 두자.";
				link.l1 = "헬렌, 너는 그녀 때문에 정말 많은 고통을 겪었지...";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "그 악마 같은 여자를 그녀의 악마들과 내버려 두시오. 곧 그녀의 영혼을 잡아먹을 테니. 그리고 우리의 영혼은 쉴 자격이 있소. 가십시다.";
				link.l1 = "그래. 이제 가야겠지. 여기서 나가자, 내 천사야. 그리고 너, 롱웨이든 창투든 - 잘 있어.";
			}
			else
			{
				dialog.text = "하지만 나는 죽지 않았어. 그리고 최악의 일도 일어나지 않았지. 나는 여기, 당신과 함께 있어. 그게 중요한 거야. 그리고 르바쇠르는 죽었어. 그 자가 없으면, 그녀는 아무것도 아니야. 그녀의 장소는 돈을 잃고 있고 곧 망할 거야. 그리고 그들도 함께 가라앉겠지. 가자, 내 캡틴. 여기서 우리가 할 일은 더 이상 없어.";
				link.l1 = "나 논쟁하지 않겠어, 헬렌.";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "어디로 가는 거야?";
			link.l1 = "뭐야, 네가 놀라는 거야? 우리가 너랑 네 여동생의 창자를 쏟아내고 싶어 안달이 아니라서? 그게 우리와 너의 차이지, 롱웨이. 그런데도 아직도 내가 악당이라고 생각하나... 하지만 좋아, 봐라. 나를 죽이고 싶다면, 헬렌도 죽여야 한다는 뜻이야. 그녀는 지금 다치고, 상처 입었어. 정말 그렇게 하고 싶은 거냐?";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "음-흠.";
			link.l1 = "네 눈에 의심이 가득한 걸 알아, 나한테 원한도 많겠지. 하지만 우리 둘 다 헬렌에게서 배워보자고, 어때? 우리 선원 중에 그녀만큼 친절하고 용서할 줄 아는 사람은 없어. 우리는 떠날 거야. 그리고 네 안에 조금이라도 선함이나 이성이 남아 있다면, 우리를 막지 않을 거다.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "그렇게 하시지요. 사과드립니다. 하지만 이제 더 이상 당신은 제 선장이 아닙니다.";
			link.l1 = "어떻게든 극복하겠어. 네 여동생이 무슨 짓을 했든, 너와 네 여동생에게 행운이 있길 바란다. 잘 가라, 롱웨이.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "어서 가자, Charles. 이제 이 반란을 진압할 시간이야.";
			link.l1 = "신만이 아시겠지, 나는 그걸 하고 싶지 않았어... 그리고 지금도 원하지 않아.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "모른다고?! Charles, 내 말 좀 들어봐. 너는 그를 위해 그렇게 많은 걸 했는데, 돌아온 건 배신이랑 더러운 말뿐이야, 그치? 진짜 이대로 넘어갈 거야?";
			link.l1 = "나는 롱웨이의 피를 흘리고 싶지 않아. 우리도 한때 친구였다는 걸 아직 잊지 않았어.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "그런 친구 따위 다 필요 없어, 적보다 더 나쁘다니까, 그치! Charles, 나 좀 봐. 나한테 무슨 일이 일어났는지 봐봐-그 자식 누이 때문에, 그년이 이 피투성이 섬으로 오는 길에 날 조롱하고, 모욕하고, 망신까지 줬잖아!";
			link.l1 = "Mary, 이해해... 지금 네가 정말, 정말 화난 거 알아...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "안 돼, Charles, 나 그냥 화난 게 아니야, 아니... 분노로 타오르고 있어! 그리고 그 비열한 놈이 너한테 뭐라고 했는지 때문만도 아니야! 다시 한 번 날 봐, Charles-그리고 우리가 지금 여기서 끝내지 않으면 얼마나 더 많은 소녀들이 이런 일을 겪게 될지 상상해 봐. 여기서, 지금.";
			link.l1 = "이제 더 이상 아무도 해치지 못해. 르바쇠르는 죽었어.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "찰스, 네가 정말 그녀가 떠드는 이단을 귀 기울여 들었단 말이야? 그녀도 그 지하실에서 벌어진 일에 그 썩은 돼지만큼이나 책임이 있어. 이제 롱웨이—아니, 지금은 뭐라고 불러야 할지 모르겠지만—그를 봐. 그녀가 얼마나 빨리 자기 편으로 끌어들였는지 봤지, 그치? 또 어떤 병든 생각을 그 배신자의 머릿속에 집어넣을지 누가 알아? 그 악마 같은 여자가 롱웨이를 르바쇠르의 길로 밀어넣는 게 그리 어렵겠어? 지금 그가 어떤 사람인지 생각하지 마, 찰스. 1년, 아니 한 달만 지나면 어떤 괴물이 될지 생각해 봐. 내가 옳다는 거, 알지?";
			link.l1 = "인정하기는 싫지만, 너에게 반박할 말이 없어, Mary...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "하하하! 정말 흥미롭군, 대단한 연기였어. 이렇게 실컷 웃어본 건 오랜만이야. 그리고 저 여자, 배짱 하나는 인정해야겠어.";
			link.l1 = "입 다물어, 이 년아.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "재밌지 않아, 드 모르? 난 투가 직접 너를 쓰러뜨리는 걸 보고 싶을 정도야. 그리고 네 여인도 나만큼이나 피에 굶주렸군. 아주 좋아. 가만히 있진 않을 거야—난 르바쇠르랑 토르투가의 내로라하는 놈들과 함께 훈련했지. 과연 누구 팀이 이길지 두고 보자고.";
			link.l1 = "너한텐 제대로 된 스승도 없었지. 그리고 Mary를 화나게 했어. 이제 끝장이야. 내가 여기 없었더라도, 너희 둘이 그녀한테는 상대도 안 됐을 거야.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "네. 드디어. 롱웨이가 다시 누이와 이야기해도 되겠습니까, 나의 주군 선장님? 오래 걸리지 않을 것입니다.";
			link.l1 = "물론이지. 하지만 서둘러야 해 - 시간이 많지 않으니까.";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "롱웨이, 빨리 끝내.";
			link.l1 = "좋소.";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "그리고 나에게 무슨 말을 하려고 했지, 내 형제여?";
			link.l1 = "롱웨이가 당신에게 매우 실망했소, Xing.";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "(만다린어로) 왜 또 얘기하고 싶으면서 우리 말을 안 쓰는 거지, 투? 그 사람 때문에 창피한 거야? 나라면 네 억양이 더 창피할 것 같은데.";
			link.l1 = "아니오. 롱웨이는 이제 더 이상 주군 선장님께 숨기는 비밀이 없습니다.";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "(프랑스어로) 먼저 로덴부르크, 이제는 드 모어. 너는 항상 ‘나리’가 필요하지. 여기서 십수 년 동안 아무것도 이루지 못했잖아. 그들의 언어 하나도 제대로 배우지 못했고. 우리 것보다 훨씬 쉬운데도 말이야! 실망이라면, 바로 네 자신이지.";
			link.l1 = "하지만 나는 여자를 거래하지 않아. 그들을 납치하거나 고문하는 일엔 관여하지 않는다.";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "진심이십니까? 로덴부르크를 위해 당신이 한 짓들을 나열해 드릴까요? 내가 해온 일들은 그에 비하면 아이 장난에 불과할 겁니다.";
			link.l1 = "나는 목적이 있었어 - 너를 찾는 것이었지. 하지만 넌 나를 만나고 싶어하지도 않았어. 그리고 마침내 널 찾았을 때, 내 앞에 있던 건 한때 내 길을 밝혀주던 따스한 길잡이 별이 아니라 괴물이었어.";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "괴물이라고? 뭐, 네 말이 맞을지도 모르지. 난 더 이상 네가 알던 그 명랑한 소녀가 아니야. 그랬다면 인생이 날 씹어먹고 뱉어버렸을 거야. 그래서 내 이빨을 스스로 길러야 했지. 내 별은 오래전에 꺼져버렸어. 그래도 난 여전히 네 누이야, 투.";
			link.l1 = "아니. 이제 넌 내 누이가 아니야.";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "이렇게 오랜 세월이 흘렀는데도 날 이렇게 쉽게 포기하는 거야? 허... 그리고 누가 알아, 그날 네가 제때 집에 돌아와 페르멘텔로스를 죽였더라면 나도 여전히 예전 그대로였을지?";
			link.l1 = "맞아. 내 잘못도 일부 있어. 내 책임이야. 내가 끝내겠다. 네 고통을 끝내주마. 이 비참한 삶을 끝내겠다.";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "정말로 네 친누이까지 죽이려는 거냐, 청투? 물론 네가 성공할 리는 없겠지만, 중요한 건...\n";
			link.l1 = "넌 더 이상 내 누이가 아니다. 싱은 십 년 전에 죽었다. 그리고 오늘이야말로 충투가 마침내 죽는 날이다. 이제부터, 그리고 영원히, 내 이름은... 롱웨이다.";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "우선, 창싱을 구출합니다.";
			link.l1 = "뭐?! 아직도 이해를 못 하는군, 친구. 네 여동생은 당장 위험에 처한 건 아니지만, " + sStr + " 있소. 그리고 장싱도 마르텐과 티보만큼이나 이 일에 책임이 있다는 걸 상기시켜야겠소?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "그건 사실이 아니야! 그녀는...";
			link.l1 = "르바쇠르가 무엇을 하고 있을지 짐작이나 하십니까 " + sStr + " 우리가 여기서 말다툼이나 하고 있을 때?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "하지만 장싱만이 내게 남은 전부입니다, My Lord Captain... 당신 가족은 아직 온전하잖습니까...";
			link.l1 = + sStr + " 내 아내는 아닐지라도, 내 가족만큼이나 소중한 사람이야.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "창싱은 내 마지막 길잡이 별이오, My Lord Captain. 그리고 로버트 마튼에게 자백을 받아낸 것, 당신이 내게 빚진 것이오.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "네 여동생을 찾으러 갈 거야, 약속할게. 하지만 그동안 Levasseur가 그녀를 건드린 적은 없어. " + sStr + " 장싱보다 훨씬 더 큰 위험에 처해 있습니다. 먼저 그녀를 구하는 걸 도와주시면, 큰 빚을 지겠습니다.";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "(신뢰) (지도력) 네 여동생을 반드시 찾으러 가겠다, 약속하지. 하지만 그동안 Levasseur가 그녀를 건드린 적은 없어. " + sStr + " 장싱보다 훨씬 더 큰 위험에 처해 있습니다. 먼저 그녀를 구하는 데 도와주시면, 큰 은혜를 입은 셈이 되겠군요.";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						Notification_Perk(true, "Trustworthy");
						notification("Skill Check Passed", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "내 말 들어! 네 여동생은 안전해. 하지만\n " + sStr + " 지금 그녀는 변태의 손아귀에 들어가 있어. 당장이라도 고문당하고 있을지 몰라, 아니면 더 끔찍한 일을 당하고 있을 수도 있지! 레바쇠르가 네 여동생을 지하 감옥의 다른 불쌍한 여자들처럼 대했다면, 그녀가 그런 고급스러운 가게를 가질 수 있게 놔뒀을 것 같아?!";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "쓸데없는 논쟁에 시간 낭비하지 않겠소. 우리 각자 우선순위가 있지. 다시 흩어집시다. 내 신이 나를 돕고, 그대 신이 그대를 돕기를.";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "맞아. 너한테 신세를 졌군. 좋아, 네 뜻대로 해. 게다가 네가 없으면 나 혼자서 레바쇠르와 그 놈들을 감당 못할 수도 있지. 하지만 만약 무슨 일이 생기면\n " + sStr + " 우리가 당신 누이 문제를 처리하는 동안...";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "이해해 주셔서 감사합니다, 나리 선장님. 행운을 빕니다!";
			link.l1 = "그리고 너에게도, 롱웨이.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "헛된 협박은 아무 의미 없는 협박입니다, 나리 선장. 서둘러야 합니다, 그래야 모든 일에 제때 도착할 수 있습니다.";
			link.l1 = "네 신이 그 말을 들었으면 좋겠군. 가자!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "이번 한 번만은 존경을 표해 넘어가겠습니다, 나의 주 선장님. 다음번엔 정말 때릴 겁니다. 이제 저는 선장님의 허락이 있든 없든 제 여동생을 찾으러 갑니다.";
			link.l1 = "더 이상 너랑 말다툼으로 시간을 낭비하지 않겠다, 롱웨이. 결국 우리 모두는 그 무엇보다 소중히 여기는 것이 있지.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "음, 그치? 알겠습니다, 나리 선장님. 하지만 서둘러야 해요.";
			link.l1 = "그래. 고마워, 롱웨이.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "그래, 그래, 이게 누구신가... 젠장. 샤를 드 모르와 그 찢어진 눈의 똥개군.";
				link.l1 = "여기 잡종은 딱 하나뿐이지. 보고 싶으면 거울이나 봐, 위그노 자식아. 아니면 네 조카나 쳐다봐. 그래도 그 녀석은 들쥐 같은 몰골이더군.";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "내가 방해하지 말라고 했잖아! 아, 샤를 드 모르, 흐흐흐. 정말 끈질긴 작은 해충이군.";
				link.l1 = "그게 내 원래 모습이야. 이제 좆같은 소리 집어치우고...";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "여긴 네 배가 아니야, 새끼야! 이 섬에 남자는 나 하나뿐이다!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "감히 이런 짓을 하다니, 이 쓰레기 놈아!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "진정해라, 조카야! 드 모르 나리가 곧 예의범절이 무엇인지 똑똑히 배우게 될 테니.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "내가 너한테 비명을 지르라고 허락했나?!";
			}
			else
			{
				dialog.text = "그 불꽃 다 어디 갔지, 응, 예쁜이? 아, 이제 알 것 같군...";
			}
			link.l1 = "그 여자 건드리지 마, 이 자식아!";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "헤헤헤... 뭐라고 소리치고 욕해도 상관없어. 하지만 네가 바람에 흔들리는 나뭇잎처럼 떨고 있는 게 다 보여. 네 눈에서 두려움이 보인다. 너랑 앙리, 그 점은 똑같지. 기분 나쁘게 듣지 마라, 조카야.";
			link.l1 = "맞아, 두려움이지. 하지만 너 따위가 아니라.";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "물론이지, 물론. 다 들어봤어 - 네가 아무도 두려워하지 않는다는 말, 드 모르. 그녀가 내게 그랬지. '오-오, 샤를이 올 거야, 샤를이 날 구해줄 거야... 샤를이 이렇고, 샤를이 저렇고...' 자, 샤를이 여기 있네. 샤를이 맨 앞자리에 앉았지. 앙리, 우리 손님을 편하게 해드려.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "그럴 필요 없어요, 아저씨. 이번에는 좀 지나치신 것 같아요...";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "삼촌, 이번에는 당신의 도움이 필요할 것 같아요...";
				}
				else
				{
					dialog.text = "삼촌, 제가 저 자를 끝장낼까요, 아니면 먼저 구경하게 둘까요?";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "나 때문이 아니야, 여기 계신 화이트 나이트 나리께서 구조하러 오시느라 너무 오래 걸렸지. 이제 연극은 끝난 것 같네, 하하하하!";
				link.l1 = "신이시여, 안 돼...";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "그럴 줄 알았소. 어떻게 이 나이까지 살아남았소? 그런데, 당신도 마찬가지요, 드 모르.";
					link.l1 = "도살자 놈, 내가 너한테 묻고 싶은 게 얼마나 많은지 너는 모를 거다!";
				}
				else
				{
					dialog.text = "우리 작은 연극에 관객이라도 있었으면 좋았을 텐데...\n하지만 여기 고집쟁이 나리께선 그런 즐거움을 줄 생각이 없는 것 같군.";
					link.l1 = "누구에게도 남는 즐거움은 없어. 오직 나만이 갖지, 널 도륙하면서, 도살자 놈!";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "어서, 가서 그녀를 데려가! 하하하!";
			link.l1 = "개새끼들, 태어난 걸 후회하게 만들어 주마!";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				ReturnOfficer_Longway();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "도살자라고? 나는 차라리 예술가, 화가라고 생각하지. 적어도 예술로 봐주려는 시도라도 해보지 않겠나... 감상해보게.\n내 작품이 마음에 드나? 진정 내 걸작 중 하나라네. 솔직히 말하면, 나는 금발을 더 좋아하지만, 그녀는... 결국 이 흉한 머리색도 용서해줬지. 머리카락 때문만은 아니었어 - 그 아가씨는 불 같았지! 나도 거의 데일 뻔했다네. 그녀는 싸우고, 물고, 야생 동물처럼 으르렁거렸지! 마치 붉은 피부의 야만인을 떠올리게 했어, 오래 가진 않았지만 정말 재미있었지...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "도살자라고? 나는 차라리 예술가, 화가라고 생각하지. 적어도 예술로 봐주려는 시도라도 해보지 않겠나... 잘 보게나.\n아직 그녀와 끝나지 않았어 – 이 캔버스엔 빈 공간이 많이 남아 있지. 그녀는 아름다울 뿐만 아니라, 바위처럼 강인하고 얼음처럼 차가워. 비명을 지르게 하려면 나도 땀을 좀 흘려야 했지. 그녀는 끝까지 버텼어, 내게 그 고운 목소리를 들려주는 기쁨조차 주지 않으려고 말이야.";
			}
			link.l1 = "지금 당장 그녀를 풀어줘, 이 타락한 놈아.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "어딜 가려고 하는 거지? 이 고깃덩어리는 이제 내 소유다. 이 주변의 모든 것처럼, 이 마을도, 이 요새도... 내가 바로 토르투가다. 그리고 너나 푸앵시, 그 썩은 늙은 칠면조 따위가 이 사실을 절대 바꿀 수 없어.";
			link.l1 = "레바쇠르, 너...";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "당신을 위한 분은 드 르네 드 부아뒤플레 드 레트르 나리이십니다.";
			link.l1 = "나는 신경도 안 써. 칼을 뽑아, 네가 진짜 남자와 싸울 때 얼마나 가치 있는지 보여 줘. 힘없는 여자 상대로가 아니라.";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "정말 대단한 분이시군요! 하지만 맞아요, 저도 이런 잡담에 지쳤습니다. 이제... 내 여인에게 돌아가고 싶군요. 하지만 마지막으로 한 가지만 더 묻겠습니다. 어떻게 여기까지 오셨습니까? 이곳의 위치를 누가 알려줬지요? 이걸 아는 사람은 손에 꼽을 정도입니다.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "공통 친구인 마르텐은 밤꾀꼬리처럼 노래를 불렀지. 아니, 사실 도살장에 끌려가는 돼지처럼 비명을 질렀다고 해야 맞겠군...";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "당신에게는 비밀로 하는 게 나을지도 모르겠군요. 당신 자존심이 상할까 두렵거든요, 드 르네 나리... 뭐시기.";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "네 희생자 중 하나다, 르바쇠르.";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "거짓말쟁이, 이 악당아! 이 벽을 넘어서 나가는 자는 없어!";
			link.l1 = "기억을 더듬어 봐, 어서. 한 명 있었지. 창싱.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "말도 안 돼. 그 애는 아니야. 내 생각 중 몇 개는 그 작은 악마한테서 나온 거라구. 어허, 우리 서로한테 많은 걸 가르쳐줬지, 헤헤. 결국 양심의 가책이라도 느끼기로 한 거야? 그럴 리 없지. 어차피 그 애 양심은 내가 오래전에 다 지워버렸으니까!";
			link.l1 = "이제 너를 말라붙을 때까지 새길 거야. 한 방울씩, 천천히.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "그리고 나를 도살자라고 부르나, 비참한 위선자여! 흐흐... 하지만 그 자가 지옥불에 타고 있는 한, 나는 두려울 게 없다.";
			link.l1 = "그가 거기서 당신을 기다리고 있어요. 당신의 그 망할 조카놈도 함께요. 실망시키지 맙시다.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "이 장난감을 좀 더 아프게 해볼까? 배나 목을 그어서, 네가 내려가려 애쓰는 동안 피를 쏟으며 죽어가는 걸 지켜보는 거지...\n";
			link.l1 = "뭐라 하든지, 르바쇠르, 뭐라 하든지... 네 아내가 안부를 전하더군. 그리고 마지막 인사도 함께였지.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "뭐라고?! 카-카... 젠장할 마르셀린... 이 비참한 년, 년, 년, 년!";
			link.l1 = "그렇지. 너희 둘은 서로 어울려. 하지만 그녀가 좀 더 정신이 똑바로 박혔지. 적어도 겉보기엔 그래.\n";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "나는 그년의 닭대가리를 창에 꽂아놓을 거야. 하지만 그 전에... 오-오, 그 창녀한테는 아주, 아주 많은 일이 벌어질 거다.... 내 새 장난감도 잠깐 쉬게 해줘야지. 잠깐! 더 좋은 생각이 났어. 앙리한테 그년을 빌려주지 뭐. 물론 잠시 동안만.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "정말요? 고마워요, 아저씨!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "먼저 자격을 보여 줘야지 - 이것 좀 도와줘, 응?";
			link.l1 = "그는 곧 이성을 잃을 것 같아.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				ReturnOfficer_Longway();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "정의의 섬... 롱웨이가 조의를 표합니다. 저희는 할 수 있는 모든 것을 했습니다.";
			link.l1 = "모두가 아니오, 턱없이 부족하오.";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "롱웨이가 창싱을 찾으러 갈 거야. 나랑 같이 갈래?";
			link.l1 = "그래, 같이 가겠다, 롱웨이. 하지만 기억해라 – 네 여동생도 이 피비린내 나는 광경에 깊이 관여했지. 내가 그녀를 살려줄 마음을 먹으려면, 그녀가 정말 죽을 힘을 다해 설득해야 할 거다. 그리고 넌 그녀를 도와줄 수 없어. 이제 가자, 끝을 볼 시간이야.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			ReturnOfficer_Longway();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "찰스, 내가 알았지, 그치? 네가 올 줄 알았어! 넌 항상 오잖아, 그치?";
					link.l1 = "네 번째는 시험하고 싶지 않아, Mary... 저 악당들, 그놈들은...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "오, 나의 캡틴, 당신이 얼마나 때맞춰 오셨는지 모르실 겁니다. 저... 저 괴물들...";
					link.l1 = "이제 끝났어, 헬렌. 괜찮아, 다 끝났어. 오, 맙소사, 대체 너한테 무슨 짓을 한 거야...";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "찰스, 너 여기 있었구나! 내가 알았지, 내가 알았어, 그치?";
					link.l1 = "난 전속력으로 돛을 올리고 목숨을 걸고 도망쳤어, Mary. 너는... 그들이... 했던 거야?..";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "내 캡틴... 오셨군요... 거의 희망을 잃을 뻔했어요...";
					link.l1 = "최대한 빨리 왔어, 헬렌. 이렇게 오래 걸려서 미안해.";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "아니야, Charles, 아니야. 그놈들이 시도하긴 했지만, 내가 할 수 있는 만큼 저항했어. 그래서 이렇게 심하게 맞은 거야... 제발, Charles, 여기서 나가자... 그치?";
					link.l1 = "바로 하겠습니다, 내 사랑. 마지막으로 할 일이 하나 남았군요.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "그 사람들이 그런 건 아니야, Charles! 아니라고. 나머지는 곧 나을 거야. 제발, 여기서 데려가 줘.";
					link.l1 = "물론이지, 내 사랑. 여기서 해야 할 일이 하나 남았어.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "아니, Charles, 아니야. 놈들이 시도했지만, 당신이 딱 맞춰 도착했어. 그때처럼 말이야. 이런 게 몇 번째지?";
					link.l1 = "난 세지 않았어, Mary. 그리고 앞으로도 절대 셀 생각 없어.";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "여기에... 딱 맞춰 도착하셨군요. 최악의 일은 일어나지 않았습니다. 이제, 제발, 여기서 나갑시다. 어디든 좋아요.";
					link.l1 = "일어나, 헬렌. 위층으로 올라가. 난 먼저 이 썩은 놈부터 처리해야겠어.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "그리고 나는 계속 셀 거야. 이제 이곳을 떠나자, 제발.";
			link.l1 = "물론이지, 내 사랑. 여기서 우리가 할 일은 더 이상 없어. 한 가지만 빼고.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "그래서 뭐야, 카-카, 겁도 없냐, 코흘리개? 네 노란 엉덩이 멧돼지한테 도와달라고 해 보든가...\n아니면 네가 직접 해 봐, 그러면 푸앵시에한테 얼마나 용감했는지 떠벌릴 이유라도 생기겠지.";
				link.l1 = "차라리 네가 얼마나 비겁하고 형편없는 놈이었는지 모두에게 떠벌릴 거다.";
			}
			else
			{
				dialog.text = "뭐야, 정말 내가 피 흘리며 죽는 꼴을 보고 싶다는 거야? 즐기고 있지, 응? 네 여인한테 얼마나 영웅인지 자랑하겠지. 저기 벽에 걸린 해골 보여? 산티아고 은행가의 부인이야... 그 남자도 자기가 영웅인 줄 알았지. 하지만 결국 비명만 잘 지르는 놈이더군 – 내가 그 바퀴에 묶어 돌렸을 때...";
				link.l1 = "네 놈 시체를 그 위에 굴릴 수도 있겠지만, 이 더러운 놈아, 네 엉덩이 무게를 그게 감당 못할까 봐 걱정이군.";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "겁쟁이라고? 오, 카-카, 그만해...\n";
				link.l1 = "잔혹함은 비겁함의 반대가 아니오. 하지만 그대 같은 이는 그 차이를 알지 못하겠지.";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "정말 영리하군. 내 말을 명심해, 드 모르 나리\n너도 그 고위 인사처럼 죽게 될 거야. 네 비명에 목이 쉬고, 네...의 울부짖음에 귀가 멀어서 말이지...";
				link.l1 = "지옥에서 불타라, 쓰레기야.";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "그래, 나는 철학자가 아니라는 건 인정하지. 저 벽에 걸린 해골 보이지, 드 모르? 저건 산티아고 은행가 부인의 남은 전부야. 그 남자도 말은 잘했지. 하지만 내가 그 몸을 바퀴에 감기 시작하자 모든 게 끝났어. 남은 건 비명뿐이었지. 그 소리에 귀가 멀 뻔했다니까...";
			link.l1 = "이제 끝내자.";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "잠깐만요, 나리 선장... 그렇게 서두르지 마십시오.";
			link.l1 = "무슨 일이야, 롱웨이?";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "죽이지 마. 너무 간단해. 저 자식은 더 끔찍한 벌을 받아야 해.";
			link.l1 = "자네는 누이 때문에 화가 났군, 내 친구. 그리고 나는 그자가 저지른 일에 분노하고 있지 " + sStr + "... 그리고 그자가 내 여동생에게 무슨 짓을 했을지. 하지만 나는 그놈처럼 짐승이 아니오. 저 화로의 숯으로 그놈을 지질 수도 있고, 저 바퀴로 뼈를 부러뜨릴 수도 있소... 사슬에 묶어 피를 흘리다 죽게 내버려둘 수도 있지. 하지만 그놈의 부하 중 하나가 그자를 구하는 위험은 감수할 수 없소. 그런 기회는 줄 수 없지.";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "잠시만요, 나리 선장. 제 말뜻은 그게 아닙니다. 저는 푸앵시에 대해 말하고 있었습니다.";
			link.l1 = "그 사람은 어쩌죠?";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "저 동물을 살아서 데려가면 그자가 널 어떻게 보상할지 생각해 봐. 두블룬을 퍼부어 줄 거야. 그리고 저 쓰레기는 캡스터빌의 지하 감옥에서 썩느니 여기서 죽는 걸 택하겠지.";
			link.l1 = "네 말이 맞을 수도 있겠군, 롱웨이. 하지만 이 쓰레기와 슈발리에 사이에 정확히 무슨 일이 있었는지는 나도 몰라. 내 말을 믿어, 난 이 무리들을 너보다 더 잘 안다. 만약 소문대로 돈이 전부라면, 이 둘은 얼마든지 타협할 수 있어. 푸앵시가 그를 풀어줄 수도 있고, 이런 방이 또 다른 섬이나 구세계의 어느 도시에도 생겨날 수 있지.";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "나쁘지 않은 생각이군, 롱웨이. 하지만 슈발리에가 그렇게 관대할 거라곤 생각하지 않아... 그 자의 본성이 아니지. 하지만 나한텐 돈이 중요한 게 아니야. 저 자를 일으켜! 그리고 때가 되기 전에 죽지 않게 상처도 치료해 줘.";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "하지만 먼저, 내가 너를 잡으러 간다. 그리고 네 동료도. 너는 건드리지 않겠다, 눈이 좁은 사내야 – 너는 내 시간조차 아깝다.";
			link.l1 = "보이지, 롱웨이? 이제 이 모든 걸 끝내야 해. 바로 여기서, 지금.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "잠깐만요, 선장님, 잠깐만요, 카-카.";
			link.l1 = "무슨 일이오, 전 총독 나리?";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "내 열쇠가 이 방 어딘가에 있다네.\n그 열쇠는 내 집무실에 있는 상자를 열 수 있지.\n거기엔 은화 이십만과 훌륭한 검이 들어 있다네.\n그걸로 부족하다면, 내 아내의 침실에 있는 서랍장 안에 값비싼 보석들이 모여 있네.";
			link.l1 = "흠, 그럼 대가로 무엇을 원하시오?";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = "총알 한 방이면 돼. 여기서, 지금 끝장내 줘.";
			link.l1 = "드 푸앵시 기사님은 어쩌실 건가요? 당신들이 오래된 친구라고 들었는데... 그분을 만나고 싶지 않으십니까?";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "퐁시 따위는 지옥에나 가라! 그래서, 동의하는 거야 아니야?";
			link.l1 = "사실 그렇지 않습니다, ... 드 나리. 당신의 성함을 전부 말하고 싶지 않군요.";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "그것도 부족해? 좋아, 더 있지...";
			link.l1 = "네 희생자들의 비명이 너를 귀머거리로 만들었겠지, 르바쇠르. 내가 말했잖아, 이건 돈 때문이 아니라고. 네가 푸앵시에를 두려워하는 데는 이유가 있겠지, 응? 그가 너한테 뭘 할지 나는 알고 싶지도 않아. 하지만 그게 네... 예술에 대한 작은 복수가 된다면, 그걸로 충분하다.";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "그래, 그게 네 진짜 모습이군, 카-카... 나랑 다를 게 없잖아.";
			link.l1 = "그만해라. 롱웨이, 저 놈 일으켜!";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) ReturnOfficer_Longway();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "우리 배다... 이렇게 기쁘게 다시 볼 줄은 몰랐어... 그치? 드디어 이 악몽이 끝났네.";
				}
				else
				{
					dialog.text = "드디어 끝났군. 이제 어디로 갈까, Charles?";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "이게 다 끝나다니 믿기지가 않아... 이제 우리는 어떻게 해야 하죠, 내 캡틴?";
				}
				else
				{
					dialog.text = "자, 이제 끝났어요, 내 캡틴. 이제 어떻게 할까요?";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "아직 끝나지 않았소. 창싱... 내가 그녀에게서 답을 얻기 전까지 이 이야기는 진정 끝나지 않소.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "캡스터빌로 향한다. 이제 르바쇠르 나리가 역사의 일부가 될 시간이야.";
				}
				else
				{
					link.l1 = "슈발리에의 임무는 끝났다. 이제 그에게 보고해야 한다. 하지만 몇몇 세부 사항은 빼고 말할 생각이다. 그가 약속을 지켜 미셸이 풀려나기만을 바랄 뿐이다...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "나도 그래, 그치? 그러니까 나도 같이 갈 거야. 그리고 나랑 말싸움하려고도 하지 마, Charles.";
				link.l1 = "Mary, 얘야, 좀 쉬어야 해. 지금 당장이라도 쓰러질 것 같아...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "함께 가겠습니다.";
				link.l1 = "헬렌, 그 악마에게 거의 죽을 뻔했어. 지금 제대로 서 있기도 힘들잖아...";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "네가 필요해, Charles. 그리고 너도 내가 필요하지. 오늘 밤 기절할 사람이 있다면, 그건 Chang Xing이야. 그녀의 창관 바닥에서, 두 눈 사이에 총알을 박고!";
				link.l1 = "그래, 르바쇠르가 네 투지를 꺾진 못했구나. 널 배로 돌려보내고 싶지만, 어차피 또 따라올 거라는 거 알아...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "하지만 아직 칼을 쥘 수 있어. Charles, 나는 꼭 거기 있어야 해. 그녀가 왜 그런 일을 저질렀는지 알아야겠어. 왜 이게 내게 그렇게 중요한지 이해하겠나?";
				link.l1 = "쉬고 치유가 필요하다는 것, 이해합니다. 그것도 오래 걸릴 거라는 것도요.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "넌 나를 너무 잘 아는구나, Charles, 그치? 그러니까 잡담은 그만두고 끝내자.";
				link.l1 = "네 뜻대로 하시오. 하지만 방심하지 마시오. 저 밖에 무슨 일이 기다리고 있을지 아무도 모릅니다.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "급할 것 없어. 네가 날 찾아왔으니, 이제 내가 너와 함께 갈 거야. 네가 원하든 원하지 않든.";
				link.l1 = "아직도 배짱이 남아 있군, 헬렌. 좋아. 내 뒤에 붙어 있어, 제발 조심해.";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "우리 배... 다시 타게 될 줄은 정말 믿기지 않아, 그치...";
					link.l1 = "메리가 오길 기다리고 있어. 푸짐한 식사랑 푹신한 침대도 준비되어 있지...\n";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "으윽... 내 두 발로 배까지 올 수 있을 거라곤 생각도 못 했소.";
					link.l1 = "내가 아는 사람 중에 가장 강인한 사람이야, 헬렌. 이제 안으로 들어가서 쉬어...\n";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "우리 배... 다시 타게 될 줄은 믿기지 않아, 그치...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "으윽... 내 두 발로 배까지 갈 수 있을 거라곤 생각도 못 했소.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "캡스터빌로 향하라. 이제 르바쇠르 나리가 역사의 일부가 될 시간이야.";
				}
				else
				{
					link.l1 = "슈발리에의 임무는 끝났다. 이제 그에게 보고해야 한다.\n하지만 몇몇 세부 사항은 빼고 말할 생각이다.\n그가 약속을 지켜 미셸이 풀려나기만을 바랄 뿐이다...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "그리고 너, Charles... 왜 그런 표정이야? 또 뭔가 꾸미고 있지, 그렇지?";
				link.l1 = "창싱. 나도 그녀에게 가야 해.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "그쪽은? 어디로 가는 거요?";
				link.l1 = "창싱을 만나러 가야지. 그녀가 이 악몽의 마지막 장이야.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "그럼 나도 같이 갈게! 걔 나한테 진 빚이 크거든, 그치!";
				link.l1 = "Mary, 얘야, 너 겨우 배까지 왔잖아. 지금은 칼도 제대로 못 쥐잖아. 네게 그런 짓을 한 그년, 내가 반드시 대가를 치르게 할 거야, 맹세코. 하지만 네가 배에 남아 안전하다는 걸 알면 난 훨씬 마음이 놓일 거야.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "내 캡틴, 정말 당신과 함께 가고 싶어요... 제발 조심해요. 그녀가 또 무슨 짓을 할지 아무도 모르잖아요? 그녀가 날 붙잡고 있었어요, 그 강아지 같은 Thibaut가...";
				link.l1 = "최악의 순간은 지났어, 헬렌. 곧 모든 게 끝날 거야, 약속할게.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "그래도 내가 없을 때 롱웨이가 네 등을 지켜줄 거야. 하지만 네게 무슨 일이라도 생기면, 롱웨이랑 창싱 둘 다 내가 직접 땅에 묻어버릴 거야!";
					link.l1 = "괜찮을 거야. 이제 가서 쉬어. 금방 돌아올 테니까.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "롱웨이는 어디로 갔지, 찰스?";
					link.l1 = "그는 나 없이 장싱을 쫓아갔어. 내가 막을 수 없었지, 하지만 내가 뭘 할 수 있었겠어?";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "그래도 롱웨이가 함께 가니까. 그나마 위안이 되네, 그치?";
					link.l1 = "봤지? 걱정할 필요 없어. 금방 다녀올게.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "롱웨이는 어디 있지? 지금 보니 여기 없네.";
					link.l1 = "그는 나 없이 자기 누이에게 갔어. 나는 그를 탓하지 않아. 이 순간을 너무 오래 기다렸으니까.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, 왠지 불길한 예감이 들어...";
				link.l1 = "알고 있습니다. 이 악몽은 너무 오래 계속되었고, 이제 끝이 가까워졌습니다. 최악은 지났습니다.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "그 자가 무슨 생각을 하는지 누가 알겠어, Charles? 눈 똑바로 뜨고 있어, 그치?";
				link.l1 = "알겠어. 곧 돌아올게, 헬렌."
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "무슨 일이 닥쳐도 준비할 거라고 약속해.";
			link.l1 = "나는 그래, 그리고 앞으로도 그럴 거야. 곧 돌아올게, Mary.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Helen");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "롱웨이가 도왔소, 선장 나리. 이제는 나리의 약속을 지킬 차례요.";
			link.l1 = "다 들었지, 롱웨이. 네 누이에게 가 보자.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "정의의 섬, 롱웨이에게 마지막 부탁이 있습니다: 창싱이 직접 해명할 수 있게 해주십시오. 어떤 결정을 내리기 전에 그녀의 말을 들어주십시오.";
			link.l1 = "무슨 일이 있었지 " + sStr + " 그녀에게 있다. 하지만 먼저 해명할 기회를 주겠소.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "롱웨이는 당신의 말과 판단, 그리고 친절을 믿습니다.";
			link.l1 = "이봐, 이 피비린내 나는 난장판엔 이성이나 자비 따윈 들어설 자리가 없어. 이제 끝낼 때가 됐지.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "나리 선장...";
				link.l1 = + sStr + " 죽었어.";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "선장님, 아가씨 " + sStr + ", 만나서 반갑소. 이쪽은... 창싱이오.";
					link.l1 = "짐작했네, 롱웨이. 비켜 있어. 자네는 동생과 충분히 이야기할 시간을 가졌지. 이제 그녀는 대답해야 하네\n " + sStr + " 르바쇠르의 하수인들이 그녀를 납치하도록 도운 죄로.";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "오셨군... 숙녀는 어디에 " + sStr + "? 그녀가...?";
					link.l1 = "아니야, 롱웨이. 신께 감사하게도, 아니야. 내가 그녀를 배로 데려갔어. 그렇지 않았다면 지금 이렇게 대화조차 못 하고 있을 거야. 하지만, 그래도 쉽거나 유쾌하진 않을 거야.";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "창싱과 저는 애도를 표합니다...";
			link.l1 = "창싱의 조의를 전한다고?! 그럴 바엔 차라리 르바쇠르의 이름으로 조의를 전하지, 롱웨이! 네가 그녀가 납치에 가담했다는 걸 아주 잘 알잖아\n " + sStr + " 다른 놈들, 그의 졸개들과 함께! 그리고 이제 그녀는 사라졌어...!";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "저희.. 아니, 저는 지금 주인님 선장께서 어떤 기분이신지 이해합니다.";
			link.l1 = "오, 정말인가?";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "나는 부모님을 잃었어, 기억하지? 아니, 기억하고 있다면 말이야. 게다가, 고문하고 죽인 건 창싱이 아니었어\n " + sStr + ". 당신의 고통과 분노를 이해합니다. 하지만 제 여동생의 죄는 당신이 생각하는 것만큼 크지 않습니다. 제 말 좀 들어주세요.";
			link.l1 = "기억나. 네 이야기를 들어줄게. 하지만 빨리 말해! 그리고 이런 일은 그냥 넘어갈 수 없다는 걸 알아둬!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "그럼 다시 전부 말씀드려야겠군요, 드 모르 나리. 우리 투는 불어를 너무 못해서, 거의 공격당할 뻔했으니까요.";
			link.l1 = "입 다물었어야 했어. 난 롱웨이를 공격할 생각 없었지만, 너는... 그녀의 죽음에 책임이 있는 건 바로 너야.";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "그 말에 반박하고 싶지만, 굳이 그러고 싶진 않군. 투는 당신을 존경과 이해심이 있는 분이라고 말했지. 하지만 정말 그런가? 내가 말을 시작하는 게 의미가 있을까? 아니면 이미 결정을 내린 건가?\n";
			link.l1 = "누군가의 머릿속에 들어가는 법을 아시는군요, 마드모아젤. 지금은 정말로 말다툼할 가치도 없습니다. 하지만 변명이라도 해보고 싶으시다면... 좋아요, 해보세요. 롱웨이를 위해서라도 들어드리겠습니다.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "그녀가 모든 걸 설명할 수 있습니다, 나리 선장님... 당신이 생각하는 그런 게 아닙니다... 정말로 그렇지 않습니다...";
			link.l1 = "그럼 설명해 보시오. 하지만 나에게 말하지 마시오. " + sStr + ". 그녀의 눈을 바라봐. 그녀의 멍과 상처를 봐. 그리고 그렇게 아니었다고 말해 봐.";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "싱을 대신해 사과드립니다, 선장님...";
			link.l1 = "그녀의 비웃는 얼굴을 보니, 헛수고하고 계십니다. 그녀는 사과받을 자격조차 없습니다.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "너무 심하게 구시네요, 드 모르 나리. 뭐, 저런 식으로 대하는 데 익숙하신가 보죠 – 흔한 누런 피부의 일꾼 취급하듯이 말입니다.";
			link.l1 = "롱웨이를 내게서 떼어놓으려는 건가? 소용없어. 나는 언제나 그를 존중해왔고, 그는 그 사실을 잘 알고 있지. 그게 전부야. 이제 남은 건 이런 장난질뿐이란 걸 나도 알아.";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "뭘 하려고 하는 거요? 불쌍한 투를 가족에게서 또 데려가려는 거요? 그가 십 년 만에 겨우 가족을 다시 찾았는데?";
			link.l1 = "피가 항상 가족을 만드는 건 아니지. 하지만, 우리가 뭘 해야 한다고 제안하나? 당신이 한 짓을 그냥 두라는 건가? " + sStr + " 벌을 받지 않고 넘어가라고? 그리고 롱웨이가 아무렇지 않게 다른 여자들을 사고파는 여자를 가끔씩 찾아가게 하라고?";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "자, 우선 들어봐. 저 사람과는 달리, 나는 방금 그에게 한 이야기를 완벽한 프랑스어로 다시 말할 수 있지. 내 이야기야. 네 눈을 똑바로 바라보면서, 아니면 그녀의 눈을 바라보면서도 말이야. 그리고 네가 이제 지긋지긋하게 느끼는 그 억양 하나 없이 말이지. 결국, 우리 모두 잃을 게 뭐가 있겠어?\n";
			link.l1 = "난 롱웨이의 억양에 익숙해. 그게 내게는 그 사람의 일부야. 네 말을 듣겠지만, 내 친구를 위해서일 뿐이야. 계속 말해.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "왜 안 되겠습니까, 나의 주군 선장님...?";
			link.l1 = "정말 물어봐야 합니까? 그녀는 납치에 가담했소\n " + sStr + ", 그렇지 않았나?";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "저... 진심으로 사과드립니다. 십 년 전 제 여동생을 지키지 못하고, 이런 일에서 구해내지 못한 것도 제 잘못입니다.";
			link.l1 = "조금의 후회도 없는 자들을 대신해 사과할 필요 없어, 롱웨이. 여기서 할 일 끝났어? 이제 내가 그녀와 이야기할 차례야.";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "나리 선장, 잠깐만요! 창싱은 르바쇠르와는 달라요. 완전히는 아니지만. 그녀는 지난 10년 동안의 삶을 내게 말해줄 거예요. 나도 당신께 이야기하게 해주세요.";
			link.l1 = "좋아, 롱웨이. 듣고 있네. 자네가 무슨 말을 하느냐에 따라 많은 것이 달려 있어.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "네가 말하면 우리 모두 머리가 아플 거야. 내가 할게, 투. 샤를 드 모르, 맞지?";
			link.l1 = "그래. 그리고 너는 벨 에투알, 창싱이라고도 불리지. 너도 티보와 마르텐과 함께 내 사랑을 납치하는 데 한몫했지. 내가 그 얘기를 꺼내니 웃는구나. 좋은 추억이라도 되는 거냐?\n";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "부정하는 건 어리석지. 하지만 그래서 뭐? 이제 와서 나를 내 오빠 앞에서 고문이라도 하겠다는 거야? 아니면 그에게 나를 고문하는 걸 도우라고 시키겠다는 거야? 아니면 그냥 날 죽이겠다는 거야? 정말 그에게 그런 짓을 하겠어?";
			link.l1 = "아까 말했듯이, 지금 당장 내가 하고 싶은 게 많아도 아직 너랑 말하고 있어. 더 이상 건드리지 마. 그에게 했던 말을 나한테도 해. 그 다음에 우리가 어떻게 될지 보자고.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "아직도 창싱이 이렇게 변할 줄은 믿기지 않아.";
				link.l1 = "사람은 변하지, 롱웨이. 누구든 부서질 수 있고, 마지막 남은 친절과 믿음조차 완전히 지워질 수 있어.";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "롱웨이는 아직도 내 누이가 이렇게 변했다는 걸 믿을 수 없어... 왜... 왜지? 그날 내가 집에만 있었더라면...";
				link.l1 = "만약에 대해 자책하지 마. 그리고, 그 오랜 세월 동안 가만히 있었던 것도 아니잖아 – 정말 미친 듯이 모든 걸 바로잡으려고 애썼지.";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "에... 세상사가 원래 그런 거지요, 나리 선장님.";
			link.l1 = "여기서 나가자. 그녀가 남긴 엉망진창을 아직 치워야 하고, 또 구해야 해\n " + sStr + " 가능한 한 빨리.";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "그래. 서둘러야 해 - 내 탓에 이미 너무 오래 지체됐으니까.";
			link.l1 = "네 잘못이 아니야, 롱웨이. 서두르자!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "알겠습니다. 지원해 주셔서 감사합니다, 나리 선장님.";
			link.l1 = "별말씀을. 그녀는 애초에 네가 그토록 헌신할 자격조차 없었어\n찾으려 했던 것도 네가 아니라 그녀였어야 했지, 기회가 있었음에도 말이야\n네 별은 오래전에 꺼졌고, 그녀는 이미 오래전에 네 가족이 아니게 되었어\n이제 우리가 네 가족이야, 롱웨이.";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "그래... 그렇군. 그리고 나는 지금까지 너무 눈이 멀어 아무것도 보지 못했지.";
			link.l1 = "늦더라도 안 오는 것보단 낫지. 이제 집으로 가자 - 우리 배가 우리를 기다리고 있어.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "좋아. 내가 이걸 얼마나 원했는지 너는 모를 거야.";
			link.l1 = "그렇다고 생각해. 기분이 어때, Mary? 내가 유혈 사태를 피하고 싶었던 이유는 네가 평소처럼 검을 단단히 쥘 수 있을지 확신이 없었기 때문이야. 내가 다른 놈과 싸우는 동안 한 놈이 우위를 점할 수도 있었으니까.";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "너 나를 얕잡아보는구나. 게다가 분노란 참으로 지독한 약이지. 네가 날 구하러 달려올 거라는 건 의심도 안 했어, 항상 그랬으니까, 그치? 있잖아, Charles... 네가 나를 붉은 부적이라고 부르지만, 혹시 너도 내 부적일 수 있지 않을까? 우리 둘이 함께 있으면 항상 뭔가 놀라운 일이 일어나잖아.";
			link.l1 = "제가 당신의 부적이라고요? 오, 그거 마음에 드네요.";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "거 봐, 벌써 웃고 있잖아! 이제 이 역겨운 데서 나가자—얼른, 빨리빨리, 그치?";
			link.l1 = "에헤, 이 엉망진창이 나를 제대로 강타했군. 다른 식으로 끝났으면 좋았을 텐데.";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "나는 아니야. 그녀를 구할 방법은 없었어, Charles. 그리고 그녀는 Longway까지 끌어들였지. 그는 자기 선택을 했고, 우리에게는 선택지가 남지 않았어. 오늘 우리가 도운 모든 사람들을 생각해 봐.";
			link.l1 = "또다시, 나는 네 말에 반박할 게 없어, Mary. 그리고 이번엔, 반박하고 싶지도 않구나. 이리 오너라, 나의 붉은 부적아...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "거기서 무슨 일이 있었던 겁니까, 나리? 욕설과 고함 소리가 들렸습니다. 하지만 끝날 때까지 감히 도움을 부르지 못했습니다.";
				link.l1 = "당연한 일이지. 너희 주인 여자는 죽었으니, 이제 자유다. 내라면 이 집 금고를 챙겨서 나눠 가진 다음, 최대한 빨리 이 섬에서 도망치겠다. 너희는 단순한 창녀가 아니라 명예로운 숙녀들이란 걸 아니까, 이 비참한 곳을 벗어나도 미래가 있을 것이다.";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "오, 당신이군요, 나리. 여주인께서 언제 내려오시는지 아십니까?";
				link.l1 = "곧 오지 않을 거야. 그리고 나라면 문에서 좀 떨어져 있을 거다. 오늘 밤 일에 대해 그녀에게 절대 말하지 마. 그녀는 아무것도 말하지 않을 거고, 쓸데없이 참견하는 고양이는 한순간에 목숨을 잃지. 네 마님은 자기 비밀을 캐묻는 걸 아주 싫어하는 것 같군.";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "네가 그녀를 죽였나?!";
			link.l1 = "내가 그랬다. 그리고 네가 머뭇거리거나 경비를 부르려 든다면, 그게 네 인생 최대의 실수가 될 거다. 그녀는 너희에게 결코 수호성인이 아니었지 – 아무리 비단과 교육을 줬다 해도, 너희는 이곳에 갇혀 있었고, 그녀가 손가락질하는 족족 아무 놈에게나 몸을 내주도록 강요당했으니까. 여기서 빠져나갈 수 있길 바란다. 행운을 빈다, 숙녀 여러분.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "그 여자는 정말 괜찮은가? 우리가 들어가도 되나? 경비병을 불러야 하나?";
			link.l1 = "그 여자는 절대 괜찮아지지 않아. 직접 물어볼 수는 있겠지... 네가 위험을 감수한다면 말이야.\n아직도 오빠랑 얘기하고 있어. 그리고 내가 보기엔, 방해받는 걸 그 둘이 달가워하지 않을 거야.";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "알겠습니다... 그럼, 나중에 또 찾아오십시오, 나리.";
			link.l1 = "절대 안 돼. 안녕히 계십시오, 숙녀 여러분.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "멈춰라! 마드모아젤 에투알의 집에서 비명과 싸움이 있었다는 신고가 들어왔다. 경비대는 네가 그 일과 관련이 있다고 생각한다. 무기를 내려놓고 우리를 따라오시오, 나리.";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "맞아, 하지만 우리가 싸움을 시작한 건 아니었지, 끝낸 거야. 고용된 깡패들이 임금이 늦게 지급된 것 때문에 반란을 일으켜 에투알 부인을 공격해서 약탈하려 했어. 용병을 믿다니, 그치? 우리가 이기긴 했지만, 안타깝게도 그녀는 살아남지 못했어.";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "오늘 내 인생의 사랑을 잃었으니, 길을 비켜 주시오, 경관.";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "당신 말만 믿고 넘어갈 수는 없다는 거 알죠? 우리가 당신을 구금해야 해요. 그리고 여성 직원들 중에서 증인도 필요해요. 그들이 뭐라고 하는지 들어봅시다.";
			link.l1 = "내 사랑하는 사람이 크게 다쳤어. 나도 완전히 지쳤고. 제발 우리 좀 그냥 보내주면 안 돼?";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "우리가 최대한 빨리 이 문제를 해결해 보겠다. 이제 우리를 따라오시오.";
			link.l1 = "지옥에나 떨어져라...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "조의를 표합니다, 나리. 그리고 저는 아직 장교가 아니지만... 아무튼, 됐습니다. 우리와 함께 가서 거기서 무슨 일이 있었는지 말씀해 주시겠습니까?";
			link.l1 = "말해주지. 그 사창가는 돈을 잃고 있었고, 용병들에게 줄 현금도 남지 않았어. 그래서 놈들은 남은 걸 다 챙기기로 했지, 내가 마침 거기 있었을 때 말이야. 마담 에투알과 나는 놈들을 물리쳤지만, 그녀는 상처 때문에 죽었어. 이제, 제발 나를 지나가게 해줘.";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "저도 그러고 싶지만, 처리해야 할 서류가 아주 많습니다. 그리고 거기서 일하는 숙녀분들도 면담해야 하죠. 진실을 말씀하신다 해도, 나리, 최소 하루는 이 도시에 머무르셔야 할 것 같습니다.";
			link.l1 = "지옥에나 떨어져라...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "롱웨이가 당신께 드릴 것이 있습니다, 나리 선장님.";
			link.l1 = "정말 아름답고 기이하군요. 이런 건 처음 봐요. 이게 뭐죠?";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "이건 내 고향의 선장 부적이오. 그리고 이제 롱웨이가 더 이상 선장이 아니니, 당신께 드리겠소.";
			link.l1 = "고마워, 롱웨이. 반 데르 빈크가 죽으면서 네가 원하던 모든 복수를 이뤘지. 이렇게 끝나서 다행이야.";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "다시 한 번 싱이 좋은 사람이 되도록 설득할 수만 있다면...";
			link.l1 = "이제 그녀는 누구의 말도 듣지 않았을 거요, 자기 오라비의 말조차도. \n당신은 할 수 있는 최선을 다했소. 우리 모두가 그랬지.";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "예... 정말 감사합니다, 나리 선장님. 롱웨이는 이제 자유롭고, 다시 집과 친구를 가지게 되었소.";
			link.l1 = "천만에, 내 친구. 이제 나와 함께 내 형을 만나러 가지 않겠나. 아, 이 얼마나 아이러니한 일인가!";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			chrDisableReloadToLocation = false;
			ReturnOfficer_Longway();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "또 만났군, 프랑수아. 인생이 너를 많이 깎아먹은 것 같아, 헤헤.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "퐁시, 이 탐욕스러운 자식... 네 금고에 금이 가득 차서 거의 숨이 막힐 지경인데도 아직도 만족 못 하겠냐?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "프랑수아, 너에게도 좀 나눠줄게. 충분할 거야, 믿어.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "뭐... 무슨 뜻이오?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "총독 나리, 정말 그렇게 하실 건가요...";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "Charles, 내 친구, 자네는 할 일을 훌륭하게 해냈네! 이 자에게 앞으로 무슨 일이 일어나든 자네가 신경 쓸 필요는 없지... 하지만, 선장, 혹시라도 자네 똑똑한 머리에 언젠가 멍청한 생각이 들까 봐 미리 알려두는 게 좋겠군. 우리 공동의 친구에게는, 비유하자면, 심각한 소화불량이 기다리고 있지. 금은 위장에 좋지 않다고 들었네... 더 설명할 필요는 없겠지.";
			link.l1 = "아니요, 총독 나리.";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "프랑수아 나리와는 달리, 샤를 당신 앞에는 위대한 미래가 기다리고 있소. 얘들아, 저 돼지를 감옥에 쳐넣어라!";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "손 떼, 이 개자식들아! 만족하냐, 드 모르?! 엿 먹어라! 너희 둘 다 나랑 똑같이 지옥에서, 같은 프라이팬에 타 죽을 거다!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Kasper";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Sharp";
			dialog.text = "글쎄요, 나리. 아가씨를 살펴봤습니다\n " + sStr + "...";
			link.l1 = "얼마나 심각합니까, Raymond?";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "걱정할 것 없습니다, 선장님. 물론 Mary가 크게 다쳤지만, 전반적으로는 다 괜찮을 겁니다.\n며칠은 침대에 누워 있어야겠지만, 2주쯤 지나면 다시 움직일 수 있을 겁니다.";
					link.l1 = "알겠다. 고맙다, Raymond. 물러가도 된다.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Mary가 꽤 심하게 당했습니다, 선장님. 멍, 상처... 그리고 무엇보다도 그 모든 충격까지요. 물론 Mary는 내색하지 않으려 애쓰고 있지만요.";
					link.l1 = "항상 그렇듯이 강한 척하고 있군요. 하지만 이제는 침대에 누워 쉬는 게 낫다는 걸 본인도 아는 것 같습니다.\n그런데 얼마나 오래 그렇게 지낼 수 있을까요?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "프로 군인이라도 그녀가 겪은 일을 버티기 힘들었을 겁니다, 선장님. 삠, 염좌, 타박상... 저 놈들이 뼈를 부러뜨리지 않은 것만도 다행입니다. 하지만 힘줄이 손상되어서, 적어도 한 달은 칼을 쥘 수 없을 겁니다.";
					link.l1 = "칼은 집어치워. 그녀는 언제쯤 두 발로 설 수 있겠어?";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "걱정 마십시오, 선장님. 헬렌이 다치긴 했지만 심각하지 않습니다. 당분간은 침대에 누워 있어야 하겠지만, 몇 주면 완전히 회복할 것 같습니다.";
					link.l1 = "알겠다. 고맙다, Raymond. 물러가라.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "상당히 심하게 다쳤습니다, 선장님. 그리고 육체적인 부상은 진단의 일부에 불과합니다... 그 끔찍한 곳에 있으면서 아르부투스에서 겪었던 악몽이 떠올랐던 모양입니다.";
					link.l1 = "물론이지... 젠장! 그녀는 언제 다시 일어설 수 있지?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "헬렌은 정말 칼날 위를 걷는 듯했소, 선장. 그 모든 일을 겪고도 살아남았다니 놀랍군요. 내부 열상이나 골절은 없지만, 염좌와 근육 손상은 많소.";
					link.l1 = "불쌍한 아이로군. 그녀가 회복하는 데 얼마나 걸릴까요?";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "적어도 일주일은 걸립니다, 나리. 제 권고를 따르면 한 달쯤 후에는 다시 움직일 수 있을 겁니다.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "이주일은 더 지나야 합니다, 나리. 그 후에는 쿼터데크에서 잠깐 산책을 허락하겠습니다. 완전히 회복하려면 최소 두 달은 걸릴 겁니다.";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "적어도 일주일은 그녀를 건드리지 마시오, 나리. 완전히 회복하려면 한 달쯤 걸릴 것이오.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "그녀는 보름 동안 침대에 누워 있어야 합니다; 그 후에야 갑판을 돌아다닐 수 있을 겁니다.\n하지만 적어도 두 달은 다시 움직이는 모습을 기대하지 마십시오.";
				}
			}
			link.l1 = "알겠다. 고맙다, Raymond. 물러나도 된다.";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "오랫동안 누워 있다가 혼자 일어서는 게 생각보다 더 힘들구나, 그치!";
				link.l1 = "갑자기 침상에서 일어나는 건 좀 무리일지도 몰라, 자기야.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "오오, 머리가...";
				link.l1 = "헬렌! 좀 일찍 일어난 거 아니야? 거의 못 서 있잖아!";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "차라리 이 피투성이 침대를 다시 눕기보단 불태워버리겠어 - 적어도 뱃머리에서 선미까지, 그리고 다시 돌아올 때까지는 말이야!";
				link.l1 = "아주 편안한 침대네. 그리고 이 배도 나쁘지 않아. 그러니 널 막진 않을 거야. 하지만 내가 곁에 있을 거야, 네가 어리석은 짓 안 하도록.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "괜찮습니다, 선장님, 하지만 완전히는 아닙니다. 아직 칼을 휘두를 준비는 안 됐지만, 이 침대가 정말 지긋지긋하게 싫습니다.";
				link.l1 = "음, 갑판 위를 잠깐 걷는 건 아마 괜찮을 거야. 하지만 밧줄 근처에는 절대 가지 마!";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "샤를, 나를 완전히 잊은 거 아니야? 우리가 마지막으로 함께 잠자리를 한 게 언제였는지 상기시켜 줘, 그치!";
				link.l1 = "이전에... 그 얘기는 하지 말자, 그치, Mary?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "내 캡틴, 내가 여자로서 더 이상 흥미롭지 않은가요?";
				link.l1 = "그건 뜻밖이네, 헬렌. 보통은 내가 먼저 그런 얘길 꺼내는데... 하지만 네가 그 일 이후로 준비가 됐는지 확신이 없었어...";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "그럼 적어도 내 얘기라도 해 줘, 그치? 아니면 그 두 놈한테 얻어맞고 나서 내가 싫어졌어?";
				link.l1 = "내가 들어본 것 중에 그게 제일 멍청한 소리야. 나는 그냥 네가 준비될 때까지 방해하고 싶지 않았을 뿐이야. 그리고 이제 네가 준비됐으니...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "괜찮아, Charles, 정말이야. 그냥 그 일은 생각하지 않으려고 해. 그리고 무엇보다, 네가 제일 끔찍한 순간에서 날 구해줬잖아. 그러니까 이제 그만 얘기하고... 그냥 같이 있어 주자.";
				link.l1 = "그거 정말 좋은 생각이야, Helen.";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "Charles, 난 원하지 않아, 요구하는 거야, 그치!";
				link.l1 = "감히 거절할 수 없지...";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "찰스, 우리 얘기 좀 해야 해, 그치.";
				link.l1 = "무슨 일 있어, Mary? 꽤 불안해 보이는데, 그럴 때면 보통 좋은 일이 아니잖아.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "내 캡틴, 드릴 말씀이 있어요.";
				link.l1 = "그래, 헬렌? 듣고 있네.";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "그게 바로 그거야! 내가 장교로서 임무에 복귀할 준비가 됐다는 게 좋은 일 아니야?";
				link.l1 = "그렇군요. 좋아요, My Lord Captain. 힘이 충분하다고 느낀다면, 그건 좋은 정도가 아니라 정말 훌륭한 일입니다.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "선원들이 나를 힘없는 늙은 여자처럼 쳐다보는 게 지겨워. 다시 키를 잡고 칼을 휘두르며 팔을 좀 풀고 싶어...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "할 수 있겠다면, 난 반대하지 않을게, 자기야. 네 장비 가져올게. 그리고 기꺼이 네가 키를 잡게 해줄게. 하지만 싸울 땐 조심해, 그치?";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "헬렌, 다리에서 당신이 없으니 모두들 허전해했소. 그리고 그 칼은, 이제 돌려줄 때가 된 것 같군.";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "물론이지요, My Captain, 말씀하시는 대로 하겠습니다.";
			link.l1 = "좋소.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "멋져, 그치? 빨리 칼로 연습해보고 싶어...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "좋은 소식이네, Mary. 하지만 아직은 너무 앞서 나가지 마... 아니, 내가 이런 말을 해도 소용없겠지?";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "그 팔라쉬가 다시 칼집에 들어가는 걸 보면 기쁘시겠지요, My Lord Captain...";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "저... 무슨 말을 해야 할지 모르겠어요, Charles. 이 커틀라스가 나에게 얼마나 큰 의미인지 이제야 깨달았어요...";
				link.l1 = "나는 그걸 오래전에 알았소, 그래서 그것이 당신을 위해 무사히 기다리고 있었던 것이오.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Gave Cutlass of Blaze", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "내 나르왈이야, 그치!!! Charles, 네가 구해줬어! 그냥 기쁜 게 아니라, 완전 신나! 고마워, 정말 고마워! Martin의 배에 두고 온 줄 알고 얼마나 걱정했는지 몰라...";
				link.l1 = "이 검은 네 손에 있어야 해, 내 붉은 부적. 다시는 잃어버리지 않으리라 믿는다... 뭐, 네 재회의 길을 막지는 않겠어, 하하!";
				notification("Gave Narwhal", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "고마워, Charles. 있지, 아마 그래서 내가 너를 사랑하는 걸 거야...";
				link.l1 = "잃어버린 것을 되찾아 준다고? 하하하하...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "너는 웃고 있지만, 나는 진심이야.";
			link.l1 = "알아, 헬렌. 나도 너를 사랑해, 아직 왜 그런지는 잘 모르겠지만.";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "아직 이 커틀라스를 너한테 안 써서 그런가 보군.";
			link.l1 = "난 그걸 피해서 보트 쪽으로 갈 거야. 거기서 기다릴게, 헬렌.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
} 