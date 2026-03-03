void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
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
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니야.";
			link.l1.go = "exit";
		break;

		case "Naemnik":
			dialog.text = "잘하네"+GetSexPhrase("","ess")+"... 존나 끝내주지"+GetSexPhrase("","ess")+". 하지만 일을 끝내기 전에 내 말 좀 들어봐. 내가 할 말이 분명 자네에게 흥미로울 거야.";
			link.l1 = "죽기 전에 유언이라도 할 수 있겠지. 하지만 기대하지 마라. 이 동굴에서 나갈 수는 없으니까.";
			link.l1.go = "Naemnik_2";
		break;

		case "Naemnik_2":
			dialog.text = "항구 책임자라니, 뭐? 내 목 따러 너를 보냈다는 거야?";
			link.l1 = "여전히 눈치가 빠르군.";
			link.l1.go = "Naemnik_3";
		break;

		case "Naemnik_3":
			dialog.text = "그가 너를 내게 보낸 건, 날 죽이려고 그런 거지? 찾으라고도, 붙잡으라고도 아니고 — 죽이라고.";
			link.l1 = "맞아. 그래서 뭐?";
			link.l1.go = "Naemnik_4";
		break;

		case "Naemnik_4":
			dialog.text = "하... 너 정말 "+GetSexPhrase("멍청이","작은 바보")+". 너는 왜 그 자가 내가 감옥에서 썩는 것보다 죽는 걸 더 중요하게 여겼는지 한 번이라도 생각해 본 적 있나? 아니지? 네가 구하려는 사람이 누구인지 전혀 모르는군. 그 선창가의 거미가 이곳 전체에 거짓의 거미줄을 쳐놨고, 그리고 너는, \n "+GetSexPhrase("소년","여보")+", 그놈은 거기에 깊이 빠져 있지.\n그자가 정직한 관리라고 생각하나? 하! 그놈이 정직을 꿈꾸는 건 잠잘 때뿐이야. 해적들이랑 네덜란드 놈들한테 정보를 팔아먹지. 믿는 사람들을 배신하고 말이야. 저런 쥐새끼는 땅속에나 들어가야 해!";
			link.l1 = "그리고 누구나 신발에 흙 좀 묻히고 다니지. 너도 수도승처럼은 안 보이는데.";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "나는 수도사가 아니고, 그런 척하지도 않아. 내 칼은 거짓말을 하지 않지. 한 번만 봐도, 놈은 죽음이 찾아왔다는 걸 알아. 나는 내 먹잇감에게 미소 짓지도, 이미 끝장난 걸 알면서 악수하지도 않아. 아니. 내 의도는 분명하지. 그 관료 말인가?\n자기를 믿는 모든 사람을 배신하면서도 도와주는 척하지. 내가 무덤에 보낸 어떤 개자식보다도 더 나쁜 놈이야.";
			link.l1 = "네 말이 사실이라고 치자. 누가 너를 고용했지?";
			link.l1.go = "Naemnik_6";
		break;

		case "Naemnik_6":
			dialog.text = "이름은 안 알려주겠어 – 나도 몰라. 하지만 그 쓰레기한테 피해를 입은 사람이야. 정의를 원하거나... 아니면 복수를 원하는 남자지. 뭐라 부르든 상관없어. 그 썩은 관리놈의 목값으로 500두블론이 걸려 있어! 나를 도와주면, 돈은 반씩 나누자.";
			link.l1 = "네 말은 이제 그만! 네 목숨을 구하려고 무슨 말이든 하겠지. 말할 기회는 줬으니, 이제 죽을 차례다.";
			link.l1.go = "Naemnik_7";
			link.l2 = "좋은 이야기군. 하지만 그냥은 믿지 않겠어. 네 말 말고 다른 게 있나? 증거나 증인이라도? 아니면 이게 또 죽음을 속이려는 수작이냐?";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "이 양피지들은 나의 후원자가 전투에서 쓰러뜨린 사나운 사략선장의 선실에서 발견된 것이다. 그 악당은 바로 항만장에게서 직접 정보를 받아왔다. 여기에는 선박의 항로, 출항 시간, 화물의 종류가 꼼꼼히 기록되어 있다. 이 배들은 이후 약탈당했고, 선원들은 무참히 살해되거나 끝없는 푸른 바다 위에서 자취를 감추었다\n잘 새겨두어라 – 이 기록의 붓놀림은 공식 선적 명세서와 완벽히 일치한다. 이 증거로 배신자의 정체가 드러날 것이다. 내 후원자는 이 문서들이 자신의 시신에서 발견되길 바란다. 치안판사의 법정으론 부족하다\n이 악당은 너무나 많은 권세를 휘두르며, 수많은 부패한 동료들을 거느리고 있다. 그가 법정에 선다 해도, 정의의 손아귀에서 교묘히 빠져나갈 것이다. 이런 해충은 신의 숨을 쉬는 피조물들 사이에 있을 자격이 없다. 오직 영원한 악명과 함께 죽음만이 이런 배신자에게 어울린다.";
			link.l1 = "배신자 놈! 사내들이 자기 재산까지 맡겼건만, 저자는 그들의 목숨을 칼잡이들과 도적놈들에게 팔아넘기고 있지! 나도 이 일에 동참하겠소. 저런 자는 신의 하늘 아래 설 자격이 없지.";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;

		case "Naemnik_9":
			dialog.text = "나는 그 호화로운 저택의 가구를 수리하던 목수를 통해 그의 집 열쇠를 손에 넣었지. 모든 것이 계획대로 진행됐어, 그가 방을 다른 이와 함께 쓴다는 걸 알기 전까지는 말이야. 정의를 집행하려고 방에 들어갔더니, 그의 부인이 그 자리에 있었지\n예상치 못한 그녀의 동행에 잠시 망설였어. 그녀의 피에 현상금이 걸린 것도 아니고, 신분 있는 여인을 죽이면 왕실의 사냥개들이 훨씬 더 집요하게 쫓을 테니까. 그래서 계획을 바꿔 세관 근처에서 그를 기다리기로 했지.";
			link.l1 = "이런 젠장, 망할 일이군! 이제 마을 전체가 경계하고 있으니, 예전처럼 대놓고 공격할 수 없게 됐어. 이제 우리에게 남은 길이 뭐지?";
			link.l1.go = "Naemnik_10";
		break;

		case "Naemnik_10":
			dialog.text = "나는 마을을 지켜보며 소동이 가라앉기를 기다렸지. 내가 시도한 후, 그 비겁한 쥐새끼는 서둘러 자기 아내를 숨기러 갔어. 내 두 눈으로 그녀가 배에 올라 항구를 떠나는 걸 봤다네\n이제 그는 혼자 남았으니, 우리가 시작한 일을 끝내기에 완벽한 때지. 어둠을 틈타 그의 소굴로 숨어들어 이 일을 끝내게. 그리고 이 치명적인 서류들을 눈에 잘 띄는 곳에 두어, 모두가 그의 마음속에 곪아 있던 더러운 부패를 알 수 있게 하게\n하지만 나는 마을 성문을 통과할 수 없어. 하지만 자네라면... 자네는 내가 못 하는 걸 해낼 수 있지. 아무 경비병도 자네 얼굴을 찾지 않으니, 쉽게 그들의 감시를 통과할 걸세. 그의 집은 도시 감옥 근처에 있네. 오백 두블론! 그 배신자가 죽으면 이 현상금의 절반을 자네가 가지게 될 걸세.";
			link.l1 = "그러면 그렇게 하겠소. 이 악당은 내 손으로 직접 창조주께 보내 주겠소. 이 문서들은 그의 거처에 남겨 두겠소 – 모두가 그의 배신의 진실을 알 수 있도록. 내 돌아올 때까지 기다리시오. 정의가 실현된 후에 다시 오겠소.";
			link.l1.go = "Naemnik_11";
		break;
		
		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l2 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l2.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "왜 거기서 얼어붙은 채로 서 있어, 발이 석회에 박힌 것처럼?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;

		case "Portman_1":
			dialog.text = "너? 뭐야, 젠장? 어떻게 여기 들어온 거야?";
			link.l1 = "내가 여기 어떻게 오게 됐는지는 전혀 중요하지 않아. 그리고 네가 속으로는 내가 왜 왔는지 알고 있다고 생각해.";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "Portman_2":
			dialog.text = "아니, 나는 이해하지 못하겠어! 보상을 받으러 온 거라면 내일 행정실로 오게, 내가 전부 줄 테니.";
			link.l1 = "순진한 척 그만해! 나는 다 알고 있어. 네가 손님들 배에 대한 정보를 해적들에게 팔았지. 그런 비열한 자가 이런 자리를 차지할 자격은 없어. 게다가, 정직한 사람들 사이에서 살 자격도 없지. 나리, 네 자리는 네 족속들 곁이야 - 지옥에서 말이지.";
			link.l1.go = "Portman_3";
		break;

		case "Portman_3":
			dialog.text = "아, 아니-아니-아니야! 아니야! 완전히 오해하고 있어! 그, 그놈들이 나를 강제로 시킨 거야... 내게 와서, 내가 도와주지 않으면 우리 가족을 해치겠다고 협박했어... 너는 이해 못 해...";
			link.l1 = "네 비열한 변명은 이제 지긋지긋하다! 네가 팁에서 몫을 요구한 내역이 적힌 쪽지가 내 손에 있다! 네 위선이 역겹고, 더는 참을 생각도 없다. 칼을 뽑아라, 용기가 있다면 맞서 싸워라!";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "그래서, 소식이 있나? 우리 일은 끝난 건가?";
			link.l1 = "나를 의심했나? 그 불쌍한 놈이 입에서 변명 한마디 짜내려고 애썼지만, 헛수고였지. 우리가 약속한 대로, 결정적인 서류는 절대 못 볼 리 없는 곳에 두었어.";
			link.l1.go = "Naemnik_22";
		break;

		case "Naemnik_22":
			dialog.text = "저런 비겁한 벌레 같은 자들은 언제나 거짓말과 돈으로 정의의 칼날에서 자비를 살 수 있다고 믿지.";
			link.l1 = "이제 그의 생각은 더 이상 그를 괴롭히지 않소. 내 보수를 건네주면 나는 떠나겠소.";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "여기 네가 정당하게 번 돈, 두블룬이다. 수고했으니 그 점은 인정하지. 하지만 잘 들어라—처음 우리가 칼을 맞댔을 때 내 손에 더 강한 검이 있었다면, 우리의 운명은 전혀 다르게 흘러갔을 것이고... 너는 평생 후회했을 거다. 저 비좁은 방 안에서는 제대로 된 무기를 휘두를 수 없어, 나는 이 형편없는 송곳 하나만 들고 네놈을 빠르게 끝내려 했지\n일이 이렇게 될 줄 알았다면, 내 기개에 어울리는 칼을 들고 나왔을 것이다.";
			link.l1 = "하! 떠나간 우리 친구가 론세스발레스 협곡 앞의 롤랑처럼 무장했다고 너를 칭찬했지! 그런데 네가 보여준 모습은 과연 기사답더군.";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;

		case "Naemnik_24":
			dialog.text = "헤헷. 두려움이란 참으로 거대한 그림자를 드리우지? 네 눈으로 직접 봤잖아, 내가 네 뛰는 심장을 거의 꿰뚫을 뻔한 그 보잘것없는 식칼을.";
			link.l1 = "네 손에 더 무거운 강철이 있었다면, 나에게 제대로 된 상대가 될 수 있었을 거라고 말하는 건가?";
			link.l1.go = "Naemnik_25";
		break;

		case "Naemnik_25":
			dialog.text = "중간 무게의 검을 다루는 솜씨라면 내 실력을 능가할 자는 없지. 내 목숨을 걸고 맹세하마. 의심하나? 좋다, 그럼. 수많은 위험 속에서 나를 지켜준 교묘한 검술 몇 가지를 전수해 주지. 잘 듣거라. 이건 허풍이 아니라, 언젠가 네 목숨을 구할 수도 있는 진짜 지혜다. 이런 비밀스러운 지식은 가장 가치 있는 제자에게만 전해지는 법이니라.";
			link.l1 = "...";
			link.l1.go = "Naemnik_26";
		break;
		
		case "Naemnik_26":
			DialogExit();
			SetLaunchFrameFormParam("An hour passes...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;

		case "Naemnik_27":
			dialog.text = "...";
			link.l1 = "확실히 당신은 자신의 일에 능숙하군요. 가르침에 감사드립니다. 하지만 우리의 일이 끝났다면, 이제 저는 가봐야겠습니다.";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 500, 0, 0);
		break;

		case "Naemnik_28":
			dialog.text = "안녕히 가시오, "+GetSexPhrase("선장","고운 아가씨")+". 더는 칼을 맞대지 않길 바라지. 너를 저세상으로 보내는 건 내게도 슬픈 일이 될 테니까. 하하.";
			link.l1 = "내가 술에 잔뜩 취해서 한 다리로 서 있다 해도, 너한테는 털끝만큼의 기회도 없을 거다! 잘 가라, 용병놈.";
			link.l1.go = "Naemnik_29";
		break;
		
		case "Naemnik_29":
			DialogExit();
			AddDialogExitQuestFunction("Naemnik_29");
			
			AddSimpleRumourCity("Word has it the Port Chief was found dead in his own home. Documents were discovered on his body proving his involvement in the disappearance of ships. Just imagine—what a disgrace for our town...", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Have you heard the news? Someone snuck into the Port Chief’s house, killed the guards, and took him out. They found notes on the body with routes of missing ships—written in his own hand! A servant of the Crown, yet a traitor in truth! Got what he deserved! And where was the Governor all these years?", "Beliz", 30, 1, "");
			AddSimpleRumourCity("The Port Master is dead! Killed right in his own home! The guards were slaughtered, and among his possessions were notes mapping routes of vanished ships. No doubt about it—he was behind the disappearances! Justice has finally caught up with the scoundrel.", "Beliz", 30, 1, "");
			break;
	}
}