// НПС по квесту Суп из черепахи
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "무슨 일이오?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// денщик Фокса - Бенджамин Джонс
		case "BenjaminJons":
			if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
			{
				dialog.text = "지금 대령 나리께서는 야외에서 군사 훈련 중이십니다. 선장님, 무슨 용무이십니까?";
				link.l1 = "이번에는, Ben, 네가 필요하네. 네 여동생 Molly에 대한 나쁜 소식이 있네. 그 아름다운 아가씨가 곤경에 처한 모양이야. Tortuga의 해적들에게 붙잡혔다네. 그녀는 도움이 필요해서 나에게 너에게 경고해 달라고 부탁했지. 그 소식을 전하려고 나선 사내는 죽임을 당했지만, 죽기 전에 네 여동생에 대해 내게 말해줄 수 있었어.";
				link.l1.go = "sister";
				break;
			}
			sld = characterFromId("Fox");
			if (sld.location == pchar.location)
			{
				dialog.text = "여기 대령 폭스를 만나러 왔다면, 들어가도 된다네 — 그분이 널 맞이할 거야..";
				link.l1 = "그러하오.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "대령은 지금 여기 없소. 나중에 다시 오시오.";
				link.l1 = "좋아...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "BenjaminJons";
		break;
		
		case "sister":
			dialog.text = "하! 자네가 우리 누이를 '아름답다'고 부른 첫 번째 남자라네. 신께서는 그녀에게 근위병의 몸과 예리코의 뿔 같은 목소리를 주셨지. 우리 몰리는 스스로 싸울 수 있어. 하지만 주님의 기발함은 그녀의 턱 아래에서 멈추지 않았다네. 아니, 아니, 그분이 하신 최고의 일은 그녀의 가슴 위에 돌아가신 우리 아버지의 털 많고 곰보 자국 투성이 얼굴을 붙여놓으신 거라네. 그리고 말이지, 나리, 우리 아버지 얼굴은 말조차 기절하게 만들 정도였어.";
			link.l1 = "별로 속상해 보이지 않는군...";
			link.l1.go = "sister_1";
		break;
		
		case "sister_1":
			dialog.text = "그녀가 왜 토르투가에 나타나겠소? 몰리는 우리 용감한 대령의 딸, 캐서린 폭스의 하녀요. 캐서린은 유럽에서 아버지의 생일을 맞아 오고 있었소. 하지만 그녀가 타고 온 함대가 지연되었지\n진짜 몰리 존스와, 참고로 아주 아름다운 그녀의 주인 아가씨를 보고 싶다면 한 달 후에 여기로 오시오. 하루도 일찍 오지 말고.";
			link.l1 = "알고 보니 네 여동생 몰리 존스가 폭스 양을 모시고 있었고, 지금은 대서양 건너편에 살고 있다는 말이군?";
			link.l1.go = "sister_2";
		break;
		
		case "sister_2":
			dialog.text = "바로 그렇소! 마지막 전령이 전해준 소식에 따르면, 크롬웰 경이 직접 파견한 해군 함대가 불과 한 달 전에 런던을 떠날 예정이었다 하오. 캐서린이 탑승한 브리그선 '알바트로스'도 그들과 함께 출항하기로 되어 있었지. 이게 사실인지 아닌지는 다음 우편선이 도착하면 알 수 있을 것이오. 아직 배들이 도착하지 않았고, 대령께서도 '알바트로스'가 단독으로 항해하는 것을 엄격히 금지하셨소.\n혹시 그분의 사랑하는 아내가 프랑스 사략선의 습격으로 세상을 떠난 걸 알고 있었소? 대령에게는 매우 힘든 일이었고, 지금도 대양의 위험을 두려워하오... 그러니 몰리 존스에 대해서는 도와줄 수 없소, 선장! 몰리라는 이름의 식민지 처녀들은 아주 많으니까! 게다가 영국에서 존스라는 성은 성이 없는 거나 마찬가지지!\n앤티과의 모든 뱃사람들은 나와 내 지휘관을 다 알지. 곤경에 처한 불쌍한 처자가 내 도움을 바란다 해도 놀랄 일은 아니오. 도와주고 싶지만, 몸값을 낼 돈이 없소. 대령이 내 월급을 석 달째 밀리고 있거든. 내 급여와 다른 이들의 급여 모두 '알바트로스'가 와야 받을 수 있지.";
			link.l1 = "그렇다면 내가 착각했던 모양이군. 그래도 설명해줘서 고맙네.";
			link.l1.go = "sister_3";
		break;
		
		case "sister_3":
			dialog.text = "전혀 아닙니다, 선장님.";
			link.l1 = "...";
			link.l1.go = "sister_4";
		break;
		
		case "sister_4":
			DialogExit();
			AddQuestRecord("Terrapin", "3");
			pchar.questTemp.Terrapin.Catherina = "take"; // возможен вариант с Кати
			DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;
		
		// Робер Мартэн
		case "Rober":
			PlaySound("Voice\English\sharlie\Rober Marten-01.wav");
			dialog.text = "뭐 원하는 거야?! 말하고 싶지 않아.";
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
			{
				link.l1 = "선장, 너에게 맡길 일이 좀 있네. 기분이 별로 좋아 보이지 않는데, 내 제안이 조금이나마 기운을 북돋아 줄지도 모르겠군.";
				link.l1.go = "rober_1";
			}
			else
			{
				link.l1 = "조용히 해, 럼이나 마셔. 내 실수였어, 미안하다.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rober";
		break;
		
		case "rober_1":
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Terrapin_LateBaster.over = "yes"; //снять таймер
			dialog.text = "그 이름 참 마음에 드는군! 그런데 네 얼굴, 어디서 본 적 있는 것 같은데... 도무지 어디서 봤는지 기억이 안 나. 자, 말해 봐!";
			link.l1 = "티보와 네 거래에 대해 알고 있어... 진정해, 친구! 나를 두려워할 필요 없어. 너한테 제안할 거래가 있거든.";
			link.l1.go = "rober_2";
		break;
		
		case "rober_2":
			dialog.text = "제기랄, 젠장할! 저 술주정뱅이 돼지 놈도 저주받아라!... 내가 못 했어...";
			link.l1 = "맞아. 네 선원이 입이 좀 걸었지만, 그 소문은 나한테서 더 이상 퍼지지 않았어. 그리고 그 소문은 더 이상 퍼지지 않을 거야, 네가 직접 처리했으니까, 그렇지?";
			link.l1.go = "rober_3";
		break;
		
		case "rober_3":
			dialog.text = "카람바! 이제야 알아보겠군! 자네가 바로 도일리 대령을 엉망으로 만들고 그의 섬 전체를 차지한 그 사람이잖아! 네덜란드 서인도 회사와도 큰 거래를 했고, 웨스트 메인의 남작과도 어울리고 있다지... 자네 이름이... "+GetFullName(pchar)+", 맞지?";
			link.l1 = "꽤 정확한 정보를 가지고 있군. 그래, 나야. 그런데 잠깐 진정할 수 있겠나, 로버트?";
			link.l1.go = "rober_4";
		break;
		
		case "rober_4":
			PlaySound("Voice\English\sharlie\Rober Marten-02.wav");
			dialog.text = "아악! 이런, 군도에서 가장 유명한 바다개 중 한 명이 나한테 관심을 가졌는데, 그것도 모자라 내 일까지 알아버렸으니 내가 어떻게 진정하겠어! 도대체 내가 무슨 생각으로 그 브리그를 공격한 거지! 대체 나한테 뭘 원하는 거야?";
			link.l1 = "입 다물고 내 말 들어. 우리 둘 다 르바쇠의 목을 쟁반에 올려놓고 싶어 하는 것 같군. 그 잘난 척하는 허풍쟁이가 제 분수를 모르고 까불다가 제대로 위험한 사람들까지 건드렸지. 나는 이 섬의 세력 균형을 바꿔서 드 푸앵시를 제자리로 돌려놓을 생각이야. 하지만 내 고향 사람들의 피를 더 흘리고 싶진 않아, 특히나 그런 더러운 도둑놈 때문에 말이지. 네가 나를 도울 수 있어. 그리고 나도 너랑 티보가 특권을 지킬 수 있게 도와줄 수 있지.";
			link.l1.go = "rober_5";
		break;
		
		case "rober_5":
			dialog.text = "잠깐, 잠깐! 내 귀를 의심하겠군! 오늘은 정말 행운이 따르는 날이야. 네 말이 맞아, 우리는 같은 목표를 가지고 있지. 너와 함께라면 일이 훨씬 더 흥미로워질 수 있겠군... 티보는 검술은 좋지만, 자기 삼촌의 목을 벨 배포는 없어... 하지만 너처럼 영악한 상어라면 할 수 있겠지. 네 명성은 이미 잘 알려져 있지\n나는 네 보장은 필요 없어, 하지만 그 대신 그 여자를 넘겨주면 도와주지. 내가 카리브에서 일을 마칠 때까지 인질로 필요하거든. 곧 영국 프리깃들이 나를 쫓기 시작할 거야. 도대체 무슨 생각으로 그 브리그를 공격했는지! 분대에서 떨어져 있어서 쉬운 먹잇감인 줄 알았는데...";
			link.l1 = "그녀가 뭐가 그렇게 특별했지? 네가 르바쇠르에게서 숨기던 그 여자애 말이야?";
			link.l1.go = "rober_6";
		break;
		
		case "rober_6":
			dialog.text = "그래. 티보가 그 처녀와 헤어지도록 설득해야 하네. 내가 그녀가 대체 누구인지 알아보는 동안 티보에게 그녀를 돌보라고 했었지. 그런데 이 '존스 아가씨'인가 뭔가 하는 여자가 완전히 그의 정신을 빼놓아서, 이제는 헨리까지 나 몰래 그녀를 숨기고 있네! 그 요염한 요부를 내게 데려오면, 내가 마을 밖에서 르바쇠르와 만날 수 있도록 자리를 마련해주지. 그때가 되면 그를 기습할 기회가 있을 걸세. 나는 피쉬아이 해변에서 기다리고 있겠네.";
			link.l1 = "거래지. 이제 티보를 어떻게 잡는지 말해 줘.";
			link.l1.go = "rober_7";
		break;
		
		case "rober_7":
			dialog.text = "선술집에 있는 사람들이 그의 집으로 가는 길을 알려줄 거야. 앙리란 녀석은 꽤 유명한 인물이니, 약점을 잡아 협박해서 그 여자를 내게 데려오게 해. 그날 바로 르바쑤르에게 그의 조카가 도시 감옥에 희귀한 미녀를 숨기고 있다는 걸 알릴 거다\n내 심부름꾼이 선술집에서 널 찾을 거야. 그가 앙리를 찾지 못하면, 총독이 소규모 부대를 이끌고 감옥으로 갈 테니 그때 총독과 얘기할 좋은 기회가 생길 거다.";
			link.l1 = "그 소녀를 어디로 데려가면 되지?";
			link.l1.go = "rober_8";
		break;
		
		case "rober_8":
			dialog.text = "그에게 직접 그녀를 해변으로 데려오라고 전해. 나도 그 김에 그와 한두 마디 할 생각이니까...";
			link.l1 = "좋아. 그렇게 하자. 토르투가에서 보자!";
			link.l1.go = "rober_9";
		break;
		
		case "rober_9":
			dialog.text = "모든 일이 계획대로 된다면, 우리는 다시는 서로 볼 일 없겠지. 적어도 나는 그러길 바라. 잘 가라!";
			link.l1 = "...";
			link.l1.go = "rober_10";
		break;
		
		case "rober_10":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina")) AddQuestRecord("Terrapin", "6");
			else AddQuestRecord("Terrapin", "5");
			pchar.questTemp.Terrapin = "tortuga";
			// создаем Тибо
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.name = "Henry";
			sld.lastname = "Thibaut";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "tibo";
			sld.greeting = "Tibo";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 40, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // таймер
			SetFunctionLocationCondition("Tonzag_AtTortuga", "Tortuga_town", false);
		break;
		
		case "rober_abordage":
			dialog.text = "아악! 이런 줄은 몰랐는데... 내 영혼을 가지러 온 거지? 약속한 대로 다 했잖아! 도대체 뭐야?!";
			link.l1 = "로버트, 너에게 형이 내려졌어. 그 형을 집행하라는 명령을 내가 받았지. 그래서 나는 내 임무를 수행하는 중이야.";
			link.l1.go = "rober_abordage_1";
		break;
		
		case "rober_abordage_1":
			dialog.text = "이 악마 같은 놈! 이건 말도 안 돼! 그가 이렇게 빨리 모든 걸 알아냈을 리 없어! 도대체 어떻게 알아낸 거지?!";
			link.l1 = "여우를 말하는 건가? 아니. 그가 날 보낸 게 아니야. 대령은 아직도 네가 그의 딸을 구해냈다는 사실조차 몰라. 널 죽이길 원하는 건 네 옛 동료 앙리 티보야. 그가 날 고용했지.";
			link.l1.go = "rober_abordage_2";
		break;
		
		case "rober_abordage_2":
			dialog.text = "저 빌어먹을 계집애 같은 놈! '볼티쥬르'에 있을 때 게들에게나 던져줄 걸 그랬지... 그 자식이 너한테 얼마를 약속했지?";
			link.l1 = "사람이 자기 머리에 걸린 현상금을 직접 듣는 날이 흔치 않지, 그렇지 로베르? 티보가 네 값을 25만으로 매겼는데, 내가 그보다 더 가치 있다고 설득했어. 네 값은 30만 실버 페소야, 친구. 기쁘지 않나?";
			link.l1.go = "rober_abordage_3";
		break;
		
		case "rober_abordage_3":
			dialog.text = "잠깐만... 거래하자! 내가 더 많이 줄게!";
			link.l1 = "무슨 돈으로, 로버트? 네가 거짓말하는 거 확실히 알고 있어. 네가 헨리가 내게 약속한 만큼의 돈을 가졌을 리 없지. 하지만 그게 중요한 게 아니야. 한 가지 사실만 아니었으면, 나는 헨리의 제안을 거절하고 네 놈과 티보의 더러운 장사를 끝장내는 일도 하지 않았을 거야.";
			link.l1.go = "rober_abordage_4";
		break;
		
		case "rober_abordage_4":
			dialog.text = "무슨 사실 말인가?";
			link.l1 = "너는 캐서린 폭스를 죽였지. 그 불쌍한 소녀의 유일한 죄는 폭스 대령의 딸로 태어난 것뿐이었어. 난 너처럼 무방비한 여자를 죽이는 비열한 겁쟁이들을 증오한다! 너와는 어떤 거래도 하지 않겠다. 생각조차 안 할 거다. 말 낭비하지 마라.";
			link.l1.go = "rober_abordage_5";
		break;
		
		case "rober_abordage_5":
			PlaySound("Voice\English\sharlie\Rober Marten-03.wav");
			dialog.text = "젠장! 내가 뭘 더 할 수 있었겠어?! 그녀를 계속 배에 숨겨두고 살려둘 순 없었잖아! 그리고 너는 누구지... 이 망할 놈, 이 자식, 이 살인자가 감히 나한테 도덕을 운운해?! 네 꼴 좀 봐라! 네 '수법' 말이다! 너라고 나보다 나을 게 뭐가 있냐!";
			link.l1 = "그만하자. 마르텐, 칼을 뽑아라! 이제 끝을 보자.";
			link.l1.go = "rober_abordage_6";
		break;
		
		case "rober_abordage_6":
			dialog.text = "지옥에서 보자!";
			link.l1 = "...";
			link.l1.go = "rober_abordage_7";
		break;
		
		case "rober_abordage_7":
			DialogExit();
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Тибо, вариант без Кати
		case "tibo":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "내 집에서 뭐 하고 있소, 나리?";
			link.l1 = TimeGreeting()+", 티보 나리. 당신이 아는 분, 로베르 마르텐 선장을 대신해 왔소.";
			link.l1.go = "tibo_1";
		break;
		
		case "tibo_1":
			dialog.text = "흠. 그래서? 어쩌라고?";
			link.l1 = "마르텐 선장이 지금 바로 피쉬아이 해변에서 당신과 함께하고 싶어 하오. 하지만 혼자만은 아니오. 몰리 존스도 같이 오면 좋겠다고 하셨소. 내 말 뜻을 알겠소?";
			link.l1.go = "tibo_2";
		break;
		
		case "tibo_2":
			PlaySound("Voice\English\sharlie\Henry Thibault-01.wav");
			dialog.text = "유감이오, 나리, 나는 모릅니다. 몰리 존스라는 사람에 대해 들어본 적도 없고, 로버트가 나에게... 한 번도 본 적 없는 전권대사를 보낼 이유도 전혀 없었소. 참고로 말씀드리자면, 나리, 나는 이 섬에서 총독이신 내 삼촌 다음으로 높은 사람이오, 그러니...";
			link.l1 = "인생이란 예측할 수 없는 괴물이야, 앙리... 지금은 네가 이 섬에서 두 번째로 높은 사람이지만, 몇 시간 뒤면 감옥에서 족쇄를 차고 있을 수도 있지... 그것도 너한테 페소 한 푼 줄 생각도 없는 사람의 목숨 때문에 말이야. 삼촌의 명령을 어긴 거지, 티보 나리? 너한테 더 중요한 건 뭐냐? 방탕한 계집이냐, 아니면 네 목숨이냐?";
			link.l1.go = "tibo_3";
		break;
		
		case "tibo_3":
			dialog.text = "이 자식아... 거짓말하지 마! 헛소리하고 있잖아!";
			link.l1 = "너도 알다시피, 네 삼촌 성질이 얼마나 불같은지 누구나 다 알지. 르바쇠르는 해가 지기 전에 네가 그 여자를 숨기고 있다는 걸 알아낼 거야. 로베르가 그걸 어떻게 알았는지는 묻지 마, 내 말만 들어. 그는 겁에 질려서 당장이라도 닻을 올릴 준비가 되어 있어. 심지어 마을에 들어올 엄두도 못 내고, 대신 이 말을 전해달라고 나에게 큰돈까지 줬다네.";
			link.l1.go = "tibo_4";
		break;
		
		case "tibo_4":
			dialog.text = "젠장... 이럴 수가!";
			link.l1 = "결정은 당신에게 달렸소, 나리. 마르텐은 두 시간 이상 더는 기다리지 않을 거요. 그는 자기 목숨을 소중히 여기니까. 아직도 토르투가 해안에 머무는 건 오직 우정의 표시일 뿐, 아니었으면 벌써 네덜란드 놈들과 어딘가에 숨어버렸을 거요.";
			link.l1.go = "tibo_5";
		break;
		
		case "tibo_5":
			dialog.text = "카람바! 우리 삼촌이 그걸 어떻게 알아냈지?";
			link.l1 = "혀 좀 조심해, 헨리. 쓸데없는 소문이 돌고 있잖아. 나도 네가 로버트랑 같이 네 동료가 나포한 영국 브리그에서 내린 미녀를 데려갔다는 거 알아. 르바쇠르한테는 숨겼지...쳇쳇. 이 얘기를 아는 사람이 나 하나뿐이라고 정말 생각하나?";
			link.l1.go = "tibo_6";
		break;
		
		case "tibo_6":
			dialog.text = "진실을 말하는 것 같군, 나리. 마르텐에게 전해...";
			link.l1 = "내 말이 무슨 뜻인지 모르는 것 같군, 헨리. 마르텐은 너를 기다려주지 않아. 네가 살 길은 그 계집애를 여기서 데리고 나가는 것뿐이야, 너랑 로버트 둘 다 목에 올가미가 걸린 이유 말이다. 네가 그녀를 숨겨둔 곳으로 달려가서, 그 예쁜 손을 잡고 볼티지어로 데려와. 빨리 찾아서, 더 빨리 데려와. 네 삼촌에게는 이 일에 대해 한마디도 하지 않을 테니.";
			link.l1.go = "tibo_7";
		break;
		
		case "tibo_7":
			dialog.text = "알겠습니다. 그렇게 하겠습니다. 친절에 감사드립니다, 나리!";
			link.l1 = "고맙다는 말은 필요 없소, 나리. 내 일은 이미 대가를 받았으니... 그저 당신이 완전히 익기 전에 이 곤경에서 벗어나길 바랄 뿐이오.";
			link.l1.go = "tibo_8";
		break;
		
		case "tibo_8":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_wait.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.Terrapin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l2 = "location";
			pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
			pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
			pchar.questTemp.Terrapin = "cave";
			AddQuestRecord("Terrapin", "8");
			SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 4, false);
			} 
			else SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;
		
		// вариант с Кати
		case "tibo_9":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "여기서 뭐 하십니까, 나리? 내가 당신을 초대한 적 없소.";
			link.l1 = TimeGreeting()+", 티보 나리. 당신이 아는 분을 대신해 왔소. 그분의 이름은 로베르 마르텐 선장이오.";
			link.l1.go = "tibo_10";
		break;
		
		case "tibo_10":
			dialog.text = "흠. 그래서? 어쩌라고?";
			link.l1 = "마르텐 선장이 지금 바로 피쉬아이 해변에서 당신과 함께하고 싶어 하오. 하지만 혼자만은 아니오. 몰리 존스도 함께 오면 좋겠다고 하셨소. 내 말 뜻을 알겠소?";
			link.l1.go = "tibo_11";
		break;
		
		case "tibo_11":
			dialog.text = "유감이오, 나리, 모릅니다.";
			link.l1 = "내가 바로 그 말을 할 줄 알았지. 물론, 자네가 예전에 폭스 대령의 딸을 만난 적이 있을 리 없다고 생각하네; 자네도 알겠지만, 폭스 대령은 악명 높은 시 폭스 해적단의 지휘관이자... 카리브 해에서 영국의 적들에게 공포를 안겨준 인물이네. 자네와 로버트가 벌집을 쑤셔놓은 덕에 아직 벌에 쏘이지 않은 게 기적이지! 자네가 영국 브리그에서 붙잡아 르바쇠르에게 숨기고 있던 그 소녀 몰리 존스, 그녀가 바로 폭스 대령의 딸, 캐서린 폭스라네!";
			link.l1.go = "tibo_12";
		break;
		
		case "tibo_12":
			dialog.text = "뭐, 뭐라고?";
			link.l1 = "얼굴이 많이 창백해졌군, 나리. 이제 내 말 잘 들어, 헨리. 그리고 집중해라. 너랑 네 동료 로버트는 지금 큰일에 휘말렸어. 언제든 크롬웰의 해군 함대가 카리브 해에 도착할 거다. 그들은 너희를 사냥하러 올 거야. 그 기함 한 척만으로도 네가 자랑하는 라 로슈와 그 선원들을 몇 시간 만에 산산조각 내고 고깃덩이로 만들 수 있지. 어때? 그 영국 브리그를 공격하고 폭스의 딸을 잡아온 게 그만한 가치가 있었나?";
			link.l1.go = "tibo_13";
		break;
		
		case "tibo_13":
			dialog.text = "";
			link.l1 = "하지만 그게 전부가 아니야. 네 계략이 나뿐만 아니라 다른 사람들에게도 알려졌지. 네 소중한 삼촌, 총독 나리께서도 네가 그의 엄격한 명령을 어기고, 그 늙은 호색한이 분명히 자기 것으로 삼고 싶어 했을 소녀를 숨겼다는 사실을 곧 알게 될 거다. 어때, 헨리? 네 삼촌이 너한테 뭘 할 것 같아? 누구보다도 그분의 불같은 성미를 잘 알 테니...\n";
			link.l1.go = "tibo_14";
		break;
		
		case "tibo_14":
			dialog.text = "전부 거짓말이야!";
			link.l1 = "그래? 친애하는 헨리, 친구 마르텐에게 물어보게. 나를 보낸 사람이 바로 그였으니. 르바쇠르는 해가 지기 전에 자네가 그 여자를 숨기고 있다는 걸 알게 될 거야. 로베르가 그걸 어떻게 알았는지는 묻지 말게, 내 말만 명심하게나: 그는 겁에 질려서 당장이라도 닻을 올리고 떠날 준비가 되어 있네. 심지어 마을 안으로 들어올 엄두도 못 냈지. 그래서 나한테 이 전갈을 전해달라고 부탁한 거야.";
			link.l1.go = "tibo_15";
		break;
		
		case "tibo_15":
			dialog.text = "";
			link.l1 = "마르텐은 너를 두 시간 이상 더 기다리지 않을 거야. 자기 목숨이 소중하거든. 네가 친구라서 아직 토르투가 해안에 머무는 거지, 아니었으면 벌써 네덜란드 놈들 틈에 숨어버렸을 거다. 그런데 그 불쌍한 로버트는 몰리 존스가 누구인지 전혀 눈치도 못 챘지. 있잖아, 너희 둘은 정말 여자들 옷차림이나 생김새에 대해 놀랄 만큼 무지하구나! 귀부인과 하녀도 구분 못 할 정도라니!";
			link.l1.go = "tibo_16";
		break;
		
		case "tibo_16":
			dialog.text = "뭘 원하지?";
			link.l1 = "드디어 그 젊은 풋내기에게서 현명한 말이 나오는군! 좋아, 티보: 지금 당장 네가 그녀를 숨겨둔 곳으로 가서, 그녀의 고운 손을 살며시 잡고, 마르텐의 볼티제르가 있는 피쉬아이 해변까지 재빨리 함께 걸어가라. 그리고 그에게 네 계획이 바뀌었다고 전해라...\n";
			link.l1.go = "tibo_17";
		break;
		
		case "tibo_17":
			dialog.text = "";
			link.l1 = "마르텐은 나와의 약속을 반드시 지켜야 해. 감히 그 계집애를 자기 배에 태우려는 시도조차 하지 말라고 해. 그 애는 해변에 남아 나를 기다릴 거야. 로베르에게도 전해, 자기 의무를 다하지 않거나 카트린을 데려가거나, 아니면 그 예쁜 머리카락 하나라도 상하게 하면, 내 남은 평생을 그녀를 찾아 헤매겠다고. 그리고 결국 찾아내면, 살아있는 채로 폭스 대령에게 넘겨주겠다고 말이야. 하지만 너희 둘은... 조각조각 내서 데려가겠다. 아, 참고로, 티보, 너도 예외는 아니야.";
			link.l1.go = "tibo_18";
		break;
		
		case "tibo_18":
			dialog.text = "";
			link.l1 = "내가 누구고 내 기회가 어떤지는 로버트에게 물어보면 알 거다. 그는 잘 알고 있지. 너희 둘 다 내가 시키는 대로 하면 우리 모두 이기는 거다. 로버트는 해적질을 계속할 수 있고, 너는 모든 특권을 지키면서 네 늙은 삼촌이 죽을 때 유산도 받게 될 거야. 나 역시 손해 볼 일은 없지. 이 정도면 다 이해됐나?";
			link.l1.go = "tibo_19";
		break;
		
		case "tibo_19":
			PlaySound("Voice\English\sharlie\Henry Thibault-03.wav");
			dialog.text = "차라리 영원한 지옥불에 타는 게 당신 명령을 따르는 것보다 낫겠소... "+GetFullName(pchar)+"! 처음부터 너를 못 알아봤다니! 이 살인마 놈! 넌 나나 로버트를 살려둘 생각이 없겠지! 네 '수법'은 이미 소문이 자자하다고! 몰리도... 아니, 캐서린도 네 같은 쓰레기한테 절대 넘기지 않아! 넌 토르투가에서 살아나가지 못할 거다, 이 개자식아!";
			link.l1 = "...";
			link.l1.go = "tibo_20";
		break;
		
		case "tibo_20":
			dialog.text = "";
			link.l1 = "멈춰, 겁쟁이!";
			link.l1.go = "tibo_21"; // patch
		break;
		
		case "tibo_21":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
			LAi_RemoveLoginTime(npchar);
		break;
		
		case "tibo_22":
			pchar.quest.Terrapin_TiboCallOver.over = "yes"; //снять прерывание
			pchar.quest.Terrapin_tibo_call.over = "yes"; //снять прерывание
			PlaySound("Voice\English\sharlie\Henry Thibault-04.wav");
			dialog.text = "드디어군! 선장 "+GetFullName(pchar)+", 와 주셔서 정말 기쁩니다. 들어오시고, 앉으세요. 뭐라도 한 잔 하시겠습니까? 아주 수익성 좋은 사업 제안이 있는데, 친구여...";
			link.l1 = "오늘따라 무척이나 공손하시군, Thibaut 나리... 빈둥거릴 시간 없소. 바로 본론으로 들어갑시다.";
			link.l1.go = "tibo_23";
		break;
		
		case "tibo_23":
			dialog.text = "그 제안은 자네도 아는 내 옛 친구이자 동료, 한때 갤리온 'Voltigeur'의 선장이었던 로베르 마르텐에 관한 것이오...";
			link.l1 = "그래서, 자네와 로버트는 이제 더 이상 친구가 아니란 말인가? 흥미로운 전개로군.";
			link.l1.go = "tibo_24";
		break;
		
		case "tibo_24":
			dialog.text = "선장님, 제발 제 사정을 들어주시면 모든 것이 분명해질 것입니다. 아시다시피, 마르텐은 영국 브리그와 접전을 벌인 끝에 영국인 하녀 몰리 존스라는 여자를 포로로 잡았습니다. 바로 그 일이 이 모든 소동의 원인입니다.";
			link.l1 = "물론이지, 알고 있네. 내 이해로는, 자네가 내 권고를 따르고 그 소녀를 마르텐의 배로 데려갔다고 하던데?";
			link.l1.go = "tibo_25";
		break;
		
		case "tibo_25":
			dialog.text = "그래, 내가 그랬어. 하지만 매일 후회하고 있어. 몰리는 정말 매력적이고 아름다운 아가씨야, 그런 사람은 처음 봤어. 솔직히 말해서, 나도 그녀를 사랑하게 됐지. 그녀도 나를 좋아했어, 직접 그렇게 말했으니까! 삼촌에게 그녀를 빼앗길 수는 없었어\n내가 그녀를 '볼티저'호로 호위할 때는, 삼촌이 아무도 자기에게서 여자를 숨기지 않았다는 걸 알게 되면 진정할 거라 생각했지, 그 늙은 호색한 말이야. 그러면 로버트가 그녀를 토르투가로 데려가고, 나는 안전하게 내 집으로 옮길 수 있었지. 어쨌든, 그게 마르텐과 한 약속이었어. 하지만 일은 다르게 흘러갔지\n삼촌이 살해당했다는 걸 알게 됐을 때는, 더 이상 몰리를 숨길 이유가 없었어. 그래서 나는 '볼티저'호가 몰리를 태우고 도착하기만을 묵묵히 기다렸지.";
			link.l1 = "그녀가 도착했나?";
			link.l1.go = "tibo_26";
		break;
		
		case "tibo_26":
			dialog.text = "그래. 안타깝게도 몰리는 그 배에 없었어. 로버트는 마치 루시퍼와 정면으로 맞붙은 것처럼 충격을 받은 상태였지. 짧은 원정 동안, 그는 어쩌다 끔찍한 사실 하나를 알아냈어. 그 소녀, 몰리는 몰리 존스가 아니라 바로 캐서린 폭스였던 거야! 해폭스 부대, 영국 해병 정예 연대의 지휘관인 폭스 대령의 친딸이었지! 그게 무슨 의미인지 알겠지!\n";
			link.l1 = "제기랄, 이럴 수가! 그렇다면 분명히 로버트가 두려워할 만한 뭔가가 있군. 그런데 어떻게 그렇게 된 거지?";
			link.l1.go = "tibo_27";
		break;
		
		case "tibo_27":
			dialog.text = "캐서린이 포로로 잡혔을 때, 그녀는 일부러 자신의 정체를 숨기고, 승선 도중에 죽은 하녀 몰리 존스로 가장했어. 마르텐이 진짜 정체를 알아챌까 봐 두려웠던 거지. 그리고 결국 그를 속이는 데 성공했어. 하지만 마지막 항해 중에 로버트가 어떻게든 그녀의 진실을 알게 됐어. 그는 그녀의 편지나 서류 같은 걸 발견했다고 말했지...\n";
			link.l1 = "그럼 그 아가씨는 지금 어디 있지, 'Voltigeur'에 타지 않았다면?";
			link.l1.go = "tibo_28";
		break;
		
		case "tibo_28":
			dialog.text = "그 여자는 죽었어. 영국 브리그를 공격한 죄로 폭스에게 곧 닥칠 처벌이 두려워서, 마르텐은 남은 유일한 증거를 물에 숨기기로 했지.\n그녀가 바로 '알바트로스'를 공격한 그의 마지막 목격자였어.";
			link.l1 = "그렇다면 그자는 자기 선원들을 전부 죽인 거나 다름없지... 페르낭 뤽처럼 말이야. 안 그러면 언젠가 선원들이 술집에서 취해 입이 너무 가벼워질 테니까...\n";
			link.l1.go = "tibo_29";
		break;
		
		case "tibo_29":
			dialog.text = "그자는 자기 선원 전부가 피로 맺어진 사이라고 믿지. 어쩌면 부분적으로는 맞을지도 몰라. 하지만 나는 폭스 대령을 잘 알아! 딸을 납치한 자가 누구인지 죽는 날까지 찾아낼 거야!";
			link.l1 = "그럴 거라 의심하지 않소. 특히 프랑스 해적이 그의 아내를 죽인 뒤로는 더더욱 그렇지. 이제 딸까지... 그런데, 나리, 정말로 카트린이 죽었다는 것에 확신이 있소? 어쩌면 로베르가 어딘가에 그녀를 숨겨놓았을지도 모르지.";
			link.l1.go = "tibo_30";
		break;
		
		case "tibo_30":
			dialog.text = "확실해. 나는 'Voltigeur'의 선원과 얘기했어. 그의 말을 믿었지. 그는 자기 눈으로 그들이 그 소녀의 목을 베고, 발에 대포알을 묶어 바다에 던지는 걸 봤대.";
			link.l1 = "하늘에 계신 하나님! 저 불쌍한 여인이라니... 헨리, 나한테 뭘 원하는 거지?";
			link.l1.go = "tibo_31";
		break;
		
		case "tibo_31":
			dialog.text = "그날 이후로 밤에 잠을 잘 수가 없어. 항상 내 눈앞에 몰리가 보여... 아니, 캐서린이지. 내가 그녀를 죽음으로 이끌었어. "+GetFullName(pchar)+"! 그 일은 도저히 용서할 수가 없어. 게다가, 나는 폭스에 대해 아무런 환상도 품지 않아. 그 자는 절대 방심하지 않고, 잠도 안 자는 것 같아. 머지않아 마르텐의 흔적을 쫓아 누군가를 입 열게 만들 거고, 자기 딸을 죽인 자가 누군지 알아내면, 지옥이 따로 없을 거야. 이 일에 조금이라도 연관된 사람은 누구든 큰 화를 입게 될 거야.";
			link.l1 = "나도 포함이야.";
			link.l1.go = "tibo_32";
		break;
		
		case "tibo_32":
			dialog.text = "그래, 나도 마찬가지다. 그래서 내가 너한테 폭스보다 먼저 마르텐을 찾아내라고 하는 거다. 그 자식 찾아서 죽여라. 가능하다면 먼저 고통을 좀 줘라. 불쌍한 카트린을 위해서 말이지. 일이 끝나면, 그놈 손에 낀 뚱뚱한 반지를 손가락째 잘라서 증거로 나한테 가져와라\n그 휘어진 손가락과 그 반지는 내가 아주 잘 안다. 그렇게만 해주면 은화 이십오만을 주겠다.";
			link.l1 = "자네, 고인이 되신 삼촌에게서 큰 유산을 받은 모양이군, 안 그러냐? 그런데 말이지, 헨리, 왜 이 일에 나에게 도움을 청하기로 한 거지?";
			link.l1.go = "tibo_33";
		break;
		
		case "tibo_33":
			dialog.text = "나도 그대에 대해 몇 가지를 알게 되었으니, "+GetFullName(pchar)+". 쉬웠지, 자네는 유명한 인물이니까. 하지만 자네가 진짜 누구를 위해 일하는지는 아무도 몰라. 드 푸앵시인지, 네덜란드 인들인지, 영국 인들인지, 아니면 얀 스벤손 남작인지... 하지만 한 가지는 분명하지. 자네는 은밀하고 조심스러운 일들을 맡아 완수하지. 그리고 그 대가로 후한 보수를 받지. 무엇보다도, 자네는 스페인과는 연관이 없어\n결국, 내 삼촌의 재산을 내가 상속받게 된 사건에도 자네가 관여했잖아. 부정하지 마... 25만은 꽤 큰돈이지. 마르텐을 어디서 찾을 수 있는지 알려주지. 자네는 그의 배를 가로채서 승선하기만 하면 돼.";
			link.l1 = "십만 더 주면 마르텐 놈은 내가 처리해 주지.";
			link.l1.go = "tibo_34";
			link.l2 = "유감이오, 티보 나리. 마르텐과 폭스 대령과의 문제는 내 참여 없이 직접 해결하셔야 하오. 나는 내 입장에서, 대령에게 그의 딸의 운명이나 그녀의 죽음에 책임이 있는 자들에 대해 아무 말도 전하지 않겠다고 약속하오. 행운을 비오, 나리.";
			link.l2.go = "tibo_exit";
		break;
		
		case "tibo_exit":
			DialogExit();
			AddQuestRecord("Sharlie", "26");
			NextDiag.CurrentNode = "tibo_over";
		break;
		
		case "tibo_34":
			dialog.text = "나리, 제발요... 제게 보물 상자에 숨겨둔 수백만 금화 따위는 없습니다, 믿어주십시오! 당신의 서비스가 돈이 드는 건 잘 압니다, 그래서 바로 이십오만을 제안드린 겁니다... 좋아요... 알겠습니다, 금화 오만을 더 얹어드리죠. 더 이상은 드릴 수 없습니다!";
			link.l1 = "좋아. 거래 성사다. 마지막으로 마르텐을 본 곳이 어디였지?";
			link.l1.go = "tibo_35";
		break;
		
		case "tibo_35":
			dialog.text = "그는 카라카스의 스페인 본토로 남쪽을 항해해 도착했고, 도지사 돈 디에고 프란시스코 데 케레스와의 알현을 성사시켰소. 뭔가 뇌물을 쓴 것 같은데, 돈 디에고가 로버트에게 스페인 왕실의 보호를 허락했거든. 그는 '볼티지어'를 팔고 지금은 중무장 갈레온 '인판타'의 선장이 되었소. 총독에게 뇌물을 주고 그런 대형 군함을 사고 장비까지 갖출 정도면, 정말 돈을 많이 모아뒀던 모양이오\n그러니 이제 그는 새 배를 타고 스페인 함대의 일원으로 카라카스에서 산토도밍고로 항해할 거요. 내 첩자가 알아낸 건 여기까지요. 마르텐을 잡을 유일한 기회는 그 스페인 함대를 따라잡는 것뿐이오\n만약 그들이 산토도밍고에 도착하면 끝이오. 로버트가 어디로 갈지 단서도 없고, 토끼가 굴에 숨듯이 사라져버릴 테니 우리는 영영 그를 찾지 못할 거요.";
			link.l1 = "알겠어. 내가 그들을 가로막을게.";
			link.l1.go = "tibo_36";
		break;
		
		case "tibo_36":
			dialog.text = "그리고 반지 낀 손가락도 잊지 마라! 그게 우리 합의의 필수 조건이야! 로버트가 확실히 죽었다는 걸 내가 완전히 확인하고 싶으니까!";
			link.l1 = "좋아. 시간 낭비하지 말자, 바로 출항하겠다!";
			link.l1.go = "tibo_37";
		break;
		
		case "tibo_37":
			DialogExit();
			AddQuestRecord("Sharlie", "27");
			Terrapin_CreateRoberConvoy();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			NextDiag.CurrentNode = "tibo_time";
		break;
		
		case "tibo_time":
			dialog.text = "마르텐이 아직도 카리브 해에서 꼴값을 떨고 있나, 선장?";
			link.l1 = "그에게 남은 시간이 얼마 없어!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_time";
		break;
		
		case "tibo_38":
			dialog.text = "마르텐이 그 존재로 카리브 해를 더럽히고 있나, 선장?";
			link.l1 = "이제는 아니오. 더 이상 폭스 대령을 두려워할 필요 없소, 그리고 당신의 카트린은 복수받았소. 여기 증거가 있소.";
			link.l1.go = "tibo_39";
		break;
		
		case "tibo_39":
			RemoveItems(pchar, "finger", 1);
			dialog.text = "그래... 저건 마르텐의 손가락이 틀림없소. 정말 감탄을 금치 못하겠군, 선장 "+GetFullName(pchar)+"! 당신은 정말로 쌓아온 명성에 걸맞은 사람이오.";
			link.l1 = "이제 결제 얘기로 넘어가 볼까, 티보?";
			link.l1.go = "tibo_40";
		break;
		
		case "tibo_40":
			AddMoneyToCharacter(pchar, 250000);
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You've received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "모두 준비됐소. 자, 보상 받아가시오.";
			link.l1 = "감사하오. 미리 준비해 주어서 기쁘오. 자, 헨리, 앞으로는 이런 곤란한 일에 휘말리지 말고 더 나은 친구들을 사귀길 바라오. 행운을 빌겠소!";
			link.l1.go = "tibo_41";
		break;
		
		case "tibo_41":
			dialog.text = "도와주셔서 감사합니다, 선장님! 제 모든 친구들에게 선장님을 추천하겠습니다. 행운을 빕니다!";
			link.l1 = "...";
			link.l1.go = "tibo_42";
		break;
		
		case "tibo_42":
			DialogExit();
			AddQuestRecord("Sharlie", "31");
			NextDiag.CurrentNode = "tibo_stop";
		break;
		
		case "tibo_stop":
			dialog.text = "예, 나리 "+GetFullName(pchar)+"? 나에게 볼일이라도 있소?";
			link.l1 = "아니오, Thibaut 나리. 그냥 잠시 들른 것뿐이오. 안녕히 계시오!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_stop";
		break;
		
		case "tibo_late":
			dialog.text = "아, "+GetFullName(pchar)+"...이봐, 뭐가 그렇게 오래 걸려! 자, 도대체 로버트 마르텐이 어디 있는지 아는 놈 없어?! 폭스 대령이 모든 걸 알아내기라도 하면, 난 정말 큰일이야...";
			link.l1 = "알겠소. 내가 너무 늦었군. 미안하오, Thibaut 나리, 하지만 급한 일들 때문에 지체되었소. 더 이상 시간을 뺏지 않겠소. 안녕히 계시오.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		case "tibo_over":
			dialog.text = "뭘 원하지, "+GetFullName(pchar)+"뭐? 잡담할 시간 없어. 더 중요한 일이 있거든. 폭스보다 먼저 마르텐을 찾아야 해...";
			link.l1 = "그래, 그래. 가고 있어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		// посланник от Мартэна
		case "envoy":
			dialog.text = "당신이 선장인가 "+GetFullName(pchar)+"?";
			link.l1 = "잘 찾아왔군, 친구. 다 듣고 있어.";
			link.l1.go = "envoy_1";
		break;
		
		case "envoy_1":
			dialog.text = "당신의 채무자가 내게 전하길, 일은 끝났고 물고기가 한 시간도 안 되어 그물에 들어올 거라 하더군. 그러니 서두르시오.";
			link.l1 = "알겠습니다. 감사합니다!";
			link.l1.go = "envoy_2";
		break;
		
		case "envoy_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Terrapin", "9");
			pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_cave.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.Terrapin_cave.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l2 = "location";
			pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
			pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;
		
		// Левассер в пещере
		case "levasser_cave":
			pchar.quest.Terrapin_LateDungeon.over = "yes"; //снять таймер
			dialog.text = "여기서 대체 왜 돌아다니는 거야? 너 누구야? 당장 대답해!";
			link.l1 = "도대체 넌 누구고, 왜 나한테 이런 멍청한 질문을 하는 거야?";
			link.l1.go = "levasser_cave_1";
		break;
		
		case "levasser_cave_1":
			dialog.text = "뭐라고?! 이 콧물 쪼끄만 녀석아! 내가 누군지 아느냐? 나는 이 섬의 총독, 프랑수아 르바쇠르, 르네 드 부아두플레 드 레트르 나리다! 이 섬에 있는 모든 것은 내 관할 아래 있지! 네놈도 내 땅에 있는 한 내 손아귀에 있다는 걸 명심해라, 꼬마!";
			link.l1 = "그래 그래... 바로 그 악명 높은 늑대님이 직접 오셨군? 길을 좀 잃은 모양이네, 르바쇠르, 르네 드 뭐시기 나리. 이제 끝이야. 총독 프랑수아 롱빌리에 드 푸앵시의 명령으로, 너는 직위에서 해임되고 즉각 사형을 선고받았다! 내가 곧 판사이자 형집행인이니라! 마지막으로 할 말 있나?";
			link.l1.go = "levasser_cave_2";
		break;
		
		case "levasser_cave_2":
			dialog.text = "";
			link.l1 = "네가 포기할 생각이 없는 것 같군, 나한테 자비를 구해도 소용없을 테니, 어서 칼을 뽑아라!";
			link.l1.go = "levasser_cave_3";
		break;
		
		case "levasser_cave_3":
			dialog.text = "제기랄! 푸앵시의 첩자다! 칼을 뽑아라! 저놈을 죽여!";
			link.l1 = "춤을 춥시다.";
			link.l1.go = "levasser_cave_4";
		break;
		
		case "levasser_cave_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
			int iScl = 30 + 2*sti(pchar.rank);
			for (i=5; i<=9; i++)
			{		
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2+50);
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Левассер в комнате таверны
		case "levasser_room":
			dialog.text = "여기서 대체 뭐 하는 거야? 누구냐? 당장 대답해!";
			link.l1 = "이런 일이! 전혀 예상 못 했군... 레바쇠르 나리 본인인가?";
			link.l1.go = "levasser_room_1";
		break;
		
		case "levasser_room_1":
			dialog.text = "그래, 내가 이 섬의 총독 프랑수아 르바쇠르, 르네 드 부아두플레 드 레트르 나리다! 이 섬의 모든 것은 내 관할 아래 있지! 네놈도 내 땅을 밟는 이상 예외가 아니다, 이 악당아! 질문에 답해라! 하사, 이 문을 잠가라. 이 자는 수상한 짓을 꾸미고 있다!";
			link.l1 = "정말 통찰력이 대단하시군, 르바쇠르 나리, 르네 드 뭐시기 영주님. 내가 여기 온 것이 당신에게는 전혀 반갑지 않겠지. 총독 프랑수아 롱빌리에 드 푸앵시의 명령에 따라, 당신은 직위에서 해임되고 즉각 사형을 선고받았소! 내가 곧 당신의 재판관이자 집행인이오!";
			link.l1.go = "levasser_room_2";
		break;
		
		case "levasser_room_2":
			dialog.text = "";
			link.l1 = "포기할 생각은 없어 보이는군, 그리고 나한테 자비를 구해도 소용없을 거다. 그러니 칼을 뽑아라! 너는 내 임무일 뿐, 개인적인 감정은 없어. 그저 국왕 폐하를 위해 일할 뿐이지, 하! 하사관, 내가 총독의 명령을 수행하는 동안 끼어들지 않는 게 좋을 거다!";
			link.l1.go = "levasser_room_3";
		break;
		
		case "levasser_room_3":
			dialog.text = "그 자 말 듣지 마시오, 하사! 저자는 스페인 첩자요! 저놈을 죽이시오! 경비병들, 도와라! 여기 스페인 놈들이 있다!\n";
			link.l1 = "사실 스페인엔 가본 적 없어, 그냥 나르본뿐이야.";
			link.l1.go = "levasser_room_4";
		break;
		
		case "levasser_room_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// девушка на балконе
		case "roof_girl":
			dialog.text = "아야! 도와줘! 군인들!";
			link.l1 = "조용히 해, 이 바보야! 네가 소리 지르지 않으면, 난 아무것도 안 할 거야!";
			link.l1.go = "roof_girl_1";
		break;
		
		case "roof_girl_1":
			dialog.text = "죽이지 마!";
			link.l1 = "말도 안 되는 소리 하지 마! 방금 10분 전에 어떤 남자가 여기로 달려갔어. 옷 잘 입은 귀족이었지. 어디에 숨었는지 말해! 그리고 못 봤다고 할 생각도 하지 마!";
			link.l1.go = "roof_girl_2";
		break;
		
		case "roof_girl_2":
			dialog.text = "티보 나리?";
			link.l1 = "그래, 그럼 그 자를 아는 거로군! 어디로 도망쳤지? 대답할 거야, 아니면 네놈 머리를 세게 흔들어서 정신 차리게 해줄까?";
			link.l1.go = "roof_girl_3";
		break;
		
		case "roof_girl_3":
			dialog.text = "아, 제발 저를 해치지 마세요! 티보 나리는 저쪽, 바다 쪽으로 도망쳤어요.\n그리고 기중기에서 뛰어내려 바로 물속으로 들어갔어요. 저렇게 높은 데서 떨어졌으니, 아마 죽었을 거예요...";
			link.l1 = "나는 그렇게 생각하지 않아. 그는 자살할 사람이 아니야. 안으로 들어가. 오늘 밤 여기 밖에 있으면 위험해.";
			link.l1.go = "roof_girl_4";
		break;
		
		case "roof_girl_4":
			dialog.text = "아야! 아야! 쏘지 마!";
			link.l1 = "뭐라고?!";
			link.l1.go = "roof_girl_5";
		break;
		
		case "roof_girl_5":
			DialogExit();
			LAi_SetActorType(pchar);
			PlaySound("People Fight\MushketShot.wav");
			DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;
		
		// Кати
		case "kathy":
			PlaySound("Voice\English\Armo02.wav");
			dialog.text = "너는 누구냐? 나를 죽이러 온 것이냐, 아니면... 더 끔찍한 일을 하러 온 것이냐?";
			link.l1 = "그런 일은 없소, 부인. 나는 당신, 캐서린 폭스를 세인트 존스에 계신 아버지께 돌려보낼 것이오.\n그 뒤에 아버지께서 명령을 어긴 죄로 당신을 꾸짖으신다면, 내 죄책감도 다시 느끼게 되겠지. 하지만 모든 걱정에도 불구하고 대령께서 살아 있는 딸을 보시고 기뻐하시길 바라오.";
			link.l1.go = "kathy_1";
		break;
		
		case "kathy_1":
			dialog.text = "신이시여, 감사합니다! 이게 꿈이란 말인가! 내가 누군지 모르는 거요? 자네는 프랑스인이자 가톨릭 신자인데, 내 동포들 손에서 나를 구하려고 여기까지 온 건가? 자네가 목숨을 걸고 구하려 한 게 겨우 폭스 대령의 딸 때문이란 말인가?";
			link.l1 = "내가 토르투가에 온 본래 이유는 전혀 달랐지. 하지만 아름다운 숙녀를 도둑놈들과 강도들의 손에 그냥 둘 수도 없었어.";
			link.l1.go = "kathy_2";
		break;
		
		case "kathy_2":
			dialog.text = "당신은 고귀한 신사로군요! 성함이 어떻게 되십니까, 나리?";
			link.l1 = ""+GetFullName(pchar)+". 선장 "+GetFullName(pchar)+".";
			link.l1.go = "kathy_3";
		break;
		
		case "kathy_3":
			dialog.text = "말해 주세요, 선장님, 정말 저를 세인트 존스에 계신 아버지께 데려다 주실 건가요?";
			link.l1 = "그래, 하지만 그는 프랑스인들을 그다지 좋아하지 않아. 뭐, 영국인 중에도 악당이 있다는 걸, 심지어 영국 장교들까지도 있다는 걸 내가 상기시켜 주지. 나도 그런 놈들 중 한 명을 직접 봤거든... 이름이 리처드 플리트우드였지.";
			link.l1.go = "kathy_4";
		break;
		
		case "kathy_4":
			dialog.text = "우리가 앤티가에 도착하면, 프랑스인들 중에도 진정한 기사들이 있다는 걸 아버지께 꼭 설득해 보겠소.";
			link.l1 = "정말 고맙군... 좋아, 내 수호천사들이 도시 지붕 위에서 내 길을 지켜보고 이미 우리 귀환을 기다리고 있기를 바라네.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;
		
		case "kathy_5":
			PlaySound("Voice\English\Armo01.wav");
			dialog.text = "지금까지 약속을 지킬 거라고는 믿지 못했어요! 요즘 저에게 정말 끔찍하고 비열한 일들이 많이 일어났거든요... 사람과 기사도에 대한 믿음을 되찾게 해주셔서 감사합니다, 선장님. 시간 되실 때 꼭 제 아버지를 찾아가 보세요!\n아버지는 당신 같은 분을 존경하세요. 그리고 당신이 프랑스인이라는 건 전혀 상관없어요. 아버지께서 당신 나라에 대한 생각을 바꾸시도록 제가 할 수 있는 모든 걸 다 해볼게요.";
			link.l1 = "고맙소, Catherine. 어쩌면 그대의 친절한 제안을 받아들일지도 모르겠군.";
			link.l1.go = "kathy_6";
		break;
		
		case "kathy_6":
			dialog.text = "꼭 그렇게 해주시길 바랍니다, 선장님. 저를 위해 해주신 일에 다시 한 번 진심으로 감사드립니다. 평생 잊지 않겠습니다.";
			link.l1 = "어서, 아버지께 빨리 가거라. 너를 보면 무척 기뻐하실 게다. 어쩌면 벌써 들판에서 돌아오셨을지도 모르지. 자, 아무튼 나는 이만 가야겠구나. 안녕!";
			link.l1.go = "kathy_7";
		break;
		
		case "kathy_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.lifeday = 0;
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
			pchar.questTemp.Terrapin_KathyReward = "true"; // награда за спасение Кати 160912
		break;
		
		// наш матрос
		case "terrapin_grot":
			dialog.text = "여기 계셨군요, 선장님! 정말 걱정 많이 했습니다! 기와 지붕 위를 그렇게 달리고, 아찔한 높이에서 그렇게 뛰어내리는 걸 보니 정말 대단했어요! 맙소사, 선장님이 무사하지 못할까 봐 얼마나 걱정했는지... 다시 배에 오신 걸 환영합니다, 선장님, 장정선 준비됐어요!";
			link.l1 = "좋아. 캐서린, 따라와!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;
		
		case "tibo_sailor":
			dialog.text = "안녕하세요, 나리. 당신이 선장입니까 "+GetFullName(pchar)+"?";
			link.l1 = "그래, 나다. 무슨 일이야?";
			link.l1.go = "tibo_sailor_1";
		break;
		
		case "tibo_sailor_1":
			dialog.text = "휴, 간신히 따라잡았군... 당신이 아는 신사, 앙리 티보라는 이름의 분을 대신해 왔소.";
			link.l1 = "헨리? 그리고 그 자가 뭘 원하지? 사랑하는 삼촌이 세상을 떠난 뒤, 뜻밖에 유산이 자기 손에 떨어진 기쁨이라도 나누고 싶다는 건가?";
			link.l1.go = "tibo_sailor_2";
		break;
		
		case "tibo_sailor_2":
			dialog.text = "티보 나리가 급히 당신에게 토르투가의 저택으로 가능한 한 빨리 와 달라고 요청했습니다.\n그분께서 당신에게 후하게 보수하는 일을 준비해 두셨답니다.\n또한, 한 이름을 꼭 전해 달라고 하셨습니다: 로베르 마르텐.\n이 이름이 당신의 흥미를 자극할 겁니다.";
			link.l1 = "그런가? 그런데 헨리는 왜 그렇게 생각했지?";
			link.l1.go = "tibo_sailor_3";
		break;
		
		case "tibo_sailor_3":
			dialog.text = "또한, 이것만으로 당신이 그를 찾아올 마음이 들지 않았다면, 그는 내가 다음 말을 꼭 전해 달라고 했소:\n'로베르 마르텐은 반드시 죽어야 한다'";
			link.l1 = "알겠어, 알겠어... 이제 좀 흥미로워지는데. 맹세한 두 친구가 막 다투기 시작했군... 네 말대로, 기회가 되면 헨리를 찾아가 볼게.";
			link.l1.go = "tibo_sailor_4";
		break;
		
		case "tibo_sailor_4":
			dialog.text = "티보 나리께서 방문을 미루지 말라고 하셨소. ‘물고기가 열흘 안에 그물을 빠져나갈 것이오’라는 말씀이셨소...";
			link.l1 = "그와 로버트는 말투가 똑같군. 좋아, 헨리에게 한번 가보지.";
			link.l1.go = "tibo_sailor_5";
		break;
		
		case "tibo_sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
			AddQuestRecord("Sharlie", "25");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
