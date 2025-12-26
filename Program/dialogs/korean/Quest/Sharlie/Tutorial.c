void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{	case "First time":
			dialog.text = "뭐 원하는 거라도 있나?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> Шарль на носу корабля, Алонсо подходит с диалогом
		case "StartSailor":
			dialog.text = "근사한 광경이지, 응?";
			link.l1 = "이 저주받은 바다가 두 달째 날 죽이려고 들고 있지. 아직까진 못 해냈지만.";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "그러하오. 때때로 바다는 우리가 얼마나 작은 존재인지 일깨워 주지.";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "나는 바다에서는 지루함과 공포, 두 가지 상태밖에 없다는 걸 알게 되었지. 그런데... 이건 다르군.";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "StartSailor_1_fencing":
			dialog.text = "하! 처음 바다에 나왔나, 나리? 이렇게 잔잔할 땐 누구나 선장 노릇을 할 수 있지. 이런 때일수록 실컷 즐기게나.";
			link.l1 = ""+GetFullName(pchar)+". 나는 귀족이오, 알아두시오. 나리라고 부르지 마시오.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_1_leadership":
			dialog.text = "하! 처음 바다에 나왔나, 나리? 이렇게 잔잔할 때는 누구나 선장 노릇을 할 수 있지. 이런 때일수록 마음껏 즐기게나.";
			link.l1 = ""+GetFullName(pchar)+". 알아두시오, 나는 귀족이오. 나를 '나리'라고 부르지 마시오.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_1_fortune":
			dialog.text = "하! 처음 바다에 나왔나, 나리? 이렇게 잔잔할 때는 누구나 선장 노릇을 할 수 있지. 이런 때일수록 즐겨 두는 게 좋아.";
			link.l1 = ""+GetFullName(pchar)+". 나는 귀족이오, 알아두시오. 나를 '나리'라고 부르지 마시오.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_2":
			dialog.text = "원하시는 대로 하겠습니다, 나리. 그럼, 첫 항해이시군요, 나리\n "+pchar.lastname+"?";
			link.l1 = "그렇게 티가 나나? 그래, 내 첫 항해야. 그리고 나는 이런 비좁은 선실이나 곰팡내 나는 배식에 맞춰 태어난 사람이 아니지.";
			link.l1.go = "StartSailor_3";
		break;
		
		case "StartSailor_3":
			dialog.text = "누가 봐도 땅개구나, 나리.";
			link.l1 = "입 조심해라! 명예로운 이에게라면 장갑을 던져 결투를 요구했겠지. 하지만 너 같은 촌놈에겐 그냥 귀부터 잘라주마.";
			link.l1.go = "StartSailor_4";
		break;
		
		case "StartSailor_4":
			dialog.text = "파리라면 모를까. 하지만 여기서는 그런 말 했다간 물고기 밥 되기 딱 좋지. 그 칼 함부로 휘두르지 마시오, 나리 - 그리고 선장께서 무장한 채 갑판을 걷게 해주신 걸 후회하게 만들지 마시오. 지난번에 말썽 피운 놈은 쥐조차 안 먹는 곰팡이 핀 건빵이랑 더러운 선창물만 먹으며 밑창에 처박혔었지. 그런데 그거 아시오? 그 불쌍한 놈, 우리가 항구에 도착하자마자 추가 요금까지 내야 했소.";
			link.l1 = "뭘 기대하겠어... 좋아, 이 오해는 잊자고. 이 고물 배가 루브르랑은 전혀 비교도 안 된다는 걸 계속 상기해야겠군.";
			link.l1.go = "StartSailor_5";
		break;
		
				case "StartSailor_5":
			dialog.text = "엉? 루브르? 그게 뭔데?";
			link.l1 = "하! 루브르는 선택받은 자들만을 위한 궁전이지. 무도회, 연회, 음모들...";
			link.l1.go = "StartSailor_6";
		break;
		
		case "StartSailor_6":
			dialog.text = "아... 그러니까 사창가 말이군. 그런 곳이라면 우리도 넉넉히 있지. 선택받은 자들만 가는 데는 아니야 - 돈만 내면 누구든 즐길 수 있거든.";
			link.l1 = "하! 뱃사람, 네 말이 아주 틀린 건 아니군.";
			link.l1.go = "StartSailor_7";
		break;
		
		case "StartSailor_7":
			dialog.text = "이름은 알론소요. 그런데 이런 세상 끝까지 무슨 일로 오셨소, 나리? 대서양을 건너 선원 하나와 말다툼하려고 오신 건 아닐 테지.";
			link.l1 = "저희 아버지는 병이 들어 가스코뉴 영지에서 떠날 수 없습니다. 저는... 형님을 찾으라는 임무를 받았습니다. 형님이 사업차 이곳에 왔는데, 그 후로 소식이 끊겼습니다.";
			link.l1.go = "StartSailor_8";
		break;
		
		case "StartSailor_8":
			dialog.text = "왜 직접 바다의 고생을 겪으려 하시오? 믿을 만한 사람을 보내면 될 텐데?";
			link.l1 = "가족이 최우선이다. 만나는 첫 번째 남자에게 그 운명을 맡길 수는 없지.";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "나도 그러고 싶었지만, 아버지께서 꼭 내가 해야 한다고 고집하시네. 왜 그런지는 전혀 모르겠어.";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;
		
		case "StartSailor_9_nobilityplus":
			dialog.text = "그대 형제의 이름이 무엇이오?";
			link.l1 = "미셸 드 몽페르.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "StartSailor_9_nobilityminus":
			dialog.text = "그대 형제의 이름이 무엇이오?";
			link.l1 = "미셸 드 몽페르.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "StartSailor_10":
			dialog.text = "드 몽페르? 그리고 너는 "+pchar.lastname+"? 어째서지?";
			link.l1 = "그렇게 쳐다보지 마. 나는 정식으로 인정받은 아들이야. 그냥 어머니 성을 따랐을 뿐이지.";
			link.l1.go = "StartSailor_11";
		break;
		
		case "StartSailor_11":
			dialog.text = "부끄러워할 것 없어. 금방 적응할 거야 – 신세계에선 누구나 사연이 있거든. 나만 해도 말이지...";
			link.l1 = "나는 아무것도 부끄럽지 않아! 그냥 마르티니크에 대해 말해 줘. 큰 도시야? 툴루즈처럼?";
			link.l1.go = "StartSailor_12";
		break;
		
		case "StartSailor_12":
			dialog.text = "도시라고? 하! 마르티니크는 섬이야. 프랑스가 카리브에서 가진 가장 큰 영지 중 하나지. 그곳에선 매운 커피를 재배하고, 지옥 같은 유황을 캐내며, 세상에서 가장 아름다운 여인들이 태어나지. 내 생각엔, 이보다 더 좋은 조합은 없을 거야.";
			link.l1 = "나는 커피나 유황에는 관심 없어. 하지만 잠깐만... 섬이라고? 그 넓은 섬에서 어떻게 형을 찾으라는 거지?";
			link.l1.go = "StartSailor_13";
		break;
		
		case "StartSailor_13":
			dialog.text = "걱정 마시오. 생피에르는 작은 마을이오 — 물론 루브르만큼은 아니지만, 그렇다고 밀림도 아니지. 그런데 르 프랑수아라면, 하늘이시여 — 제대로 된 사람이라면 거긴 갈 일이 없소.";
			link.l1 = "어쩔 수 없다면, 도적들에게 가겠어. 미셸은 항상 나를 곤경에서 구해줬지. 이제는 내 차례야.";
			link.l1.go = "StartSailor_14";
		break;
		
		case "StartSailor_14":
			dialog.text = "나쁘지 않군... 땅개 치고는.";
			link.l1 = "또 시작이군. 도대체 언제쯤이면 이 빌어먹을 마르티니크에 도착하는 거야?";
			link.l1.go = "StartSailor_15";
		break;
		
		case "StartSailor_15":
			dialog.text = "닷새.";
			link.l1 = "다섯이라고?!";
			link.l1.go = "StartSailor_16";
		break;
		
		case "StartSailor_16":
			dialog.text = "적어도 그렇지. 그리고 해적들이 나타나면 — 우리 모두 살아남지 못할 수도 있어. 귀중한 화물이 없어도 소앤틸리스 제도 근해는 위험한 바다야.";
			link.l1 = "승객들은 제외하고!";
			link.l1.go = "StartSailor_17";
		break;
		
		case "StartSailor_17":
			dialog.text = "하하! 걱정 마. 정말 최악의 상황이 오면 내가 직접 너를 창고에 숨겨줄게 — 어떤 해적도 럼통 사이에서 가스코뉴 귀족을 찾으리라곤 생각 못 할 테니까! 아무리 그래도 우린 바보는 아니지 — 살아 있는 가스코뉴 놈을 럼과 섞다니. 그건 화약보다 더 크게 터질 거야, 하하!";
			link.l1 = "하! 럼이 한 달 전에 떨어져서 다행이지!";
			link.l1.go = "StartSailor_18";
		break;
		
		case "StartSailor_18":
			dialog.text = "어... 그런 말은 크게 하지 않는 게 좋겠어. 사람들이 우리가 럼주를 다 마신 게 네 탓이라고 생각할지도 모르니까.";
			link.l1 = "알았어, 알론소, 안 할게. 어차피 그런 싸구려 술은 마시지도 않아. 그리고 전투 전에 나를 창고에 숨기겠다는 그 멋진 계획도, 절대 안 돼.";
			link.l1.go = "StartSailor_20";
		break;
		
		case "StartSailor_20":
			dialog.text = "왜 안 되지?";
			link.l1 = "나는 귀족이고, 검도 잘 다루며, 창고에 숨어 있는 것도 아니오.";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "만약 그렇게 된다면, 나도 배를 지키고 다른 이들과 함께 싸울 거야. 또 뭐가 있겠어?";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "언제 싸우고 언제 도망칠지는 내가 직접 결정하지. 어떻게 되는지 두고 보자.";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;
		
		case "StartSailor_21_fencing":
			dialog.text = "하. 너도 뭔가 있긴 한 모양이군. 하지만 조심해라 — 이 카리브 해는 코를 높이 쳐들고 들어오는 자들을 아주 가차 없이 벗겨내지. 해적 선봉대랑 처음 맞닥뜨리면 살아남지 못할 거다. 아니, 생피에르 밖에 있는 누더기 깡패한테도 순식간에 배를 갈릴걸.";
			link.l1 = "넌 나를 전혀 모르잖아.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_21_leadership":
			dialog.text = "하. 너도 제법인 구석이 있나 보군. 하지만 조심해라 — 이 카리브 해는 코를 높이 들고 들어오는 자들을 벗겨내길 좋아하지. 해적 선봉대와 처음 맞닥뜨리면 살아남지 못할 거다. 아니, 생피에르 밖에 있는 누더기 깡패가 널 순식간에 배 갈라버릴지도 몰라.";
			link.l1 = "넌 나를 전혀 모르잖아.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_21_fortune":
			dialog.text = "하. 그래도 뭔가 있긴 한 모양이군. 하지만 조심해라 — 이 카리브 해는 콧대 높이 들고 들어오는 놈들을 아주 가차 없이 벗겨버리지. 해적 선봉대랑 처음 맞닥뜨리면 살아남지 못할 거다. 아니, 생피에르 밖에 있는 누더기 깡패한테도 눈 깜짝할 새에 배 갈릴 거야.";
			link.l1 = "넌 나를 전혀 모르잖아.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_22":
			dialog.text = "하지만 나는 신세계와 그곳 사람들을 잘 알지. 만약 장부 뒤에 숨어 시들거나 총독 관저에서 일할 생각이 아니라면, 모든 것을 처음부터 배워야 할 거야.";
			link.l1 = "여기 오래 머물 생각은 없으니 다행이지.";
			link.l1.go = "StartSailor_23";
		break;
		
		case "StartSailor_23":
			dialog.text = "그건 자네 생각이지. 우린 유럽으로 돌아가는 승객을 자주 태우지 않아. 어떤 자들은 열병, 밧줄, 혹은 총알에 죽고, 또 어떤 자들은 영원히 이곳에 남지. 내가 본 귀족 약골들이 선장이 되기도 하고, 무자비한 악당들이 존경받는 플랜터가 되기도 했지. 그리고 뛰어난 장교들이 빈털터리 떠돌이가 되는 것도 봤다.";
			link.l1 = "지독하게 유혹적이긴 한데, 난 프랑스로 돌아갈 거야. 날 기다리는 사람들이 있거든.";
			link.l1.go = "StartSailor_24";
		break;
		
		case "StartSailor_24":
			dialog.text = "아, 맞아. 아버지가 편찮으신가?";
			link.l1 = "그냥 이렇게 말하지... 파리에 내가 있길 정말 원치 않는 남편이 있는 어떤 숙녀가 있거든. 하지만 몇 달만 지나면 — 열정도 식을 테지.";
			link.l1.go = "StartSailor_25";
		break;
		
		case "StartSailor_25":
			dialog.text = "하하하! 그럼 제대로 온 거야. 카리브 해는 질투 많은 남편들에게서 도망치는 자들에게는 천국이지. 그리고 여기선 시간이 순식간에 지나가. 좀만 기다려 봐 — 너도 결국 뱃사람이 될지 몰라!";
			link.l1 = "선장 쪽이 더 어울릴 것 같군. 나는 평범한 선원으론 영 소질이 없어. 힘쓰는 일은 내 체질이 아니거든.";
			link.l1.go = "StartSailor_26";
		break;
		
		case "StartSailor_26":
			dialog.text = "프랑스에서는 태생으로 사람이 지배하지. 하지만 배 위에서는 선장이 곧 왕이자, 재판관이자, 신이다. 그가 그 모자를 얻기 위해 어떤 시련을 겪었는지 아무도 모른다네. 여기서는 모두가 자기 몫을 받게 되지. 갑판 위에서는 이렇게 말하지 — 각자 자기 운명을 받는다고.";
			link.l1 = "허튼소리군. 선장 얘기가 나와서 말인데 — 네 선장과 얘기 좀 해야겠어, 특히 그가 나를 찾고 있었다니. 잘 있어라, 알론소.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// <-- Шарль на носу корабля, матрос подходит с диалогом
		
		// --> С Алонсо можно в любой момент поговорить
		case "AlonsoWait":
			dialog.text = "무엇을 묻고 싶으신가요?";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "나는 핀숑 나리에게서 왔소.";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "아무것도 아니다.";
			link.l2.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_2":
			dialog.text = "하! 그 안경잡이 녀석이 너도 이 일에 끌어들였냐?";
			link.l1 = "네 눈깔이?";
			link.l1.go = "AlonsoGold_3";
		break;
		
		case "AlonsoGold_3":
			dialog.text = "그 사람 안경 봤어? 맞아! 하지만 오해하지 마, 선원들은 핑숑 나리를 존경해. 배에서는 좋은 의사가 항상 귀하게 여겨지거든. 게다가 그는 훌륭한 급사이기도 해.";
			link.l1 = "그와 무슨 볼일이 있소?";
			link.l1.go = "AlonsoGold_4";
		break;
		
		case "AlonsoGold_4":
			dialog.text = "어... 미안하지만, 그건 우리 사정이야. 하지만 걱정 마, 선박 규칙은 안 어기고 있으니까.";
			link.l1 = "그럼 평범한 법은 어찌 되는 거지?";
			link.l1.go = "AlonsoGold_5";
		break;
		
		case "AlonsoGold_5":
			dialog.text = "우린 평범한 법 따위 신경 안 써. 그래서, 내 몫으로 얼마를 매겼지?";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "40 두블룬.";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "50두블룬.";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "60 더블룬.";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			// link.l4 = "모든 걸 다시 한 번 확인해야겠어. 나중에 다시 올게.";
			// link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "저기 금이 있군. 생피에르, 내가 간다! 하하!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "저기 금이 있군. 생피에르, 내가 간다! 하하!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "저기 금이 있군. 생피에르, 내가 간다! 하하!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// <-- С Алонсо можно в любой момент поговорить
		
		// --> капитан на корабле, который идёт из Европы
		case "Captain":
			dialog.text = "아, 샤를. 그다지 서두르진 않았군? 선장이 부르면 즉시 보고해야 하는 법이야. 명령 따르는 게 힘드냐?";
			link.l1 = "명령을 듣는 건 익숙하지 않소, 선장.";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "죄송합니다, 선장님, 제가 지체되었습니다.";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "네 배에서는 네가 곧 법이라는 걸 아주 분명히 알겠군.";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "베타테스트 (튜토리얼을 건너뛰고 마르티니크에서 게임 시작)";
				link.l9.go = "BetaTest_StartGame";
			}
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;
		
		case "Captain_2_fencing":
			dialog.text = "내 권위에 이의를 제기하는 건 용납 못 하오. 바다에서는 승객들에게 불운이 얼마나 자주 닥치는지 자네는 모를 것이오. 내가 자네를 생피에르까지 무사히 데려다주고 싶어 한다는 사실이 자네에겐 큰 행운이오.";
			link.l1 = "무슨 소리를 하는 거야?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "Captain_2_leadership":
			dialog.text = "사과는 받아들이겠소. 지금 이 순간을 즐기시오. 이런 노을은 자주 볼 수 없을 것이오.";
			link.l1 = "무슨 소리를 하는 거야?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "Captain_2_sailing":
			dialog.text = "이번 항해에서 뭔가 배운 것 같아 다행이군. 선장의 말이 곧 법이지 — 그리고 그 법은 때로는 배에서 멀리 떨어진 육지에서도 통한다네.";
			link.l1 = "무슨 소리를 하는 거야?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		case "Captain_3":
			dialog.text = "선장. 해상 규범에 따라 저를 불러 주시기 바랍니다.";
			link.l1 = "무슨 말씀이십니까, 선장님?";
			link.l1.go = "Captain_4";
		break;
		
		case "Captain_4":
			dialog.text = "돛을 내리고 표류 중임을 알려드리고자 했습니다.\n유감스럽게도 마르티니크 도착이 며칠 지연될 것입니다.";
			link.l1 = "하지만 왜입니까, 선장님?";
			link.l1.go = "Captain_5";
		break;
		
		case "Captain_5":
			dialog.text = "내가 그렇게 결정했으니까.";
			link.l1 = "이게 어제 그... 뭐더라... 상인 호송대랑 마주친 일과 somehow 관련 있나?\n";
			link.l1.go = "Captain_6";
		break;
		
		case "Captain_6":
			dialog.text = "캡스터빌. 들어봐, "+pchar.name+": 우리 진지하게 이야기할 필요가 있소. 내 선실에서 식사를 하자고 초대하겠소. 곧 종이 울릴 테니, 그때 문명인답게 대화하며 배에 남은 마지막 와인 한 병을 비울 시간이 있을 것이오.";
			link.l1 = "초대해 주셔서 감사합니다. 영광이오, 선장.";
			link.l1.go = "Captain_7";
		break;
		
		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "준비되면 알려 주시오. 아직 시간이 좀 있으니, 배 안을 돌아다녀도 괜찮소 — 다만 내 선원들 일하는 데 방해만 하지 마시오.";
				npchar.SharlieTutorial_question_0 = true;
				// теперь можно пострелять из пушки
				sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
				SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
			}
			else dialog.text = "다른 질문 있나?";
			link.l1 = "(마무리할게요) 준비됐습니다, 선장님. 선장님과 함께라면 부르고뉴 와인도 마시겠어요!";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "그 망원경으로 그렇게 열심히 뭘 보고 있소... 선장?";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "선장님, 알론소라는 자와 즐겁게 대화를 나눴습니다. 그 자는 배에서 어떤 직책을 맡고 있습니까?";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "선장님, 배에 대해 말씀해 주시겠습니까? 핀네스 맞지요?";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "다음에 또 뵙지요, 선장님.";
			link.l5.go = "Captain_7_exit";
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "별다른 건 없어, 그냥 수평선을 살피고 있지. 표류하는 배는 쉬운 먹잇감이거든.";
			link.l1 = "해적을 찾고 있나?";
			link.l1.go = "Captain_7_question_1_2";
		break;
		
		case "Captain_7_question_1_2":
			dialog.text = "아니면 스페인 놈들일 수도 있지. 우리는 프랑스 깃발 아래 호위도 없이 항해하고 있고, 소앤틸리스 제도는 진짜 교차로야 — 게다가 자크 바르바종의 영역이지.";
			link.l1 = "저 사람 누구지? 총독인가?";
			link.l1.go = "Captain_7_question_1_3";
		break;
		
		case "Captain_7_question_1_3":
			dialog.text = "더 심각한 건, 해적 남작들 중 하나라는 거지. 이 교수대에 오를 놈들이 일종의 조직을 만들어서 자신들을 해안의 형제단이라 부르거든. 이 자들이 카리브 해를 여섯 구역으로 나누고, 각 구역마다 남작 하나씩을 세워 서로 잡아먹지 못하게 했지.";
			link.l1 = "왜 당국은 아무런 조치도 취하지 않는 것이오?";
			link.l1.go = "Captain_7_question_1_4";
		break;
		
		case "Captain_7_question_1_4":
			dialog.text = "너 참 순진하구나, "+pchar.name+". 해적질이 존재하는 이유는 오직 현지 당국이 일부 항구에서 수리와 보급을 허용해 주는 대신 전리품의 일부를 받기 때문이오. 인정하기는 싫지만, 이 검은 역병에 대해 실제로 뭔가 조치를 취하는 건 스페인 놈들뿐이오. 그들이 아니었다면, 우리도 값비싼 대포로 배를 무장하고 호위까지 고용해야 했을 것이오.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "Captain_7_question_2_1":
			dialog.text = "선임 선원이오. 그에 대해 잘 아는 건 없지만, 한 가지는 말할 수 있소. 모든 사람에게 비밀이 있다면, 알론소는 아예 묘지를 숨기고 있지.";
			link.l1 = "그를 믿지 않는 것 같군.";
			link.l1.go = "Captain_7_question_2_2";
		break;
		
				case "Captain_7_question_2_2":
			dialog.text = "전혀 그렇지 않소. 그렇게 경험 많은 선원들을 구하는 게 쉬운 일인 줄 아시오? 선술집에서 술만 마시던 놈들을 그럴듯한 선원으로 만들려면 최소 1년은 걸리고, 훌륭한 보선장이 꼭 필요하오.\n게다가 알론소는 선원들의 대변자이기도 하오. 선장은 아랫사람들과 굳이 말을 섞지 않지만, 평범한 선원들도 자기 이해관계가 있다는 걸 잊는 건 어리석고, 목숨까지 위태롭게 하지. 필요할 때 알론소가 그들을 대신해 말하오.";
			link.l1 = "그런데 선원들이 불만이면 어떻게 되지?";
			link.l1.go = "Captain_7_question_2_3";
		break;
		
		case "Captain_7_question_2_3":
			dialog.text = "나야 목이 매달릴 테고, 넌 그냥 칼에 찔리겠지. 그렇게 창백해질 것 없어. 선원들만 돈 받고, 밥 먹고, 술 마시고, 상처 치료받으면 — 선장과 선원 사이의 계약은 지켜지는 거야. 나는 그들의 목숨을 걸고 도박하지도 않고, 즉흥적으로 벌을 내리지도 않아. 전리품을 나누고, 가끔은 술이나 육지 휴가로 선원들을 챙겨주기도 하지. 그렇게 해서 겨우 균형을 유지하는 거고 — 그래서 우리 배는 항상 목적지에 도착하는 거야.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Captain_7_question_3_1":
			dialog.text = "아픈 데를 건드렸군, "+pchar.name+"! 내 아름다움에 대해라면 끝없이 이야기할 수 있지. 삼류, 20문, 엄청난 속도 — '상선'이라는 말에 속지 마!";
			link.l1 = "총과 속도에 대해서는 이해했어. 그런데 '비율'? '상인'?";
			link.l1.go = "Captain_7_question_3_2";
		break;
		
		case "Captain_7_question_3_2":
			dialog.text = "함급은 대포 수에 따라 대략적으로 분류된 것이오. 7함급은 배라기보다는 거의 보트 수준이고, 1함급은 요새에 가까우니. 하지만 이런 말은 유럽에서는 함부로 하지 마시오 — 특히 해군 장교들 근처에서는 말이오.";
			link.l1 = "왜 안 되지? 이게 선원들 농담이라도 되는 거야?";
			link.l1.go = "Captain_7_question_3_3";
		break;
		
		case "Captain_7_question_3_3":
			dialog.text = "너를 완전한 바보로 보고 비웃을 거야. 사실 제대로 된 해군에서는 계급 체계가 다르고, 전함에만 적용되지. 하지만 여기 카리브에서는 언제나 그렇듯 우리 방식대로 하지.\n";
			link.l1 = "그리고 네가 네 배를 '상선'이라고 부른 건 무슨 뜻이었지?";
			link.l1.go = "Captain_7_question_3_4";
		break;
		
		case "Captain_7_question_3_4":
			dialog.text = "또 하나의 애매한 용어지. 전함은 더 튼튼하고, 포격도 잘하지. 약탈선은 털고 도망치는 데 특화됐고. 상선은 화물이나 선원, 대포를 많이 실을 수 있지만, 뭔가를 포기해야 해. 안 그러면 속도가 우스울 정도로 느려지거든. 다목적 선박도 있긴 한데, 주인 필요에 맞춰 바뀐다는 것 말고는 딱히 할 말이 없어.";
			link.l1 = "흥분하시는군요, 선장.";
			link.l1.go = "Captain_7_question_3_5";
		break;
		
		case "Captain_7_question_3_5":
			dialog.text = "내 배를 사랑해, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;
			
		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "운이 좋군 — 이제 남은 건 부르고뉴뿐이야... 잠깐만, "+pchar.name+". 내 옛 모자는 어디서 났어?!\n잠깐. 이봐, 돛대 위에! 거기서 무슨 일이야?";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "운이 좋군 — 이제 남은 건 부르고뉴뿐이야\n잠깐. 이봐, 돛대 위에! 거기서 무슨 일이야?";
			link.l1 = "...";
			link.l1.go = "Captain_9";
		break;
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// досрочный выход на сушу
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// <-- капитан на корабле, который идёт из Европы
		
		// --> Диалог с охранником каюты
		case "OhrannikCabin":
			dialog.text = "용서하십시오, 드 모르 나리, 하지만 그곳에는 들어가실 수 없습니다.";
			link.l1 = "난 이미 선장 선실에 가 본 적 있어. 이제쯤은 기억해야지.";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "아아, 내 교묘한 계획이 실패하고 말았군. 잘 가라, 뱃사람.";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 12) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
				DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
			}
		break;
		
		case "OhrannikCabin_1":
			dialog.text = "용서하십시오, 나리, 하지만 상황이 달라졌습니다.";
			link.l1 = "그래서 도대체 무슨 일이 있었소?";
			link.l1.go = "OhrannikCabin_2";
		break;
		
		case "OhrannikCabin_2":
			dialog.text = "이제 항해도 거의 끝나가고, 선장님은 누가 자기 귀중품을 털어가서 도적 소굴인 르 프랑수아로 사라지는 걸 원치 않으시지.";
			link.l1 = "선장께서 그런 명령을 내릴 때 나를 염두에 두셨을 것 같진 않군.";
			link.l1.go = "OhrannikCabin_3";
		break;
		
		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 12)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "음... 일리가 있군. 그리고 이미 선장실에서 여러 번 식사했잖아. 가보시오, 드 모르 나리.";
					link.l1 = "이제 좀 제대로군!";
					link.l1.go = "OhrannikCabin_4";
					Notification_Skill(true, 12, SKILL_LEADERSHIP);
				}
				else
				{
					dialog.text = "인시... 인시누아-뭐라고? 그런 뜻 전혀 아니었어요, 드 모르 나리!";
					link.l1 = "그렇다면 나를 통과시켜야 하오.";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "나리, 선장 선실은 아무나 드나드는 곳이 아니라는 것쯤은 아시겠지요. 명령은 명령입니다.";
					link.l1 = "젠장, 얼른 뭍으로 돌아가고 싶어. 이건 정말 굴욕이잖아!";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "나리, 이미 이 문제에 대해 이야기했소. 통과시켜 드릴 수 없소.";
					link.l1 = "여전히 고집이 세군, 선원. 잘 가라.";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				Notification_Skill(false, 12, SKILL_LEADERSHIP);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "에... 좋아. 뭐, 큰일은 없겠지.";
			link.l1 = "이제야 제대로군!";
			link.l1.go = "OhrannikCabin_4";
			Notification_Skill(true, 12, SKILL_LEADERSHIP);
		break;
		
		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;
		
		case "OhrannikCabin_again":
			dialog.text = "다른 일이라도 있으십니까, 나리? 들여보낼 수 없습니다 — 선장님께서 귀중품을 걱정하고 계십니다.";
			link.l1 = "도둑질을 암시하는 거냐, 선원? 말 조심해라. 그건 순전히 넌지시 비꼬는 말이야!";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "아무것도 아니야, 선원.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// <-- Диалог с охранником каюты
		
		// --> матрос ругается на ГГ, который активировал брашпиль
		case "SailorWithWindlass_1":
			dialog.text = "이봐, 이 귀족 멍청이! 뭘 하는 거야, 윈들라스에 악마라도 쑤셔 넣으려고?\n네 왕족 발로 마개를 걷어찼잖아! 우리 전부 바다 밑으로 보내려고 작정이냐?!\n부탁이니까 — 프랑스 귀족 콧물 아니면 아무것도 건드리지 마!";
			link.l1 = "이게 대체 뭐지?";
			link.l1.go = "SailorWithWindlass_2";
		break;
		
		case "SailorWithWindlass_2":
			dialog.text = "그건 윈들라스야, 이 멍청아. 닻을 들어 올리는 장치지. 그리고 그게 고정되어 있지 않으면 — 배를 산산조각 내버리거나 누군가를 청어처럼 통에 감아버릴 거야!";
			link.l1 = "하... 그리고 반대로 돌리면 닻이 내려가는 거지, 맞아?";
			link.l1.go = "SailorWithWindlass_3";
		break;
		
		case "SailorWithWindlass_3":
			dialog.text = "아니, 천재야, 그건 시간을 되돌리는 거야. 안됐지만 넌 이미 태어났거든!";
			link.l1 = "뭐, 아무도 다치지 않았잖아? 배라는 게 정말 복잡한 기계야. 앞으로 더 조심할게.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		// <-- матрос ругается на ГГ, который активировал брашпиль
		
		// --> матрос ругается на ГГ, который активировал пушку
		case "SailorWithCannon_1":
			dialog.text = "아까 해넘이에 감탄하던 그 눈빛으로 지금은 저 대포의 긴 포신을 바라보고 있군.";
			link.l1 = "날 지켜보는 걸 즐기는군, 알론소. 차라리 이 군사 공학의 경이로움에 대해 말해보지 그래.";
			link.l1.go = "SailorWithCannon_2";
		break;

		case "SailorWithCannon_2":
			dialog.text = "저건 16파운드포야. 모든 군함에 있는 건 아니지.";
			link.l1 = "그걸로 뭔가를 맞히는 게 쉽나?";
			link.l1.go = "SailorWithCannon_3";
		break;

		case "SailorWithCannon_3":
			dialog.text = "바로 코앞에서는 뭐든지 산산조각 내버릴 수 있지. 백 야드 거리면 제대로 한판 붙는 거고. 그 이상이면 그냥 소음과 불꽃일 뿐이지만, 없는 것보단 낫지.";
			link.l1 = "백 야드 거리다 — 적도 똑같이 할 수 있지.";
			link.l1.go = "SailorWithCannon_4";
		break;

		case "SailorWithCannon_4":
			dialog.text = "맞아. 하지만 결국 중요한 건 선원들의 팀워크와 포수의 실력이야. 아쉽게도 우리 포수는 지금 자고 있지 — 그 녀석이 깨어 있었다면 너한테 한 수 가르쳐주고는 직접 대포에 집어넣어 쏴버렸을 거다, 하!";
			link.l1 = "포수도 장교 맞지?";
			link.l1.go = "SailorWithCannon_5";
		break;

		case "SailorWithCannon_5":
			dialog.text = "보통 그래. 최소한 반쯤은 쓸 만한 포수가 없으면 싸움은 피하는 게 나아 — 차라리 대포를 바다에 던져버리고 도망치는 게 낫지.\n상인 선장들은 여섯 파운드짜리보다 큰 대포는 거의 싣지 않아 — 호위나 운에 기대는 거지.\n그럴 만도 해. 무거운 대포나 탄약이 없으면 배가 더 잘 나가고, 팔 화물도 더 실을 수 있으니까.\n우리 선장이 이 멋진 대포에 돈을 펑펑 쓰지만 않았어도, 럼주가 아직 좀 남아 있었을 텐데. 하아.";
			link.l1 = "선장께서 직접 포격을 지휘하지 않으십니까?";
			link.l1.go = "SailorWithCannon_6";
		break;

		case "SailorWithCannon_6":
			dialog.text = "좋은 포수와 선원이 있으면 굳이 그럴 필요 없지. 하지만 말해두겠네: 선장이 함교에서 '쏴라!' 하고 소리치는 대신 직접 대포를 조준하면, 적선은 구멍이 더 많이 뚫리게 마련이야.";
			link.l1 = "하나 쏴도 돼?";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "흥미로운 강의 고맙소, 알론소. 자네는 정말 해상 지식의 보물창고구려.";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "알겠어! 그래도 대포는 건드리지 말고 선원들 불안하게 하지 마.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;

		case "SailorWithCannon_7":
			dialog.text = "쏜다고? 그럴 리 없지. 한 발이라도 쏘려면 선장 허락이 필요하거든. 지금 가서 물어볼게!";
			link.l1 = "필요 없어!";
			link.l1.go = "SailorWithCannon_8";
		break;

		case "SailorWithCannon_8":
			dialog.text = "선장님!";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;
		
		case "CaptainWithCannon_1":
			dialog.text = "무슨 일이오, 알론소?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_2";
		break;

		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_3":
			dialog.text = "샤를 나리가 대포를 쏘자고 제안하셨소 — 어디까지나 훈련 목적으로 말이오.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_5":
			dialog.text = "난 네가 선원들 이익을 챙기는 줄 알았는데, 알론소. 그런데 지금 네가 하는 말이, 다음 당직을 깨우고 모두를 가장 야만적인 방법으로 들쑤시자는 거냐?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_7":
			dialog.text = "내 생각엔 저놈들 피를 끓게 하고 준비시키는 게 현명할 것 같아. 우리가 이렇게 훤히 보이는 데 떠다니는 게 마음에 안 들어. 무슨 일이 벌어질지도 몰라.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_9":
			dialog.text = "재수 없게 굴지 마!.. 좋아. 한 잔. 빈 잔이야.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_10":
			dialog.text = "즐기시오, "+pchar.name+"... 우리가 선원들을 깨울 테니... 네 돈으로 말이야, 하하!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// <-- матрос ругается на ГГ, который активировал пушку
		
		// --> Диалог с матросом, который хочет рома
		case "SailorWantRum":
			dialog.text = "잠시 시간 내주실 수 있겠소, 나리?";
			link.l1 = "말해 봐라, 선원.";
			link.l1.go = "SailorWantRum_1";
		break;

		case "SailorWantRum_1":
			dialog.text = "만나서 반갑습니다, 나리. 제 이름은 앙리입니다. 돈 좀 벌어볼 생각 있으신가요?";
			link.l1 = "'조금'이 얼마나 된다는 거지?";
			link.l1.go = "SailorWantRum_2";
		break;

		case "SailorWantRum_2":
			dialog.text = "오백 페소.";
			link.l1 = "얼마라고?! 그 돈을 받으려면 내가 뭘 해야 하지? 반란이라도 일으키라는 거야?";
			link.l1.go = "SailorWantRum_3";
		break;

		case "SailorWantRum_3":
			dialog.text = "세상에, 나리! 그렇게 소리칠 필요는 없소!";
			link.l1 = "돈이 꽤 많군, 선원. 그 정도면 파리에서 호화롭게 살 수 있겠어.";
			link.l1.go = "SailorWantRum_4";
		break;

		case "SailorWantRum_4":
			dialog.text = "아, 네가 모르는 걸 이용하진 않겠어. 여기 카리브 해에서는 500페소쯤은 아무것도 아니지. 선장들이랑 상인들이 워낙 많은 물건을 들여와서, 쓸 만한 건 뭐든 값이 천정부지로 뛰었거든. 가끔은 희귀한 검 한 자루 값이 작은 배 한 척 값만큼 하기도 해.";
			link.l1 = "그거 미쳤군.";
			link.l1.go = "SailorWantRum_5";
		break;

		case "SailorWantRum_5":
			dialog.text = "뭐라고 해야 할까? 우리 모두 상황이 안정되고 물가가 정상으로 돌아오길 기다리고 있지. 자, 500페소 벌 생각 있나?";
			link.l1 = "먼저, 일이 무엇인지 알고 싶소.";
			link.l1.go = "SailorWantRum_6";
		break;

		case "SailorWantRum_6":
			dialog.text = "배에 럼이 부족한 건 분명히 알고 있을 거야. 하지만 어딘가에 아직 몇 병은 남아 있다고 확신해. 병에 든 럼은 통에 든 싸구려 술이랑은 다르지. 맛도 훌륭하고, 중독도 막아주고, 팔과 건강도 튼튼하게 해 주는 진짜 보물이라구. 특히 항해가 끝나갈 때쯤, 지평선만 바라보다 미쳐버릴 것 같은 그때 말이야.";
			link.l1 = "그걸 가지고 뭘 하시겠소? 왜 직접 찾아보지 않으시오?";
			link.l1.go = "SailorWantRum_7";
		break;

		case "SailorWantRum_7":
			dialog.text = "내가 언제 시간이 있겠어? 인원이 부족해서 세 사람 몫으로 일하고 있거든. 럼주라면, 다시 팔 거야 — 사줄 사람은 내가 알아서 찾지.";
			link.l1 = "음, 나는 남자의 솔직함을 존중하지.";
			link.l1.go = "SailorWantRum_8";
		break;
		
		case "SailorWantRum_8":
			dialog.text = "그래서, 일을 맡겠나? 나는 병 세 개가 필요하네.";
			link.l1 = "해보겠지만, 장담은 못 해.";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "사양하겠소. 이런 일은 내 격에 맞지 않으니.";
			link.l2.go = "SailorWantRum_10";
		break;

		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;

		case "SailorWantRum_10":
			dialog.text = "안타깝지만, 원한은 품지 않겠소. 좋은 저녁 되시오, 나리.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;

		case "SailorWantRum_PrinestiRum": // ждёт ром
			dialog.text = "예, 나리 "+pchar.lastname+"";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "여기 럼주 세 병이 있소.";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "앙리, 핀숑 나리께서 너에게 전해달라고 하신 것이 있어.";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "아무것도 아니다.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "RumGold_2":
			dialog.text = "항상 그분을 위해 기꺼이 봉사하지! 이번엔 내가 얼마나 받아야 하지?";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28 더블룬.";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "35 더블룬.";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "두블론 42개.";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			// link.l4 = "모든 걸 다시 한 번 확인해야겠어. 금방 돌아올게.";
			// link.l4.go = "RumGold_DatDeneg_3";
		break;

		case "RumGold_DatDeneg_gold28":
			dialog.text = "감사합니다, 나리 "+pchar.lastname+". 재무관에게 안부 전해 주십시오.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold35":
			dialog.text = "감사합니다, 나리 "+pchar.lastname+". 재무관에게 안부 전해 주십시오.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold42":
			dialog.text = "감사합니다, 나리 "+pchar.lastname+". 재무관에게 안부 전해 주십시오.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "감사합니다, 나리 "+pchar.lastname+". 멋지게 해냈군!";
			link.l1 = "나도 내 보수를 이렇게 순조롭게 받을 수 있으면 좋겠군.";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;

		case "SailorWantRum_PrinestiRum_3":
			dialog.text = "금전이 아닌 다른 방식의 대가를 받아들이시겠습니까?";
			link.l1 = "자네가 주장하는 것만큼 정직하지는 않은 것 같군.";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;

		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "아니, 아니오! 돈이 필요하다면 돈을 주겠소! 하지만 지식도 좀 나눌 수 있소.";
			link.l1 = "무슨 지식 말인가?";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;

		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "학자들이 보는 책에서는 찾을 수 없는 뱃사람의 지식, 내가 많이 알려줄 수 있지.";
			link.l1 = "좋아, 그럼 내 인생에서 가장 비싼 교훈을 줘봐.";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2 = "오백 개의 조언이 오백 닢을 대신해주진 않지. 돈은 내가 가져가겠어.";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;

		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "여기 있습니다, 나리 "+pchar.lastname+". 그리고 다시 한 번 감사하오!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
			AddMoneyToCharacter(pchar, 500);
		break;
		
		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "진심으로 그러길 바랍니다, 나리 "+pchar.name+", 내 가르침이 도움이 되길 바라오. 항해가 무엇인지 아시오?";
			link.l1 = "놀라겠지만, 나도 할 줄 알아. 심지어 글도 읽을 수 있지. 항해술이란, 예를 들어 배의 경우, 공간에서 자신의 위치를 파악하고 항로를 정하는 거야.";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;

		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "아, 별이나 해도 말하는 거지. 아니, 난 그런 건 몰라. 그건 항해사나 선장이 하는 일이야. 여기서 '항해'란 배를 조종하고 지휘할 수 있는 능력을 말하지.";
			link.l1 = "여기 '주변'에 누가 있는데?";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;

		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "카리브 해에선 원래 그래. 왜냐고 묻지 마. 그러니 항해술이 뛰어날수록 배에서 더 많은 속도와 기동성을 뽑아낼 수 있지. 선원들도 돛을 더 빨리 다루고. 하지만 그게 가장 중요한 건 아니야.";
			link.l1 = "긴장감을 조성하는 데는 정말 일가견이 있군.";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;

		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "항해 실력이 좋을수록 더 큰 배를 지휘할 수 있소! 너무 고급스러운 배를 억지로 타면 집중력, 기력, 심지어 건강까지 잃게 될 것이오!";
			link.l1 = "위험해 보이네. 내가 이걸 모르고도 이렇게 오래 살아남았다니, 신기하군.";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;

		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "다행히 모든 분야의 전문가일 필요는 없어. 부족한 부분은 훌륭한 항해사를 고용해서 메우면 되지. 대신 그들에게 보수도 주고 충성심도 챙겨야 해. 네 실력을 넘어서는 배에서 항해사를 잃는 건... 재미없는 일이거든.";
			link.l1 = "강의 고마워, 헨리. 내가 이걸 쓸 일이 있을지는 모르겠지만, 지식은 많을수록 나쁠 건 없겠지.";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;

		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "천만에요, 나리 "+pchar.lastname+". 그리고 다시 한 번 감사드립니다!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// <-- Диалог с матросом, который хочет рома
		
		// --> Диалог со старым матросом в трюме
		case "OldSailor":
			dialog.text = "(노래함) 미셸 아주머니가 고양이를 잃었네... 창문 너머로 누가 돌려줄지 외치고 있네...";
			link.l1 = "여기서 뭐 하고 있나, 선원?";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;
		
		case "OldSailor_1":
			dialog.text = "이제 나는 미셸 부인처럼 고양이를 찾고 있는 셈이야. 하지만 나는 소리치지 않아 — 그분은 소리치는 걸 싫어하시거든.";
			link.l1 = "오늘 아침에 그녀를 봤어 — 또 내 부츠에 매달리고 있더군.";
			link.l1.go = "OldSailor_2";
		break;

		case "OldSailor_2":
			dialog.text = "그건 아무것도 아니야. 선장 부츠가 더 심했지. 고양이 좋아해?";
			link.l1 = "당연히 그렇지.";
			link.l1.go = "OldSailor_3";
			link.l2 = "꼭 그렇진 않아.";
			link.l2.go = "OldSailor_4";
		break;

		case "OldSailor_3":
			dialog.text = "일리가 있군. 아니면 그 빌어먹을 쥐들을 어떻게 처리하겠어?";
			link.l1 = "하지만 고양이만을 영원히 믿을 수는 없잖아, 그렇지? 녀석들은 꽤 제멋대로인 동물이거든.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "OldSailor_4":
			dialog.text = "안됐군. 고양이는 배에서 사랑받고 소중히 여겨지지. 아니었으면 저 빌어먹을 쥐들을 어떻게 처리했겠어?";
			link.l1 = "하지만 고양이만 계속 믿을 순 없잖아? 녀석들은 꽤 제멋대로인 동물이거든.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "OldSailor_5":
			dialog.text = "맞아. 그래서 우리는 비소에 의존하지. 하지만 카리브 해에서 그걸 구하는 건 운에 맡겨야 해. 그래서 화물을 잃지 — 쥐들이 럼주를 더럽히고, 건빵을 망치고, 나머지도 다 갉아먹지\n그리고 우리 경리 놈은 말하지: '걱정 마, 그냥 통상세 같은 거야.'\n하지만 우리는 진실을 알지: 그 자식 그냥 게으른 거야. 우리 샹탈이 아니었으면 선장님이 진작에 저 놈을 창고에 쳐박아두고 직접 쥐나 잡게 했을 거야, 하하!";
			link.l1 = "고양이와 잘 지내게. 나는 가봐야겠어.";
			link.l1.go = "OldSailor_6";
		break;

		case "OldSailor_6":
			dialog.text = "잠깐만요, 나리. 평범한 선원들은 보통 귀족 손님들을 갑판 위에서만 보는데, 어째서 나리께서는 이렇게 밑창까지 내려오셨습니까!";
			link.l1 = "호기심이 고양이를 죽였지, 하하!";
			link.l1.go = "OldSailor_7";
		break;

		case "OldSailor_7":
			dialog.text = "항해술에 관심이 생긴 건가?";
			link.l1 = "상륙하기 전에 모든 선원들이 나를 진짜 선원으로 만들 작정인 것 같군.";
			link.l1.go = "OldSailor_8";
		break;

		case "OldSailor_8":
			dialog.text = "놀랄 일도 아니지. 바다는 우리 중 많은 이들에게 슬픔만을 안겨줬지만, 우리는 이 일을 사랑해. 그리고 선원은 언제나 누군가 새로 온 사람이 진심으로 관심을 보이면 기뻐하지.";
			link.l1 = "...";
			link.l1.go = "OldSailor_9";
		break;
		
		case "OldSailor_9":
			dialog.text = "이제 말해 보시오. 선장에게 가장 중요한 능력이 무엇이라고 생각하오?";
			if (GetSummonSkillFromName(pchar, SKILL_SAILING) >= 6)
			{
				link.l1 = "항해술. 그가 지휘할 수 있는 배의 크기를 결정한다.";
				link.l1.go = "OldSailor_10";
				Notification_Skill(true, 6, SKILL_SAILING);
			}
			else
			{
				link.l1 = "거짓말하지 않겠소 — 모르겠소.";
				link.l1.go = "OldSailor_9_1";
				Notification_Skill(false, 6, SKILL_SAILING);
			}
		break;

		case "OldSailor_9_1":
			dialog.text = "기분 상해하지 마시오, 나리. 선원들과 이야기해 보고, 배도 탐험해 보시오. 답을 찾는다면—정말 흥미로운 것을 나누어 주겠소. 마치 우리 중 한 사람인 것처럼.";
			link.l1 = "명심하겠소. 안녕히 가시오!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;

		case "OldSailor_10":
			dialog.text = "정답이야! 이제 좀 더 어려운 문제다: 사각돛과 횡돛, 어느 쪽이 더 좋은가?";
			link.l1 = "뭐라 단정짓긴 어렵지만, 뭔가 속임수가 있는 것 같아. 각각 나름의 장점이 있다고 생각해.";
			link.l1.go = "OldSailor_11";
		break;

		case "OldSailor_11":
			dialog.text = "또 맞췄군! 사각 돛은 뒷바람이 불 때 최고지. 하지만 횡돛은 바람을 가로질러서도 항해할 수 있어. 시간 헛되이 보내지 않은 것 같아 보기 좋군, 나리.";
			link.l1 = "이 지식이 쓸모 있을지는 모르겠군... 상류층 숙녀들 앞에서 진짜 선원인 척 뽐내고 싶을 때나 써먹겠지, 하하!";
			link.l1.go = "OldSailor_12";
		break;
		
		case "OldSailor_12":
			dialog.text = "아, 잘 모르겠소, 나리 "+pchar.name+". 자네가 귀족일지는 몰라도 우리를 제대로 대하더군. 그 점은 우리가 높이 평가하지. 선장께서 뭔가 꾸미고 계셔. 검은 고양이가 자네 앞길을 가로질렀어.";
			link.l1 = "헛소리군. 무슨 소리를 하는 거야, 선원?";
			link.l1.go = "OldSailor_13";
		break;

		case "OldSailor_13":
			dialog.text = "며칠 전, 그는 지나가던 배를 통해 캡스터빌에 편지를 보냈다는 소문이 있소\n그리고 항해가 끝나갈 무렵, 모두가 땅을 그리워하며 아우성칠 때 그는 표류했다고 하오.";
			link.l1 = "나는 소문 따위 신경 안 써. 뭐하러 신경 쓰겠어? 그냥 직접 물어보면 되지. 귀족에게는 솔직하게 대답 안 할 리 없잖아.";
			link.l1.go = "OldSailor_14";
		break;

		case "OldSailor_14":
			dialog.text = "당신은 그를 모릅니다, 나리 "+pchar.name+". 그는 분명히 그럴 거야 — 아주 제대로 말이지. 그리고 지금 화가 나 있어 — 열쇠를 잃어버렸거든.";
			link.l1 = "열쇠?";
			link.l1.go = "OldSailor_15";
		break;

		case "OldSailor_15":
			dialog.text = "선실에 있는 그의 궤짝에. 어딘가에 그냥 굴러다니고 있을 거야.";
			link.l1 = "열쇠를 찾으라고? 내가?";
			link.l1.go = "OldSailor_16";
		break;

		case "OldSailor_16":
			dialog.text = "그건 당신이 결정할 일이오\n그런데, 나리 "+pchar.name+", 럼주 남았지? 설마 전부 헨리한테 줘버린 건 아니겠지, 하하!";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "그렇소. 여기 있소.";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "아니, 못 구했어. 그 세 병을 찾은 것도 기적이었다.";
			link.l2.go = "OldSailor_16_1";
		break;

		case "OldSailor_16_1":
			dialog.text = "그렇소. 행운을 빕니다, 나리 "+pchar.name+". 그 줄무늬 악당을 계속 찾아볼 거야.";
			link.l1 = "너도 행운을 빌어, 선원.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;
		
		case "OldSailor_17":
			dialog.text = "선원들에게 큰 도움을 주셨소, 나리 "+pchar.name+". 자, 행운을 비는 작은 부적이오!";
			link.l1 = "구멍 뚫린 돌이라니? 참 귀엽군.";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;

		case "OldSailor_18":
			dialog.text = "실컷 웃어라. 바다에서는 부적이 해가 되진 않으니.";
			link.l1 = "너희 선원들은 미신이 심하구나. 행운을 빌지.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;

		case "OldSailor_again":
			dialog.text = "벌써 답을 찾았나? 선장에게 가장 중요한 능력이 무엇인지 아는가?";
			if (GetSummonSkillFromName(pchar, SKILL_SAILING) >= 6)
			{
				link.l1 = "항해술. 그가 지휘할 수 있는 배의 크기를 결정한다.";
				link.l1.go = "OldSailor_10";
				Notification_Skill(true, 6, SKILL_SAILING);
			}
			else
			{
				link.l1 = "아직 아니야.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				Notification_Skill(false, 6, SKILL_SAILING);
			}
		break;
		
		// <-- Диалог со старым матросом в трюме
		
		// --> Диалог с матросом, которому нужен ящик с ядрами (Поль)
		case "SailorNeedBox":
			dialog.text = "이봐, 꼬마야!";
			link.l1 = "너는 우리 아버지처럼 안 보여. 그나마 다행이지.";
			link.l1.go = "SailorNeedBox_1";
		break;

		case "SailorNeedBox_1":
			dialog.text = "하! 저렇게 키 크고 고귀한 아들이 있다면 자랑스러울 텐데. 하지만 나는 나처럼 평범한 놈밖에 못 낳지.";
			link.l1 = "좋아, 칭찬은 고맙게 받을게. 무슨 문제야?";
			link.l1.go = "SailorNeedBox_2";
		break;

		case "SailorNeedBox_2":
			dialog.text = "도움이 좀 필요하군, 꼬마야. 대포 옆에서 탄환을 쌓으라는 명령을 받았어 — 이 위험한 바다에서 무슨 일이 생길지 모르니까 말이지. 감시 시간의 절반을 창고에서 이 쇳덩이들을 끌어올리느라 보냈더니, 마지막 상자에서 허리가 나가버렸어.";
			link.l1 = "그냥 네 동료들에게 물어보지 그래? 난 너희 선원들이 서로 돕는 줄 알았는데.";
			link.l1.go = "SailorNeedBox_3";
		break;

		case "SailorNeedBox_3":
			dialog.text = "우리 형제단이 정말 싫어하는 것 한 가지는, 별 이유도 없이 무거운 짐을 나르는 거지. 오늘은 재수 없게 제비를 뽑아 탄약 상자를 창고에서 끌어내게 됐어. 이런 허드렛일은 내 급의 선원이 할 일이 아닌데 말이야. 하지만 별 수 있나?";
			link.l1 = "징징대지 마라. 내가 도와주지. 적어도 모두가 나를 겁주는 그 감옥이 어떤지 한번 볼 수는 있겠군.";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "(운동선수) 내 허리띠에 달린 이 브로드소드 보이지? 네 몸무게보다 더 나가. 네 공 가져오는 거쯤은 식은 죽 먹기지.";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "나는 잡일 따위는 하지 않네, 선원. 네 짐은 네가 직접 나르도록 하게.";
			link.l3.go = "SailorNeedBox_Net";
		break;

		case "SailorNeedBox_4":
			dialog.text = "고맙다, 이 녀석. 허리나 삐지 말라고!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls":	// ожидание выстрела
			dialog.text = "어떻게 지내냐, 이 녀석?";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "여기 네 술이야. 더 클 줄 알았는데.";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "네 이름이 폴 맞지?";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "안녕히 가십시오.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "BallsGold_2":
			dialog.text = "어... 예, 예.";
			link.l1 = "네 이름이 핀숑 나리가 내게 준 명단에 있어.";
			link.l1.go = "BallsGold_3";
		break;
		
		case "BallsGold_3":
			dialog.text = "휴, 잠깐 동안은... 그래, 폴 - 나 맞아. 거기서 나 줄 돈이 얼마나 있지?";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "20 더블룬.";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "25 더블룬.";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "30 더블룬.";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			// link.l4 = "모든 걸 다시 한번 확인해야겠어. 나중에 다시 올게.";
			// link.l4.go = "BallsGold_DatDeneg_3";
		break;
		
		case "BallsGold_DatDeneg_gold20":
			dialog.text = "고맙다, 이 녀석.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold25":
			dialog.text = "고맙다, 이 녀석.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold30":
			dialog.text = "고맙다, 이 녀석.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "더 커지면 적한테 선물이나 다름없지! 선체에 맞으면... 뭐, 누군가만 산산조각날지도 몰라. 하지만 선미에 맞으면, 공처럼 갑판 위를 이리저리 튈 거야!";
			link.l1 = "전에 그런 일 본 적 있어?";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;
		
		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "내가 직접 봤지, 이 녀석아. 인간이란 죽이는 기계 만드는 데는 정말 선수야. 산탄을 봐라 — 사거리는 짧지만 선체를 뚫진 못해도, 한 번에 열두 명쯤은 저세상으로 보내버리지. 체인탄은 어때 — 돛을 맞추면 순식간에 누더기로 만들어버려! 폭탄은… 난 아무 말도 안 하련다, 본 적도 없고, 하느님께 감사할 뿐이지! 악마의 물건들이고, 값도 더럽게 비싸거든.";
			link.l1 = "나는 이미 대포알이 얼마나 치명적인지 봤어 — 네 불쌍한 등한테 물어보라고.";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;

		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "그래, 정말 큰 신세를 졌군. 나도 보답하지. 자 — 거의 다 찬 최고급 럼주 한 병이야, 하하!";
			link.l1 = "어디서 구했어? 럼주가 진작에 다 떨어졌다는 소문만 들었는데. 이런 물건이면, 선창에 있는 상자 전부를 너 혼자 옮기라고 해도 누구든 시켰겠구만.";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;

		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "그렇게 된 거다, 꼬마야. 고맙고, 잘 가라.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// <-- Диалог с матросом, которому нужен ящик с ядрами
		
		// --> Диалог с офицером-торговцем, который торгует всяким
		case "OfficerTorgovets":
			dialog.text = "아, 나리 "+pchar.lastname+". 자려는 생각이라면, 운이 없군. 우리 포수 녀석이 네 침대를 차지했어. 알다시피, 그 녀석 깨우는 건 꽤나 힘들지.";
			link.l1 = "말하자면, 필요할 때는 뭐든 다 잘 듣더군!";
			link.l1.go = "OfficerTorgovets_1";
			/*link.l2 = "아니.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets";*/
		break;
		
		case "OfficerTorgovets_1":
			dialog.text = "별것도 아니지. 샤프 선장의 선원 중에 한때 장님 포수도 있었다더군. 총성 소리만 듣고 조준했다던데.";
			link.l1 = "오늘따라 유난히 말이 많으시군, 보스웽 나리.";
			link.l1.go = "OfficerTorgovets_2";
		break;

		case "OfficerTorgovets_2":
			dialog.text = "그럴 만한 이유가 있지! 곧 상륙할 거야 — 남은 물건을 짤랑거리는 페소로 바꿀 시간이거든. 생피에르의 사창가 놈들은 그런 돈만 보면 항상 반기지, 하하!";
			link.l1 = "배의 자질구레한 거래를 네가 맡고 있다니, 급사 대신이라니 이상하군.";
			link.l1.go = "OfficerTorgovets_3";
		break;

		case "OfficerTorgovets_3":
			dialog.text = "급사놈은 사람들하고 말도 못 해! 그게 바로 보선장이 하는 일이거든 — 말도 잘하고 일도 잘하지, 하하! 급사놈도 자기 꿍꿍이가 따로 있겠지 — 하지만 난 그 더러운 일엔 끼어들 생각 없어.";
			link.l1 = "오늘은 뭐가 준비되어 있지?";
			link.l1.go = "OfficerTorgovets_4";
		break;

		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "배에 남은 마지막 럼주 한 병, 행운을 부르는 부적 몇 개... 그리고 봐라! 완벽한 보물 지도가 완성됐지.";
				link.l1 = "너는 갑판장이 아니라 상인이 되어야겠어! 어디 한번 네가 뭘 가졌는지 보자.";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "또 필요한 거 있나?";
				link.l1 = "어디 한번 네가 뭘 가진 놈인지 보자.";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "부적 말인가? 네 목에 걸려 있는 그거처럼?";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "미안... 지금 보물 지도를 말한 건가?";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "다음에 하자.";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;

		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "아, 눈썰미가 좋으시군요, 나리. 그래요, '코럴 헤드' 말입니다 — 훌륭한 물건이죠. 특히 저한테는 말입니다. 백병전을 이끌어야 할 때면, 이게 사내들을 모으는 데 큰 도움이 되거든요.";
			link.l1 = "그걸 정말 믿는 거야?";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;

		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "믿을 필요는 없어. 그게 바로 카리브 해의 방식이고, 뱃사람의 운명이야. 부적은 쓸모 있는 물건이지. 그러니 우리랑 같이 다닐 거라면, 여러 상황에 맞춰 몇 개쯤 챙겨두는 걸 추천해.";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "아, 그렇지. 카리브에선 흔한 일이야. 운 좋은 놈들은 한몫 잡지. 그러고는 세금 내고 조용히 오래 살거나... 아니면 금을 동굴에 숨기지. 결국 남는 건 무덤, 보물... 그리고 종이 쪼가리 하나뿐이지.";
			link.l1 = "그냥 그렇게?";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;

		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "꼭 그렇진 않아. 지도는 비싸고, 너 같은 다른 사냥꾼들도 끌어들이지. 그리고 때로는 노획물이 고생한 만큼도 안 나올 때가 있어. 위대한 알버트 블랙우드조차 처음엔 고생했지. 보물 사냥을 업으로 삼아라 — 많이 찾을수록 보상도 커진다. 그리고 행운의 부적이라도 있다면 — 더할 나위 없지!";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		// <-- Диалог с офицером-торговцем, который торгует всяким
		
		// --> Диалог с офицером-казначеем
		case "OfficerKaznachey":
			dialog.text = "Monsieur "+pchar.lastname+"! 잠깐만.";
			link.l1 = "또 잔소리입니까, Pinchon 나리? 당신의 소중한 잉크에는 손도 안 댔소!";
			link.l1.go = "OfficerKaznachey_2";
		break;

		case "OfficerKaznachey_2":
			dialog.text = "그럼 그 작은 책에 뭘로 끄적이고 있는 거지? 성수라도 쓰는 건가? 승객 명단에는 잉크가 없었어. 어쨌든, 지금은 더 큰 문제가 있잖아.";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_3";
		break;

		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "And two hundred more — for the broken windlass. The anchor cable snapped.";
			dialog.text = "너는 아직 배의 금고에 서른 페소를 빚지고 있어 — 네가 망가뜨린 빗물통 값이지. 네가 셔츠를 빨아보겠다고 한 그 우스꽝스러운 시도는, 그때 또 비가 오지 않았더라면 더 큰돈이 들 뻔했어. "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "막 내리자마자 빚이라니, 딱 필요했던 거네. 자, 받아.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "딱 필요했던 거네 — 배에서 내리자마자 빚이라니. 자, 받아.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "그게 다야? 이건 도박빚이 아니라고. 나 좀 바쁘니까 — 항구에 도착할 때까지 기다려야 해.";
			link.l2.go = "OfficerKaznachey_3_1";
		break;

		case "OfficerKaznachey_3_1":
			dialog.text = "유감이군. 그럼 — 본론으로 들어가지. 자네에게 맡길 일이 있네.";
			link.l1 = "넌 사람을 잘 다루는 타입은 아니구나?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_4":
			dialog.text = "잠깐만, 세어볼게.";
			link.l1 = "저녁 식사 후에 내가 식탁에 남긴 빵조각들도 꼭 세어보도록 해.";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;
		
		case "OfficerKaznachey_5":
			dialog.text = "축하하오. 이제 선박 금고에서 더 이상 묻는 것이 없소. 당분간은 말이오.\n바로 본론으로 들어가지. 자네에게 맡길 일이 있소.";
			link.l1 = "너, 사람 상대하는 데 영 소질 없지?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_6":
			dialog.text = "사람? 딱히. 하지만 숫자에는 자신 있지.\n그쪽은 어떤가, 나리 "+pchar.lastname+" — 너 숫자 셀 줄 아니?";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "(회계사) 나는 장부나 환어음에 익숙하지. 심지어 '제로'가 뭔지도 안다네.";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "아버지의 빈약한 용돈으로 한 철을 겨우 버틸 만큼이네.";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;

		case "OfficerKaznachey_7":
			dialog.text = "오오오! 진작 말해줬으면 더 재미있는 항해가 됐을 텐데.";
			link.l1 = "임무에 대해 말씀하셨습니까?";
			link.l1.go = "OfficerKaznachey_9";
		break;

		case "OfficerKaznachey_8":
			dialog.text = "자네를 위해서라도, 선주가 되지 않길 바라네. 자네는 자기 자신뿐만 아니라 배에 탄 모두를 파산시킬 테니까.";
			link.l1 = "임무가 있다고 하셨소?";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "그래. 알고 있는지 모르겠지만, 급사랑 의사는 선장 바로 아래야.\n"+"둘 중 어느 것도 없이 출항하는 건 돈을 걸고 도박하는 거지. 돈이 없으면, 배란 그저 값비싼 나무덩어리에 불과하거든.\n"+"회계장이 없으면 작은 슬루프 한 척도 선장을 파산시킬 수 있지. 그리고 의사 없이 치르는 첫 전투는 선원 전부를 몰살시킬 수도 있어 — 그럼 새 선원을 뽑고 훈련시키는 데 오랜 시간과 돈이 들게 되지.\n"+"다행히 우리 둘 다에게 좋게도, 나는 두 역할을 모두 맡고 있지. 그래서 개인적으로 거래를 하거나 선원들에게 사소한 부탁을 할 수 있네.\n"+"물론이지, 나는 후하게 지불하지 — 그리고 지금이 딱 그럴 때야.\n"+"이 명단과 이 더블룬 상자를 받아서, 선원들에게 급여를 지급해 주게.\n"+"적혀 있는 그대로야! 그래서 내가 네가 셈을 할 수 있는지 물어본 거지.";
			link.l1 = "왜 직접 하지 않으시오? 돈을 바란다면, 그들이 직접 당신에게 오게 하시오.";
			link.l1.go = "OfficerKaznachey_10";
		break;
		
		case "OfficerKaznachey_10":
			dialog.text = "지금 할 일이 너무 많아. 항해도 며칠 안 남았고, 곧 백 명이나 되는 선원들이 줄지어 임금을 달라고 할 거야.";
			link.l1 = "더블룬을 언급했지...";
			link.l1.go = "OfficerKaznachey_11";
		break;

		case "OfficerKaznachey_11":
			dialog.text = "스페인 금화. 진정한 경화지. 부의 진짜 척도라 할 수 있지. 가장 희귀하고 값진 서비스만이 이걸로 지불된다네.\n이런 상자에 보관하는 건 편의 때문이야.";
			link.l1 = "그럼 나는 뭐를 얻게 되지?";
			link.l1.go = "OfficerKaznachey_12";
		break;

		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "(회계사) 150페소, 그리고 추가로 5두블론 — 거의 내 동료나 다름없으니 말이오. 그리고 페소와 두블론 간의 환율도 공정하게 쳐주겠소.";
			}
			else
			{
				dialog.text = "150페소, 그리고 페소를 두블룬으로 바꿀 수 있는 권한이지. 많지는 않지만, 일이 간단하거든.";
			}
			link.l1 = "좋아. 목록이랑 상자를 넘겨.";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "이런 일은 제게 맞지 않는 것 같소. 안녕히 계시오, Pinchon 나리.";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;
		
		case "OfficerKaznachey_11_otkaz":
			dialog.text = "네가 알아서 해. 하지만 내 길을 막지 마, 나리 "+pchar.lastname+"";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;

		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "자, 여기 있다. 제발, 하느님 맙소사 — 상자에서 두블론을 꼭 챙기고, 목록대로 정확히 따르며, 절대 더 챙기지 마라. 빈 상자도 반드시 돌려주길 기대하네.\n무리하지 마시오, 나리. 왜 그렇게 잡동사니를 많이 들고 다니는 거요? 물건 일부는 상자에 넣어두는 걸 추천하네.";
			}
			else
			{
				dialog.text = "여기 있다. 제발, 신의 이름으로 — 상자에서 두블론을 꼭 챙기고, 목록대로만 가져가며, 남는 건 절대 챙기지 마라. 빈 상자도 반드시 돌려주길 바란다.";
			}
			link.l1 = "원하시는 대로 하겠습니다. 곧 뵙겠습니다, Pinchon 나리.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
				
		case "OfficerKaznachey_12_Wait":
			dialog.text = "어떻게 됐어? 다 갚았나? 남은 두블론이랑 빈 궤짝은 챙겼지?";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && PCharDublonsTotal() >= 18)
			{
				link.l1 = "모두 끝났어.";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "아직 아닙니다, Pinchon 나리.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;

		case "OfficerKaznachey_13":
			dialog.text = "어디 보자...";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_14";
		break;

		case "OfficerKaznachey_14":
			addGold = PCharDublonsTotal();
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "그리고 자네는 셈을 잘한다고 했지. 기대했던 것보다 두블룬을 적게 가져왔군. 그 말은 내 일이 더 늘어난다는 뜻이지, 줄어드는 게 아니야 — 그러니 자네는 보수도 못 받는다.";
				link.l1 = "그래도 두블룬은 바꿔줄 건가?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "그리고 자네가 셈을 잘한다고 했지. 가져온 게 정해진 것보다 더 많군. 그 말은 내 일이 더 늘어난다는 거고, 자네는 돈을 못 받는다는 뜻이야.";
				link.l1 = "교환은 어떤가?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "모두 맞았군. 젊은 세대도 아직 셈을 할 줄 아는 걸 보니 반갑소. 감사합니다, 나리 "+pchar.lastname+". 여기 네 임금이야 — 그리고 작은 보너스도 있지, 프로끼리 주는 거니까.";
					link.l1 = "그럼 교환은?";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "모두 맞네. 젊은이들이 돈을 책임감 있게 다루는 걸 보니 기쁘군. 고맙네, 나리 "+pchar.lastname+". 자, 여기 네 임금이다.";
					link.l1 = "아직도 교환하고 있나?";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 300);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
			pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "왜 안 되겠소. 더블룬당 115페소요. 관심 있으면 나에게 오시오.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;

		case "OfficerKaznachey_15_gold_105":
			dialog.text = "물론이지. 더블룬 한 개당 105페소야. 관심 있으면 나한테 와.\n조언 하나 해주지. 만약 운명이 널 배의 선장으로 만든다면, 제일 먼저 재무관부터 고용해. 형편없는 놈이라도 돈을 엄청 아껴줄 거야.";
			link.l1 = "감사합니다, Pinchon 나리.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;

		case "OfficerKaznachey_15_gold_100":
			dialog.text = "물론이지! 두블룬 한 개당 100페소 — 이 정도면 공정한 환율이야. 카리브의 은행들은 더 비싸게 받을걸.\n조언 하나 해주지: 만약 운명처럼 네가 배를 맡게 된다면, 제일 먼저 재무관을 고용해. 실력 없는 놈이라도 네 돈을 엄청 아껴줄 거야.";
			link.l1 = "감사합니다, Pinchon 나리.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;
		
		case "OfficerKaznachey_16_Proval": // Если не выполнил задание, то отбирает дублоны
			dialog.text = "빈둥거리고 있소, 나리 "+pchar.lastname+"?";
			link.l1 = "너도 창고 담당 맡았어?";
			link.l1.go = "OfficerKaznachey_16_Proval_2";
		break;
		
		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "나는 배의 의사요, "+pchar.lastname+"! 곧 사관실이 부상자들로 가득 차겠지, 나는 어떤 전사보다도 더 많은 피를 보게 될 거야. 내가 단순히 경리장교였더라도, 여전히 총알이 날아드는 곳에 서 있었을 거고. 아니, 아늑한 창고에서 쉴 수 있게 된 건 오직 너 하나뿐이야.";
			link.l1 = "그럼 여기서 뭘 하고 있는 거지?";
			link.l1.go = "OfficerKaznachey_16_Proval_3";
		break;
		
		case "OfficerKaznachey_16_Proval_3":
			dialog.text = "전투가 시작되려면 아직 몇 시간 남았으니, 오늘의 장부를 정리하기 딱 좋은 시간이오. 내 더블룬 상자는 자네가 가지고 있지, 드 모르 나리. 돌려주게.";
			if (PCharDublonsTotal() >= 1 || GetCharacterItem(pchar, "chest") >= 1 || GetCharacterItem(pchar, "chest_open") >= 1)
			{
				link.l1 = "가져가. 그리고 다시는 여기 내려오지 마라.";
				link.l1.go = "OfficerKaznachey_16_Proval_4";
			}
			else
			{
				link.l1 = "네 물건은 다른 데 두고 왔어.";
				link.l1.go = "OfficerKaznachey_16_Proval_5";
			}
		break;
		
		case "OfficerKaznachey_16_Proval_4":
			addGold = PCharDublonsTotal();
			dialog.text = "그럴 의도는 없었어. 난 뭍사람이 아니야 - 내 자리는 창고가 아니지. 잘 있어라.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			if (PCharDublonsTotal() >= 1 || GetCharacterItem(pchar, "chest") >= 1) ChangeCharacterComplexReputation(pchar, "nobility", -3);
			else ChangeCharacterComplexReputation(pchar, "nobility", -6);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;
		
		case "OfficerKaznachey_16_Proval_5":
			dialog.text = "다른 곳에서... 이 이야기는 전투가 끝난 후, 선장님 앞에서 나누도록 하죠. 그때까지 기다리시오.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
		break;
		
		case "TreasurerTrade":
			dialog.text = "두블룬에 관심 있소, 나리 "+pchar.lastname+"?";
			link.l1 = "거래를 하자.";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "지금은 아니야.";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;
		
		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;
		// <-- Диалог с офицером-казначеем
		
		// --> Матрос сообщает о приближающихся кораблях
		case "Sailor_Trevoga":
			dialog.text = "선장님, 경보예요! 수평선에 해적이 보여요!";
			link.l1 = "...";
			link.l1.go = "Sailor_Trevoga_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
			PlaySound("Ship\rynda_alarm.wav");
		break;

		case "Sailor_Trevoga_2":
			StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "Sailor_Trevoga_3":
			dialog.text = "알론소, 나리 모셔다 드리게 "+pchar.lastname+" 창고로 가라. 그리고 드뤼삭 나리가 깨어 있고 포수들이 준비됐는지 꼭 확인해라.";
			link.l1 = "선장님, 싸울 준비가 됐습니다! 귀족이란 자가...";
			link.l1.go = "Sailor_Trevoga_4_fencing";
			link.l2 = "제가 어떻게든 도울 수 있다면...";
			link.l2.go = "Sailor_Trevoga_4_leadership";
			link.l3 = "잠깐, 그럼 부르고뉴 와인도 없는 거야?..";
			link.l3.go = "Sailor_Trevoga_4_fortune";
		break;

		case "Sailor_Trevoga_4_fencing":
			dialog.text = "알론소, 저 자를 끌고 나가라. 어서 움직여, 게으름뱅이들아! 돛 올려!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Sailor_Trevoga_4_leadership":
			dialog.text = "알론소, 저 자를 데리고 나가라. 어서 움직여, 게으름뱅이들! 돛 올려!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Sailor_Trevoga_4_fortune":
			dialog.text = "알론소, 저 자식 끌고 나가! 어서 움직여, 게으름뱅이들아! 돛 올려라!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
				// <-- Матрос сообщает о приближающихся кораблях
				
				// --> Диалог с пиратом в трюме
		case "EnemyPirate_1":
			dialog.text = "제기랄! 고집 센 악마들 같으니!";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_2";
			//PlaySound("VOICE\Spanish\OliverTrast01.wav"); //вставить для испанской версии
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
		break;

		case "EnemyPirate_2":
			dialog.text = "여기서 뭐 하는 거야?! 선원들 버리고 싸움에서 도망치는 쥐새끼냐?! 지금 당장 네 배를 갈라버릴 테다!";
			link.l1 = "내 화물칸에 기어들어온 건 실수였지. 내가 직접 네 배를 갈라주마.";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "너 겨우 서 있잖아, 게다가 네 몸에 묻은 피 대부분은 네 것도 아니야.";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "(결투사) 이 맛이 얼마나 그리웠던가.";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;

		case "EnemyPirate_3_Fencing":
			dialog.text = "헤헤. 가 봐라, 멋쟁이.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "EnemyPirate_3_Leadership":
			dialog.text = "헤헤. 그럼 난 잃을 게 없군.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "EnemyPirate_3_Duelyant":
			dialog.text = "무슨 헛소리를 지껄이는 거야?!";
			link.l1 = "두 달. 두 달이나 칼을 뽑지 못했지. 이제 한판 붙자!";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// <-- Диалог с пиратом в трюме
		
		// --> Диалог с выжившим матросом
		case "SailorAlive_1":
			dialog.text = "적어도 넌 살아 있군... 난 끝장이야. 키에 세게 얻어맞았어...";
			link.l1 = "무슨 일이야?!";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_2":
			dialog.text = "놈들이 배에 올라탔어. 악! 고집 센 악마들 같으니!\n잘 들어: 우리가 포갑판은 지켰지만, 위층에서 진짜 난리가 시작됐어. 맹세컨대, 놈들이 곧 여기로 내려올 거야. 산탄총 가져가! 조심해, 악마야! 장전돼 있으니까!";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "(저격수) 나 걱정하지 마. 덤비는 놈은 다 구멍 내줄 테니까.";
			}
			else link.l1 = "...";
			link.l1.go = "SailorAlive_3";
		break;

		case "SailorAlive_3":
			dialog.text = "포도탄이 들어 있어. 제대로만 하면 한 번에 두세 놈은 쓰러뜨릴 수 있지.\n난 네 실력을 믿어. "+pchar.name+". 놈들을 물리치고 나면, 시체들을 뒤져 봐. 혹시 나 줄 술이라도 찾을 수 있을지 모르지... 아니면 난 아무 쓸모 없어.";
			link.l1 = "버텨, Alonso. 손님들이 온다!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;

		case "SailorAlive_11":
			dialog.text = "좋아... 수고했어, "+pchar.name+". 나에게 줄 만한 걸 찾았나?";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "여기가 맞는 것 같아. 그래도 좀 수상해 보이는데.";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "아직도 찾고 있어!";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;

		case "SailorAlive_12":
			dialog.text = "꽤 괜찮은데, 하하! 고마워, "+pchar.name+". 그리고 저 셋도 — 잘 처리했군. 자네가 진정한 귀족이니, 지휘를 맡게. 함께라면 이 갑판을 지킬 수 있어. 위층 녀석들도 해내면 — 오늘은 우리 날이야!";
			link.l1 = "...";
			//link.l1.go = "exit";
			link.l1.go = "SailorAlive_13";
			//AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_13":
			/*if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "훨씬 낫군. 산탄총은 장전했나?";
				link.l1 = "그냥 그렇게 하고 있었는데... 왜 갑자기 이렇게 조용해진 거지?";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "그대가 진정한 귀족이니, 지휘를 맡으시오.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}*/
			dialog.text = "훨씬 낫군. 산탄총 장전했나?";
			link.l1 = "그냥 그렇게 하고 있었는데... 왜 갑자기 이렇게 조용해진 거지?";
			link.l1.go = "SailorAlive_14";
			SetMusic("");
			LAi_SetActorType(npchar);
			LAi_ActorSetGroundSitMode(npchar);
			LAi_ActorAnimation(npchar, "ground_standup", "1", -1);
		break;

		case "SailorAlive_14":
			dialog.text = "그냥 분위기 좀 내보려고. 이제 곧 시작이야.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		// <-- Диалог с выжившим матросом
		
		// --> Диалог с Алонсо после боя
		case "AfterBattle_Alonso_1":
			dialog.text = "여기까지 왔군, 시작했던 곳에서 끝을 맺네. 내 목숨을 구해줘서 고마워, "+pchar.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "이제 우리 비긴 셈이군. 네가 어떻게 날 거기서 끌고 나왔는지도 기억이 안 나.";
			}
			else
			{
				link.l1 = "이제 우리 퉁친 셈이군. 너랑 녀석들 아니었으면, 난 아직도 거기 있었을 거야.";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "AfterBattle_Alonso_2":
			dialog.text = "시킨 대로 창고에 그냥 있었으면 됐잖아. 선장님이 살아 계셨다면 제대로 혼 좀 내주셨을 텐데, 아쉽군.";
			link.l1 = "우리가 시체 더미 밑에서 그를 끄집어내야 했지. 저 자식이 몇 놈이나 해치운 거야?";
			link.l1.go = "AfterBattle_Alonso_3";
		break;

		case "AfterBattle_Alonso_3":
			dialog.text = "어떤 놈들은 그가 셋을 쓰러뜨렸다고 하고, 다른 놈들은 열둘이라고 하더군. 내 생각엔 악마만이 제대로 셌을 거야.";
			link.l1 = "아직도 어떻게 이렇게 된 건지 말하지 않았잖아.";
			link.l1.go = "AfterBattle_Alonso_4";
		break;

		case "AfterBattle_Alonso_4":
			dialog.text = "무슨 할 말이 있겠어? 우리 16파운드포도 해적 브리그 한 척도 막지 못했지.\n"+"눈 깜짝할 사이에 우리에게 들이닥쳐서, 우리가 방향을 틀 때 산탄을 쏘아댔고, 바로 배에 올라탔지. 갑판을 봤어야 했어 — 외과의가 할 일이 하나도 남지 않았더군.\n"+"해적들과 싸우는 게 제일 싫은 점은, 이득이 하나도 없다는 거지. 다 거지들뿐이야. 그놈들 브리그조차 못 챙겼다니까.";
			link.l1 = "그 다음엔 어떻게 되는 거지?";
			link.l1.go = "AfterBattle_Alonso_5";
		break;

		case "AfterBattle_Alonso_5":
			dialog.text = "배는 떠 있고, 남은 선원도 충분하니 예정대로 생피에르까지 데려다 줄 수 있소. 거기서 나는 새 선장을 구할 것이고, 그대는 형을 찾아가서 그간의 모험을 모두 이야기하게 될 것이오. 그 다음에 무슨 일이 일어날지는… 오직 신만이 아시겠지.\n"+"하지만 한 가지는 확실해 - 너 우리랑 잘 어울릴 거야. 육지 쥐 치고는 괜찮은데, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "AfterBattle_Alonso_6";
		break;

		case "AfterBattle_Alonso_6":
			dialog.text = "하! 이제 곧 속이 뒤집히기 시작할 거야. 쫄지 마라. 그건 네 몸에서 두려움이 빠져나가는 거니까. 카리브에 온 걸 환영한다!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		// <-- Диалог с Алонсо после боя
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}