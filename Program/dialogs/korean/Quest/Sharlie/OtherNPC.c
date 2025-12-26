// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "무엇을 원하시오?";
			link.l1 = "아니, 지금은 아니야.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "이런 젠장, 드디어 땅이 보인다! 일어나시오, 나리... 이름이 뭐였더라... 도착했소!";
			link.l1 = "아-아! 벌써 아침인가? 이 지독한 더위랑 습기는 또 뭐야?";
			link.l1.go = "Startsailor_1";
			link.l2 = "이봐! 샤를 드 모르! 귀족 나리잖아. 이런 더위에 어떻게 술을 마실 수가 있어? 제발 물이나 마시겠네.";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "익숙해지시오, 나리. 여기서는 이런 날씨밖에 없소... 더 나쁠 수도 있지.";
			link.l1 = "이보다 더 나쁠 수가 있겠어!? 난 린넨 셔츠 한 장만 입고 있는데 등에 땀이 줄줄 흐르고 있잖아!";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "곧 알게 될 거요, 하하! 지금이 허리케인 시즌일지도 모르지! 서두르시오, 나리. 장정선이 당신을 기다려주지 않을 거요. 마르티니크까지 수영해서 가고 싶진 않겠지?";
			link.l1 = "잠깐만 기다려 줄래? 내 검이 어디 있지? 아, 여기 있군...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "이제 더 이상 유럽이 아니오... 조심하시오, 나리. 요즘은 뒤숭숭한 시기라오. 아메리카 제도 회사가 마르티니크 섬을 종교 광신자들, 십자군인가 뭔가 하는 자들에게 팔았다는 소문이 돌고 있소. 아직까지는 갑판에서 해안을 바라봐도 별다른 이상은 못 느꼈소. 하지만 우리가 자리를 비운 사이에 많은 것이 변했을 수도 있지.";
			link.l1 = "십자군? 말도 안 돼!";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "헛소리든 아니든, 소문이 무성하네. 우리는 이미 골치 아픈 일이 산더미야. 정글의 식인종, 열대성 열병, 해적들, 골목길의 도적들, 거기에 스페인 놈들이랑 영국 놈들까지 있으니 말 다 했지...\n";
			link.l1 = "아, 또 시작이군... 지금 내가 겪는 유일한 문제라면 숨막히는 더위랑 모기뿐인데... 좋아, 준비됐어. 갈까?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "갑판 위로 올라가서 장선에 타시오, 나리. 카리브에 오신 것을 환영하오!";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "여기서는 다른 날씨란 없소, '나리'. 굳이 말하자면, 더 나빠질 뿐이오.";
			link.l1 = "날씨가 참을 수 없을 정도로 고약하군, 지난 몇 달간 내 동행들처럼 말이지. 군도에는 괜찮은 사람들이 좀 있기를 바란다.";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "그렇다면, 이제야 드디어 떠나신다니 우리 모두 기뻐할 것 같소, 나리. 배가 기다리고 있소. 너무 기뻐서 바지까지 벗지 마시오. 그리고 짐도 잊지 마시오 - 배는 더 멀리 나아갈 테니, 안 챙기면 영영 잊어버릴 수도 있소.";
			link.l1 = "네놈 즐기라고 내가 그들을 두고 가겠냐. 페소도, 검도 그대로네 - 도둑맞진 않은 것 같군.";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "우린 물론 정직한 사람들이지만, 조심하는 게 옳아 – 네 물건은 항상 잘 챙겨. 안 그러면 누가 주머니를 털지도 몰라. 옛 유럽처럼 말이지. 사실 어디서든 마찬가지야. 하지만 여긴 네가 살던 곳과는 달라. 어떤 광신도들이 여기 근거지를 차렸거든. 소문으론, 그 자들이 이 섬 전체를 몰래 사들였다고 해. 그러니 방심하지 말고 괜히 눈에 띄지 마라.";
			link.l1 = "무슨 헛소리야!";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "그게 소문이야. 내가 굳이 신경 써서 알려주고, 여기 머무는 걸 걱정해준 것만으로도 고마워해야지. 안 그랬으면, 그 연약한 가스코뉴 장미가 우리 작열하는 태양 아래 시들어버릴 수도 있었을 테니까. 헛소리든 아니든, 정신 똑바로 차려. 광신도들 없이도 골치 아픈 일이 넘치거든. 골목과 정글엔 산적, 바다엔 해적, 그리고 붉은 피부의 식인종들까지...\n";
			link.l1 = "자, 자! 내가 알아서 할 수 있어. 지금은 좀 덥긴 하지만, 나는 고향에서도 햇볕에 단련된 몸이야. 뭐, 노르망디 녀석들처럼 약하지 않지. 그리고 칼로 해결할 수 있는 일이라면 나만 믿으라고. 하지만 이 모기들은... 이건 정말 고문이야! 뭐, 내 짐은 다 챙겼고. 배도 준비됐다고?";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "기대하고 있소. 직접 올 수 있겠지, 나리? 고개 들고, 거기서 길 잃지 않길 바라오. 아, 그리고 군도에 온 걸 환영하오, 흐흐.";
			link.l1 = "그래, 고맙군. 위안이 되는 건 내가 여기 오래 있지 않을 거란 사실뿐이야.";
			link.l1.go = "Startsailor_6";
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// горожанин знает Мишеля
		case "Benuatalker":
			DelLandQuestMark(npchar);
			link.l1 = "실례합니다, "+GetAddress_FormToNPC(NPChar)+", 혹시 미셸 드 몽페르가 어디에 있는지 알려주실 수 있겠소? 분명 이 마을 어딘가에 있을 텐데.";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "흠... 네가 이런 질문을 아무렇지 않게 하는 걸 보니, 막 도착한 모양이군... 충고하자면 그만두는 게 좋을 거다, 안 그러면 곧 곤란한 일을 겪게 될 테니. 네 질문에 대해서는... 아바 신부에게 물어봐라. 교회에 계실 거다.";
			link.l1 = "감사합니다!";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "멈춰라! 당장 무기를 내려놓고, 나리, 우리를 따라오시오!";
			link.l1 = "이게 도대체 뭐야?";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_enterSoldiers_2");
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "만나서 반갑소, 드 모르 나리. 무슨 일로 오셨소?";
				link.l1 = TimeGreeting()+", 장교 나리. 제 형 미셸 드 몽페르에 대해 이야기하고 싶습니다. 물론 비공식적으로 말입니다. 이곳 카리브에서 그가 어떤 근무를 했는지 알아보려 합니다.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "심문은 어떻게 진행됐소? 쓸만한 정보라도 얻었소?";
				link.l1 = "오, 그렇소. 그래서 이 스페인 놈을 내 배로 데려가려 하오. 그는 중요한 증인이니, 추가 심문을 위해 세인트 크리스토퍼로 반드시 데려가야 하오.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "여기서 무슨 일로 오셨소, 나리?";
				link.l1 = "나는 내 형 미셸 드 몽페르를 만나러 왔다.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "나리, 조심스럽게 말씀드리오만, 지금은 군사 주둔지 안에 계십니다. 부디 그에 맞게 행동해 주십시오.";
				link.l1 = "예, 나리. 물론입니다.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = "나리, 조심스럽게 말씀드리지만 지금은 군사 주둔지 안에 계십니다. 부디 그에 맞게 행동해 주십시오.";
				link.l1 = "예, 나리. 물론입니다.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			DelLandQuestMark(npchar);
			dialog.text = "미셸 드 몽페르는 현재 우리 요새의 지하 감방 중 한 곳에서 경비를 받고 있으며, 이는 필리프 드 푸앵시 기사 나리의 직접 명령이오. 아래층으로 내려가시오. 그곳에 우리가 창고와 감방으로 쓰는 지하실이 있을 것이오. 길은 스스로 찾을 수 있을 거라 생각하오.";
			link.l1 = "감사합니다!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "안녕하십니까, 나리. 무엇을 도와드릴까요?";
			link.l1 = "고맙네, 병사. 하지만 괜찮으니 계속하라네.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "기다려 주셔서 감사합니다, 나리. 그럼, 미셸 드 몽페르를 찾고 계십니까? 그의 동생이신가요?";
			link.l1 = "예, 맞습니다. 저는 그의 동생 샤를입니다. 즉시 그를 만나야 합니다. 미셸이 곤란한 일에 처했습니까?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "유감스럽게도 사실입니다, 나리. 미셸은 아래 감방 중 한 곳에 갇혀 있습니다. 신세계 프랑스 식민지의 총독, 슈발리에 드 푸앵시께서 직접 체포 명령서에 서명하셨지요. 우리 모두 충격을 받았습니다. 당신의 형님은 남성적 미덕과 규율, 용기의 본보기이자 우리 기사단의 자랑입니다! 가장 괴로운 점은, 우리 같은 친구들이 그를 평범한 범죄자처럼 감옥에 가두고 지켜야 한다는 사실입니다! 우리는 그가 편히 지낼 수 있도록 최선을 다하고 있지만... 감옥은 결국 감옥이지요.";
			link.l1 = "무슨 죄로 고발당했지? 무슨 범죄를 저질렀나?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "총독부에서 미셸을 횡령 혐의로 고발했다오! 참으로 어이없는 일이오! 여기 있는 우리 모두는 정치적인 동기에서 비롯된 일임을 확신하고 있소. 비밀로 하나 말해주겠소. 미셸은 기사단을 위해 어떤 은밀한 임무에 참여해 왔소. 아마도 그가 알아서는 안 될 무언가를 알게 되었거나, 더 나쁘게는 권력자들의 노여움을 샀을 수도 있지. 하지만 돈을 훔쳤다고? 아무도 그걸 믿지 않소. 그건 진짜 이유가 아니라, 비겁하고 비열한 핑계일 뿐이오! 더 말할 필요도 없겠군. 형제가 널 만나길 고대하고 있으니, 직접 모든 것을 말해줄 것이오.";
			link.l1 = "좋아. 네 감옥은 어디에 있지?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "우리 지하 무기고가 바로 이 도시 안에 있지. 나를 따라와. 길을 안내해 주지.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_1");
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "여기에 도착했네. 여기가 우리 작전 기지야 - 예루살렘, 로도스, 몰타의 성 요한 군사 호스피탈러 기사단 카리브 지부지. 우리가 있는 곳 아래에 감방이 있지. 식당과 예배당을 지나 복도를 따라가게. 거기 계단이 아래층으로 이어져 있네. 감방이 늘어선 복도를 찾아보게. 맨 뒤쪽 근처에서 그대의 형을 찾을 수 있을 걸세.\n어서 가게, 샤를, 그리고 신의 가호가 함께하길. 미셸을 꼭 도와주게! 그는 결백하네, 여기 있는 모두가 맹세할 수 있네.";
			link.l1 = "이 구린 곳까지 온 이유가 다 내 형을 보기 위해서였지. 적어도 이 궁지에서 형을 빼낼 수 있길 바란다.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_2");
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "그래서 자네가 미셸 드 몽페르를 찾고 있었던 건가? 그리고 자네가 그의 동생이란 말이지?";
			link.l1 = "그래, 맞소. 나는 그의 동생 샤를이오. 지금 당장 그를 만나야 하오. 무슨 곤란한 일에 휘말린 게지, 그렇지 않소?";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "유감스럽게도 사실입니다, 나리. 미셸은 체포되어 우리 감옥에 갇혀 있습니다. 프랑스 식민지의 총독인 드 푸앵시 경이 직접 명령을 내리고 서명하셨습니다. 우리 모두 큰 충격을 받았습니다.\n당신의 형님은 남성다움과 결단력, 용기의 본보기이며, 우리 기사단의 자랑입니다! 가장 괴로운 점은 우리, 그의 친구들이 그를 범죄자처럼 감방에 가두고 지켜야 한다는 사실입니다! 우리는 그의 처지를 조금이라도 덜어주려고 애쓰고 있지만... 감옥은 결국 감옥이지요.";
			link.l1 = "그래서 무슨 혐의로 잡혀 있소? 무슨 죄라도 저질렀소?";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "말도 안 돼! 완전히 터무니없어! 미셸이 공금 횡령과 국가 자금 절도 혐의를 받았다니. 말도 안 되는 소리야! 우리 모두 그저 정치적 술수일 뿐이라고 확신하고 있네. 미셸은 기사단의 비밀 작전에 관여했었지; 아마도 그가 알아서는 안 될 무언가를 알아낸 걸지도 몰라.\n아니면 다른 무언가일 수도 있고. 하지만 돈을 훔쳤다니! 그걸 믿는 사람은 아무도 없어. 그건 단지 구실일 뿐, 이유가 아니야—이렇게 조잡하고 어리석은 구실이라니! 이제 그만 이야기하자. 네 형이 너를 몹시 기다리고 있어; 직접 모든 걸 말해줄 거라 확신하네.";
			link.l1 = "좋아. 감옥은 어디에 있지?";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "우리 지하 기지에 있어, 바로 이 도시 안에 있지. 나를 따라와. 길을 안내해 주겠네.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_3");
		break;
		//<-- cle
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "그리고 그는 난간에 몸을 기울이더니 카리브 해 자체가 초록색으로 변할 만큼 쏟아냈지! 하하하!";
			link.l1 = "알론소?";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "오! 샤를, 내가 방금 우리 무용담을 녀석들에게 들려주고 있었지!";
			link.l1 = "알아챘어. 들어봐, 알론소. 나... 선장이 되었어.";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "벌써? 최소 한 달은 걸릴 줄 알았는데, 하하!";
			link.l1 = "나는 아주 진지하다네!";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "나 혼자라면 당장이라도 동의했겠소. 하지만 나는 율리시스호에서 온 마흔 명의 선원들과 함께 있소. 그들이 자신의 미래를 내게 맡겼으니, 당신이 그들을 저버리지 않을 거라는 확신이 있어야 하오\n"+
			"무슨 배를 가지고 있지?";
			link.l1 = "배는 배다, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype),"Name")))+". 왜, 그게 그렇게 중요한가?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "있잖아, 율리시스호 이후로는 바크나 타르탄 같은 배에서 일하고 싶지 않아. 이미 당신 배를 봤고, 선원들도 마음에 들어 하더라고\n"+"이제, 돈 얘기지. 선불로 4,800페소를 요구하네. 그 다음엔—평소처럼 몫을 나누는 거야. 무리한 조건은 아니라고 장담하지. 할 수 있겠나?";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "아주 잘했군! 여기 네 돈이다.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "안타깝게도, 지금 내게 그 정도 돈은 없어.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "선장, 창고에 식량은 있소? 약은? 없다고? 그럼 곤란하군. 항해에 필요한 최소한의 물자라도 구해 오시오, 그 다음에 다시 이야기하지. 상점에 가서 필요한 것들을 사오시오.";
				link.l1 = "흠. 네 말이 맞아. 좋아, 그렇게 하지.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "쳇! 축하하오... 선장! 내가 당장 녀석들을 모아 당신 배로 가겠소.";
				link.l1 = "우리 모험을 다시 시작하게 되어 기쁘구나, 알론소. 배를 바다에 나갈 준비를 하게!";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "그래, 돈을 충분히 구하면 바로 돌아와라. 우리는 여기 선술집에 있을 거다.\n어차피 근처에 다른 배도 없으니 말이지. 그냥 계속 술 마시고 창녀들이랑 돈이나 펑펑 쓰고 있을 테니까, 하하!";
			link.l1 = "가능한 한 빨리 돌아오도록 하겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "돌아왔어, 선장? 나랑 내 동료들 고용할 준비 됐어? 우리 주머니가 가벼워지기 시작했거든, 다시 바닷바람을 맞아야겠어!";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "아직 아니야, 아직 모든 준비를 하고 있어.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "그래. 선금 받아라. 이제부터 내 밑에서 일하게 된 거다.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("이봐, 선장! 뭐 필요한 거야?","안녕하십니까, 나리. 무엇을 도와드릴까요?","좋은 하루요. 무엇을 원하시오?");
			link.l1 = RandPhraseSimple("너에게 물어볼 게 있어.","이 식민지에 대한 정보가 필요하오.");
			link.l1.go = "skipertalker_1";
			link.l2 = "그냥 인사하러 왔소. 아우 르부아르!";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("무슨 일이야?","무슨 일이오?");
			link.l1 = "들어봐, "+GetAddress_FormToNPC(NPChar)+"자, 그게 말이야... 내가 항해사를 찾고 있는데. 혹시 이 마을에 그 일에 어울릴 만한 사람을 알고 있나?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "항해사? 흠. 한 명 알고 있긴 하지... 그런데 문제가 하나 있어. 그 자가 지금 감옥, 채무자 감옥에 갇혀 있거든. 불쌍한 놈, 거의 한 달째 감방에 갇혀서 자기가 빚을 갚든 누가 대신 갚아주든 해야 풀려날 수 있지.";
			link.l1 = "빚쟁이? 흠... 이름이 뭐지?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "그의 이름은 폴크 들뤽이야. 그를 만나고 싶으면 감옥 사령관에게 물어봐. 하지만 네가 그의 빚을 갚지 않는 한 거기서 나올 수 없을 거야, 걔가 갚을 리는 없으니까, 하하하!";
			link.l1 = "어쩌면 그렇게 할지도 모르지. 정보 고마워, 친구.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "어떤 영광으로 이런 대접을 받는 것입니까, 나리?";
			link.l1 = "안녕, Folke. 간단해. 난 배는 있는데 항해사가 없어. 그런데 꼭 필요하지. 그래서 네 빚을 내가 갚았어...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "날 여기서 끌어내서 네 선원으로 삼으려고 했다는 거야?";
			link.l1 = "정확하오. 내가 너에게 쓴 돈을 금방 만회할 것 같구나. 자... 어떻게 되는지 두고 보겠네.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "감사하오, 나리. 이 썩고 눅눅한 감옥은 이제 진저리가 나네. 다시 한 번 배에 오를 수 있다면 더할 나위 없이 기쁠 것이오. 아, 바다여...";
			link.l1 = "합의에 도달해서 기쁘네, Folke. 한 가지 더 묻지. 배를 조종하는 것 말고 다른 재주도 있나?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "별걸 다 해봤습니다, 선장님. 예전엔 네덜란드 서인도 회사의 사략선에서 복무했었죠. 거기서 대포 다루는 법을 배워서, 필요하시다면 포술 장교로 일할 수 있습니다. 무역이나 백병전은 제가 좀 약합니다.";
			link.l1 = "나눠줘서 고맙네, 이제 나를 따라 배로 가게. 출항 준비를 하는 선원들을 자네의 노련한 눈으로 지켜봐 주었으면 하네. 그 다음엔 가능한 한 빨리 과들루프로 향하고 싶네.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "알겠어요, 선장님! 선실에서 기다릴게요. \n*바다에 있을 때 행동 메뉴를 사용하면 선실과 다른 구역에 들어갈 수 있습니다*";
			link.l1 = "고마워, Folke. 배에서 보자.";
			link.l1.go = "Folke_5";
			Log_Info("You have received amulet 'Merchant's Rosary'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "Your first officer is waiting for you. Use the action menu (ENTER) to go to the cabin.";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "좋은 루거선이군요, 선장님! 장비도 훌륭하고 선체도 튼튼한 아주 괜찮은 작은 배입니다. 이런 배라면 과들루프까지 안전하게 갈 수 있을 뿐만 아니라, 원한다면 카리브 해 전역을 누빌 수도 있겠어요.";
			link.l1 = "훌륭하군. 적어도 물 새는 고물선에 내 돈을 버리진 않았으니... 출항하기 전에 조언해 줄 게 있나, Folke?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "젠장, 이 슬루프는 체처럼 물이 새고 있습니다, 선장님. 과달루프까지 건너가는 것도 아슬아슬할 겁니다. 바스테르에 멀쩡히 도착하고 싶으시면, 즉시 조선소에 들러 수리를 해야 합니다.";
			link.l1 = "선택의 여지가 없었어, 이게 유일하게 팔고 있던 배였거든! 게다가 값도 엄청 비싸게 받더라고. 알다시피, 지금은 수리할 시간도 없고... 출항하기 전에 조언해줄 거 있나?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "자, 화약과 탄환은 충분히 준비되어 있습니다, 선장님. 당분간은 이걸로 충분하겠지만, 제때 보급하는 것만 잊지 마십시오.";
				link.l1 = "그건 말할 필요도 없지. 다른 할 말 있나?";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "아! 상기시켜 줘서 고맙네. 마침 나한테 탄환 한 상자가 있지!";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "탄약고에 탄약이 충분하지 않습니다, 선장님. 최소한 대포알, 체인샷, 폭탄 각각 백 발과 산탄 백 자루, 화약 이백 통이 더 필요합니다. 필요한 군수품을 구입해 주십시오, 선장님. 비용은 많이 들지 않겠지만, 해적이나 스페인 놈들에게 공격당할 때 우리 목숨을 구할 수도 있습니다.";
				link.l1 = "값진 투자군. 나는 상인에게 가보겠네.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "...그걸 들고 다닌 지 얼마나 됐지?";
			link.l1 = "거의 보름이지.";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
			Achievment_Set("ach_CL_164");
		break;
		
		case "Folke_8_2":
			dialog.text = "하지만 왜요, 선장님?!";
			link.l1 = "나는 잡동사니 모으는 걸 좋아해. 뭐가 쓸모 있을지 모르는 법이니까.";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "뭐, 너희들한테는 안됐군. 이 탄환은 우리 장난감 총에는 절대 안 맞아. 사실 이렇게 큰 탄환은 본 적도 없어. 저런 게 한 발만 맞아도 아델린은 바로 침몰하겠지.";
			link.l1 = "...";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "탄약 구입은 끝났습니까, 선장님?";
			if (bOk)
			{
				link.l1 = "그래, 했다. 다른 할 말 있나?";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "지금은 아니야, 아직 작업 중이거든.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "잘했네, 선원들을 위해 무기를 충분히 샀군. 무기가 부족하면 백병전에서 훨씬 더 많은 사상자가 나올 거야. 신께서 그런 일은 막아주시길. 화물창에 있는 무기 수량을 자주 확인하는 것, 잊지 마라\n필요한 것보다 조금 더 여유 있게 무기를 갖추는 게 현명하지. 젠장할 쥐들이 나무 손잡이랑 개머리판을 갉아먹는 걸 좋아하거든.";
				link.l1 = "알겠습니다. 아직 더 하실 말씀이 있으신가요?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "우리 선원들에게 무기를 충분히 지급하지 못하고 있소. 무기가 부족하면 백병전에서 훨씬 더 많은 사상자가 나올 것이오. 신께서 그런 일을 막아주시길 바라오. 내가 알기로 당신 선원은 마흔 명이오\n각자에게 무기를 충분히 사 주고, 여유가 된다면 더 사 두시오. 쉰 세트면 충분할 것이오. 필요한 것보다 조금 더 준비해 두는 게 현명하오. 빌어먹을 쥐들이 나무 손잡이랑 개머리판을 갉아먹는 걸 좋아하거든.";
				link.l1 = "그렇게 하지. 곧 돌아올게.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "무기 구입은 끝났습니까, 선장님?";
			if (bOk)
			{
				link.l1 = "무기는 창고에 있네. 아직 더 하고 싶은 말이 있나?";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "지금은 아니야, 아직 작업 중이거든.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "아니, 이제 다 된 것 같네. 식량도 충분하고, 선원들 럼도 챙겼지. 현명한 판단이야. 근무 끝나고 시원한 럼 한 잔만큼 만병통치약도 없으니까. 선원들은 매일 럼을 챙겨주는 선장을 사랑하고 존경하지. 선원들이 왜 럼이 다 떨어졌지?라고 묻는 소리는 절대 듣고 싶지 않을 거야.";
				link.l1 = "이제 출항할 수 있나?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "그래. 식량과 럼주 말이야. 배에 식량이 부족하면 정말 끔찍한 일이 벌어지지. 항상 필요하다고 생각하는 것보다 더 많은 식량을 싣고 다녀야 해. 항해가 얼마나 오래 걸릴지 아무도 모르는 법이거든. 바람이 완전히 멎거나 폭풍이 불면 어떤 계획도 다 망가질 수 있어. 식량이 떨어지면 선원들은 반란을 일으키거나 굶어 죽을 거야\n럼주는 식량만큼 절박하진 않지만, 항상 어느 정도는 실어두는 걸 강력히 추천하지. 근무를 마치고 마시는 시원한 럼 한 잔만큼 모든 병에 좋은 약도 없으니까. 선원들은 매일 럼을 나눠주는 선장을 사랑하고 존경하지\n그러니 우리가 필요한 보급품을 사오게. 최소한 식량 백 상자와 럼 열 통은 필요하다. '럼이 왜 다 떨어졌지?'라는 말을 선원들 입에서 듣고 싶지 않을 테니까.";
				link.l1 = "그대 말이 맞는 것 같군. 다시 상인에게 가서 이야기해 보겠소.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "우리 식량이랑 럼 사는 거 끝냈어요, 선장?";
			if (bOk)
			{
				link.l1 = "그래. 이제 출항할 수 있나?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "아니, 아직 작업 중이야.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "예, 선장님. 말씀하신 대로 닻을 올리고 북쪽 과들루프로 향할 수 있습니다.";
			// belamour legendary edition -->
			link.l1 = "잘했어, Folke. 네가 없었으면 나는 못 해냈을 거야.";
			link.l1.go = "Folke_13";
			link.l2 = "좋아, 일이나 시작하자. 네가 돈값을 하는지 한번 보자.";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "그럼 저를 항해사로 임명하시오. 그러면 갑판에서 제 자리를 지키겠소.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// <-- legendary edition
			dialog.text = "그럼 저를 항해사로 임명하시오, 그러면 갑판에서 제 자리를 맡겠소.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> копипаста LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeEng", 3.0);
			//NewGameTip("Welcome aboard your new officer! Press F4 to assign him as your Navigator.");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "출항 준비 완료입니다, 선장님!";
			link.l1 = "...";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "선장님, 저를 항해사로 삼으십시오, 아니면 곧 좌초할 겁니다.";
				link.l1 = "알겠어, 지금 할게.";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
	
		// штурман

	// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "죄송합니다. "+GetFullName(pchar)+"?";
			link.l1 = "맞소. 이번 일에 대해 내가 얼마를 드려야 하오, 나리?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "자기소개를 하겠습니다 - "+GetFullName(npchar)+". 나는 세자르 크레이그에게서 보내심을 받았소. 그 사람을 알겠지. 르 프랑수아의 선술집 주인이오. 그가 알기로는, 당신이 곧 과들루프로 떠난다 하더군. 그가 쉬운 돈벌이를 하나 제안하고 싶다 하오.";
			link.l1 = "흠... 흥미롭군! 그런데 세자르 크레이그가 어떻게 그렇게 잘 알게 되었지?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "간단하지, 선장. 지금 생피에르에 있는 배는 당신 배뿐이야. 귀 두 개, 눈 하나만 있으면 당신이 누구고 어디로 가는지 다 알 수 있지. 이 식민지에선 소문이 갈매기보다 더 빨리 퍼진다네. 자, 우리 제안 들어볼 생각 있나?";
			link.l1 = "물론이지. 돈 버는 일이라면 언제든 환영이야.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "이제야 말이 통하는군, 친구! 자네, 장사 수완이 보통이 아니구만. 자, 조건을 말해주지. 세자르가 급하게 와인을 과들루프에 보내야 해. 200통인데, 자네 배 창고면 거뜬히 실을 수 있지. 쉬운 일에 만 페소나 주겠다고 하네. 세자르는 급하고, 지금 항구에 있는 배는 자네 것뿐이야. 이런 알짜 제안, 흔치 않다는 거 인정하지?";
			link.l1 = "젠장, 만 페소라고? 좋아, 거래 성사다!";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "르 프랑수아로 가서 세자르와 이야기하게. 모든 건 그가 알아서 할 거야. 자네는 르 프랑수아 바로 앞 만에 닻만 내리면 돼. 실망시키지 마, 세자르가 자네를 설득하면 천 페소를 준다고 약속했거든...\n";
			link.l1 = "걱정 마시오, 이미 설득당했다고 생각하시오. 내가 출항할 준비가 되는 즉시, 바로 르 프랑수아로 항해하겠소.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "만세! 이제 내 천을 받으러 간다. 고마워, 친구!";
			link.l1 = "천만에요...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.location = "None";
		break;
	// пират-обманщик

	// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;

	// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "선장님, 승선대가 편성되어 준비 완료되었습니다! 명령을 기다리고 있습니다!";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "알겠어요, 선장님! 준비해, 녀석들아, 선장님 따라가! 하나, 둘, 셋!\n";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "젠장, 프랑스 지원군이다! 대열을 갖춰라! 로렌초, 진영으로 가서 경보를 울려! 죽어라, 이 개자식들아!";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;

	// страж истины
		case "spanish":
			dialog.text = "내가 그런 정보를 유포할 권한이 없다는 걸 이해하시오?";
			link.l1 = "내가 제때 개입하지 않았다면 생피에르가 스페인 놈들에게 유린당했을 거라는 걸 이해하시오? 내 형제가 사라졌고, 기사단도 버렸소! 분명 이유가 있었을 게요. 나는 필리프 드 푸앵시 나리의 대리인으로서 조사할 권한이 있소!";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "알겠소, 알겠소, 드 모르 나리. 질문에 답해 드리리다. 우선 진정하시오. 이제, 무엇이든 물으시오.";
			link.l1 = "미셸이 감금되기 전에 무슨 일이 있었지?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "미셸 드 몽페르는 토르투가에서 정권 교체를 모의하기 위해 몇몇 해적 남작들과 협상 중이었다.";
			link.l1 = "그건 이미 알고 있소. 또 뭐가 있소?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "그는 또한 스페인에 대한 또 다른 작전을 계획하고 있었소. 구체적으로 말하자면, 귀중한 화물을 실은 스페인 선박을 나포하는 것이었지. 미셸은 목표물을 무거운 코르벳함 '그리퐁도르'의 포대 아래로 유인해야 했소. 그가 이 작전을 준비하는 동안 우리는 한동안 미셸의 소식조차 들을 수 없었지.\n하지만 계획은 어긋났소. 스페인 수송선은 도착하지 않았고, 미셸 본인은 르 마랭 만 해안에 반쯤 죽은 채로 현지 어부들에게 발견되었소. 작전은 실패한 것 같았지.\n전쟁이란 원래 그런 법이오. 일이 잘못될 수도 있지. 미셸이 살아남은 것만 해도 기적이었소. 하지만 푸앵시 기사 나리는 분노에 휩싸였지. 그는 미셸이 기사단의 자금을 횡령했다고 몰아세우며 감옥에 가두었소. 물론 우리는 그런 누명 따위 믿지 않았지. 미셸은 정직한 사람이자 진정한 기사단의 기사요. 총독이 왜 그리 격노했는지는 신만이 아실 일이오. 어쩌면 푸앵시 기사 나리가 직접 말해줄지도 모르겠군?";
			link.l1 = "그럴 수도 있지. 그게 전부인가?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "유감스럽게도 더 할 말이 없소. 당신 형님의 작전 세부 사항은 본인과 드 푸앵시 기사만이 알고 있었소. 우리는 몰타의 성 요한 기사단의 기사들이오. 우리는 명령을 수행할 뿐이오.";
			link.l1 = "슈발리에가 미셸을 그렇게 신뢰한다면, 예전에 비밀 계획을 성공적으로 수행한 적이 있었던 게 분명하군요. 미셸이 성공적으로 해낸 일에 대해 알고 계십니까?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "틀림없소. 미셸 드 몽페르의 이번 실패는 그의 첫 번째였기에, 우리는 슈발리에의 반응에 크게 놀랐소. 얼마 전만 해도 '그리핀도르'는 미셸의 치밀한 계획 덕분에 은으로 가득 찬 스페인 보물 갤리온선을 나포했지. 그것만으로도 앞으로 수십 번의 실패를 만회하고도 남을 일이었소. 그런데도, 당신 형은 체포되었소.";
			link.l1 = "알겠소. 미셸이 생피에르에서 도망친 이유를 알고 있소?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "나는 미셸과 드 푸앵시 사이의 개인적인 갈등이 그가 체포된 이유였다고 의심하오. 분명히, 당신의 형은 슈발리에가 석방 후에도 계속 자신을 박해할 것을 두려워하여 미리 조치를 취한 것이오. 그리고 있지, 드 모르 나리 - 여기서 아무도 그의 결정을 탓하지 않소!\n그 사람은 기사단을 위해 용감하게 일해왔건만, 처음으로 실패했다는 이유로 중상을 입은 채로 악취 나는 감방에 던져졌소! 그 실패도 그리 심각하지 않았소, 아무도 죽지 않았고 배도 침몰하지 않았으니!\n참, 이 대화는 철저히 비공식적인 것이니 내가 방금 한 말을 맹세코 다시 반복하지 않을 것이오, 이해했소, 드 모르 나리?";
			link.l1 = "예, 나리. 이미 이 대화를 나눈 것도 잊었습니다. 말씀해 주시겠습니까, 생피에르에 대한 스페인군의 공격이 기사단이 스페인 선박을 습격한 것 때문에 촉발된 일일 수 있겠습니까? 혹시 나리께서 언급하신 그 은화 실은 스페인 갈레온 때문일지도요? 카스티야인들은 나리의 근거지를 찾아내는 데 아주 열성적이었습니다...\n";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "의심스럽군. 카리브 해에 기사단이 있다는 걸 아는 사람은 극히 드물고, 우리가 스페인에 대한 모든 출격도 신중하게 계획했지. 우리가 포로로 잡은 스페인 장교에게 물어보게. 지금쯤 우리 감방에서 그 불같은 카스티야 기질을 식히고 있을 테니. 이미 심문도 마쳤네. 생피에르 공격은 평범한 습격이었고, 스페인 귀족 라몬 데 멘도사 이 리바라는 자가 자기 이익과 프랑스 식민지를 겁주려고 조직한 일이었지. 에스코리알의 환심을 사려는 목적도 있었다네.";
			link.l1 = "내가 저 스페인 놈과 이야기하겠다. 어디서 그를 찾을 수 있지?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "아래층, 네 형이 갇혀 있던 그 감방이야.";
			link.l1 = "길은 내가 알아. 스페인 놈 심문하고 돌아올게. 추가로 물어볼 게 있을지도 몰라.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "이거 참, 별일이군! 내가 그 포로를 풀어줄 수 없다는 걸 알겠지? 저 악당이 생피에르 공격을 주도한 놈이야!";
			link.l1 = "장교 나리, 이 사람은 중요한 증인이오. 생피에르에 대한 공격은 단순히 전리품을 노린 습격이 아니었소. 돈 라몬 멘도사는 다른 무언가를 찾고 있었소. 우리는 확실한 동기를 밝혀내야 하오. 그러니 이 스페인인을 내게 넘기겠소, 아니면 드 푸앵시에게 허락을 청해야 하겠소?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "전능하신 하느님 맙소사... 좋아, 데려가라. 어차피 이 자식은 평범한 해적놈처럼 생피에르 광장에서 목을 매달 생각이었으니... 이제부터는 네 골칫거리다. 반드시 정의를 피해 도망치지 못하게 하라!";
			link.l1 = "틀림없소. 내가 이 스페인 놈에 대해 드 푸앵시 나리께 책임지겠소. 이 포로를 결박해서 항구의 내 장선으로 데려가시오.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "좋소, 선장.";
			link.l1 = "한 가지 더 묻겠소, 장교 나리. 미겔 디초소라는 이름이 기억나시오?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "아니. 처음 듣는 말이야. 왜 묻는 거지?";
			link.l1 = "확실합니까? 그 이름을 가진 사람을 이 막사에서도, 총독 관저에서도, 생피에르 어디에서도 본 적이 없다는 말입니까?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "아니, 못 봤어. 내가 온 곳에서는 스페인 놈들을 그리 좋게 보지 않거든.";
			link.l1 = "좋아. 뭐, 원래 그런 거지. 너무 쉬웠다면 재미없었을 테니까... 고맙네, 장교! 정말 큰 도움이 되었어.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "천만에요... 어떻게 생각하시오, 드 모르 나리, 지금 당신 형은 어디에 있을 것 같소?";
			link.l1 = "나도 그 질문의 답을 알고 싶군. 그리고 언젠가는 반드시 알아낼 거야... 조만간 말이지. 잘 있어!";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
	// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"! 네가 선장이냐 "+GetFullName(pchar)+"?";
			link.l1 = "그래, 나다. 무슨 일이냐?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "안녕하십니까, 선장님. 빈센테 신부님께서 저를 보내셨습니다. 당신께 드릴 것이 있습니다...";
			link.l1 = "빈첸토 신부님? 이제 더 이상 그분을 위해 일하지 않소. 디에고 데 몬토야의 충복인 알론소 데 말도나도를 보내 나를 죽이려 한 뒤로는 말이오. 존경하는 신부님께 이렇게 전하시오: 실패했다고.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "잠깐만요, 선장님. 비첸토 신부님께서 선장님의 이런 반응을 예상하시고 저에게 미리 경고하셨습니다. 각하께서는 결코 선장님께 해를 끼치실 생각이 없으시다는 점을 확신드립니다. 제발, 이 편지를 읽어보십시오. 정말, 정말 중요한 내용입니다.";
			link.l1 = "빈첸토 신부가 나에게 악의를 품지 않았다고? 흠. 혹시 나와 말도나도 돈에 대해 아무 말도 안 했던 건 아닌가? 내가 그대를 믿어야 할 이유가 없군.";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "이 편지를 받으시오, 선장. 읽어보고 스스로 결정하시오. 모든 그리스도교 세계의 운명이 그대 손에 달려 있음을 명심하시오. 결코 가볍게 여기지 마시오. 신의 가호가 함께하여 그대가 올바른 길을 걷기를 바라오!\n";
			link.l1 = "좋아, 편지를 내게 줘.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "여기 있습니다. 올바른 결정을 내리시길 기도합니다. 팍스 보비스쿰.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
	// падре Адриан
		case "adrian":
			dialog.text = "안녕하냐, 아들아. 주님께서 너와 함께하시길.";
			link.l1 = "아드리안 신부님께도 평안이 있기를. 각하께서 신부님이 저에게 부적과 약을 주실 수 있다고 말씀하셨습니다.";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "예, 물론이지요. 당신만을 위해 산티아고에서 특별히 들여온 화물이 있소. 여기 축복받은 부적들과 치유 물약들이 있소. 그리고 결정적으로, 전투에서 무적이 되게 해줄 희귀하고 유일한 오메토치틀리 팅크처도 있소. 이 모든 것이 다 너를 위한 것이란다, 아들아. 받아서 주님의 은총이 얼마나 좋은지 직접 느껴보거라.";
			link.l1 = "감사합니다!";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "더 치유 약초가 필요하다면, 매일 각각 한 병씩 드릴 수 있습니다. 필요하신 만큼 준비해 드리겠습니다.";
			link.l1 = "감사합니다, 아드리안 신부님. 명심하겠습니다.";
			link.l1.go = "exit";
			link.l2 = "좋아. 지금 당장 좀 필요해.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "신의 가호가 너와 함께하길, 아들아. 무엇을 원하느냐?";
			link.l1 = "치유 물약을 좀 사고 싶습니다.";
			link.l1.go = "potion";
			link.l2 = "지금은 별일 없어, 여행 준비 중이야. 그냥 인사도 할 겸 네가 어떻게 지내는지 보러 들렀어.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "물론이지, 아들아. 어떤 약이 필요하냐?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "그저 간단한 치료제일 뿐이오.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "건강을 주는 영약이오.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "해독제다.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "약초 혼합물.";
				link.l4.go = "potion4";
			}
			link.l5 = "폐를 끼쳐 죄송합니다, 신부님. 마음을 바꿨습니다.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "치유의 정수인가? 재료비로 90페소다, 아가야.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "감사합니다, 아버지.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "안타깝게도, 지금은 돈이 없어... 나중에 다시 올게.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "몸에 좋은 영약인가? 500페소다, 아가야.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "감사합니다, 아버지.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "유감이지만, 돈이 없어... 나중에 다시 올게.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "해독제? 200페소다, 아가.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "감사합니다, 아버지.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "유감이지만, 돈이 없어... 나중에 다시 올게.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "약초 혼합물인가? 900페소다, 아가야.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "감사합니다, 아버지.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "유감이지만, 돈이 없어... 나중에 다시 올게.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "‘내가 네게 건강을 회복시켜 주고, 네 상처를 고쳐 주리라, 주께서 말씀하시니라.’ 여기 약이 있네. 도미누스 보비스쿰!";
			link.l1 = "감사합니다, Adrian 신부님.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
	// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Captain "+GetFullName(pchar)+"?";
			link.l1 = "그래, 나다. 무슨 일이냐?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "미겔 디초소 선장에게서 당신에게 전할 말이 있습니다. 그가 당신이 자신을 안다고 하더군요.";
			link.l1 = "그래, 그 사람에 대해 들어본 적은 있소. 직접 만날 영광은 없었지만.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "디초소 선장은 그걸 바꾸고 싶어 하오. 그는 당신과 직접 만나고 싶어 하오. 스페인 본토 깊숙한 곳에 있는 잃어버린 인디언 도시 타야살로 떠나는 원정에 관해 제안을 하고 싶다더군. 그는 당신의 경험과 자신의 지식이 합쳐지면 만족스러운 결과를 낼 수 있을 거라고 내게 말했소.";
			link.l1 = "그게 그의 정확한 말이었소?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "맞소. 디초소 선장이 세인트 크리스토퍼에서 기다릴 것이오. 그는 캡스터빌 묘지의 큰 지하 납골당에서 기다릴 테니, 남의 눈과 귀를 피하기 위함이오.";
			link.l1 = "흠...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "디초소가 네가 망설일 거라고 미리 경고했지. 협상 중에는 어떤 결정을 내리든 해를 입지 않을 거라는 보장을 해주라고도 했어. 그리고 네가 어떤 섬에서 발견한 것은, 테야살에서 찾게 될 것에 비하면 그저 아주 작은 전채 요리에 불과하다고도 덧붙였지.";
			link.l1 = "그런가... 참 흥미롭군. 그런데 왜 디초소 선장 본인이 직접 오지 않고, 제삼자를 보낸 거지?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "돈 디초소가 처음에는 이슬라 테소로에서 너를 찾았고, 그 다음엔 여기에서, 그리고 지금은 네가 거기 있을까 싶어 세인트 크리스토퍼로 떠났어. 너는 필리프 드 푸앵시 그분의 직속 장교 아니냐? 네가 블루웰드에 도착할 경우를 대비해서 여기서 기다리라고 하더군.";
			link.l1 = "그럼 이제 다 이해됐군. 좋아, 알겠어. 시간 낭비하지 말고, 바로 캡스터빌로 가야겠어.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
	// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "드디어 만나는군, 선장 "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "미겔 디초소는 어디 있지? 그리고 변명하려 들지 마라. 내가 그 자의 진짜 정체를 알고 있고, 너도 알고 있다고 생각한다.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "이 사람이 바로 미겔 디초소 본인인가?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "정확히 짐작하셨소, 선장. 우리는 오랫동안 서로를 쫓아다녔지, 그렇지 않소?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "너 거짓말하는 거 딱 보면 알겠어, 이 친구야. 넌 디초소가 아니지. 나는 '산타 키테리아' 선장의 항해일지도 읽었고, 그의 생김새에 대해 여기저기 물어봤거든. 넌 전혀 안 닮았어. 얼굴에 기병도검 자국 흉터도 없잖아. 이봐, 아무리 흉내내기라도 그려 넣으려고는 했어야지!";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "그렇소. 내 이해가 맞다면, 우리는 잃어버린 도시 타야살에 대해 이야기하려고 여기 온 것이오?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "하! 그럼 이 연극을 계속할 필요도 없겠군. 미겔이 네가 교활한 녀석이라고 경고했지...";
			link.l1 = "미겔 디초소는 어디 있지?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "그분은 여기 없소. 내가 그분을 대신해 당신을 만나고 이야기할 권한을 받았소.";
			link.l1 = "나는 졸개와는 말하지 않겠다. 나는 왕을 찾으러 왔다. 그는 어디 있지?!";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "유쾌한 대화 상대는 아니군, 선장. 침착함을 잃었어.";
			link.l1 = "장난은 이제 그만하지. 알겠어. 또 매복이군. 너희 녀석들, 좀 새로운 수법 좀 생각해 봐라.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "하하, 또 맞췄군! 내 부하들이 지하 묘지로 내려가는 문 바로 뒤에서 널 기다리고 있지. 게다가 묘비마다 머스킷총병들이 숨어 있어서, 언제든 쏠 준비가 되어 있다네. 도망칠 길은 없어. 그러니 이 수법이 아무리 뻔하다 해도, 넌 제대로 걸려든 거야! 테야살을 보고 싶다는 욕망이 상식보다 앞섰군!";
			link.l1 = "싸움하기에 참 좋은 곳을 골랐구나, 이 쓰레기야. 너랑 네 도적 친구들 묻어줄 데가 바로 근처라 멀리 갈 필요도 없겠군.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "하하! 네 재치 마음에 드는군! 미겔이랑 똑같아! 뭐라 떠들든, 둘 다 한통속이지... 그가 시킨 대로 해주마 – 최대한 빠르고 고통 없이 지옥으로 보내주지. 무기 들어라, 녀석들!";
			link.l1 = "너보다 더 나은 사내들도 시도했지. 악마에게 안부나 전해라, 이 악당아!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "정말로 도시로 가고 싶으신가요? 이해합니다, 선장님, 하지만 좋은 생각 같지는 않습니다.";
			link.l1 = "그럼 우리가 여기서 무슨 이야기를 하려고 온 거지?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "너랑 길고 낭만적인 대화를 나눌 생각 없어. 네가 여기 있다는 것만으로도 나한텐 충분해.";
			link.l1 = "장난은 이제 그만하지. 알겠어. 또 매복이군. 너희 녀석들, 새로운 수법 좀 생각해 봐야겠어.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
	// командир абордажников
		case "newcastle_officer":
			dialog.text = "명령만 내리십시오, 선장님!";
			link.l1 = "우리는 정글을 지나 캡스터빌 묘지로 간다. 거기에 도착하면, 묘지 안으로 들어가지 마라. 정문 바로 밖에서 사격 위치를 잡고, 내가 안으로 들어갈 때 잘 듣고 있어라. 싸우는 소리가 들리면 즉시 안으로 뛰어들어와라.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "명령만 내리십시오, 선장님!";
			link.l1 = "우리는 정글을 지나 캡스터빌 묘지로 간다. 거기에 도착하면, 묘지 안으로는 들어가지 마라. 오솔길을 따라 사격 위치를 잡고, 묘지를 포위한 뒤 내가 안으로 들어갈 때를 잘 들어라. 이 모든 계획에서 매복 냄새가 진하게 난다. 적을 보자마자 즉시 공격해라.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "알겠어요, 선장님!";
			link.l1 = "좋아. 전진하라!";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;

case "Europe":
			PlaySound("Voice\English\military01.wav");
			dialog.text = "호바트 선장! 우리 첩자의 정보에 따르면 반란군이 이 영지에 숨어 있다고 하오. 당신이 쓸 수 있는 드라군 다섯 명이 대기 중이오. 건물을 수색해서 안에 숨어 있는 자들을 모두 붙잡으시오! 이런 쓰레기들에게는 자비를 베풀 필요 없소. 당신은 국왕의 이름으로 행동하는 것이오!\n";
			link.l1 = "예, 나리!";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//Индеец по квесту "Знакомство с индейцами"
		case "ZsI_ListKakao":
			dialog.text = "쳇! 바다의 아들!";
			link.l1 = "어... 뭐라고? 나한테 말하는 거야?";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "알겠다. 나는 코코아 리프다. 너와 볼 일이 있어, 바다의 아들.";
			link.l1 = "나는 코코아가 어떻게 생겼는지도 모르겠고, 왜 네 이름이 그거랑 같은지도 모르겠어. 하지만 좋아, 필요한 게 뭔지 빨리 말해.";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "쳇! 마을에 가서 권총 두 자루와 화약, 탄환 열 세트씩 두 개를 사 와라. 나한테 가져오면 보상이 있다. 바다의 아들이 기뻐할 거다.";
			link.l1 = "권총 두 자루에 탄환 스무 발? 그게 다야? 그럼 직접 사지 그래?";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "이해 못 하겠어, 창백한 놈아? 누가 나한테 총을 팔겠냐?!";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		//Sinistra Только если проходил квест "Каннибалы"
			{
				link.l1 = "있지, 나 예전에 마르티니크에서 너희 같은 놈들을 만난 적이 있어... 식인종 말이야. 그놈들이 여자 하나랑 남자 둘을 납치했지. 남자 하나는 구워서 잡아먹더군. 그때 그들 중 누구라도 총이 있었더라면, 지금 이렇게 얘기하고 있진 않았을 거야.";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "그런데 화기가 왜 필요하지, 코코아 잎? 누굴 죽이려고 하는 거야?";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "구-우! 코코아 리프는 도적이 아니다, 내 싸움은 오직 너희 부족의 전사들과만 있다. 창백한 얼굴들이 우리 땅에 와서 우리를 노예로 만든다. 코코아 리프 자신이 싸운다. 노예를 데려간다. 좋지도 나쁘지도 않다. 세상일이 다 그렇다. 인디언이든 백인이든 차이 없다. 불을 뿜는 무기만이 차이를 만든다.";
			link.l1 = "그런데 화기를 왜 필요로 하지, 코코아 잎? 누군가를 죽일 생각이냐?";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "싸우기 위해서지. 하지만 동등한 조건에서 말이야. 백인들은 화기를 가지고 있지만, 인디언들은 없어. 그건 불공평하지. 그리고 인디언이 화기를 갖는다는 건, 백인들에게 부당한 대우나 모욕, 모멸을 당하지 않기 위한 보호수단이야.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "알겠습니다, 선장님. 저 창백한 얼굴 놈들이 우리를 깔보고 있습니다.";
			link.l1 = "알고 있지. 유럽에 있을 때는 인디언들에게 진정한 신앙을 가르친다고 설교하고, 모두가 플랜테이션에서 평화롭게 함께 일한다고들 하지...";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "티칭이투는 선장 말을 이해하지 못하지만, 코코아 잎은 잘 안다. 그는 복수를 원한다.";
			link.l1 = "그런 것 같군... 너도 우리를 잡았던 놈들에게 복수하고 싶지 않아?";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "아마도. 하지만 티칭기투는 그렇게까지 하진 않을 거야. 티칭기투는 지금 네 곁에 있지. 그리고 티칭기투는 자기 머리로 생각해. 피가 너무 많이 흘러. 백인의 피, 인디언의 피. 고통도 너무 크고. 그건 옳지 않아.";
			link.l1 = "그래, 이미 상황이 안 좋은데, 코코아 리프가 총을 갖게 도와주면 더 악화될 거야... 하지만 그 녀석 말도 일리는 있어. 그리고 곧 선원들 월급도 줘야 하잖아.";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "머리를 좀 쓰시오, 선장.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "바다의 아들은 말이 많아. 콧수염 달린 여자 같군.";
			link.l1 = "누구? 설명해 봐, 코코아 잎. 나도 백인인데, 너는 백인들과 싸울 무기를 나한테 달라고 하잖아. 그거 모순 아니야? 왜 나한테 접근하는 거지?";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "나는 그 이상하게 차려입은 인디언과 나눈 대화를 엿들었소. 자네는 다른 백인들과는 다르군. 티칭기투를 이해하더군. 그리고 코코아 잎도 분명히 이해할 테지.";
			link.l1 = "오... 무기 값으로 뭘 내놓을 건데, 코코아 잎?";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "신들의 눈물. 너희는 그것을 진주라 부르지. 진주가 아주 많지.";
			link.l1 = "내 결정을 내렸어, 코코아 리프. 여기서 기다려. 나는 무기 상인에게 다녀올 거야. 필요한 걸 사고 돌아올게.";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "내 결정을 내렸어, 코코아 리프. 네가 필요한 건 이미 가지고 있어. 자, 여기 있다.";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "나는 결정을 내렸어, 코코아 리프. 쓸데없는 문제를 만들고 싶지 않아. 내게선 화기를 못 얻어. 이제 가봐.";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "쳇!";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "이런! 바다의 아들이 머스킷을 가지고 있나? 머스킷 값은 톡톡히 치르게 될 거다!";
			link.l1 = "아니, 하지만 내 배의 대포는 어때? 지금 당장 떠나, 코코아 리프. 우리가 들켜서 잡히기 전에.";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			Log_Info("You have received 180 small pearls");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "좋은 거래군! 바다의 자식아, 셀바로 들어가려거든 화기를 챙겨라. 인디언을 만나면 흥정을 해봐라.";
			link.l1 = "명심하겠다. 잘 가라, 코코아 리프.";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			ReturnOfficer_Tichingitu();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "코코아 리프가 기다릴 거야.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "쳇, 여기 원주민들이 모였나 보군!\n감옥으로 다시 가고 싶으냐, 이 개새끼야?\n여기서 뭐 하는 거요, 나리?";
			}
			else
			{
				dialog.text = "멈춰라! 여기서 뭐 하는 거요, 나리?";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
			EndBattleLandInterface();
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "이봐, 쓰레기들아, 이 훌륭한 시민을 기다리고 있었냐?";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "모든 창백한 얼굴들은 내게 다 똑같이 보여. 하지만 이 자는 처음 본다. 전사여, 네가 해야 할 일을 하라. 이젠 지겹구나. 코코아 잎은 숲의 정령들을 맞이할 준비가 되어 있다.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "지옥이 너를 기다린다, 숲의 정령들이 아니라.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "선장, 물러나시오. 내 앞길을 막지 마시오. 도시를 지키는 일은 중대한 임무요.";
			link.l1 = "그렇군... 하지만 이 인디언은 어쩔 셈인가?";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "인디언들에게 무슨 관심이 있으시오, 나리? 뭐, 그렇지... 예, 당신은 유럽에서 막 온 사람이니\n파리는 어떤가? 아직도 시궁쥐를 잡아 죽이나, 아니면 이제는 쥐들까지 성찬식에 초대하나? 여기선 쥐 대신 원주민이 있소. 그놈들은 버커니어들과 거래하고, 벌목꾼을 습격하고, 사람까지 잡아먹는다니까, 젠장\n사흘 전에 똑똑한 놈 하나가 이런 놈들에게 머스켓을 팔았지. 어찌 됐을 것 같소? 그 망할 놈들이 순찰 중이던 병사들을 전부 죽였소. 그 순찰대는, 참고로, 내 친구이자 동료가 이끌고 있었지. 우리는 그 배신자 식민자를 찾아내서 본보기로 태양 아래 매달아 말려버렸소. 인디언들에게 총을 넘기다니! 그건 반역이오! 프랑스를 배신한 짓이지! 그 유색 원숭이는 이미 여러 사건에서 얼굴을 비쳐서 우리가 한동안 쫓고 있었소\n이제 그놈도 곧 마땅한 최후를 맞이할 거요. 이제 가시오, 선장. 당신과 상관없는 일에 끼어들지 마시오. 이 전쟁은 당신 일이 아니오... 아직은... 아니면, 혹시 당신도?";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(믿을 만한) 그러니까, 경관 양반... 나는 샤를 드 모르 선장이고, 모스크바인 파데이의 손님이오. 우리도 이 인디언에게 관심이 좀 있소... 그러니 서로의 일에 간섭하지 맙시다. 동의하오, 중위?";
				link.l1.go = "ZsI_officer_Mir";
			}
			link.l2 = "신참에 대한 태도, 원주민에 대한 태도... 식민지 사람들, 원주민들... 아직 이 모든 걸 완전히 이해하지 못하겠지만, 지금 이 순간만큼은 중위 나리, 비교해보면 당신 쪽이 불리하오... 전투다!";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "맞소, 중위, 나는 아니오. 안녕히 가시오.";
			link.l3.go = "ZsI_officerKIll";
			StartBattleLandInterface();
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "크흠! 알겠습니다, 선장님. 파데이 나리께 안부 전해 주십시오. 분대, 순찰 재개하라!";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "이런!";
			link.l1 = "그래, 뭐, 나도 이게 통할 줄은 몰랐어. 자, 네 물건이야, 코코아 잎.";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "바다의 아들이 말을 잘하는구나. 인디언을 구하는 건 결코 쉬운 일이 아니지! 큰 보상이 기다리고 있다!";
			link.l1 = "이런 젠장, 엄청난 전리품이군... 그리고 구멍 뚫린 돌이랑, 뭔가 부적 같은 것도 있네.";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "바다의 아들이 머스킷을 가지고 있나? 머스킷을 비싼 값에 사라!";
			link.l1 = "아니, 하지만 내 배의 대포는 어때? 지금 당장 떠나라, 코코아 리프, 우리가 들켜서 잡히기 전에.";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "좋은 거래군! 바다의 아들아, 정글로 들어가면 화기를 챙겨라. 인디언을 만나면 흥정을 해봐라.";
			link.l1 = "명심하겠다. 잘 있어, 코코아 리프.";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "이런! 바다의 아들아, 잘못된 선택이군. 왜 그런 짓을 한 거지?";
			link.l1 = "으윽... 방금 전까지만 해도 옳은 일인 줄 알았는데... 이제는 잘 모르겠어... 결국 내 사람을 죽였잖아. 이제 어떻게 해야 하지? 만약 들키면 어쩌지? 젠장! 젠장!";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "이제 습격이 있을 거다. 군인들이 모두를 죽일 거야. 두 개의 순찰대는 용서하지 않아. 코코아 잎은 도망쳐. 그리고 너, 바다의 아들아... 왜지. 코코아 잎은 어차피 죽을 거야. 정령들이 그렇게 원하니까.";
			link.l1 = "오... 우리 거래 아직 유효한가?";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "나쁜 선택이군, 바다의 아들아. 하지만 고맙다. 큰 보상이 있지.";
			link.l1 = "생각보다 그렇게 크진 않군...";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "바다의 아들아, 살아남아 정글로 간다면 화기를 챙겨라. 인디언을 만나면 흥정을 하거라.";
			link.l1 = "앞으로 기억해 두겠소. 잘 가시오, 코코아 리프.";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//Торговец Барбье по квесту "Деньги на деревьях"
		case "MOT_Barbie":
			dialog.text = "안녕하십니까, 샤를 드 모르 선장. 제 이름은 샤를 바르비에입니다. 잠시 시간 내주실 수 있겠습니까?";
			link.l1 = "드 모르 선장... 그렇소, 내가 바로 그 사람이오! 계속 말씀하시지요, 바르비에 나리.";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = "동료를 만나는 건 언제나 반갑지요, 특히 이름까지 같은 분이라면 더더욱! 제안이 하나 있습니다, 선장님. 제가 생피에르까지 호위를 부탁드리고 싶은데요, 그리고...";
			link.l1 = "나도 생피에르를 알아! 하지만 거긴 이틀이면 갈 수 있잖아! 그리고 솔직히 말해서, 호위 역할은 아직 많이 서툴러. 이 배의 지휘를 맡은 지도 겨우 일주일밖에 안 됐거든.";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "당신의 솔직함에 감사하오, 선장. 샤를, 무례를 용서하시오만, 바로 당신이 내가 필요로 하는 사람이오.";
			link.l1 = "흠... 얼마 전에 비슷한 제안을 들은 기억이 있군. 그 일로 르 프랑수아 근처에서 해적 매복을 당했지.";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "그 사건에 대해 들었기에 당신을 찾아왔소\n첫째로, 나는 꽤 값진 화물을 싣고 있는데, 언제나 약탈자들이 도사리고 있지. 하지만 최근 르 프랑수아 근처에서 해적들을 물리친 당신의 승리는 그곳의 악당들에게 경계심을 줄 것이오\n둘째로, 파데이 모스코바이트와의 친분은 큰 신뢰의 표시요.";
			link.l1 = "설득력 있는 말씀입니다, 나리. 이 호의에 대한 보상은 무엇을 제안하십니까?";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "호의가 아니라, 선장, 서로에게 이득이 되는 거래요! 나를 제때 생피에르까지 호위해 주면 금화 마흔 닢을 드리겠소!";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(믿을 만함) 반대 방향으로 가는 길이니, 나리, 선불로 지불해 주셔야 하오.";
				link.l1.go = "MOT_Barbie_Torg";
			}
			link.l2 = "나쁘지 않은 제안이군. 어차피 그쪽으로 가는 길이야. 거래지!";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "귀중한 화물이라 하셨소? 유감이오, 나리, 지금은 모험에 질려버렸소.";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "그렇게 진지한 젊은이를 거절하기는 어렵군요, 선장. 여기 당신의 40두블룬이오. 바로 출항할까요? 시간은 곧 돈이니.";
			link.l1 = "오래 머무르지 않을 것이오, 나리. 곧 출항할 것이니.";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("You've received 40 doubloons");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "훌륭하군! 즉시 출항 준비를 하겠소!";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "알겠습니다, 선장님. 폐 끼치지 않겠습니다. 안녕히 계십시오, 좋은 하루 보내시길.";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Charles", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "모범적으로 호위해 주셔서 감사합니다, 선장님. 아무런 사고도 없어서 기쁩니다.";
				link.l1 = "거래하게 되어 기쁩니다, 나리. 이제 실례하겠습니다, 처리할 일이 많아서요.";
			}
			else
			{	
				dialog.text = "모범적인 호위를 해주셔서 감사합니다, 선장님. 아무런 사고 없이 도착하게 되어 기쁩니다. 여기 약속한 전액, 금화 마흔 닢을 드리겠습니다.";
				link.l1 = "거래하게 되어 기쁩니다, 나리. 이제 실례하겠습니다, 처리할 일이 많아서요.";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("You've received 40 doubloons");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "샤를...";
			link.l1 = "그래, 샤를? 무슨 고민이라도 있나? 무슨 일이라도 생겼나?";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "음, 자네가 믿을 만한 사람이고 파데이와도 아는 사이니... 봐, 상업이라는 게 위험한 일이잖아?";
			link.l1 = "그렇다면 그렇게 하죠.";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "과들루프에서... 알잖아, 그 사람한테 밧줄 한 묶음을 헐값에 구했지. 그걸 생피에르에서 빨리 팔고, 그 돈으로 빌렘스타드에서 되팔 커피를 살 생각이었어. 괜찮은 계획처럼 보였지.";
			link.l1 = "나는 당신의 청렴함을 의심하는 건 아니오, 나리. 하지만 이 모든 이야기가 꽤 수상하게 들리는군. 당신은 마치 화물이 금이라도 되는 양 말하지만, 내 배에는 이런 밧줄들만 가득하고 값도 형편없이 싸오.";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "샤를, 이 밧줄들은 최고의 품질로, 뛰어난 삼베로 만들어졌고 모스크바 차르의 공장에서 짜여진 것이오. 전략적 용도로 쓰이며 군함의 장비에 사용되지. 영국인들이 모스크바와의 교역로를 독점하여 이런 밧줄의 자유로운 거래를 금지하고 있소. 다른 나라들도 유럽의 조선소에 필요한 전량을 확보하려고 치열하게 경쟁하고 있지.";
			link.l1 = "그래서, 이게 밀수란 말인가?";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "그래. 안타깝게도 작년에 산티아고 밀수업자들과 사이가 틀어졌지. 거의 잊고 있었는데, 저놈들은 인맥도 끈질기고 앙심도 오래 간다네. 충고 하나 하지: 저들과 거래할 땐 화나게 하거나 약속을 어기지 마시오; 나중엔 아무리 해도 수습이 안 될 테니.";
			link.l1 = "감사하지만, 밀수에는 관심 없소.";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "안타깝군! 정직한 장사로도 제법 이익을 남길 수는 있지만, 큰 부를 쌓기는 어렵지.\n하지만 내가 이렇게 위험한 이야기를 괜히 꺼낸 건 아니야. 내게서 밧줄 한 화물을 사가게. 이 근처 밀수꾼들이 선술집에 자주 들르는데, 이 화물이라면 분명히 군침을 흘릴 거야. 생각해 봐! 오늘은 바다에 나가지 않고도 상당한 이익을 챙길 수 있을 거라고.";
			link.l1 = "화물값으로 얼마를 요구하시오?";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = "만 페소. 적은 금액이지, 그리고 밧줄을 밀수업자들에게 다시 팔면 상당한 이익을 남길 수 있어.";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "이런 기회를 놓친다면 평생 후회할 거요. 은화를 가져가고 물건을 내 배에 신속히 전달하도록 하시오.";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "이건 위험한 거래야, 친구. 서로 한발씩 양보하자고, 어때? 네 밧줄을 7천에 받아주지.";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "꽤 큰 금액이군요, 나리. 처지를 동정하오만, 그런 위험은 감수할 수 없습니다.";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "고맙네, 샤를! 자네 덕분에 파산을 면했어! 물건은 신속하고 최대한 조심스럽게 보내겠네\n같은 상인으로서 한 가지 조언을 하겠네. 괜찮은 경리 하나를 고용하면, 생피에르에서 커피를 구입해 빌렘스타트에서 팔게. 현지 자본가들은 식민지 상품에 후하게 값을 쳐주고, 그것을 유럽으로 수출해 큰 이익을 남기지. 자네 사업에 행운이 있기를 바라네, 친구!";
			link.l1 = "안녕히 가십시오, 나리.";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("You've received 30 ropes");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				Notification_Skill(true, 25, SKILL_COMMERCE);
				dialog.text = "고맙네, 샤를! 자네 덕분에 파산을 면했어! 물건은 신속하고 최대한 조심스럽게 보내도록 하겠네\n같은 상인으로서 한 가지 조언을 하겠네. 괜찮은 경리 하나를 고용하면, 생피에르에서 커피를 사서 빌렘스타트에서 팔게나. 이곳 자본가들은 식민지 물품에 큰돈을 주고, 유럽으로 수출해 막대한 이익을 챙기지. 자네 사업에 행운이 있길 바라네, 친구!";
				link.l1 = "안녕히 가십시오, 나리.";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("You've received 30 ropes");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				Notification_Skill(false, 25, SKILL_COMMERCE);
				dialog.text = "못 하겠습니다, 선장님. 제 상품은 중대한 물건이라 신중히 다뤄야 합니다. 대부분의 자유 선장들은 전략 물자를 거래할 엄두도 못 내지요. 유감스럽게도, 여기서는 흥정이 통하지 않습니다.";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "이런 기회를 놓친다면 평생 나 자신을 용서하지 못할 거요. 은화를 가져가서 물건을 내 배에 신속히 전달하도록 하시오.";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "상당한 금액이군요, 나리. 처지를 딱하게 여기오만, 그런 위험은 감수할 수 없소.";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "안타깝군! 안녕히 가시오, 선장.";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//Миниквест "Делюк"
		//Матрос Алонсо
		case "Del_Alonso":
			dialog.text = "문제야, 선장.";
			link.l1 = "그래?";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "우리 항해사가 체포되어 현지 감옥에 끌려갔어. 빚 문제라더군.";
			link.l1 = "뭐야, 또야?!";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "그 녀석 참 장난꾸러기입니다, 선장님.";
			link.l1 = "이런 재수 없는 타이밍이 있나! 항해사가 없으니 우리 여기서 꼼짝 못 하잖아. 또 내가 그 녀석을 빼내야겠군! 지휘관하고 얘기해 보지...\n";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "말씀드려도 되겠습니까, 선장님?";
			link.l1 = "앞서 가시오.";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "왜 이렇게까지 애를 써야 하지? 저런 놈은 배에 문제만 가져올 거야.";
			link.l1 = "내게 선택권이 있나? 다른 항해사는 거의 없으니, 내 선택지는 정말로 제한적이군.";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "맞아, 뛰어난 항해사는 구하기 힘들지. 하지만 아직 대가까지는 필요 없어, 그저 실력 있는 사람만 있으면 돼. 지난 일주일 동안 네 상황이 달라졌다는 거, 알고 있지? 이제는 선원 구하려고 바닥까지 긁어모을 필요 없어. 사람들이 네가 그 해적을 쓰러뜨린 얘기랑 네 인맥에 대해 떠들고 있거든. 선원들도 네 편이야, 선장. 우리도 너를 좋아해.";
			link.l1 = "안심이 되는군, 알론소. 그리고 선원들은 들루크에 대해 어떻게 생각하지?";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "빨리 배우는군, 선장. 선원들 말로는 그가 유능한 장교고 우리를 공정하게 대하긴 하지만, 굳이 신경 쓸 필요는 없다고 하더군. 큰 상선 하나가 장교들을 방금 내보냈으니, 선술집에 가보는 게 어때? 적임자가 분명 거기 있을 거야. 그리고 들뤽은 잊어버려. 그게 선원들 사이의 소문이야.";
			link.l1 = "조언 고맙네, 알론소. 자네라면 믿을 수 있을 줄 알았지. 이제 배로 돌아가서 내가 이 일을 정리하는 동안 당직을 서게.";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "아이 아이!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_Alonso_DlgExit");
		break;
		
		//Делюк
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "선장...";
			link.l1 = "궁금한 게 백만 가지나 되지만, 딱 하나만 묻겠소: 그동안 내내 내 곁에서 항해술을 가르쳐줬으면서, 어떻게 또 새 빚을 질 수 있었던 거요!";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "부끄럽지만 고백하자면, 선장님, 저는 선원으로 들어오기 훨씬 전부터 여기저기서 돈을 빌려왔습니다. 제 계획은 조용히 지내며 선장님의 배에서 일해서 빚을 모두 갚을 만큼 돈을 모으는 것이었죠. 그런데 여기 생피에르에서 어떤 여자와 엮이려고 배를 나섰다가, 그녀 바로 앞에서 병사들에게 붙잡히고 말았습니다. 마르티니크에서는 새로운 빚을 지지 않았습니다, 마지막 빚은 선장님이 갚아주셨으니 맹세합니다!";
			link.l1 = "너는 바보야, 들뤽. 네 탓에 내가 생피에르의 웃음거리가 됐잖아!";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "인상적이군, Folke. 일화 들려줘서 고맙다.";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "어쩔 생각이십니까, 선장님? 또 한 번 저를 구해주실 수 있겠습니까? 새 항해사를 구하는 건 쉽지 않을 텐데요...\n";
			link.l1 = "지금은 가만히 있어라. 내가 결정을 내릴 것이다. 은행가를 다시 찾아갈지도 모르겠군.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "어쩔 건가요, 선장님? 또 한 번 저를 빼내 주실 수 있겠습니까? 새 항해사를 구하는 건 쉽지 않을 텐데요...\n";
			link.l1 = "지금은 가만히 있어라. 내가 결정하겠다. 은행가를 다시 찾아갈 수도 있겠군.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = "딱히 갈 데도 없으니까...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_Folke_DlgExit_1");
		break;
		
		case "Del_Folke_10":
			dialog.text = "선장님, 감사합니다. 제 빚을 갚아주셨으니, 이제는 제 목숨까지 빚지게 되었군요. 진심으로 감사드립니다! 분명히 말씀드리지만, 이 세상 어디에서도 저보다 충성스러운 사람은 찾기 힘드실 겁니다!";
			link.l1 = "어떤 빚은 또 다른 빚을 져야만 갚을 수 있는 법이지. 일로 돌아가자, Folke. 바다에서 할 일이 아직 많으니.";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "잊지 마라, Deluc. 다음번엔 그냥 쏴버릴 거다.";
			link.l2.go = "Del_Folke_11b";
			Del_Ohrannik();
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "알겠어요, 선장님!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "예, 알겠습니다, 선장님!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			AddDialogExitQuestFunction("Del_Folke_DlgExit_2");
		break;
		
		//Штурман из таверны. Стандартный диалог, но с некоторыми изменениями (обучение найма для новичков)
		case "Del_shturman":
			dialog.text = "장교가 필요하십니까, 선장님?";
    		Link.l1 = "장교라고? 그런데 뭐를 잘하는데?";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "아니, 나는 다 갖고 있어.";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "이 바다에서 내가 최고의 항해사다. 의학에도 조금 아는 게 있지. 그리고 당신을 위해 한 가지 호의를 베풀고 당신 밑에서 일할 준비도 되어 있다.";
			Link.l1 = "그래서 얼마나 원하는 거지?";
			Link.l1.go = "Del_price";
			Link.l2 = "그대는 어떤 전문가인가?";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "유감이지만, 나는 이미 항해사가 있소.";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "4,000페소로 합의할 수 있을 것 같군.";
			Link.l1 = "그건 좀 심하지 않아?";
			Link.l1.go = "Del_trade";
			Link.l2 = "동의하오. 이제부터 자네도 우리 선원이라 생각하시오.";
			Link.l2.go = "Del_hire";
			Link.l3 = "너는 이 돈의 가치도 없어.";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "마음이 바뀌었습니까, 선장님? 새 항해사를 두는 것도 나쁘지 않겠다고 생각하셨나요?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "그런 셈이지. 얼마를 원하는가?";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "그래서 너는 뭘 할 수 있는데?";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "나는 전부 다 갖췄어. 또 보자.";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "좋아... 2500페소라면 동의해 줄 수도 있겠군. 어때?";
				Link.l1 = "이제야 좀 낫군. 합류했어.";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "죄송합니다, 선장님, 하지만 저는 제가 요구한 만큼의 가치가 있습니다. 그게 너무 부담스럽다면 다른 사람을 찾아보시지요.";
				Link.l1 = "좋아, 동의하네. 데려가 주지.";
				Link.l1.go = "Del_hire";				
				Link.l2 = "그렇게 할 생각이오. 안녕히 계시오.";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "감사합니다, 선장님. 당신의 선택을 후회하지 않을 것입니다.";
					Link.l1 = "그러길 바라오.";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "선장, 돈이 부족한 것 같군! 미안하지만, 외상으로는 일하지 않아.";
					Link.l1 = "오, 젠장!";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "감사합니다, 선장님. 당신의 선택을 후회하지 않을 것입니다.";
					Link.l1 = "그러길 바라오.";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "선장님, 돈이 부족해 보이시는군요! 미안하지만, 외상으로는 일하지 않습니다.";
					Link.l1 = "오, 젠장!";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "내 술만 다 마시고 갈게, 선장. 그리고 곧 배로 가겠어. 걱정 마, 제시간에 도착할 테니까.";
			Link.l1 = "좋아. 늦으면 갑판 청소 시킬 거야!";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			DialogExit();
			AddDialogExitQuestFunction("Del_shturman_DlgExit");
		break;
		
		//Квест "Травля крысы"
		//Капитан корабля Хейтер
		case "TK_Kapitan":
			dialog.text = "알았어, 알았다고! 젠장, 항복할게!";
			link.l1 = "이제 네놈은 내 포로다. 하지만 곧 생피에르에서 교수형을 맞이하게 될 거다.";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "이제 끝인가... 어떻게 내가 어디 있는지 알았지?";
			link.l1 = "총독께서 직접 상황을 설명해 주셨소.";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "정말 개자식이군! 내 계획을 눈치채고는 다른 선원들에게 본보기를 보이려고 자기 소굴 앞에서 대놓고 나를 엿먹이기로 한 거야!";
			link.l1 = "각하께 또 한 번만 무례를 범하면, 생피에르로 가는 여정이 아주 빠르고 잊지 못할 경험이 될 것이오.";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "어? 나는 자네 나리 얘기하는 게 아니야, 친구. 나는 착한 자크 얘기라고\n젠장, 소문이 사실이었군! 바르바종이 내가 위협이 된다고 느껴서 날 자기 길에서 치우려고 총독에게 넘긴 거였어. 그래서 자네가 내 정확한 위치를 알았던 거고, 내가 완전히 방심한 틈을 노렸지, 하하!";
			link.l1 = "넌 망상에 빠졌군. 마르티니크의 총독이 해적 두목과 거래할 리 없지!";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "그래, 그렇지. 직접적으로는 아닐지 몰라도, 바르바종하고 거래를 한 것 같아. 그 사람 입장에선 편하지. 위험한 해적은 교수형에 처하고, 보고서도 그럴듯하고, '군사 작전 비용'도 정당화되지. 나도 복무했거든? 그래서 거기 사정은 잘 알아. 그런데 너는? 주둔군에서 복무하나?";
			link.l1 = "나는 내 조국을 위해 봉사하오, 이 대화는 여기서 끝이오. 감방에 온 것을 환영하오.";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "잠깐만, 이봐. 난 카스티야 사람이 아니고, 오늘 바다에 나가서 프랑스 상인들을 약탈한 것도 아니야. 나도 나름대로 원칙이 있다고, 젠장! 우리 거래 좀 해볼까?";
			link.l1 = "헛소리 그만해라, 해적. 감방에 쳐넣어라.";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "목매달리는 걸 피하려는 거야?";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "여기서 확실한 정보를 잡았어. 나를 풀어주면 네 몫도 챙겨줄게. 내 목숨 값이야 은화 몇 천 개면 되겠지만, 내가 훨씬 더 많이 벌게 해줄 수 있어 – 그것도 세금 없이.";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "그거 꽤 솔깃한 제안이군... 하지만 해적질은 내 전문이 아니지.";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "나는 해적이 아니야!";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "네가 결정해, 친구. 운 좋은 사내가 될지, 원칙만 지키는 무일푼 선장이 될지는 말이야.\n진짜 돈과 자유를 원한다면, 뭐든 다 해봐야 해. 기회가 오면 잡아.";
			link.l1 = "정말 말솜씨가 대단하군...";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "음... 내가 그대를 생피에르로 데려가야겠군. 그게 옳은 일인 것 같소.";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "그럼 지옥이나 가라!";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "그럼, 거래하는 거지?";
			link.l1 = "그래. 네 우두머리가 누구인지 말하면, 풀어주겠다.";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "헨리라는 바크에 똑똑한 영국인이 타고 있어. 그 친구는 프랑스 플랜테이션에서 윌렘스타드로 물건을 옮기며 짭짤하게 한탕 벌 준비를 하고 있지. 곧 마르티니크에서 퀴라소로 떠난다더군. 일은 쉽지 - 호위도 없고, 바크에는 값진 물건만 잔뜩 실려 있는데 방어는 허술해. 너무 오래 지체하다 보니 소문이 돌기 시작했어. 내 조언 한마디 해줄까, 친구? 선술집에서 쭈뼛거리지 마. 현지인들에게 술 몇 잔 돌리면 비밀 몇 개쯤은 술술 풀릴 거야.";
			link.l1 = "왜 호위가 없지?";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "영국인이 큐라소에서 조용히 장사를 하려면 달리 방법이 있겠나? 영국과 네덜란드가 대놓고 전쟁 중인데, 무역 허가증 받는 것도 번거롭고 값도 비싸지.";
			link.l1 = "하지만 프랑스와 영국 사이에는 전쟁이 없잖아. 내가 중립 선박을 공격하면 어떻게 되는 거지?";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "조용히만 움직이면 문제없어. 선원들이 네 무용담을 가까운 항구에서 떠벌리긴 하겠지만, 네가 영국이나 네덜란드 배만 골라서 털지 않는 한 괜찮을 거야. 프랑스 깃발을 달고 헨리 호에 접근해. 포탄은 산탄으로 장전하고, 거리를 좁혀서 흑기를 올려. 몇 발 쏘고, 배에 올라타. 간단하지, 이 친구야.";
			link.l1 = "두고 보자고. 약속은 지키겠으니 널 풀어주지. 후회할 일 만들지 마라.";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "안 해. 사냥 잘 해, 친구.";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//Диего и Гийом за столиком по квесту "Встреча с Диего"
		case "VsD_DiegoAndErnat":
			dialog.text = "... 네 도박 문제는 내가 처리할게. 이봐! 정신 좀 차려, 이 사람아! 정신 못 차리면 내가 직접 정신 차리게 해줄 테니까.";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "나리, 실례하오나, 지금 좀 성가시군요.";
			link.l1 = "네, 물론이지요. 좋은 하루 보내십시오, 신사 여러분.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_DiegoInTaverna_3");
		break;
		
		//Гийом Дюбуа по квесту "Встреча с Диего"
		case "VsD_GiumDyubua":
			dialog.text = "드 모르 선장! 잠깐만요!";
			link.l1 = "예, 부관?";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "당신 따라가기도 벅찼소. 약간의 문제가 생겼습니다, 선장님. 이거 완전 엉망이군요!";
			link.l1 = "숨을 좀 고르고 진정하십시오.";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "그래, 그래. 이봐, 대포를 다 실은 다음에 창고에 아직 공간이 남아 있나?";
			link.l1 = "저도 아직 익숙하지 않아서 확실하진 않지만, 아마 있어야 할 거라고 생각해요.";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "훌륭하군! 사령부에서는 포르토 벨로 작전을 최대한 지원하고자 전쟁선에 화약 200통을 추가로 보내라고 명령했네. 많아 보이지 않을 수도 있지만, 몇 번의 추가 일제사격이 전세를 뒤집을 수도 있지!";
			link.l1 = "알겠소, 중위. 내 할 일은 준비됐소. 화약을 장전하시오 – 전혀 개의치 않으니.";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "감사합니다, 선장님. 바로 하역반에게 알리겠습니다. 다행히 아직 그들은 작업을 끝내지 않았습니다 "+PChar.Ship.Name+"' 아직이오. 임무에 행운을 빌겠소!";
			link.l1 = "고맙소, 지금까지 꽤 혼란스러웠지만. 안녕히 계시오, 중위.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//Фульк или Алонсо по квесту "Встреча с Диего"
		case "VsD_FolkeAlonso":
			dialog.text = "이런, 선장님! 하늘에 감사해야겠군요, 무사하셔서!";
			link.l1 = "무슨 일이야?! 내 배에 무슨 일이 생긴 거지?!";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "모르겠습니다, 선장님! 저는 그냥 최근에 만난 현지 여자에게 작별 인사만 하고 있었어요... 이런 젠장! 유제니!";
			link.l1 = "그녀는 죽었어, "+npchar.name+". 미안하지만, 지금은 집중해서 우리 선원 중에 다친 사람이 있는지 확인해야 해.";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "우린 서로 거의 알지도 못했는데... 아아! 젠장! 보고드립니다, 선장님: 폭발이 일어났을 때 대부분의 선원들은 다행히도 육지에 있었습니다. 녀석들이 다음 큰 항해 전에 휴가를 즐기고 있었거든요. 하지만 배를 지키던 감시조는... 살아남은 이가 없을까 두렵습니다. 주위를 좀 보십시오! 이 부두까지도 파편에 맞아 다치거나 죽은 사람들이 있습니다! 우리 둘이 멀쩡한 게 기적입니다.";
			link.l1 = "배는 어쩌지? 괜찮은 거야?!";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "정말입니까?! 실례했습니다, 선장님. 확실히 말하긴 어렵지만, 폭발은 아래가 아니라 상갑판에서 일어난 것 같습니다. 현재 불길은 보이지 않고, 큰 피해는 피한 듯합니다.";
			link.l1 = "...";
			link.l1.go = "VsD_FolkeAlonso_5";
			
			VsD_AfterVzriv_1();
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			AddDialogExitQuestFunction("VsD_AfterVzriv_2");
		break;
		
		case "VsD_Komendant":
			dialog.text = "이런 망할, 선장님?!";
			link.l1 = "나도 같은 걸 묻고 있소, 대령!";
			link.l1.go = "VsD_Komendant_1";
			VsD_AfterVzriv_3();
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "조심하시오, 드 모르! 자네는 해군에게서 이 임무를 받아들였고, 무거운 대포들을 맡았지. 그 대포들은 왕실의 재산이자 전략적으로 중요한 물건이오! 이 대포들이 전체 작전에 얼마나 중요한지 알고 있나?! 자네의 부주의로 인해 거의 400명의 병사와 프랑스 군함 한 척이 위험에 처했소! 자네는 여기서 반역죄로 재판을 받게 될 것이오!";
			link.l1 = "진정하시오, 대령님! 기적적으로 내 배가 살아남았고, 당신의 소중한 화물도 대부분 멀쩡하오... 대부분은 말이오.";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "대체 '대부분'이라는 게 무슨 뜻이야?!";
			link.l1 = "마지막 순간에 당신의 부하 중 한 명이 실은 화약 200통이 손상되지 않았다고는 장담할 수 없습니다. 그 화약은 원래 맨 마지막에 실으려던 것이었고, 아마도 폭발한 것도 그것들이었을 겁니다.";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "이게 무슨 헛소리냐, 샤를? 무슨 부관? 무슨 화약? 나는 그런 명령 내린 적 없다!";
			link.l1 = "이 중위는 자네 주둔지에서 온 사람이었던 것 같소. 이름은 묻지 않았지만, 작전에 대해 알고 있는 듯했소.";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "아, 젠장! 카스티야 놈들도 더러운 수를 쓰려는 모양이군... 이 불미스러운 일은 내가 처리하겠소, 선장. 하지만 자네는 아직 할 일이 남았지. 자네 배가 정말 항해할 수 있을 만큼 멀쩡한지 확실한가?";
			link.l1 = "물에 떠 있긴 하지만, 확실히 대대적인 수리가 필요해.";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "그럴 시간 없어, 선장. 즉시 출항해서 임무를 완수하시오. 지체하기엔 위험이 너무 크오.";
			link.l1 = "제발 하루만이라도 쉴 수 없는 거요? 여기 조선소에서 필요한 수리는 다 할 수 있잖소! 그리고 내 선원들은 어쩌라고?! 분명히 사상자도 있을 텐데!";
			link.l1.go = "VsD_Komendant_6";
			VsD_AfterVzriv_4();
		break;
		
		case "VsD_Komendant_6":
			dialog.text = "혹시 못 보셨다면, 조선소에 불이 났소. 우리가 아직 그게 고의인지, 아니면 폭발의 여파인지 조사 중이오. 다만 부상자들은 치료를 받을 것이며, 전사자들의 장례 비용은 국왕이 부담할 것임을 약속드릴 수 있소.";
			link.l1 = "진심이오? 그게 최선이오?";
			link.l1.go = "VsD_Komendant_7";
			VsD_AfterVzriv_5();
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "선장님, 프랑스가 긴급히 당신의 도움이 필요합니다. 제가 판자를 제공하겠으니, 잘만 하면 자메이카에 도착할 때쯤 당신의 배는 거의 완전히 수리될 것입니다.";
			link.l1 = "실례하지만, 어떤 판자를 말씀하시는 거죠? 그리고 왜 자메이카입니까?";
			link.l1.go = "VsD_Komendant_8";
			VsD_AfterVzriv_6();
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "당신의 선원들은 바다에서 판자를 이용해 긴급 수리를 할 수 있습니다. 판자는 주요 수리 자재입니다.\n그리고 자메이카는 포르토 벨로로 가는 항로 중 하나와 꽤 가깝습니다. 시간을 낭비하지 않는다면 그곳에서 수리를 마치고 선원도 충분히 모집할 수 있습니다.";
			link.l1 = "그러면 좋소. 즉시 출항하겠소, 대령.";
			link.l1.go = "VsD_Komendant_9";
			
			VsD_AfterVzriv_7();
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			AddDialogExitQuestFunction("VsD_AfterVzriv_8");
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "왜 이렇게 서두르세요, 자기야?";
			link.l1 = "자기야, 지금 이럴 시간 없어. 무슨 일이 벌어지고 있는지 안 보여?";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "아, 지금의 곤경도 심각하지만, 그대의 손을 보니 앞으로 더 큰 일이 닥칠 것 같군.";
			link.l1 = "내 손을 굳이 보지 않아도 누구나 알 수 있지, 게다가 내 손엔 장갑까지 끼고 있다네. 좋아, 장단 맞춰주지. 요즘 재앙을 피하려면 얼마를 내야 하나?";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "나는 그런 힘 없어, 잘생긴이. 설령 있다 해도, 그걸 감당할 수는 없지. 하지만 네 배라면 도와줄 수 있어... 그 아가씨 상태가 말이 아니구나, 내 사랑.";
			link.l1 = "나는 네 집시 무리들이 목수 일에 야망을 가진 걸 본 적이 없어.";
			link.l1.go = "VsD_Tsyganka_3";
			
			VsD_Final_1();
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "그대, 자기야, 자네도 목수는 아니잖아. 널빤지 몇 개만으로 배가 고쳐질 거라 생각하나? 대목수가 없으면 널빤지는 오히려 짐만 될 뿐이야...";
			link.l1 = "아니면?";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "현지인들이 숭배하는 강력한 부적이 있소. 나무가 그 부적의 뜻대로 휘어지고, 목공에 익숙하지 않은 자도 그것을 착용하면 능숙해진다 하오. 겨우 천 페소면 드릴 수 있소, 그대여.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "좋소, 거래하겠소. 나는 가능한 모든 도움이 필요하오.";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "네 마법에 쓸 시간 없다. 평안히 가라, 마녀야, 그리고 참견하지 마라.";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			AddDialogExitQuestFunction("VsD_Tsyganka_Net");
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			AddDialogExitQuestFunction("VsD_Tsyganka_Da");
			Log_info("You have received Amulet 'Teredo'");
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"이봐, 너. 나는 이 도시의 법을 지키는 시민이야. 강도처럼 칼을 드러내고 다니지 말아 달라고 부탁해야겠군.","나리, 제발이오, 법은 명확하오: 도시 성벽 안에서는 남자들이 무기를 뽑은 채 다닐 수 없소.");
			link.l1 = LinkRandPhrase("좋아.","좋아.","원하시는 대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
