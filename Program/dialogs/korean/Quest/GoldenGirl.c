// диалоги персонажей по квесту Дороже золота
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
			link.l1 = "가야겠군...";
			link.l1.go = "exit";
		break;
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = "샤를 드 모르 선장님! 드디어 찾았습니다! 자크 딜 드 파르케 나리께서 당신을 당장 뵙자고 하십니다! 급한 일입니다!";
			link.l1 = "왜 놀랍지도 않지? 좋아, 각하께 곧 찾아뵙겠다고 전해 주시오.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = "내 눈이 잘못된 게 아니라면, 이 사람이 바로 샤를 드 모르 본인이라니! 내가 이런 환영회를 자주 여는 것도 아닌데, 이렇게 보잘것없는 수도원에 시간을 내주셔서 정말 기쁩니다. 내가 운이 좋군요! 이건 건배할 만한 일이지!";
			link.l1 = "안부를 전합니다, 부인. 혹시 제 태도가 실망스러웠다면 용서해 주십시오 - 이런... 행사에 참석한 지 정말 오래되었습니다. 배 위의 예절이란 상관에 대한 복종, 깨끗한 스카프, 그리고 매일 아침 한 잔의 상쾌한 커피 정도뿐이니까요.";
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = "정말 매력적이군요, 선장님. 아직도 파리에서 묻어난 세련됨이 남아 있네요. 이 바다에 단련되고 소금에 절인 얼굴 아래로 그 은은한 빛이 보입니다. 걱정 마세요, 이렇게 드디어 만나게 되어 너무 기뻐서 뭐든 다 용서해 드릴 수 있을 것 같아요. 지금은요. 앞으로 우리 사이가 어떻게 될지는 두고 봐야겠죠. 와인 드릴까요? 적포도주로 할까요, 백포도주로 할까요?\n";
			link.l1 = "럼 농담하기 딱 좋은 순간인데, 아쉽게도 지금은 그럴 기분이 아니야. 미안해. 네 고운 손이 따라주는 거라면 뭐든 기꺼이 마실게.";
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = "괜찮은데. 하지만 난 고집이 세. 와인을 좋아하는 취향만 봐도 그 사람이 어떤 사람인지 알 수 있거든. 오늘 밤엔 너에 대해 전부 알아낼 생각이야. 그러니 다시 묻지: 레드야, 화이트야?";
			link.l1 = "네 마음대로 해. 너도 적포도주를 마시고 있군. 나도 같은 걸로 할게. 너에 대해서도 좀 알고 싶으니까.";
			link.l1.go = "Julianna_3";
			link.l2 = "그렇다면 나는 백포도주로 할게, 하지만 네가 골라. 이건 서로에게 괜찮겠지, 안 그래?";
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = "훌륭하군, 이제 내 차례인가? 이건 부르고뉴 피노 누아야. 양조사들은 '말썽꾸러기 아가씨'라고 부르지. 다루기 쉽지 않은 품종이고, 여운도 꽤나 속을 알 수 없지. 만족하나?";
			link.l1 = "피노 누아라, 그래? 나야 좋지. 믿을 수 없고 신비로운 녀석, 처음엔 암울한 맛이지만, 좀 숨 쉬게 두면 놀라게 될 거야. 은은하게 어우러지는 색과 향, 진짜 애주가들이 고르는 술이지. 첫인상은 속이기 마련 아니겠어? 당신의 눈을 위해 마시겠소, 부인!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = "훌륭하군, 이제 내 차례인가? 나는 루아르 밸리에서 온 멋진 소비뇽 블랑을 가지고 있지. 꽤나 거칠어서, 혀끝에서 톡 쏘는 느낌이 들 거야. 그리고 결정적으로, 화약 냄새가 살짝 감도는군. 우리 사이에 공통점이 있는 것 같아.";
			link.l1 = "나는 더 나은 걸 기대했지, 예를 들면 리슬링 같은 거 말이야. 뭐, 여름과 화약 냄새가 나는 이 투박한 술이나 마시자고. 어떤 사람들은 이걸 '고양이 오줌'으로 착각한다는 얘기 들어봤나? 네 이 사파이어만큼 빛나는 미소를 위해 한잔하겠어!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = "대단하군, Charles! 그렇게 불러도 되겠어? 내가 너를 잘못 본 게 아니었어; 다른 날이었다면 오늘 밤의 주인공은 분명 너였을 거야. 하지만 아쉽게도, 내 선장님, 오늘은 강력한 경쟁자가 있네. 저기서 곧 스캔들이 터질 것 같은데, 보이나?";
			link.l1 = "화난 목소리가 들리네. 이 불쾌한 나리는 누구고, 우리 소중한 총독님을 어떻게 화나게 한 거지?";
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = "이 '불쾌한' 나리는 앙제랑 드 시에부스로, 드 레비 방타뒤르 백작의 인정받지 못한 사생아야. 너는 지금 그들의 논쟁거리에 휘말린 거지. 드 시에부스는 수년간 내 환심을 사려고 애썼고, 여기까지 따라왔어. 자기 아버지를 대신할 수 있다고 생각한 거지. 정식 아들은 아니지만, 돈도 많고 권력도 있어. 고집도 그의 특징 중 하나야. 어떤 사람들에겐 그게 지혜를 대신하지. 네가 오기 직전에, 그와 자크가 뻔한 주제로 말다툼을 시작했어. 각하께서는 항상 아주 감동적으로 날 보호해 주시지, 네가 직접 보면 좋을 텐데! 자, 가서 이번엔 어떻게 끝나는지 지켜보자고.";
			link.l1 = "공기에서 뭔가 불길한 냄새가 나는군... 이렇게 멋진 밤에도 왜 항상 함정이 있는 거지...";
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = "뭐라고, Charles?";
			link.l1 = "잊어버려. 네가 그렇게 집요하게 구는 친구를 소개해 줘, 그다음에 생각해 보지...";
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = "나리, 제 소중한 손님을 소개하겠습니다 - 바로 이분이 직접 오신 샤를 드 모르 선장님이십니다! 이렇게 유명하신 분이 저희를 찾아주신 건 정말 드문 일입니다.";
			link.l1 = "...";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = "샤를, 이 상황이 영 마음에 안 들어! 자크는 내 말에 귀를 닫았고, 앙제랑은 분명 뭔가 꾸미고 있어. 이 싸움엔 분명 목적이 있었어, 네 도움이 필요해!";
			link.l1 = "무슨 말인지 잘 모르겠군... 내가 여기서 뭘 할 수 있겠어? 그는 이미 결투를 거절했잖아...";
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = "선장님, 제발 저를 실망시키지 마십시오. 방금 전까지만 해도 대화의 달인이셨는데, 지금은 칼로 찌를 수 있는 것과 없는 것만 생각하고 계시잖습니까. 좀 더 유연하게 생각해 보세요! 앙제랑의 계획을 망쳐버립시다. 저 자는 불쌍한 자크에게 혼자 도전하려고 하는데, 그건 너무 재미없잖아요! 우리 토너먼트를 열어봅시다! 여기 계신 여러 신사분들이 큰 판돈도 거실 수 있고, 선장님의 행운은 이미 전설로 통하고 있습니다! 어쩌면 오늘 밤엔 카드가 선장님 편을 들어줄지도 모르지요?\n";
			link.l1 = "그게 어떻게 드 쉬에부스가 우리 귀여운 총독과 싸우는 걸 막을 수 있을지는 잘 모르겠지만, 저도 함께하겠습니다, 부인. 그 자의 얄미운 미소를 지워버릴 수 있다면 뭐든 하죠.";
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = "훌륭해, 이제 가서 식탁에서 뭐라도 먹어둬. 오늘 밤은 길 거야. 준비가 되면 홀에서 나를 찾아와, 이 일엔 더 넓은 공간이 필요하니까. 그동안 나는 다른 이들을 설득해서 구경거리와 고액 도박을 벌이게 하며, 쇼를 좀 펼칠 거야. 심지어 저 멍청이들이 지루해 죽는 여자를 좀 알아보라고 소리도 질러줄지 몰라. 제발 끼어들지 마, 오늘 밤 우리가 한편인 건 아무도 알아선 안 돼. 이따 보자, 내 선장!";
			link.l1 = "무엇이든 말씀대로 하겠습니다, 부인, 말씀대로 하겠습니다...";
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = "자, 축하해 줘, 성공했어! 약간의 자존심, 약간의 편견, 그리고 짠! 지루한 표정 지어, 우리를 지켜보고 있으니까. 네가 나한테 관심 있는 게 아니라 술에 관심 있는 것처럼 보이게 해\n곧 토너먼트가 시작돼, 판돈도 크고, 두 번의 기회나 재경기는 없어. 왠지 네가 이런 상황에 익숙하다는 걸 알고 있어. 잘 해낼 거야. 기억해, 앙제랑이 뭔가 꾸미고 있어, 우리 친구 자크를 노릴 거야. 하지만 네 등장은 계산에 없었지. 내 비장의 패가 되어 줘, 저 자만에 찬 앙제랑의 얼굴을 보는 건 절대 좋은 징조가 아니니까. 참가자는 여덟 명, 네가 결승까지는 그와 맞붙지 않게 내가 신경 써 뒀어\n오! 네 첫 상대다! 대령이자 우리 요새의 사령관이야. 바다 대 육지, 군 경력이 있는 손님들에게 딱 어울리는 대결이지! 박수!";
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "잘했어, Charles, 정말 훌륭했어. Angerran이랑 Jacques가 곧 맞붙게 생겼군. 일주일만 토너먼트를 미뤘으면 좋았을 텐데, 내 말을 안 들으니 아쉽군. 그랬다면 정말 화려한 인물들을 모아서 파리까지 소문이 퍼질 만한 잔치를 열 수 있었을 텐데! 뭐, 다음 기회를 노려야겠지. 다음 상대는 네 운에 걸맞은 진짜 강자야, 진정한 바다늑대, Moreno 선장! 선장들, 앞으로!\n";
				link.l1 = "";
			}
			else
			{
				dialog.text = "안타깝게도, 선장님의 운이 다했군요. 유감이지만, 당신의 게임은 끝났습니다. 앙제랑은 이미 자크와 대결 중이니, 저는 이만 가봐야겠어요. 안녕히 계십시오.";
				link.l1 = "즐거웠소... 부인.";
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "자격 있는 승리를 축하하오, 선장! 결승에서 누가 당신과 맞붙을지는 아직 불분명하군... 잠시 옆으로 가시지. 목소리를 낮추고 저 테이블을 보시오. 저기, 저 사람 보이시오! 이제야 앙제랑이 뭘 꾸미는지 알 것 같군! 벌써 착한 자크의 돈을 다 털었는데도, 테이블에서 못 떠나게 하고 있소. 내가 지나갈 때 보니, 그 불쌍한 놈이 화물까지 실린 배 전체를 걸고 서류를 내기하고 있더군. 안타깝게도 오늘 밤은 운이 그의 편이 아닌 것 같소. 아니면 누가 운에게 그러지 말라고 했나 보군.";
				link.l1 = "드 시비우스가 속임수를 쓰고 있다고 생각해?";
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = "안타깝게도, 선장님의 운이 다했군요. 유감이지만, 게임은 여기서 끝입니다. 앙제랑은 이미 자크와 대결 중이니, 저는 이만 가봐야겠군요. 안녕히 계십시오.";
				link.l1 = "즐거웠습니다... 부인.";
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = "그가 원했다면 분명히 할 수 있었겠지만, 나는 증거가 없어. 우리 총독 나리께서 카드 실력이 좋으시지만, 상대도 만만치 않아. 앙제랑은 자기 프리깃함을 걸고도 눈 하나 깜빡이지 않았어, 상상이나 해 봐. 이 결투가 파리나 리옹에서 벌어졌다면 전설이 됐을 거야, 샤를! 그래도 오늘 밤은 그냥 운이 좋은 걸 수도 있어. 가까이 가서 직접 확인해 보자고.";
			link.l1 = "...";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = "찰스, 나 좀 붙잡아 줘, 아니면 쓰러질 것 같아... 아니, 안 쓰러질지도 모르지 - 이 멍청이들은 내가 기절해도 눈치도 못 챌 테니까. 봤어? 자크, 네 멍청함을 저주한다! 어린애 같잖아, 이런! 바보 같은 애야!";
			link.l1 = "마르키즈, 무슨 말씀인지 잘 모르겠습니다. \n저기 저 테이블에서 지금 무슨 일이 벌어지고 있습니까? 뭘 걸고 내기하는 거죠?";
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = "나한테 걸었지, Charles. 우리 착하고 어리석은 Jacques가 나한테 내기를 걸었어. Angerran이 그의 유일한 약점을 찾아내서 딱 맞는 순간에 찔렀지.";
			link.l1 = "젠장! 하지만 내가 다음 시합에 나가는데, 그 자식 배를 되찾을 수도 있었잖아! 왜지?";
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = "앙제랑은 이 일을 깊이 생각하고 모든 걸 치밀하게 계획했으니까. 내 말 잘 들어, 우리에겐 시간이 많지 않아. 너도 그에게 똑같이 해야 해. 그놈의 모든 걸 빼앗아, 돈도, 배도 전부 가져가, 자극해! 명예든, 평판이든, 열정이든 뭐든지로 그놈이 이성을 잃게 만들어! 오늘 밤 어떻게 하는지 봤잖아. 그를 궁지에 몰아넣고 판돈을 걸게 만들어\n제발 부탁이야, 샤를! 난 뭐든 할 준비가 되어 있지만, 저놈에게 직접 가지는 않을 거야. 이렇게는 못 해! 반타뒤르 백작조차 정정당당한 카드 승부 앞에서는 나서지 않을 거고, 날 도와주려고 손가락 하나 까딱하지도 않을 거야. 알다시피, 귀족들에게 카드는 빌어먹을 신성한 거야, 젠장! 너만이 내 마지막, 유일한 희망이야, 샤를!";
			link.l1 = "아직 우리 총독을 묻지 마시오, 부인. 어쩌면 그가 배를 되찾을지도 모르지. 행운의 여신은 변덕스러운... 여자니까.";
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = "아직도 모르겠어? 저 테이블엔 운이 끼어들 틈이 없어! 앙제랑 드 시에부가 모든 걸 쥐고 있지. 그는 나를 손에 넣으면서도 자기 아버지를 이 일에서 빼는 방법을 찾아냈어. 얼마나 오래 준비한 건지 나도 모르지만, 지금쯤이면 거의 다 이긴 셈이야. 그는 게임을 완전히 장악했고, 우리가 판을 뒤집을 기회는 단 한 번뿐이야. 자, 이걸 받아! 내가 일부러 허세를 부릴 테니, 그 틈에 1~2분 정도 생길 거야. 현명하게 써.";
			link.l1 = "마르키즈님... 아무나, 제발 도와주세요! 마담께서 몸이 안 좋으십니다! 빨리요!";
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			Log_Info("You have received amulet 'Turtle'");
			Log_Info("You have received amulet 'Joker'");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = "아니, 아니요, 전 괜찮아요... 여기 안이 좀 답답해서요... 정말 죄송합니다, 여러분. 잠시 바람 좀 쐬고 오겠습니다. 저 없이 계속 하셔도 됩니다.";
			link.l1 = "...";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = "지금 이 순간, 그리고 생피에르에서는 아니지만, 내가 아는 사람이 있네. 내가 약속하지, 앙제랑. 이건 분명 훌륭한 그림이 될 거야...";
			link.l1 = "...";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = "앙제랑, 넌 정말 답이 없구나! 질 줄도 좀 배워라! 이건 그냥 게임일 뿐이고, 모든 걸 예측할 수는 없어. 와인이나 다 마시고 옷 입어라 - 규칙은 그대로야 - 진 사람은 우리 아늑한 파티에서 나가야 해.";
			link.l1 = "마르키즈님, 잠깐만...";
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = "이건 도가 지나치오, 신사 여러분! 당장 멈추시오! 우리는 모두 지치는 밤을 보내 몹시 피곤하오. 유감이지만 이제 손님들께 작별을 청해야겠소. 명예로운 신사답게 내일 다시 논쟁을 이어가도 되오, 마음이 바뀌지 않는다면 말이오. 하지만 여기서는 누구도 무기를 뽑아서는 안 되오, 알겠소?\n";
			link.l1 = "...";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = "찰스, 미안하지만 너도 이제 자리를 비워 줘야겠어. 위층에 올라가서 방 하나 잡아. 내가 모든 걸 알아서 할 테니. 네가 나를 위해 해 준 모든 일에 말로 다 할 수 없이 고맙지만, 나도 혼자만의 시간이 좀 필요하고, 너도 많이 피곤할 거야.";
			link.l1 = "그렇게 나쁘진 않소, 마님. 그래도 침대는 마다하지 않겠소. 이 소박한 파티가 거대한 적 해군 함대보다 더 힘들게 했소. 이 모든 일이 마르키즈 당신에게도 쉽지 않았으리라 이해하오. 푹 쉬시고, 걱정 마시오. 내게 빚진 것 없소. 지금 내게 필요한 건 잠뿐이오.";
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = "정오까지는 꼭 깨워 주겠소. 이미 새벽이니 더 이상 잘 자라는 인사는 못 하겠군. 푹 쉬시오.";
			link.l1 = "마르키즈 당신도요.";
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = "여기 있었군, Charles. 사실 나는 한숨도 못 잤는데, 너는 푹 잔 얼굴이네. 잠은 잘 잤어? 아침은 곧 나올 거야.";
			link.l1 = "나리의 환대는 전설적이지만, 유감스럽게도 즐길 시간이 없소. 각하와 드 시에부의 수행원들, 내가 획득한 배들—이 모든 것이 나를 기다리고 있소.";
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = "너는 배만 이긴 게 아니야. 내가 또 물어보고 싶은 게 있어, Charles...";
			link.l1 = "나는 자크도 앙제랑도 아니오, 후작 부인. 나는 여인의 환심을 사려고 내기를 하지 않소. 당신은 나에게 아무런 빚도 지지 않았소.";
			link.l1.go = "Julianna_41";
			link.l2 = "당신은 내 보호 아래에 있소, Marquise. Jacques도 Angerran도 더는 당신을 괴롭히지 못할 것이오, 내가 약속하오.";
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = "찰스, 자네는 엄청나게 명예로운 사람이거나 사랑에 빠진 게 분명하군. 물론 나랑은 아니지. 그래도 다시 한 번, 진심으로 고맙네. 내가 자네에게 도움이 될 수 있다면, 언제든 말만 하게.";
			link.l1 = "줄리안느, 시간이 얼마 남지 않았고, 나는 앞에 놓인 가장 불편한 일을 마주하고 있어. 드 쉬에부는 쓰레기 같은 놈이고, 정정당당한 결투조차 어젯밤 우리가 본 것처럼 금방 끝장날 수 있지. 이 모든 일이 완전히 끝나면 다시 이야기하자. 조용히 잘 수 있는 기회를 줘서 고맙고, 다시 만날 날을 기대하고 있어.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = "진심으로 감사해요, Charles... 믿어줘요, 당신의 전리품이 된 것도 내겐 일종의 승리거든요. \n이 대화를 좀 더... 사적인 곳에서 이어갈까요?";
			link.l1 = "줄리안느, 시간이 얼마 남지 않았고 내 앞에는 가장 어려운 일이 기다리고 있어. 드 시에부스는 쓰레기 같은 놈이야, 그리고 정정당당한 결투조차도 어젯밤 우리가 본 것처럼 순식간에 끝날 수 있지. 이 모든 일이 끝나면 나중에 다시 얘기하자. 평안히 쉴 수 있는 기회를 줘서 고마워, 다시 만날 날을 기대하고 있어.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = "그럼 더 이상 지체하지 않겠소, 내 선장님. 하지만 기억하시오, 앙제랑은 위험한 자요. 그의 전투 실력은 내가 판단할 수 없지만, 여러 전쟁에 참전했고 로크루아 전투에도 참여했소. 또 권총으로 치른 결투에서 몇 번이나 이겼다는 소문도 들었지. 무엇보다도, 자네도 알다시피 그는 아주 교활한 놈이오. 제발 조심해 주시오, 그리고 끝나면 꼭 나를 찾아오시오!";
			link.l1 = "신경을 쓰시니 더욱 빛나십니다, 마르키즈님. 믿으십시오, 드 쉬에부 놈이 제 앞길을 막은 첫 번째 자식은 아닙니다. 저는 알아서 할 수 있습니다. 이제 정말 각하를 뵙고 결투 문제에 대해 상의해야겠군요.";
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = "행운을 빕니다, 내 선장님! 그리고 자크에게 내 집 문 근처엔 얼씬도 하지 말라고 전해 주십시오.";
			link.l1 = "내가 약속하지. 또 보자, Marquise!";
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = "선장님, 오셨군요, 정말 다행입니다! 어떻게 됐습니까? 피 흘리시는 건 아니죠?!";
			link.l1 = "이건 내 피가 아니야... 적어도 전부는 아니지. 마르키즈, 드 쉬에부스는 어디 있지?";
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = "나도 똑같은 걸 물어보려고 했어 - 네가 그 자를 쓰러뜨리지 못한 거야? 무슨 일이 있었던 거지? 왜 마을 경비병 절반이 밖에 있는 거야?";
			link.l1 = "나는 총독에게 자네가 위험할 수도 있다고 말했어. 드 쉬비우스는 부상을 입고 도망쳤고, 자기 졸개들을 우리에게 풀어놨어. 그야말로 학살이었지.\n하지만 이런 이야기는 자네처럼 고운 귀에 들려줄 만한 게 아니야.\n이제 끝났어. 자네는 그놈과 우리 '달콤한' 자크에게서도 자유야.";
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = "이거 정말 안 좋군, Charles. Angerran de Chievous 같은 적은 기회가 있을 때 확실히 죽여야 해. 난 그 자를 여러 해 동안 알아왔지—절대 용서하는 성격이 아니야. 머지않아 반드시 복수할 방법을 찾아낼 거다. 그런데 자세가 안 좋아 보이는데, 상처는 제대로 치료받았나?";
			link.l1 = "그냥 긁힌 상처일 뿐이오, 더 심했던 적도 있었소. 조금 아프긴 하지만 괜찮소. 신경 써 주셔서 고맙소, 부인. 하지만 이만 가봐야겠소...";
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = "선장님, 저를 위해 배와 재산을 걸고 도박을 하셨고, 저를 위해 목숨과 경력을 걸고 싸우셨지요. 제가 해드릴 수 있는 최소한은 상처를 치료해드리고, 안전하게 쉴 곳을 마련해드리는 것입니다.\n안 돼요! 더 이상 아무 말도 듣고 싶지 않아요. 제 손을 잡고 위층으로 따라오세요. 선장님의 방이 기다리고 있어요.";
			link.l1 = "제안을 받아들이겠소, 부인, 고맙소. 하지만 폐를 끼치고 싶지 않으니, 내가 직접 위층으로 올라가겠소.";
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = "마르키즈, 당신은 제 수호천사이십니다. 이제는 제가 당신께 빚을 진 셈이군요.";
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = "샤를, 너는 기사도의 본보기야! 맹세컨대, 네가 계속 그러면 내 정신이 나갈 것 같아! 좋아, 내 기사님, 드니즈를 너에게 보내줄게. 그녀가 제대로 된 의사처럼 네 상처를 치료해줄 거야.";
			link.l1 = "감사합니다, 후작부인 나리. 제 마음이 이미 다른 이에게 빼앗기지 않았다면 기꺼이 어울렸을 텐데요. 하지만 아쉽게도! 안녕히 주무십시오!";
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = "이번에는 내 말대로 당장 따라줘야겠어. 내 손을 잡고 내가 시키는 대로 해. 드니즈! 솜이랑 뜨거운 와인, 먹을 것 좀 위층으로 가져와! 가요, 내 선장님. 그리고 기억해, 이번엔 절대 토 달지 마!";
			link.l1 = "말씀대로입니다, 마르키즈 나리, 저는 온전히 나리의 것입니다.";
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_KissJulianna");
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "좋은 아침이네, Charles. 네 '상처'들은 좀 어떤가?";
				link.l1 = "그대의 노력 덕분에 내가 다시 태어난 기분이오. 진심으로 감사드리오, Julianna.";
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = "좋은 아침이오, 내 영웅. 그대의 '상처'들은 좀 어떤가?";
				link.l1 = "걱정해 주셔서 감사합니다, 부인. 저는 아무 문제 없습니다. 데니스가 제 배의 의사로 일해 준다면 큰돈이라도 내겠어요. 정말 기적 같은 분이십니다!";
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = "쉽게 해결되지는 않을 것 같소. 하지만 정말 중요한 이유가 아니면 감히 당신을 깨우지 않았을 거요. 믿으시오, 나는 두려움 없이 당신의 잠을 지켰소. 그런데 아래에 있는 저 사내가 아주 끈질기게 굴더군. 자기 말로는 당신 선원 중 한 명이라며 급한 일이라고 하오.";
			link.l1 = "내 선원들? 깨워줘서 잘했소, 마르키즈 나리! 곧바로 출발하겠소.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = "상황이 달랐다면 그러고 싶었겠소, 선장님. 하지만 미뤄야 할 것 같소. 아래층에 다소 무식한 나리가 기다리고 있소. 자기 말로는 선장님의 선원 중 한 명이고, 급한 일이라 하더이다.";
			link.l1 = "돌아오면 다시 이야기합시다, 마담. 이번에도 또 스페인 놈들이 포위했다는 얘기는 아니길 바랍니다.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = "찰스, 돌아왔구나! 네 부하가 무슨 소식을 가져왔지? 작별 인사도 안 하고 갔잖아!";
			link.l1 = "죄송합니다, 마르키즈 나리. 드 쉬에부가 또 비열하게 굴었습니다. 그는 제 배를 훔쳐 오늘 밤에 출항했어요. 제 신임 장교 중 한 명이 그 배에 타고 있었는데, 그 악당 손에 그녀를 맡길 수는 없습니다.";
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = "그녀라고? 네 배에 여자 장교가 있다고? 그건 내가 아는 모든 항해 규칙에 어긋나. 그녀가 아직 살아 있다고 생각하는 이유가 뭐지?";
			link.l1 = "바라지. 줄리아나, 지금 내게 남은 건 희망뿐이야. 앙제랑 드 시에부에 대해 더 알아내야 해. 그가 어디로 갔는지 반드시 밝혀내야 해! 반드시 그녀를 데려와야 해!";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = "이제 알겠군! 너 정말 사랑에 빠졌구나, 내 기사여! 그런 충성과 애정이라면 내 목숨의 반쯤은 기꺼이 내어줄 수 있겠어, 망설임도 없이!";
			link.l1 = "나는 어떤 서약도 하지 않았지만, 이 여인은 내게 매우 소중한 사람입니다, 마르키즈 나리.";
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = "이거 질투심이 솟구치게 하는군. 들어봐, Charles, 나도 너 때문에 질투할 준비가 되어 있어! 하지만 진정한 사랑의 목소리를 외면할 창녀가 어디 있겠어? 게다가 네가 날 구해줬잖아, 내 기사님, 당연히 도와줄 거야. 뭐든 물어봐.";
			link.l1 = "감사합니다. 당신은 드 쉬에부와 꽤 오래 알고 지냈지. 그 난리 끝에 아버지의 분노를 피해서 어디로 숨었을까?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = "브런치로 유혹하면 어때? 이... 여자에 대해 이틀이나 생각 안 했잖아, 하루쯤 더 기다릴 수 있지 않을까?";
			link.l1 = "마르키즈 나리, 제 모습이 나리 눈에 어떻게 비칠지 압니다만, 이미 벌어진 일입니다. 비록 맹세를 하진 않았지만, 제 마음은 그녀에게 있습니다. 부디 저를 이해해 주시고 도와주시길 간청합니다.";
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = "어서 와, Charles! 기생 앞에서 사랑 타령으로 변명하다니? 이렇게 웃어본 게 얼마 만인지 모르겠군! 정말 대단하네! 진정해, 이 집에서 일어난 일은 이 집에만 남는 거야. 내가 너한테 진 빚도 기억하고 있어. 뭐든 물어봐.";
			link.l1 = "감사합니다. 당신은 드 시에부스를 꽤 오래 알고 있었지. 그 난리 끝에 그는 아버지의 분노를 피해서 어디로 숨었을까?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = "사실을 말하자면, 앙제랑 드 시에부스를 초대하는 일이 그리 유쾌한 일은 아닐지라도 정치적으로는 매우 유용하지. 그는 어디서든, 심지어 프랑스와 동맹을 맺은 국가들에서도 환영받는 손님이야. 하지만 내가 아는 한, 근처에서 언제나 그에게 손을 내밀고 피신처를 제공해 줄 사람은 단 한 명뿐이네. 바로 우리 과들루프 식민지의 총독 프랑수아 드 리옹이지. 그는 레비 방타뒤르 백작의 오랜 동료이며, 언제나 이 사생아에게 약한 마음을 가져왔지.";
			link.l1 = "과들루프라니! 이보다 더 좋은 단서는 없겠군! 오늘 저녁에 출항하면, 그들보다 하루만 늦게 도착할 수 있어.";
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = "잠깐, Charles, 아직 할 말이 더 있어. 얼마 전에 너한테 온 편지를 받았거든. 처음엔 결투와 관련된 건 줄 알았는데, 이제는 잘 모르겠어. 여기 있어.";
			link.l1 = "봉인은 없지만, 종이가 비싸 보이네. 마음에 안 들어...";
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "어서 말해, Charles! 날 애태우지 말고, 그 사람한테서 온 거야?";
			link.l1 = "그래, 그 사람에게서 온 거야. 그녀는 살아 있어! 내 배를 훔칠 때 그가 그녀를 붙잡았어. 이제 그는 우리가 문명적인 곳에서 만나 얘기를 해보자고 제안했어. 네가 말한 대로야, 과들루프 바스테르.";
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = "드 리옹 나리는 분명히 너보다 르브 방타뒤르의 아들을 선택할 거야. 드 시에부가 또다시 너한테 함정을 놓을지도 몰라! 나를 변호해 줘서, 샤를, 너는 아주 강력한 적을 만들고 말았어. 내가 도와줄 수 있으면 좋겠지만, 그저 조심하라고 말하는 것밖에 할 수 없을 것 같아.";
			link.l1 = "줄리안느, 내가 항상 정공법만 고집했다면 신세계에서 살아남지 못했을 거야. 음흉한 일은 내 전문은 아니지만, 상황에 맞춰 연기하는 법은 알고 있지.";
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = "무슨 소식 있나, 선장?";
			link.l1 = "아아, 아무것도 없군...";
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = "돌아왔구나, Charles! 살아 있고 건강해서 다행이야. 무슨 소식이 있나?";
			link.l1 = "우리가 드 시에부스의 능력에 대해 알던 건 전부 심각하게 과소평가한 거였어. 그 자식이 내... 장교를 붙잡고 몸값을 요구하고 있는데, 내가 몸값을 모을 시간은 겨우 2주일뿐이야. 네 도움이 없으면 불가능할 것 같아.";
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "샤를, 네 사랑은 참으로 바람꽃 같구나. 하지만 나는 네게 큰 빚을 졌으니, 할 수 있는 한 도와주겠다. 무엇을 도와주면 되겠느냐?";
			}
			else
			{
				dialog.text = "찰스, 내가 당신이 나를 위해 해준 일을 절대 잊지 않겠다고 이미 말했잖아. 내가 할 수 있는 한 보답할게. 준비는 됐지만, 이 일에서 내가 어떻게 당신에게 도움이 될 수 있는지는 잘 모르겠어.";
			}
			link.l1 = "앉으시오, 줄리아나. 보시다시피, 앙제랑의 몸값은... 바로 그대요. 내가 말하는 건 공식적인 후원이 아니라, 그의 화물칸에 결박된 포로로서라는 뜻이오.";
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = "할 말을 잃었군... 하지만 네 얼굴을 보니 농담이 아닌 것 같아. 그 자, 제정신을 잃은 거냐?";
			link.l1 = "오히려, 그 자는 내가 그랬다고 믿는 거지. 놈은 제정신이 아닐 만큼 필사적이야, 못할 짓이 없을 정도로.";
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = "그리고 뭐요, 나한테 묻는 거요? 납치당할 때 소리 지르지 말라고? 선장, 그건 너무 심한 부탁 아니오? 내가 당신에게 큰 빚을 졌지만, 내 목숨을 영광도 없는 놈에게 내주면서 남의 사랑을 구하라니... 여기서 기사도적인 건 당신이고, 나는 지극히 현실적이고 계산적인 여자요.";
			link.l1 = "두렵지만, 부인, 바로 그것을 부탁드리는 겁니다. 짐을 싸십시오, 우리는 떠나야 합니다. 정말 유감이지만, 시간이 없습니다.";
			link.l1.go = "Julianna_76";
			link.l2 = "마르키즈, 나를 믿는 여자를 납치하는 짓은 안 해. 그리고 이게 우리에게 기회일지도 몰라.";
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = "넌 정말 예상을 못 하겠구나, Charles. 들었지? 방금 그게 내가 너한테 줄 수 있는 마지막 관용이었는데, 이제 산산조각 났어. 사랑이든 뭐든, 널 내 납치를 허락하지 않을 거야. 경비병들! 도와줘!!! 누구든!!!!";
			link.l1 = "나는 우리가 친구인 줄 알았는데.";
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = "이건 말도 안 돼! 내 응접실을 뭘로 만들어 놓은 거야?! 이건 대체 무슨 악마 같은 끔찍한 짓이냐? 찰스, 정신 차려! 너는 귀족이지, 빌어먹을 해적이 아니야!!";
			link.l1 = "나는 이미 너에게 사과했어. 더 이상 일을 복잡하게 만들지 말라고 했는데, 넌 듣지 않았지. 믿어줘, 나도 내가 하는 일이 마음에 들지 않아. 하지만 어쩔 수 없어. 그 여자를 위해서라면 뭐든 할 거야.";
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = "어떤 숙녀가 너 같은 기사놈을 고르겠냐? 내가 직접 갈 테니, 손 떼! 소 훔치는 것도 아니잖아, 좀 품위 있게 굴어!";
			link.l1 = "좋아. 나랑 같이 가시오, 부인. 내 뒤에 붙어서 고개 숙이고 있으시오 - 어쩌면 저놈들이 총을 쏠지도 모르니까.";
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.greeting = "Marquesa_again";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = "잠깐 동안은 내가 너를 전혀 모르는 사람인 줄 알았어, Charles. 그 표정... 그런데 이제 뭘 하려는 거야? 네가 말한 기회란 게 뭐지?";
			link.l1 = "왜 그 자식이 너한테 가기 위해 나를 이용하는 거지? 왜 자기가 원하는 걸 그냥 가져가지 않고 카드 게임까지 꾸민 거야? 도대체 뭘 두려워하는 거야?";
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = "아무것도 아니야. 안타깝게도, 그 모든 일의 이유는 시시하고 원시적이야. 앙리 백작은 아직도 나에게 미련이 남아 있어. 앙제랑은 내 의지에 반하는 일을 하면 큰 위험을 감수해야 해. 미안해, 샤를, 이건 막다른 길이야. 그는 모든 걸 부인하고 빠져나갈 거야. 아무도 너, 유괴범의 말을 믿지 않을 거고, 그의 아버지는 널 파멸시킬 거야.";
			link.l1 = "젠장! 이렇게까지 되지 않았으면 좋았을 텐데... 준비하시오, 마르키즈, 가야 하오. 그리고, 조용히 해 주길 바라오.";
			link.l1.go = "Julianna_76";
			link.l2 = "하지만 그 자식도 아버지 말고 다른 약점이 있겠지? 완벽한 놈은 아니잖아, 오히려 완벽과는 정반대지!";
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = "이게 우리에게 도움이 될지는 모르겠어. 앙제랑이 현지 해적 남작하고 뭔가 거래가 있었지. 자크 바라반?";
			link.l1 = "바르바종입니다, 부인. 두 분 다 좋은 분들이죠! 하지만 친절한 자크는 저를 좋아하지 않고, 확실한 증거 없이는 르 프랑수아를 공격할 수 없습니다.";
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = "또 너무 직설적이군, 내 기사야. 모레노 선장 기억하지? 네 두 번째 도박 상대 말이야. 내 생각엔 그가 앙제랑 때문에 여기 온 것 같아. 우리에게 가치 있는 뭔가를 알고 있을 게 분명해.";
				link.l1 = "모레노 선장이라, 하! 그래, 물론이지. 아직 이 마을에 있나? 어디서 그를 찾을 수 있지?";
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = "또 너무 직설적이군, 내 기사여. 누군가는 항상 뭔가를 알고 있고, 어떤 상황에서는 모두가 입을 다물 수 있는 건 아니지. 내... 제자들이 이 집에서 이런저런 소문을 듣거든. 하루만 시간을 주면 더 알아보겠네, 아니면 알아낼 만한 사람을 찾아주지.";
				link.l1 = "마르키즈 나리, 걱정하는 모습도 잘 어울린다고 생각했지만, 화내는 모습이 더 잘 어울리는군요. 고맙습니다, 나리 덕분에 희망이 생깁니다!";
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = "그래, 그는 아직 여기 있어. 네가 여기저기 돌아다니며 찾는 수고는 덜어주지. 내일 저녁에 이리로 오게. 모레노 선장이 이 방에서 자네를 기다릴 거야. 더 도와주고 싶지만, 그 이상은 못 하겠네, 찰스.";
			link.l1 = "이미 충분하고도 남습니다, 마르키즈 나리. 저분이 내 편이 되어 준다면 모든 일이 훨씬 수월해질 겁니다. 감사합니다. 내일 저녁에 뵙겠습니다.";
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = "차라리 다른 상황에서 그 말을 들었으면 좋았을 텐데, Charles. 내일 저녁에 나를 찾아오게. 자네에게 필요한 걸 내가 구해놓길 바라네.";
			link.l1 = "다시 한 번 고마워, 줄리아나! 그럼 내일 저녁에 보자.";
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = "여기 있군, 친구! 모레노 선장이 벌써 기다리고 있어.";
				link.l1 = "...";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = "찰스, 뭔가를 찾은 것 같아. 모레노 선장 기억나? 그 불운한 밤에 너랑 내기했던 그 사람 말이야?";
				link.l1 = "그래, 정말 떠돌이군. 그리고 저 녀석은 어때?";
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = "나는 처음부터 알고 있었소, Bartolomeo de la Cueva. 그래서 당신을 내 연회에 초대한 것이오. 마치 저녁 식사에 할라피뇨를 더하는 것과 같았지. 당신과 부하들이 이미 몇 주째 이 섬을 뒤지고 있다는 것도 알고 있소. 이 일이 분명 Le Francois의 해적 남작과 Angerran de Chievous와 관련되어 있다는 것도 말이오. 내 친구에게 모든 것을 털어놓으시오. 그러면 당신의 전설적인 이름은 비밀로 해주겠소. 그렇지 않으면, 이미 문 뒤에 대기 중인 경비병들을 부를 것이오. 당신이 도착하자마자 내가 그들을 불러두었소.";
			link.l1 = "...";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = "그들만이 아니야! 앙제랑이 내게 목걸이를 줬어, 아주 아름다운 거였지! 크고 흠 없는 진주들이었고, 이 가운데 있는 이 진주는 남쪽 밤처럼 어두웠어. 하지만 그건 현지 보석상에게 주문한 거였어!";
			link.l1 = "...";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = "그가 나를 기쁘게 하려고 값비싼 선물을 준 것만은 아닐 거야. 그래도 그 선물은 체면을 지키면서 내 환심을 사기 위한 마지막 수단이었지. 앙제랑은 작위도, 땅도 없고, 그의 프리깃도 아버지가 마음을 바꾸기 전까지만 그의 것이야. 권력과 영향력은 이용하지만, 자기만의 수입원은 없어. 어쩌면 아버지의 시혜를 기다리는 데 지쳐서, 스스로 재정 상태를 바로잡으려 한 걸까?";
			link.l1 = "잠깐만요, 부인! 카드 게임 말입니다! 우리가 맞다면, 그리고 드 쉬에부스가 모든 걸 미리 계획했다면, 총독을 제대로 궁지에 몰아넣으려면 판돈으로 엄청난 돈이 필요했을 겁니다. 부모에게 그런 돈을 달라고 하면 괜히 일이 커질 수도 있죠. 이미 사략선들이 훔친 보물을 다시 훔치는 게 조용하고 안전하게 돈을 마련하는 방법이었겠네요. 아무도 모를 테니까요!";
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = "우리 쪽으로, Charles! 이번에는 Angerran이 그냥 넘어가게 두면 안 돼. 그 자가 나 위에 군림하는 것도 이제 너무 지나쳤어. 네가 그걸 바로잡는 데 내가 힘을 보태고 싶어.";
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = "패배자 해적에다, 거의 반한 창녀라니. 샤를, 너 정말 꿈의 조합을 만들었구나!";
			link.l1 = "그래도 고맙다, 너희 둘 다. 진심이야! 이제 잠깐 생각 좀 하고 계획을 세워야겠어.";
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = "이 집에는 손님들이 원하는 모든 것이 있소. 내가 준비를 하겠소. 준비되면 우리에게 합류하시오, Charles.";
			link.l1 = "알겠습니다, 부인.";
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = "아무것도 아니야, 하지만 마을에 누군가 그를 찾고 있어. 그들은 너와 그날 밤의 다른 손님들에 대해 적극적으로 캐묻고 있지. 아직 무슨 일인지 잘 모르겠지만, 네가 생각하는 것보다 더 큰 일에 휘말린 게 분명해. ";
			link.l1 = "더 큰 일? 무슨 뜻이야, 줄리안느?";
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = "앙제랑... 아니, 드 시에부 나리가 내게 정말 멋진 진주 목걸이를 선물로 주었어. 진주 중 하나는 밤처럼 새까맸지. 그냥 그럴듯한 이야기가 붙은 가짜일 거라고 생각했어. 한 번도 차본 적 없어, 헛된 희망을 주고 싶지 않았으니까. 하지만 정말 넋을 빼앗길 만큼 아름다워.";
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = "어쩔 거야, Charles? 지금 무슨 일이 벌어지고 있는지 알기나 해?";
			link.l1 = "아직은 아니지만, 곧 그럴 거야. 드 쉬에부는 뭔가 심각한 일에 깊이 빠져 있어. 이게 내 기회지. 그의 고향에서는 감히 손도 못 대겠지만, 영국 당국이라면 모를까. 줄리안, 널 납치하고 싶진 않아.";
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = "정말 다정하구나, Charles, 하지만 별로 재미있지는 않아.";
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = "찰스, 뭔가 알아냈나? 불안해 보이는데... 무슨 일이라도 있나?";
			link.l1 = "젠장! 모든 게 달랐으면 좋겠는데... 짐 챙기시오, 마르키즈. 제발 문제 일으키지 마시오.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = "찰스, 들어오게. 바로넷 나리는 이미 와 계시고, 우리는 즐겁게 이야기를 나누고 있었네. 내가 자네가 최근 일들에 관심이 많다고 막 말씀드리던 참이었네.";
			link.l1 = "줄리안느, 그게 현명한 선택이었는지 잘 모르겠어...";
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = "바로넷 나리, 당신 부하들이 방금 문 뒤에 뭔가를 떨어뜨린 것 같습니다! 그들에게 좀 더 예의 바르게 행동하라고 말씀해 주시겠습니까?";
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = "끔찍하군! 이제 어쩌지?!";
			link.l1 = "젠장! 모든 게 달랐으면 좋겠는데... 짐 챙기시오, 마르키즈. 제발 문제 일으키지 마시오.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = "전능하신 하느님! 신사 여러분, 내 거실에 도대체 무슨 짓을 한 거요?! 이건 중세의 악몽처럼 보이잖소! 이 사람들은 또 누구요? 그리고 경비병들은 어디 간 거요?";
			link.l1 = "괜찮아, 줄리안느? 좋아. 경비병들은 힘들게 받은 뇌물을 선술집에서 쓰고 있겠지. 바로나, 축하해야겠군 - 그대 덕분에 굿맨 잭이 몹시 화가 났소. 이렇게 엉망이고 준비도 안 된 암살 시도는 전혀 그의 방식이 아니오.";
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = "흥미진진한 대화를 방해해서 미안하오만, 다친 사람이 없다면 이제 방으로 옮기는 게 어떻겠소? 이런 광경은 숙녀에게 그리 유쾌하지 않으니... 천장만이 피로 물들지 않았군!";
			link.l1 = "그럼 위층으로 가시지요, Marquise 나리. 잠시 누워서 이 피비린내에서 벗어나셔야 합니다. Baronet Cortney 나리와 저는 이 문제를 상의하겠습니다. 계속해도 되겠습니까?";
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = "Charles, 이제 우리에게 네 계획을 말해줄 준비가 됐나?";
			link.l1 = "거의 다 됐어. 말해 봐, 드 시비우스는 꼼꼼한 성격이냐? 장부나 항해일지를 제대로 정리해 두는 놈이야?";
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = "앙제랑은 재정 문제에 있어서 미루기의 화신이지! 내가 아는 어떤 은행가보다도 서류에 더 많이 서명하더군. 어릴 때부터 그랬던 것 같아. 아버지가 누군지도 모르고 거리에서 가난하게 살았으니까.";
			link.l1 = "훌륭해! 이제 그의 항해일지와 장부가 필요해! 그게 영국 놈들에게 확실한 증거가 될 거야. 어떻게 구할 수 있을지 알아봐야 해! 내가 그 자의 배를 손에 넣었을 때 이걸 알았더라면 좋았을 텐데... 하, 한숨만 나오네.";
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = "잠깐, Charles, 지금까지 이런 일들이 다 있었는데 내가 de Chievous한테 염소처럼 팔려가게 내버려 둘 거라고 정말 생각해?";
			link.l1 = "걱정 마, Julianne, 며칠이면 끝날 거야. 네가 중국에서 온 값비싼 도자기처럼 대접받게 해주겠다고 약속할게. 내가 틀렸다면 말해줘, 하지만 de Chievous는 절대 교환 장소에 직접 나타나지 않지?";
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = "확실히 그렇소. 앙제랑은 프랑수아 드 리옹의 보호 아래에서 기다릴 것이며, 결코 공해에서 당신을 맞설 용기를 내지 못할 거요. 하지만 내 포획에 관해서는...";
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "찰스, 방해해서 미안하지만, 이 모든 일에 대해 내 의견을 묻는 걸 잊은 거 아니오? 몇 주나 그 삐걱거리는 관 속에 갇혀 있으라니... 내가 뭘 요구받는지 당신은 정말 알고 있소?! 분명히 그... 여자애에게 마음이 가 있는 건 알겠지만, 나는 당신 선원 중 한 명이 아니오! 미안하지만, 이 모든 게 진지한 사랑 이야기처럼 들리진 않소.";
				link.l1 = "두렵지만, 마르키즈 나리, 제가 고집을 부릴 수밖에 없겠소. 그녀를 잃을 여유가 없으니.";
				link.l1.go = "Julianna_127";
				link.l2 = "우린 모두 실수하지, 줄리아나. 너야말로 그걸 잘 알잖아. 나 좀 도와줘.";
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = "찰스, 방해해서 미안하지만, 이 모든 일에 대해 내 의견은 묻지 않은 거 아니야? 몇 주나 그 삐걱거리는 관 속에 갇혀 있으라니... 네가 나한테 뭘 요구하는지 정말 알고는 있어?! 네 감정은 기사도에 관한 고전 문학에나 어울릴 법하지만, 나는 그냥 평범한 창녀일 뿐이야. 널 존경하고 도와주고 싶지만, 모든 일엔 한계가 있어!";
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = "알겠어, Charles. 나도 완벽하고 진정한 사랑을 믿고 싶지만, 이 세상엔 그런 건 없는 것 같아.";
				link.l1 = "감사합니다, 마르키즈. 이번에는 반드시 모든 것을 바로잡겠습니다. 이번 일을 통해 많은 것을 배웠고, 제가 저지른 일에 대해 너무 혹독한 대가를 치르지 않기를 기도합니다.";
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = "결정은 네가 내렸고, 나는 줄곧 너를 지지했지. 하지만 이제 그만해야겠어. 이미 내 침실에서 버린 사랑을 위해 모든 걸 희생한다니. 이 모든 게 참 감동적이긴 해, Charles. 하지만 나는 그렇게 어리고 순진하지 않아.";
				link.l1 = "두렵지만, 마르키즈 나리, 꼭 말씀드려야겠습니다. 그녀를 잃을 여유가 없습니다.";
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = "좋소, 선장님, 원하는 대로 하시오. 나는 저항하지 않겠소, 하지만 이것이 내 의지와는 다름을 알아두시오.";
			link.l1 = "나를 어떻게 생각하든 상관없어, 줄리아나. 그럴 만한 짓을 했으니. 하지만 무슨 대가를 치르더라도 반드시 그녀를 되찾을 거야\n줄리아나, 들어줘. 내가 너에게 무엇을 요구하는지 알아. 모든 걸 버리고 남들에게 끌려가 위험한 도박에 뛰어들라는 거니까. 하지만 지금 이 순간, 내겐 네가 유일한 희망이야! 네 도움이 필요해, 그리고 평생 네 빚을 지고 살겠어!";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = "좋소, 선장. 결국 앙제란은 반드시 끝장내야 하오. 내가 도와주겠소, 하지만 한 가지 묻겠소, 그의 배에서 나를 어떻게 구출할 생각이오?";
			link.l1 = "...";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = "잠깐. 내 진주 목걸이를 가져가. 영국 놈들이 흑진주를 찾고 있잖아? 이걸 보여주면 네 말을 들어줄 거야. 그 다음엔 뭐 할 거지?";
			link.l1 = "다음으로, 내가 조사관을 배에 태우고 과들루프로 항해할 것이오.\n당신이 타고 돌아오면 드 쉬에부스의 프리깃함을 공식적으로 수색할 거요.\n머큐리 사건은 우리 동맹이 연루된 중대한 일이었으니, 드 리옹도 허락할 수밖에 없을 것이오!";
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "그자는 모두에게 자기 부하들이 나를 포로 생활에서 구해냈다고 말할 거요. 그리고 명심하시오, 선장. 내가 그들에게 무슨 말을 할지는 아직 정하지 않았소.";
				link.l1 = "아무 말도 하지 않아도 괜찮소, 마르키즈. 내 말 믿으시오, 내가 반드시 당신을 끌어내서 앙제랑에게 모든 값을 치르게 할 것이오.";
			}
			else
			{
				dialog.text = "나는 낯선 자들에게 집에서 바로 납치되어 앙제란의 배에 태워졌다고 말할 거야.\n그가 용병들에게 돈을 주고 나를 납치하게 한 것처럼 보이겠지.";
				link.l1 = "앙제란의 관에 또 하나의 못이 박혔군요, 후작부인.";
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "아침까지 시간 좀 줘. 아니면 자루에 날 담아 가야 할 텐데. 그리고 나 좀 도와줄 사람 둘쯤 보내 줘. 이런 신분 있는 여자가 아무런 편의도 없이 다닐 순 없잖아. 찰스, 네가 날 구했으니 나도 널 도울게. 그리고 이 귀중한 흑진주도 받아 줘, 내 선물이야. 이게 잘 풀리면 우리 빚은 끝난 거다.";
				link.l1 = "말씀대로 하겠습니다, 마르키즈 나리. 두 분 모두 행운을 빕니다! 일이 끝나면 여기서 다시 뵙지요.";
			}
			else
			{
				dialog.text = "해 뜨기 전이면 준비 끝낼 거야. 나는 화물칸에서 덜컹거리며 갈 생각 없으니, 제대로 된 방이든 뭐든 준비해 둬. 찰스, 이거 받아. 이건 귀한 흑진주야. 이게 이곳보다 더 값나간다는 건 알지만, 세상엔 금으로 값을 매길 수 없는 것도 있지. 네게 도움이 되길 바란다. 신의 가호가 있기를!";
				link.l1 = "행운을 빈다, 너희 둘 다! 끝나면 여기서 다시 보자.";
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			GiveItem2Character(pchar, "blackpearl"); // черная жемчужина 
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "축하합니다, 선장님. 계획이 성공했군요. 정말 엄청난 소동을 일으키셨습니다! 영국 놈들이 앙제랑과 그의 배, 그리고 모든 화물을 가져갔지만, 저만은 예외였지요.";
				link.l1 = "윌리엄 나리는 작별 인사조차 하러 오지 않았어. 사과하겠다고 약속했었는데.";
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = "찰스, 우리가 해냈어! 이제 곧 널 풀어줄 거야! 하지만 최대한 빨리 이 섬을 떠나야 해. 총독이 앙제란의 최근 체포 때문에 몹시 화가 났거든.";
				link.l1 = "널 다시 보게 되어 기쁘구나, 줄리안느. 잘 지냈니? 교환은 어떻게 됐어? 그녀는 괜찮아?";
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "그 사람도 너무 바빠서 그랬겠지. 지금 우리 총독처럼 말이야. 그가 네 존재를 기억해내기 전에 이 도시를 떠나는 게 좋을 거다.\n그는 앙리의 아들을 정말 아꼈지만, 영국 신문들이 완전히 그를 몰아세웠지.\n그가 너에게 모든 분풀이를 쏟기로 결심할 때까지 기다릴 필요는 없을 거야.";
			link.l1 = "그럴 만도 하지. 게다가 그녀가 마르티니크에서 나를 기다리고 있어. 교환은 어떻게 됐지? 그녀는 무사한가?";
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = "미안하지만, 그 이야기는 하고 싶지 않아. 대신 그녀에게 물어봐. 안녕히 계시오, 선장. 나는 혼자 돌아가겠소. 바다에서 좀 쉬어야겠어 – 프랑수아는 지루한 영국 관리들에게 방해받지 않을 때 꽤 좋은 주인이거든.";
			link.l1 = "이 모든 일에 진심으로 유감입니다, 마담. 어쨌든 협조해 주셔서 감사합니다. 새로운... 친구를 사귀셨다니 기쁘군요.";
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = "너도 고맙다, Charles, 약속을 지켜줘서. St. Pierre에 있는 내 집에서 Bartholomew를 찾아라.\n안녕히 가라. 우리는 다시 만날 것이다.";
			link.l1 = "잘 가요, 줄리안느. 신의 가호가 있기를.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "나는 그녀를 보지 못했지만, 바르톨로뮤가 그녀를 멀쩡히 생포해 갔어. 그 영국인은 드 시에부스를 체포하고 그의 재산까지 이 지방 총독 코앞에서 빼앗아 갔지 - 총독은 한마디도 못 했어! 기적이야!";
			link.l1 = "알다시피, 이번 체포의 배경을 생각하면 놀랄 만큼 순조롭게 진행됐어. 그래도 나중에 분명히 문제가 터질 거야. 뭐 어때! 지금 당장 마르티니크로 가야 해, 최대한 빨리 그녀를 만나야 하니까!";
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = "분명 너희 둘은 할 말이 많겠지. 아, 샤를, 저렇게 눈에 불꽃이 살아 있는 남자가 내 곁에 있었으면 좋겠어. 어서 가자, 뜨거운 목욕이랑 깨끗한 시트가 정말 그리워. 바르톨로메오는 생피에르에 있는 내 집에서 우리를 기다리고 있을 거야.";
			link.l1 = "그래, 바다 여행의 낭만이란 게 과장된 거지. 내 선실을 드리겠소, 마르키즈 나리. 이 정도는 해 드려야지. 어서 오시오.";
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = "넌 이미 내가 바랄 수 있는 모든 걸 해줬어, Charles. 냉소적이던 내가 다시 믿게 됐지.";
			link.l1 = "나도 그래, 줄리안느. 나도 그래.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, 와줘서 정말 기쁘네! 그대의 그 숙녀분은 어찌 지내나? 별일 없으신가?";
				link.l1 = "모든 게 잘 됐어, 네 덕분이야, 줄리안느. 다시 한 번 말하고 싶었어. 너는 정말 대단한 여자야, 그리고 네 용기와 기지에 나는 평생 빚을 지게 될 거야.";
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = "찰스, 와줘서 정말 기쁘구나! 그대의 그 숙녀분은 어찌 지내는가? 별일 없으신가?";
				link.l1 = "모든 게 잘 됐어, 네 덕분이야, 줄리안느. 다시 한번 말하고 싶었어. 넌 정말 대단한 여자야, 네 용기와 기지에 나는 평생 빚진 셈이야.";
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = "어쩌면 내가 오히려 신세를 진 것일지도 모르겠군. 결국 당신이 나를 아주 성가신 손님 둘에게서 구해줬으니 말이야. 아직도 당신에게 빚을 진 것 같아. 뭐든 말해봐, Charles.";
			link.l1 = "그렇다면, 부인, 작은 부탁이 하나 있소. 우리 사이를 공평하게 만들 수 있는 일이 있소.";
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = "듣고 있소, 선장. 무슨 일이오?";
			link.l1 = "사람은 실수를 하지만, 그렇다고 세상이 나빠지는 건 아니야. 그걸 기억하고 행복하게 살아, 줄리안느. 너는 행복할 자격이 있어.";
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = "나... 나도 노력해 볼게, Charles. 고마워. 가끔씩... 친구로서 나를 찾아와 줄 수 있겠어? 언제든 내 집에 환영이야!";
			link.l1 = "고맙소, 마르키즈. 안녕히 가시오, 그리고 내게 한 약속 잊지 마시오.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = "아직 그리 대단하진 않았던 모양이군... 그래도 당신이 잘 끝냈다니 기쁘네. 나한테 빚진 건 없어; 당신이 해준 일에 비하면 내가 아무리 고마워해도 부족하지! 육지에 올 때마다 언제든 찾아오게. 내 집은 항상 친구인 당신을 환영하네!";
			link.l1 = "감사합니다, 후작 나리. 모든 일이 잘 되길 바랍니다. 안녕히 계십시오!";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = "찰스, 친구, 넌 정말 무례하군 – 이렇게 드물게 찾아오다니! 네가 그리웠어, 알지? 와인 한잔 할래? 네가 직접 들려주는 신나는 이야기 듣고 싶어서 죽겠다고! 그리고 네 그 유명한 행운도 한번 시험해보고 싶고!";
			link.l1 = "마르키즈님, 그냥 인사드리고 괜찮으신지 확인하고 싶었습니다.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак Дьель дю Парке
		case "governor":
			dialog.text = "거기 있었군, 친구! 다시 보게 되어 반갑다!";
			link.l1 = "...";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = "네가 내 친구를 대하는 걸 보니, 선택의 여지가 없군, 나리. 네 도전을 받아들이지. 시간과 장소는?";
			link.l1 = "여기서, 지금 당장이다. 하인들을 불러서 촛불을 가져오라고 해라. 이런 아늑한 땅거미로는 안 된다. 이곳이 대낮처럼 밝아야 하니!";
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = "친구야, 제발, 너무 감정적으로 받아들이지 마. 앙게란이 정말 고약한 놈인 건 맞지만, 네가 그에게 시비 걸 필요는 없어. 이 일은 나한테 맡겨.";
			link.l1 = "정말이십니까, 각하? 저 친구는 일주일 동안 육지에 있었던 내 사관처럼 취했지만, 칼 다루는 솜씨는 확실합니다. 그런 건 한눈에 알 수 있지요.";
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = "맙소사, Charles! 나는 그와 결투하지 않을 거야. 우리는 도박을 할 거고, 카드가 문명인의 무기지. 내가 그 자를 완전히 털어서 너한테 보내 줄게, 퀘벡으로 무사히 돌아가려고 돈 좀 빌려 달라고 애원하게 말이야.";
			link.l1 = "그거라면 확실한 계획이지. 하지만 내 생각엔, 그 자식이 가난해지는 것보다 죽는 게 더 낫겠어. 행운을 빕니다, 각하!";
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			sld.greeting = "Marquesa_needhelp";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = "젠장, 앙제랑, 거기에 10이 나올 리가 없잖아! 절대 아니야!";
			link.l1 = "그게 비난이었나? 그건 당신 거래였소, 나리.";
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = "그렇지 않아. 그냥... 내가 좀 흥분했을 뿐이야, 미안하다. 사고였고, 재경기를 요구하겠어! 이 배, 나는... 반드시 되찾아야 해! 아니면 게임이고 뭐고 다 집어치우고, 그냥 얼마에 팔 생각인지 말해 줘! 값을 말하면 내일 정오 전에 꼭 지불하겠어!";
			link.l1 = "안타깝지만, 내 온 마음을 다해 말하건대 도박에서 잃은 전리품은 돈으로 되찾을 수 없다고 믿네. 오직 다시 이겨야만 되찾을 수 있지. 이제 그 플루트는 내 것이고, 팔 생각은 없어. 자네의 열정이 이런 처지로 몰아넣은 건 유감이네. 때로는 우리 능력을 좀 더 현실적으로 봐야 하네... 혹시 배 서류가 더 있나?";
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = "너는 쓰레기야, 앙제란. 그리고 지금 나를 궁지에 몰아넣었지. 하지만 네가 받아들일 만한 제안을 할 수 있을 것 같군.";
			link.l1 = "...";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = "찰스, 너만이 내 유일한 희망이야, 제발 도와줘! 그 플루트랑 그녀의... 화물은 이미 네덜란드 회사에 팔렸어. 내일 그들에게 모든 서류를 넘겨줘야 해. 밤새 여기 머물 생각으로 서류도 다 가져왔지. 만약 거래가 틀어지면 나는 정말 끔찍한 상황에 처하게 될 거야!";
			link.l1 = "하지만 '스위트 자크', 자네가 마음에 두었던 그 여인이 지금 훨씬 더 끔찍한 상황에 처해 있다는 데 동의하지 않나? 나도 도박 좀 해봤으니 배를 걸고 내기하는 심정은 이해하지, 그게 자기 배가 아니더라도 말이야. 하지만 여자를 두고 도박을 하다니?! 정말 놀랐군! 그런데 이제 자네는 거래의 결과만 신경 쓰는 건가?";
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = "나를 판단하지 마, Charles. 권력 있는 백작의 옛 연인을 감싸주고 잠시 사랑에 빠졌던 건, Peter Stuyvesant에게 백만 페소를 빚진 것에 비하면 아무것도 아니야. 그 사람의 대리인에게 이걸 어떻게 설명하란 말이지? 내 평판이 얼마나 망가질지 상상이나 해 봐!";
			link.l1 = "나도 예전에 비슷한 빚이 있었지만, 정말 아무것도 없었어도 잘 버텼지. 너도 그럴 거야. 또 보자, 자크. 약속은 못 하고, 플루트에 넣어둘 만큼 가치 있는 화물이 뭔지는 묻지도 않을 거야.";
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = "여기 있었군, Charles. 내가 곧 너를 부르려던 참이었어. De Chievous가 결투를 고집하고 있고, 이미 화해의 기회도 거부했어. 카드에서는 잘했지만, 계속 이렇게 할 생각이 확실한가?";
			link.l1 = "이상하게도 계속 의심이 드는군요, 각하. 애초에 이 결과를 원하셨던 것 아닙니까? 그러니 내 대답은 예요. 이번에야말로 확실히 끝을 봐야겠소. 결투의 조건은 어떻게 됩니까?";
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = "너무 네 생각에만 빠져 있군, 친구. 우리 세상에는 아직도 네 중심으로 돌아가지 않는 부분이 많아. 믿어, 어젯밤 일이 이렇게 된 건 나도 정말 실망스러워. 아주 깊이 말이야. 하지만 먼저, 네... 횡재의 운명부터 논의해 보자.";
			link.l1 = "좋아. 네 피리를 어떻게 되찾는지 알고 싶은 거야, 아니면 줄리안느 부인이 어떻게 지내는지 궁금한 거야?";
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = "네가 그 부적절한 빈정거림 대신 악의로 바꿨군? Charles, 우리 같은 편이야, 잊지 마.";
			link.l1 = "논쟁의 여지가 있는 주장입니다, 각하. 아주 점잖게 말해서 그렇지요. 이제 어디서부터 시작할까요: 배부터 할까요, 아니면 그 숙녀부터 할까요?";
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = "물론 스튜이베선트 건 말이오 – 그의 대리인이 아침 내내 나를 기다리고 있는데, 더 이상 둘러댈 핑계도 없소. 플루트 선박 서류가 필요하네, Charles.";
			link.l1 = "좋아. 그녀는 네 거다. 드 시에부가 정정당당하게 게임을 했다고는 믿지 않으니, 네 재산을 절반 값에 돌려주겠다. 15만이다.";
			link.l1.go = "governor_18";
			link.l2 = "기꺼이 도와주지. 배 값이 얼마라고 했지? 50만? 그 정도면 괜찮아.";
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "이제 세금 포함해서 46만 페소가 되겠군. 거래지. 13만 5천.";
			link.l1 = "이봐... 더 이상 말싸움하기도 지친다. 그러니까 돈 내고, 서류 챙겨서 끝내자고.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = "넌 옛 친구한테도 동정심이 없구나, 그렇지 Charles? 이제, 모든 세금까지 포함해서...";
			link.l1 = "카드빚과 우정은 아무 상관이 없소, 각하. 세금은 구매자인 당신이 직접 내야 하오, 아니면 내가 그 배를 르 프랑수아에서 팔겠소. 명심하시오, 아직은 당신의 지위를 이용하지 않고 있소...";
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = "좋아, 그렇게 하지. 이제 결투다. 나는 드 레비 반타뒤르 백작과 문제를 일으키고 싶지 않으니, 모든 것이 최대한 합법적으로 진행되어야 한다. 들었나, 샤를? 법대로 해야 한다! 내 주둔지에서 장교 두 명을 보내 너를 동행하게 하겠다. 둘 다 귀족 출신의 존경받는 사람들이니, 네 평소... 동료들 대신 세컨드 역할을 할 것이다. 일이 마무리될 때까지 모든 게 투명하게 진행되길 바란다!";
			link.l1 = "참 친절하군. 그런데 우리 좋은 친구가 비열하게 나온다면 어쩔 건데? 나는 그런 상황에서 뭘 해야 하는지 아는 친구들, 그리고 내가 친구라 부를 수 있는 사람들에게 내 등을 맡기는 게 더 낫다고 생각해. 태어나길 좋은 집안에서 태어난 사람들보다는 말이지.";
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = "샤를, 이 결투가 너와 나 사이의 일인 것처럼 굴지 마라. 이건 심각한 일이야. 드 시에비우스는 죽이고 그냥 넘어갈 수 있는 그런 사람이 아니야. 어떤 결과가 나오든 조사, 어쩌면 재판까지도 이어질 거다. 우리가 신뢰할 수 있는 증인들도 필요해. 봐라, 나는 네 편을 들어주고 있는 거야! 하지만 가장 중요한 건, 절대 그를 죽이면 안 된다는 거다. 알겠지만, 앙제랑은 결의에 차 있고 아마도 꽤 실력 있는 검객일 거야. 그래도 샤를, 절대 그를 죽이면 안 돼! 상처를 입히거나 망신을 줘도 되지만, 거기서 멈춰야 해. 그를 죽이면 반드시 결과가 따를 거고, 우리 둘 다 피하거나 살아남을 수 없을 거다. 드 레비 방타뒤르 백작이 사생아를 공식적으로 인정하지는 않았지만, 다른 아들은 없어. 그의 분노는 끝이 없을 거다.";
			link.l1 = "훌륭하군, 그럼 내가 분노한 백작이 너를 총독 자리에서 쫓아내지 못하게 하려고 대신 죽으란 말이냐?";
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = "네가 말을 듣지 않으면 우리도 앙제랑 드 시에부보다 오래 살지 못할까 두렵다. 그 점을 명심하고 조심해라. 결투는 오늘 밤 열 시, 마을 성문 밖에서 열릴 거다. 내 장교들이 거기서 널 기다릴 거야. 이제 마지막으로, 줄리안느 보토 부인은 어찌 되었나?";
			link.l1 = "내가 이미 내 전리품을 이용해 봤냐고 묻는 건가? 아니오, 각하, 아직도 아니고 앞으로도 아닐지 몰라요. 그건 중요하지 않소. 중요한 건 당신이 이제 영영 후작부인의 집에서 쫓겨났다는 거요. 그녀는 그 점을 아주 분명히 했소. 내가 그녀를 탓할 수는 없지. 줄리안느는 다음 후원자를 스스로 고를 거요.";
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = "정말 놀라게 하는군, Charles. 아무튼, 나는 회사 대리인과 지루한 회의에 참석해야 해. 너도 가서 준비하고, 내가 경고한 거 잊지 마라.";
			link.l1 = "반드시 노력하겠습니다, 각하. 하지만 싸움이니 장담은 못 하겠습니다. 도와주셔서 감사합니다.";
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = "살아 있었군, Charles! 다행이야, 어떻게 된 거야? 이건 피야?! de Chievous는 살아남았어?";
			link.l1 = "유감스럽게도, 맞아. 그 자는 다치긴 했지만, 심각하진 않아. 도망칠 수밖에 없었고, 자기 부하들을 우리에게 풀었지. 한마디로, 이 피 중 일부는 내 것이 아니야.";
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = "이 자식아! 그리고 내 부하들은? 그놈들도 살아서 무슨 일이 있었는지 증언할 수 있나?";
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = "모두 무사합니다, 각하. 좀 두들겨 맞긴 했지만, 살아남을 겁니다.";
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = "전부는 아닙니다, 각하. 한 신사는 살아남지 못했습니다 - 드 시에부가 일부러 머스킷총병들을 데려왔거든요. 제가 어쩔 수가 없었습니다.";
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = "거긴 완전 지옥이었소, 각하. 용감한 신사 두 분 다 전투에서 쓰러졌습니다. 그분들이 아니었으면 저도 큰일 날 뻔했지요. 드 시에부스가 제대로 피비린내 나는 매복을 꾸몄습니다.";
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = "훌륭하군! 믿을 만한 증인들 앞에서 그들의 서면 진술을 받아내겠다. 드 쉬에부 놈, 반드시 대가를 치르게 해주지!";
			link.l1 = "그 자의 이름에 조금이라도 흠집을 낼 수 있을 것 같지 않아. 네가 아무리 경고해도, 차라리 내가 직접 찾아가서 끝장을 내겠어. 저런 겁쟁이는 살 자격도 없어.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = "끔찍하군. 하지만 최소한 한 명의 증인에게서라도 서면 증언을 받아낼 거야. 드 시에부스, 반드시 대가를 치르게 하겠다!";
			link.l1 = "그의 이름에 조금이라도 흠집을 낼 수 있을 것 같지 않아. 네가 뭐라 경고해도, 차라리 내가 직접 찾아가서 끝을 내겠어. 그런 겁쟁이는 살아 있을 자격도 없어.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = "젠장할 놈! 그들은 좋은 사람들이었어, Charles! 맹세컨대, 그 자식 반드시 대가를 치르게 할 거야!";
			link.l1 = "그 자의 이름에 조금이라도 흠집을 낼 수 있을 것 같지 않아. 네가 아무리 경고해도, 차라리 내가 직접 찾아가서 끝장을 내겠어. 그런 겁쟁이는 살 자격도 없어.";
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = "신경 쓰지 마, Charles. 그 자식이 알아서 다 망쳐 놨어. 내 생각엔 지금쯤 어디 가난한 식민지에서 땅바닥에 숨어 도망 다니고 있을 거야. 이제 너한테 위협이 될 가능성은 거의 없어. 이번 악행은 도망치는 뱀이 물고 간 정도지. 너도 다친 것 같은데, 의원이 필요하냐?";
			link.l1 = "염려해 주셔서 감사합니다, 각하. 하지만 저는 괜찮습니다.";
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = "알아두면 좋지. 이제 숨 좀 돌려도 돼, 이 이야기는 끝났으니까. 편하게 쉬고 네 일로 돌아가. 그런데 말이야... 아까 네가 최근에 딴 돈 얘기를 다 못 끝냈잖아. 그걸 어떻게 할지 결정했어?";
			link.l1 = "잘 이해가 안 가는군, 자크. 무슨 말이지? 혹시 마르키즈를 말하는 건가? 젠장! 보토 부인! 드 시에부스가 도망쳤어, 이제 더 이상 내게 위협은 아니지만, 절박하니 무슨 짓이든 할 수 있어! 내가 가야겠어! 경비병들을 마르키즈 저택으로 보내! 지금 당장!";
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			if (pchar.questTemp.Sharlie == "escape")
			{
				dialog.text = "유명한 선장 말인가? 이 작은 마을을 불태울 뻔했던 스페인 공격을 막아낸 그 사람? 알겠소. 뭘로 한잔하시겠소?";
			}
			else
			{
				dialog.text = "유명한 선장이라고? 난 들어본 적 없는데... 뭘 마실래?";
			}
			link.l1 = "...";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = "피노 누아르, 우리 아름다운 여주인과 같은 걸로? 이 바닷바람에 소금기를 잔뜩 머금고도 정말 맛을 느낄 수 있다고 확신하나? 보통 그대 같은 부류는 낡은 장화를 녹일 만한 술을 더 좋아하던데.";
			link.l1 = "이게 같이 문을 지나가자는 제안이라면, 나도 동의하지. 나도 너를 좋아하지 않고, 그 감정이 서로 같아서 다행이군. 말은 그만하자. 너는 말솜씨도 별로니까. 조건과 무기는 네가 정해라.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = "흙이랑 고양이 오줌 냄새가 나는 부케라니? 참 매력적이군! 이런 시큼한 쓰레기는 어차피 와인이 될 일도 없으니 통에 숙성조차 안 시키지. 그런데 말이야, 바닷소금이 원래 이렇게 맛을 박살내나?";
			link.l1 = "이게 같이 문을 지나가자는 제안이라면, 나도 찬성이야. 나도 너 마음에 안 들고, 서로 기분이 똑같아서 다행이군. 말은 그만하자; 너 말솜씨도 별로잖아. 조건이랑 무기는 네가 정해.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = "하, 참 용감한 녀석이군! 이제 흥분 좀 가라앉히고 거리 좀 두도록 해라. 여기는 선술집이 아니고, 나는 네 술친구가 아니다. 너 따위는 내 신분에 한참 못 미치지; 원래라면 말도 섞지 않을 텐데, 그 아가씨가 부탁해서 이렇게 얘기하는 거다. 자, 자크와 나는 아직 끝내지 못한 일이 있다...";
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = "줄리안느, 괜찮아? 이 멍청이들아, 물 가져와! 물 가져오라고!";
			link.l1 = "...";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = "네 말이 맞아, 여긴 정말 후덥지근하군. 지금까지 아주 재미있는 게임이었지만, 결말 전에 잠깐 쉬자고. 잘 가, 자크. 우리 시합의 조건 기억하지?\n그리고 여기 샤를 드 모르가 있군, 맞지? 와인 취향이 형편없는 선장, 기억나. 걱정 마, 내가 끝내고 나면 넌 물만 마시게 될 거야. 그러니 천천히 해, 이 순간을 즐기고, 한 잔 해. 준비되면 이 작은 방으로 와. 오늘 밤은 좀 더 편안한 곳에서 마무리하지...";
			link.l1 = "기대하고 있소, 나리.";
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = "드디어 왔군. 돈 내놓을 준비됐어?";
			link.l1 = "차라리 네 것도 거기에 추가하고 싶어. 제발!";
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = "잘 말했소, 하지만 안타깝게도 우리 총독 나리께서 그 치욕스러운 패배 직전에 규칙을 바꾸자고 고집하셨지. 이제 우리는 돈 말고도 뭔가 더 내걸어야 하오. 양쪽 모두가 내기에 동의해야 하니까. 내가 내거는 것은 은장식 플루트요.";
			link.l1 = "이봐, 이건 시시하잖아 – 내가 약탈 몇 주만 하면 저런 건 금으로 다섯 개는 쉽게 구하지. 좀 더 큰 거 내놔.";
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "그래, 네 배를 봤지. 인정해야겠군, 정말 장관이더라. 그럼 판을 키워보자고. 두 척 대 한 척, 내 프리깃과 플루트, 그리고 은화로 네 배에 맞서겠어?";
				link.l1 = "훌륭한 승부였어! 보토 부인이 틀렸군 – 이 결투는 전설로 남을 거야. 거래지!";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = "이것 좀 봐, 우리 선장이 아주 말썽꾸러기잖아! 하지만 사략질은 신성하지. 그럼 전열함은 어때? 프리깃, 48문포. 웬만한 코르벳보다 빠르지 – 왕실 조선소에서 만든 작품이고, 세계 최고의 조선공들이 더 개선했어. 실은 이 배가 싣고 있는 컬버린포는 사거리도 길고 명중률도 뛰어나지. 어때, 한 번 해볼래?";
					link.l1 = "훨씬 낫군, 나도 끼겠다! 가자!";
				}
				else
				{
					dialog.text = "여기 정박했다는 소문 들었소, 선장. 내가 당신 그 낡은 배를 내기로 받아주기로 한 걸 감사하게 생각하시오. 자, 거절할 게 아니라면 오시오?";
					link.l1 = "좋아, 네 말이 맞아. 가자.";
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = "끝났군, 선장. 원하는 걸 얻었으니 실컷 자랑해도 되겠지. 내일 정오에 내 프리깃함 매입 조건을 논의하는 게 어떻겠소?";
					link.l1 = "그게 다야? 나도 자네처럼 도박에서 잃은 건 다시 살 수 있는 게 아니라 이겨서 되찾아야 한다고 진심으로 믿지. 아니면 그 배를 마을 어부들에게 목재로 팔고, 자네의 후한 기부 이야기를 실컷 해줄 수도 있겠군.";
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = "이제 운명의 여신이 말씀하셨군. 정말 기이한 결과로군. 축하하오, 드 모르 선장. 내일 정오에 내 프리깃함 매입 조건을 논의하는 것이 어떻겠소?";
						link.l1 = "그렇게 빨리? 다른 손님들에게 실망을 안겨주고 있군, 나리. 내가 기억하기로는, 당신에겐 아직 배가 한 척 더 있지. 나 역시 당신처럼, 도박에서 잃은 것은 돈으로 되찾을 수 없고, 오직 다시 이겨야만 한다고 진심으로 믿소.";
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = "그러면 운명의 여신이 말씀하셨군. 정말 기묘하게 끝났어. 축하하오, 드 모르 선장. 이제 제대로 한잔할 자격이 있소, 산지오베제를 마셔보시오. 자크가 이 배에 대해선 값을 후하게 쳐줄 거라 생각하오; 그 친구가 이 배에 품은 감정이 다른 어떤 것보다도 깊은 듯하니. 그 정도면 좋은 와인 한 병은 충분히 살 수 있을 거요.";
						link.l1 = "벌써 항복하겠다는 건가? 다른 손님들에게 실망을 주고 있군, 나리. 내가 기억하기로는 아직 배 한 척이 더 남아 있지 않나. 자네가 내 배를 너무 초라하다고 했으니, 나는 자네의 프리깃을 내 은장 플루트와 맞바꾸겠네.";
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = "운이 없었군, 선장. 그래도 네 용기는 인정하지. 오늘은 기분이 좋으니 금은 내가 가져가겠지만, 배는 네가 가져가도 된다. 내 눈앞에서 꺼져라. 그리고 앞으로는 도박 따위 하지 마라. 언젠가 그게 네 목숨을 앗아갈 테니.";
				link.l1 = "참 고결하시군요, 그렇게 나올 줄은 몰랐소. 안녕히 가시오, de Chievous 나리.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = "승리감에 도취하는 것과 패배한 상대를 조롱하는 것은 분명히 다르오, 드 모르 나리.";
			link.l1 = "벌써 패배했다고 생각하는 건가? 그런데 시작은 그렇게 좋았는데... 아! 보토 부인, 당신의 살롱에 말과 행동의 차이에 대한 멋진 이야기가 하나 더 추가된 것 같군!";
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = "또 뭘 더 원해? 이제 더 꺼낼 배도 없고, 배 한 척 살 돈도 없어. 두블룬 걸고 도박하는 건 진지한 일이 아니야, 오늘 밤 우리가 겪은 걸 생각하면 더더욱 그렇지.";
			link.l1 = "우리 귀여운 자크 딜 드 파르케보다 눈치가 없다는 거냐? 내가 너에게 사랑이 모두 돈으로 살 수 있는 게 아니라는 걸 증명할 최고의 기회를 주는 거다. 행운도 자신의 호의를 팔지 않아. 은빛 배와 네 프리깃함, 그리고 네가 금보다 더 소중히 여기는 그 무언가를 걸고 승부하자.";
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = "선장, 이건 웃기지도 않아요. 빨리 끝내죠 – 곧 새벽이 오니까요. 내 프리깃함 매입에 대해서는 내일 얘기합시다.";
			link.l1 = "좋아, 가져가. 세 척의 배야! 그중에는 진짜 군함도 있지, 신세계에서 가장... 뭐랄까, 값비싼 숙녀를 상대로 말이야. 이런 판돈을 거절할 수나 있겠어?";
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = "그건 미친 짓이오. 아니, 사실 미친 짓이지, 드 모르 나리. 제발. 하지만 기억하시오, 이건 당신 생각이었소.";
			link.l1 = "이건 앞으로 1년 동안 문 닫고 두고두고 곱씹을 전설이 될 거야! 이봐, 거기! 와인하고 촛불 더 가져와! 놀이는 계속돼야 하니까!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = "방금 전까지만 해도 이 플루트를 우리 배들과 맞바꿀 가치도 없다고 했잖아. 뭐가 달라진 거지?";
			link.l1 = "지겨워졌군. 결투에 좀 더 재미를 붙여보자고 - 네 프리깃과 내 배로 맞붙는 거야...";
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = "네가 그토록 하찮게 여겼던 플루트 말이야? 혹시 열이라도 있는 거 아니야? 얼굴이 안 좋아 보여.";
			link.l1 = "나는 아주 멀쩡하네, 고맙군. 너는 내 말을 듣지 않았지. 둘 대 하나의 확률이 그리 대단한 건 아니지, 맞아, 그러니 균형을 맞춰보자고! 모든 귀중한 것이 금으로만 측정되는 건 아니지, 동의하지 않나? 아니면 네 계획대로 되지 않으면 바람과 싸우지 않고 그냥 항로를 바꿔버리는 걸 더 좋아하는 건가? 그렇다면 유감이군, 내가 너를 잘못 봤던 것 같아. 보토 부인, 당신의 살롱에 말과 행동의 차이에 대한 또 하나의 흥미로운 이야기가 추가된 것 같군...";
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = "내 속을 떠보려 들지 마시오, 드 모르 나리. 그럴 만큼 순진하구려.";
			link.l1 = "그렇지. 의지가 부족한 건 죄가 아니야... 물론 군인이라면 얘기가 다르지. 아니면 귀족이라든가 — 집안의 명예라는 게, 알다시피, 때론 무거운 짐이거든. 뭐, 너는 그런 고민하고는 거리가 멀 것 같지만 말이야.";
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = "결투를 시작하려는 거야, 아니면 게임을 계속하려는 거야?";
			link.l1 = "둘 다 괜찮아. 자네가 정신 차릴 동안 나는 후작 부인의 와인 컬렉션에 공을 돌릴 생각이야.";
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = "그러면 되겠군. 오늘 밤은 제대로 끝나야지. 두 척의 거대한 배가 은과 누벨프랑스 최고의 여인이 가득 실린 낡은 배를 상대하는 거다! 숨을 깊이 들이쉬시오, 드 모르 나리, 이 내기는 상류층의 소문거리로 전설이 될 테니.";
			link.l1 = "당신의 패배는 전설이 될 거요, 드 시에부 나리. 와인과 촛불을 더 가져와라! 자, 해보자고!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = "운에 정신이 팔렸군, de Maure 나리. 여기서 위험을 감수하고 있소; 행운은 오래가지 않으니.";
			link.l1 = "짧은 호의는 진정한 사랑으로 가는 길이지. 돈으로 산 충성도 역시 마찬가지야; 결국 경멸이나 지루함만 남기거든.";
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = "네가 내 속을 긁으려는 시도, 꽤 재미있군. 그런 호의나 사랑, 그리고 돈으로 살 수 있는 것과 없는 것에 대해선 줄리아나 부인에게 물어보는 게 좋을 거야. 하지만 서둘러라 – 그분은 내일 이 마을을 떠나니까.";
			link.l1 = "적어도 자네의 지식은 한쪽으로 치우쳐 있군. 여기서 이기거나 돈을 내도 행운의 여신의 총애를 얻을 수 없어, 그러니 그녀의 사랑을 알 수 없지. 위험을 감수하려면 용기와 흔들림 없는 의지가 필요하네, 나리. 게다가... 이 세상 여인들도 이런 걸 높이 산다는 걸 말할 필요도 없지. 내 배 두 척을 자네 한 척과 맞붙이겠네, 할 텐가?";
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = "그렇게까지 열심히 계속하고 싶어? 좋아, 맘대로 해. 하지만 적어도 좀 더 극적으로 가보자고, 드 모르 나리. 아까 사랑이니 값어치니 뭐라 했던가? 내 제안이 있네. 네 그 낡은 배와 은 피리, 그리고 내 프리깃함과 누벨프랑스 최고의 여인을 걸고 내기하자고. 이제 어찌하겠나?";
			link.l1 = "정말 멋지게 도박하는 법을 아시는군요, 나리! 와인과 촛불을 더 가져와라! 가자!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "믿을 수가 없군요, de Maure 나리, 이건 정말 믿기지 않습니다!";
				link.l1 = "그래요, 정말로, 유럽은 로크루아 전투 이후 이런 패배를 겪은 적이 없었지요, 드 시에부 나리. 제 안의 예술가가 이런 역사적인 순간을 담고 싶어 몸이 떨립니다. 젊었을 때처럼 더는 그림을 그리지 못하는 게 아쉽군요. 하지만 줄리안느 부인 곁에는 분명 재능 있는 화가가 있겠지요, 맞습니까?";
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = "운이 없었군, 선장. 그래도 네 용기는 인정하지. 오늘은 기분이 좋으니, 네 금은 받겠지만 배는 가져가라. 내 눈앞에서 꺼져, 그리고 앞으로는 도박은 삼가라. 언젠가 그게 네 목숨을 앗아갈 테니.";
				link.l1 = "참 고결하군, 그럴 줄은 몰랐소. 안녕히 가시오, de Chievous 나리.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = "아니, 너는 이해를 못 하는구나. 이건 너무 말도 안 돼서 도저히 믿을 수가 없어!";
			link.l1 = "우리 모두 카드를 봤소, 드 시에부 나리 - 운명은 결코 거짓말하지 않지.";
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = "행운은 그렇지 않지만, 당신은 달라요, 드 모르 나리. 내 생각엔 당신의 뻔뻔함 뒤에는 단순한 열정이 아니라 계획이 있었던 것 같군요. 당신은 거짓말쟁이에 사기꾼이에요 - 나는 모든 손님들 앞에서 이것을 증명할 준비가 되어 있습니다.";
			link.l1 = "...";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = "드 시에부 나리, 내가 제대로 들은 게 맞소? 그대의 의심을 말뿐만 아니라 행동으로도 증명할 준비가 되었소? 그대의 모욕이 도를 넘은 것 같군, 그리고 나는 그대와 달리 우리 가문의 명예를 소중히 여기오.";
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = "둘째 아들, 사기꾼 주제에 감히 내게 가문의 명예를 논하려 들지 마라! 조용히 해, 줄리안느, 너는 나중에 상대해 주마! 샤를 드 모르, 지금 당장 결투로 내게 만족을 줘야겠어! 검이냐, 권총이냐?";
			link.l1 = "둘 다지. 솔직히 말해서, 네가 마음을 바꿔서 기쁘다. 내가 성문 근처를 산책하자고 제안했던 거 기억나? 내 보잘것없는 신분에 대해 뭐라고 했더라? 결국 카드놀이가 너한테 용기를 좀 준 모양이군?";
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			sld.greeting = "Marquesa_vecherkonchen";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = "과분한 영광이지만, 나는 후작부인과 같은 의견이오. 너는 그럴 자격도 없지만, 드 모르, 나는 귀족답게 너를 끝장내주겠소. 내일 정오에 각하 총독을 통해 결투를 신청하오. 직접 총독을 찾아오거나, 아니면 대리인을 보내 조건을 논의하게 하시오. 그때까지 기다리겠소. 부인께 경의를 표하오.";
			link.l1 = "...";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = "거기 있었군, 행운아. 네 물건은 잘 챙겼겠지? 고해성사는 잊지 않았겠지? 고해 없이 지옥에 가면 꽤나 불편하다고들 하더군.";
			link.l1 = "말은 쉽지, 나리. 카드도 제대로 못 하니, 이번엔 검술 실력을 시험해 보자고... 붙어보자!";
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = "좋았어... 한 방 먹였군, 젠장할 놈. 하지만 난 아직 살아 있어!";
			link.l1 = "상처가 심해 보여. 그래도 의사한테는 꼭 가 봐야 해. 이대로는 더 못 버틸 거야; 계속 이러면 죽게 될 거라고. 이제 우리 일은 끝난 것 같군. 내가 이겼고, 속임수는 쓰지 않았어. 네 배는 돌려주마, 그리고 넌 생피에르를 떠나야 해. 우리 둘은 다시는 만날 일 없을 거다.";
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = "이런 엄청난 기사도라니! 봐, 드 모르 나리, 자네는 타고난 검객일지는 몰라도 카드에서는 분명히 속임수를 썼어. 내가 덱을 세 번이나 건드렸다고. 세 번이나, 젠장! 세상 어떤 기적도 자네를 구할 수 없었을 텐데, 그런데도 자네가 이겼잖아! 도대체 어떻게 한 건지 알고 싶군... 뭐, 곧 악마한테 다 털어놓게 될 거야. 쳐라, 녀석들!";
			link.l1 = "이 자식아! 내가 자비를 베풀었더니 이렇게 보답하는 거냐?! 나리들, 무기를 들어라!";
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			LAi_RemoveCheckMinHP(npchar); 
            LAi_SetCurHPMax(npchar);
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = "인정하오, 드 모르 나리, 여기서 당신을 보게 되어 좀 놀랐소. 그 말은 내가 당신을 오해한 게 아니었고, 그 거친 아가씨가 당신에게 뭔가 의미가 있다는 뜻이오?";
			link.l1 = "네 좋은 친구인 드 리옹 나리가 우리 해군의 존경받는 선장들에게서 장교를 납치하는 일에 대해 어떻게 생각하는지 궁금하군?\n아마 그를 불러서 우리와 함께하게 하고, 모든 이야기를 들려줘야 하지 않을까?";
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = "그건 아무 소용도 없을 거야, 믿어라. 그리고 네 여자는 포로가 된 장군보다도 잘 대해줬지. 지금까지는 말이야. 하지만 모든 건 달라질 수 있고, 그건 전적으로 네 손에 달렸어, Charles.";
			link.l1 = "우리가 너랑 연인주를 나눈 기억은 없는데. 나한테 ‘샤를’이라고 부르지 마, 드 쉬부 나리. 용건만 말하고 나한테 원하는 게 뭔지 바로 말해.";
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = "너한테서? 아니, 절대 아니지! 우리 둘은 그저 불미스러운 카드 게임 뒤에 불행하게 싸웠다가, 술 몇 잔 나누고 이 방을 옛 친구처럼 떠났을 뿐이야.";
			link.l1 = "앙제랑, 최근에 다쳤다더니 멀쩡해 보이네. 이런 쓸데없는 잡담을 할수록 네 상처를 다시 내주고 싶어지는군. 프랑수아 드 리옹의 이 고급 양탄자를 피로 더럽히는 상상조차 점점 더 끌리기 시작하는걸.";
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = "하지만 우리 프랑수아 영감은 이 양탄자를 정말 좋아하지, 샤를. 누구나 뭔가를 좋아하는 법이지. 네가 여기 온 걸 보니, 네 무기 든 작은 애인을 사랑하는 게 분명하군. 내 재산과 맞바꾸는 조건으로 그 애를 돌려줄 준비가 되어 있다. 네가 판을 망쳐놨고, 나는 보통 이런 일은 용서하지 않지만, 너만은 예외로 해주지. 내가 그토록 원하는 보상을 내게 주면, 나도 네게 같은 걸 주겠다. 그러고 나서 우리는 깔끔하게 갈라서는 거지. 사랑이란 게 다 그런 거야.";
			link.l1 = "내가 후작부인을 지갑에 보석처럼 들고 다닌다고 생각하나? 말도 안 돼! 내가 어떻게 그녀를 당신에게 넘길 수 있겠어?!";
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "나는 전혀 신경 안 써, Charles. 이 일을 처리할 시간은 2주일이야.\n그리고 그래, 이 상품은 조용히 받아야 해.\n예를 들어, 터무니없이 비싼 창녀를 땄지만 결국 그녀의 환심을 사지 못한 어떤 선장이, 그 일로 바보 같은 짓을 할 수도 있겠지, 안 그래?\n벌써 절박해진 것 같아, Charles?";
			link.l1 = "먼저 내 부하를 만나서 아직 살아 있는지 확인하고 싶어.";
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = "말도 안 돼. 내 말을 믿는 수밖에 없어. 그녀는 안전한 곳에 있고, 내가 내 보상을 받을 때까지 거기 있을 거야. 하지만 계속 그녀를 미리 보겠다고 우긴다면, 기꺼이 그녀의 일부를 보내주지. 뭘 받고 싶나? 귀, 코, 아니면 손가락 두 개쯤?\n";
			link.l1 = "그 여자한테 손대면, 이 쓰레기야, 내가 맨손으로 목 졸라 죽여버릴 거다, 맹세코! 감히 나를 시험하지 마라!";
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = "진정해라. 이제 곧 일어날 모든 일은 전적으로 네가 자초한 거다. 나는 폭력을 좋아하지 않아. 꼭 필요할 때만 쓴다. 나를 자극하지 마라. 내 상금을 도미니카의 케이프 스콧 헤드에서 2주 이내에 넘겨주면 네 것도 돌려받게 될 거다. 어떻게 하든 상관없어. 훔치고 싶으면 훔쳐라, 어차피 너도 해적이잖아, 다만 옷차림만 좀 번듯할 뿐이지.";
			link.l1 = "너 완전히 미쳤구나, 해적이랑 빌어먹을 노예상은 완전히 다르거든...";
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = "숨 크게 쉬어, 이제 곧 프랑수아 영감 앞에서 멋지게 등장할 거니까. 이제 우리 친구잖아, 기억하지? 웃어, 샤를, 어서! 이제 헤어지자. 케이프 스콧 헤드, 도미니카, 2주 후다. 늦지 마.";
			link.l1 = "거기서 보자.";
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			PlaySound("VOICE\English\LE\Cortny\Cortny_01.wav");
			dialog.text = "좋은 저녁입니다, Botot 부인, de Maure 선장. 침착해 주시기 바랍니다.";
			link.l1 = "마르키즈, 내 뒤로 와요, 지금! 나리, 이게 무슨 짓입니까?!";
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "문 뒤에 내 부하 열두 명이 대기 중이고, 당신 국가에서 승인받은 비상 권한도 있다네. 경비병들은 자네를 도와주지 않을 걸세. 그러니 검을 거두시오, 나리. 나는 그저 대화만 하고 싶을 뿐이오. 지금은.";
			link.l1 = "나리, 누구시며 어떻게 여기 오셨소?! 설명을 하셔야겠소!";
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = "자기소개를 하겠습니다 - 윌리엄 코트니 나리, 코트니 준남작입니다. 이제 모두 진정하고 이야기합시다.";
			link.l1 = "좋소, Cortney 나리, 우리 모두 귀 기울이고 있소.";
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = "엿듣게 된 것을 용서해 주시오. 하지만 지금 상황에서는 어쩔 수가 없었소. 나는 이 생피에르에서 익명으로 지내고 있지만, 영국 왕실을 대신해 매우 중요한 조사를 진행 중이오. 바다에서 실종된 사절선에 관한 일이오. 혹시 '레지나'라는 브리건틴에 대해 들어본 적 있소? ";
			link.l1 = "나는 못 들었고, 그 수상쩍은 암시도 이해 못 하겠소, 나리. 나는 정직한 선장이오...";
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = "네 수상쩍은 장사 따위엔 눈곱만큼도 관심 없어, 나리. 너에 대해 좀 캐봤는데, 솔직히 말해서 레지나가 사라진 직후 마르티니크에 들렀다는 얘길 듣고 널 제일 먼저 의심했지. 하지만 넌 바보가 아니고, 네 부하들도 여기서 진주를 가지고 장난치지 않았어. 그러니 지금은 내 의심 대상에서 제외다.";
			link.l1 = "진주? 무슨 진주 얘기를 하는 거야?";
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = "스페인 서인도에서 직접 선별한 대형 진주들이야. 게다가 이 진주들은 검은색이라서, 정말 희귀하지. 이런 걸 들어본 적 있나?";
			link.l1 = "그런가 보군, 하지만 난 늘 그저 또 하나의 뱃사람들 헛소문인 줄 알았어. 플라잉 더치맨 이야기도 마찬가지고. 줄리안느, 왜 그래?";
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = "여기서 그걸 제시해 주셔야겠소, 부인. 이는 매우 중대한 문제요. 그동안 당신은, 나리, 모레노 선장에 대해 모두 말해 주시오. 그가 당신에게 그 정보를 준 것이라 의심하고 있소. 이 일에서 그의 역할이 무엇인지 매우 궁금하오.";
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = "모레노는 진짜 이름이 아니오, 코트니 나리. 그의 본명은 에르난도 바스케스, 일명 피의 돈이라 불리는 자로, 한때 악명 높은 포르투갈인 바르톨로메오의 배 알바트로스의 선임 사관이었던 스페인 해적이오.";
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = "우리는 몇 마디만 나눴어. 내가 말할 건 별로 없어. 그는 진짜 바다늑대처럼 보였지.";
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = "이런, 이런. 그런데 그걸 어떻게 알았는지 물어봐도 되겠소?";
			link.l1 = "나는 그 선장의 얼굴을 알았지. 사실, 내가 그를 붙잡아서 네덜란드 놈들에게 넘겼어. 이야기가 길지. 그때 바스케스 본인을 잡지 못한 게 한스럽군...";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = "당신도 바다늑대잖소, 나리. 더 많은 걸 못 봤다는 말은 믿기 어렵군.";
			link.l1 = "약간의 억양, 그리고 그가 보이고 행동하는 방식. 내 생각엔 스페인 사람일 거요, Cortney 나리.";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = "그건 상황을 뒤집는군, 나리. 그리고 좋지 않아. 부인, 목걸이 찾으셨소? 내가 좀 살펴보겠소\n그래, 확실히 이건 스페인산 흑진주 중 하나요. 봐요, 이 뱃사람의 이야기가 거의 사실이란 말이오. 이제 남은 건 저 드 쉬에부가 이걸 어떻게 손에 넣었는지 알아내는 것뿐이오. 그런데, 저자는 드 레비 반타뒤르 공작의 사생아 아니오?";
			link.l1 = "맞아, 그 자가 틀림없어. 우리가 아는 한, 그는 르 프랑수아의 현지 해적 두목과 거래가 있었지. 아마 그에게서 이 진주를 샀을지도 몰라?";
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = "그럴지도 모르지. 하지만 이 일에 스페인 냄새가 나는 건 영 마음에 들지 않아. 어쨌든 협조해 줘서 고맙네. 유감이지만 내일도 같은 시간에 다시 찾아와야겠어. 드 모르 선장도 함께 있어 주었으면 하네. 아마 자네에게 더 물어볼 게 있을지도 모르니까. 이제 르 프랑수아로 가봐야겠군.";
			link.l1 = "코트니 나리, 잠깐만요. 혹시 저도 함께할 수 있을까요? 자크 바르바종은 다정하고 온화해서 그런 별명을 얻은 게 아니니, 저도 이 일에 관심이 있습니다.";
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = "선장님, 걱정해 주셔서 감동이지만, 대답은 아니오. 이것은 국사의 문제요. 그 악당도 자기 처지를 알고 있으니, 감히 왕실 사절에게 손을 대지는 못할 것이오. 그렇지 않으면 그 비참한 마을은 사라질 테니까! 다시 한 번 폐를 끼쳐 죄송하오, 부인. 좋은 저녁 되십시오.";
			link.l1 = "내일 저녁에 봅시다, 남작 나리.";
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "그녀에게 화내지 마시오, 선장님. 나는 꽤 설득력이 있거든. 당신의 이야기는 정말 인상적이오. 내가 당신을 쓸 일이 있을지도 모르겠군.";
			link.l1 = "기분이 좋아 보이네. 르 프랑수아에서는 어땠어?";
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = "내 예상대로, 네 그 남작은 어린 양처럼 순하더군. 내가 알고 싶은 건 전부 말했지. 말했듯이, 나는 아주 설득력 있는 사람이거든.";
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = "오늘은 나 혼자 여기 왔다, 저 문 뒤엔 내 부하도 없어. 뭐야, 이게 대체?!";
			link.l1 = "왠지 불길한 예감이 드는군. 줄리안느, 내 뒤로 와, 지금! 바로넷, 왕실의 사절들은 말만큼 싸움도 잘하나?";
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "칼 다루는 솜씨가 대단하십니다, 선장님! \n음, 솔직히 말해서 쉽지 않았어요. 도대체 저놈들은 누구였죠?!";
			link.l1 = "저놈들 친구한테 물어봐야겠어 - 발소리가 더 들리거든. 경비병이면 좋겠는데...";
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = "말도 안 돼! 그 자식이 이런 짓을 감히 했다고 생각해?! 반드시 대가를 치르게 할 거야, 맹세한다!";
			link.l1 = "숨 좀 쉬어. 바르바존은 어떤 혐의도 교묘하게 빠져나갈 놈이야. 분명 그냥 좀도둑들이 부잣집을 털었다고 둘러댈 거다. 게다가, 저놈은 악질 해적이잖아, 관헌 따위 신경이나 쓰겠어! 그래도 이제 확실히 알겠군, 자네가 정말 값진 정보를 알아냈다는 걸. 그 지식을 나와 나눠주길 부탁하네.";
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = "내가 정말 거절할 수 있겠어? 안 그러면 다음 시도는 성공할지도 모르지? 좋아, 네 말투에서 위협의 기운이 느껴졌다는 건 못 본 척해주지. 은혜를 갚는 셈 치자. 자크 더 카인드는 네 그 고귀한 사생아에게 진주를 판 게 아니야. 오히려 사들이고 있었지. 그게 다야.";
			link.l1 = "그래서 레지나를 가로챈 게 드 시에부스였단 말인가? 그 자는 악당이지만, 평범한 해적으로 전락할 인물이라고는 믿기 어렵군.";
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = "레지나는 전형적인 해적의 전리품이라고 부르기 어렵겠소, 선장님. 우리는 최소한 검은 진주가 여섯 개쯤 있었으리라 추정하오. 검은 진주 한 알만 있어도 값으로 매길 수 없지. 나는 반드시 그 드 시에부 나리를 어떻게든 만나야 하오.";
			link.l1 = "여기서 내가 좀 도와줄 수 있소, 나리. 하지만 먼저 한 가지 분명히 해두겠소. 나는 보토 부인의 목걸이에는 별 관심이 없었으니, 진주가 자네가 여기 온 이유는 아니겠지. 그럼 레지나호에는 또 무엇이 실려 있었나?";
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = "좋아, 상황이 이러니 더 얘기해줘야겠군. 사실 화물 자체보다 배가 더 중요해. 쿠리어 브리건틴 레지나는 산호세, 트리니다드 항에 배정되어 있었지. 그녀의 선장은 우리를 위해 정보를 모으고, 이런저런... 심부름도 했어.\n그가 마지막으로 맡은 일은 우리 일당이 스페인 진주 작업장에서 빼낸 전리품을 운반하는 거였지. 그 정보를 얻으려고 우리가 3년이나 공들였어. 흑진주는 물론 중요하지만, 레지나를 잃은 건 재앙이야. 그건 사고가 아니었어. 그녀가 진주를 실었다는 걸 아는 자라면, 나머지 일도 알고 있었던 게 분명해.";
			link.l1 = "훌륭하군, 결국 정보국 일이라는 거지! 네가 쌓아 올린 첩보망 전체가 위험에 처할까 봐 두려운 거냐? 이제야 네 고민이 얼마나 큰지 알겠군.";
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = "존 설로에에 대해 들어본 적 있나? 그는 왕실 정보국의 수장이야. 언젠가 나는 런던에 가서 레지나의 운명에 대해 그에게 직접 보고할 거다. 어디서 정보가 새는지 찾아내서... 그 근원을 처리해야 해. 게다가 네가 말한 그 수수께끼의 모레노 선장도 있지. 만약 스페인 놈들이 우리 식민지 첩보망을 추적한다면, 수년간 힘들게 쌓아온 노력이 물거품이 될 거다!\n";
			link.l1 = "있잖아, 전체적으로 보면 이제야 모든 게 이해가 되기 시작해. 스페인 억양을 가진 누군가가 드 시에부스에게 레지나와 흑진주에 대해 말한 것 같다는 생각이 들어.";
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = "우린 생각이 같군. 드러난 첩보망을 이용하는 데 이보다 더 좋은 방법은 없어. 그렇게 높은 지위의 인물이 연루된 외교적 사건이라니... 그런 사건은 영국과 프랑스의 관계에 심각한 타격을 줄 수 있지. 필요한 건 적절한 정보를 흘리고 국제적 스캔들을 기다리는 것뿐이야. 어쩌면 흑진주에 관한 단서도 일부러 우리에게 넘긴 걸지도 몰라.";
			link.l1 = "그 빌어먹을 카스티야 놈들 말이지? 그럼 드 쉬비우스는 어떻게 할까?";
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = "솔직히 말해서, 나도 전혀 모르겠네. 만약 이게 스페인 쪽의 도발이라면 그냥 무시하는 게 현명할 거야. 하지만 그자가 어떻게 레지나에 대해 알게 됐는지, 그리고 우리 조직이 스페인 식민지에서 얼마나 위험해졌는지는 반드시 알아내야 해. 그리고 나는 자네에게 목숨을 빚졌으니, 반드시 그 은혜를 갚을 생각이네.";
			link.l1 = "솔직하게 말하자면, 바로넷 나리. 나는 받을 수 있는 어떤 도움이라도 필요하오. 이제는 마르키즈를 납치하는 것까지도 고려할 만큼 절박하오.";
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = "네가 지금 이게 드 시에부가 자기 흔적을 감추는 방식이라는 걸 알고 있겠지? 이 모든 난장판, 그리고 레지나의 실종까지 전부 네 탓으로 돌리기 정말 쉬울 거야. 그래서 내 제안을 하겠다. 보토 마르키즈가 말하길, 드 시에부는 교환에 참석하지 않고 바스테르에 안전하게 머무를 거라고 했어. 그가 자신이 얼마나 큰 문제에 휘말렸는지 깨달았거나, 뭔가를 의심하기 시작한 걸지도 몰라. 그는 부엌 쥐처럼 조심할 거야. 그래서 내가 너와 함께 도미니카에 가겠다는 거다.";
			link.l1 = "하지만 그의 포로가 내 우선이야, 그녀의 목숨을 걸 수는 없어! 그녀는 교환을 기다리는 인질이거든!";
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = "걱정 마시오 - 내가 자크 딜 드 파르퀘를 압박해서 드 시에부스의 선박에 대한 체포 영장을 받아내겠소. 그의 부하들이 자신들이 처한 상황을 완전히 알고 있다고는 생각하지 않소, 그렇지 않았다면 진주를 그렇게 함부로 다루지 않았을 것이오. 우리가 직접 장선(롱보트)을 타고 가서 영장을 내밀겠소.";
			link.l1 = "그래, 네 협박 솜씨는 기억하지, 나리. 하지만 그건 위험한 짓이야. 그리고 아주 큰 위험이지.";
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = "네 말이 맞아. 하지만 내 도움이 필요하다면 받아들여야 해. 우리가 도미니카에서 일을 끝내면, 나는 바세테르로 가서 드 리옹 총독에게 네 적을 넘기라고 요구할 거야. 내 권한으로 그럴 수 있지. 드 시에부가 몰래 빠져나가게 둘 순 없어.";
			link.l1 = "정말 할 생각이오, 나리? 이러다 전쟁이 날 수도 있잖소?";
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = "절대 그렇게 두지 않을 걸 장담하지. 우리가 이미 진실을 알고 있으니, 그건 절대 불가능해. 정치란 창녀 같은 거야, 선장. 당신을 위해서라도 드 시에부스를 영국의 감옥에 넣어주겠다고 약속하지. 그 정도면 그의 아버지도 합리적인 대가라고 생각할 만한 조용한 해결책일 거야.";
			link.l1 = "네 계획이 마음에 들진 않지만, 다른 방법이 없어 보여.";
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = "우리가 해낼 거라고 장담하오. 이제 나는 총독을 뵙고 부하들에게 명령을 내려야 하오. 혹시 후작부인을 만나거든, 조사에 협조해 준 감사의 표시로 진주는 그대로 가지셔도 된다고 전해 주시오.";
			link.l1 = "감사합니다, 남작님. 제 배에서 뵙지요, 곧 출항할 겁니다.";
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "윌리엄 코트니, 코트니 남작, 당신을 위해 봉사하오. 대영제국이 내게 부여한 권한과, 신뢰받는 동맹국 프랑스의 전폭적인 지원 아래, 당신의 선박은 지금부터 억류됨을 알리오. 여기 문서가 있소. 반드시 읽고, 부하들에게 무기에 손대지 말라고 전하시오. 당신은 구금된 것이지, 아직 체포된 것은 아니오. 어리석은 짓만 하지 않는다면, 첫 번째 항구에서 풀려날 것이오.";
			link.l1 = "바로넷 나리, 내... 내 장교를 반드시 찾아야 하오!";
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "걱정 마십시오, 선장님. 제가 그녀를 당신 배까지 데려다주겠습니다. 이제 장선으로 돌아가 주시길 바랍니다. 이 배는 제가 지휘해서 바스테르로 향할 것입니다. 당신이 숙적을 직접 조롱할 생각이 없다면, 편히 떠나셔도 됩니다. 다만 과달루프로 가는 데 도움이 될 수 있도록 부하 몇 명만 저에게 넘겨주시길 부탁드립니다.";
			link.l1 = "알겠소, 나리. 나는 사양하겠소. 그에게 내 최악의 인사를 전해 주시오. 그럼 이만, 다시 한 번 감사하오!";
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "찰스, 다시 만나서 기쁘네. 자네가 돌아오길 바랐지만, 사실 정말로 그럴 거라고는 믿지 않았지.";
			link.l1 = "저도 반갑소, 준남작 나리. 후작부인께 인사드리러 오셨소? 그런데 그분은 어디 계신가?";
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = "아직도 이해 못 했나? 그녀는 도망쳤어. 그리고 앙제랑 드 시에부가 너에게 진심으로 사과를 전하라고 했어. 내가 그에게 네가 처음부터 이 일에 끼어든 게 아니라, 그저 또 다른 희생자일 뿐이라고 설득했거든. 그도 마찬가지로 말이야. 그 착한 양반이 직접 편지를 쓰진 않았지만, 일이 이렇게 된 걸 정말 안타까워하고 있어.";
			link.l1 = "정말 미안하다고?! 무슨 소리야, 나리?";
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = "너랑 나, 우리 둘 다 가장 중요한 걸 간과했어. 그자가 어떻게 진주에 대해 알게 된 거지? 누가 그 스페인 선장을 바로 이 집으로 불렀지? 누가 그 자식에게 그런 보물을 쫓으라고 부추겼을까?";
			link.l1 = "진심이야? 그럴 리가...";
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = "그럼, 확실히 그럴 수 있지. 마르키즈는 자기 역할을 완벽하게 해냈고, 거의 전부 성공시킬 뻔했어. 하지만 우리 조사의 덕분에, 나는 도둑이나 해적이 아니라 속임수의 희생자인 드 쉬부에게 접근할 수 있었지. 그는 그녀가 자신을 어떤 일에 끌어들였는지 꽤 빨리 알아챘지만, 증거가 없어서 혼자 행동하기로 결심했어. 그 다음에 무슨 일이 있었는지는 너도 알잖아.";
			link.l1 = "그 모든 게 마르키즈가 꾸민 일이었다는 거야? 드 쉬에부스는 아무 생각 없는 아이처럼 그대로 속아 넘어갔군!";
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = "정확히 그래. 열정이란 아주 위험한 거야, Charles! 이 집에서 네가 도박하던 그 밤을 기억하지? Angerran은 후원을 얻어서 마르키즈에게서 필요한 증거를 빼내려고 했지. 그래, 그는 속임수를 썼지만, 수년간의 헛된 열정이 가장 참혹한 배신으로 끝난 뒤라 절박했거든! 그런데 네가 나서서 스스로 그녀의 옹호자라 칭했고, 그 역할을 제대로 해냈지. De Chievous는 너와 그녀가 한마음이라고 생각했어. 그는 네가 그 선박의 항해일지를 손에 넣지 못하게 하려고, 네게 빼앗겼던 배를 훔쳤지. 그리고 네 장교를 이용해, 네가 그의 치명적인 적들이라고 믿었던 그녀와 너를 서로 싸우게 만들려고 했어.";
			link.l1 = "할 말을 잃었군!";
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = "이제 알겠지, Charles! 후작부인은 영리하고 숨이 멎을 만큼 아름다우며, 그만큼 위험하기도 해. 그녀가 얼마나 오랫동안 누벨프랑스의 최고의 인물들을 조종해 왔는지 나도 몰라. 아마 수년은 되었을 거야. 어쨌든, 이제 너와는 상관없는 일이야. 다시 만나서 반가웠지만, 나는 아직 뒤집어야 할 방이 더 많아. 이 집은 크거든. 아마 아무것도 못 찾을 테지만, 적어도 시도는 해봐야지.\n헤어지기 전에 한 가지 더. 자, 이걸 가져. 추억으로 간직해. 준비가 되면 네 연인에게 주는 것도 좋겠지. 너 정말 운이 좋은 놈이야, 알지? 특히 그 불쌍한 de Chievous와 비교하면 말이야!";
			link.l1 = "맞소, 그렇소. 안녕히 가시오, 그리고 당신의 탐색에 신의 가호가 있기를, 남작 나리!";
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "오늘 정말 좋은 날이군, 그렇지 선장? 자네의 무용담은 들었지만, 설마 평범한 해적일 줄은 몰랐지. 그런 무례함이라니 – 자네가 저지른 짓을 하고도 세인트 존스에 오다니!";
			link.l1 = "나는 해적일지도 모르지, 그건 맞아, 나리. 하지만 내가 바보처럼 보이나? 대체 왜 내가 머큐리를 털고 스페인 진주까지 빼앗은 뒤에 여기로 오겠나?";
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = "인정하지, 네가 지금 이렇게 대화하고 있는 유일한 이유가 바로 그것 때문이야. 아니었으면 이미 교수대에 매달렸을 거다. 자, 이 사건에서 우리가 숨긴 아주 작은 세부사항이 하나 있지. 네 몸에서 발견한 진주 얘기는 아니야. 바로 그 브리건틴의 이름이지.";
			link.l1 = "무슨 뜻이야?";
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "사환 브리건틴 레지나는 지난 2년간 산호세 항구에 배정되어 있었소. 그 배의 선장은 우리를 위해 정보를 모으고, 온갖 심부름도 했지. 우리는 공식적으로는 그녀가 운반하던 외교 문서 분실을 구실로 그 배를 수색하고 있소. 변명치고는 그리 그럴듯하지 않다는 건 인정하오. 그래도, 선장의 선실을 제대로 뒤지지 않고서는 그 배의 진짜 이름을 알아낼 수 없었을 것이오.";
			link.l1 = "나는 눈이 멀었지만 이제는 볼 수 있어. 내 말 좀 들어주시오, 나리, 설명하겠소!";
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = "더 열심히 해 보시오, 선장. 자네 목숨이 달려 있잖아.";
			link.l1 = "나는 이 첩자 사건과 아무런 관련이 없어! 스페인 놈들도 마찬가지고. 네 조직은 안전하니 걱정하지 마라.\n하지만 네 쪽에서 정보가 새어나갔고, 누군가 그걸 이용했지. 그리고 나서 내가 그 자와 언쟁에 휘말렸어. 내가 그가 머큐리 사업에 연루된 증거를 찾아냈고, 그걸로 그를 이기려고 했지.";
			link.l1.go = "Cortny_48_1";
		break;
		
		case "Cortny_48_1":
			dialog.text = "";
			link.l1 = "신이 내 증인이시다, 나는 이 사건을 평범한 해적질로만 생각했지, 왕실 정보국이 관련되어 있을 거라고는 상상도 못했어! 내게 남은 건 이 진주 하나뿐이지만, 네가 더 많은 진주를 언제 어디서 찾을 수 있는지는 아주 잘 알고 있지.";
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = "존 설로우에 대해 들어본 적 있나? 그는 왕실 정보국의 수장이야. 언젠가 나는 런던에 가서 머큐리호의 운명에 대해 직접 그에게 보고할 거다. 그러니 네 그 비참한 적의 이름을 내게 말해라.";
			link.l1 = "앙제랑 드 시에부, 드 레비 반타뒤르 백작의 사생아지. 머큐리를 그냥 해적질한 전리품을 옮기는 수송선쯤으로 여겼던 모양이야. 진주에 대해서는 알았을지도 모르지만, 영국 정보국과의 연관성은 전혀 몰랐겠지.";
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = "실망시키지 않는군, 선장. 그 점은 인정하지! 이런 오락과 적의 선택이라니! 좋아. 진주 말고 또 다른 증거는 무엇이 있지?";
			link.l1 = "드 쉬비우스는 프리깃을 가지고 있어. 나도 한때 그 배를 가졌었지... 딱 하룻밤뿐이었지만, 그래도 뭔가를 배웠어. 그는 엄청나게 꼼꼼한 사람이야; 머큐리호를 공격한 내용이 그의 항해일지에 다 적혀 있을 거야. 그는 아직도 전리품 일부를 갖고 있을 거라고 확신해. 어쩌면 흑진주도 더 있을지 몰라, 여러 개였다면 말이지.";
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = "한둘이 아니야, 그건 확실하지. 우리가 평범한 진주 몇 개 때문에 레지나를 위험에 빠뜨릴 리 없지. 나는 꼭 드 시에부 나리와 이야기해야 한다는 걸 알아줬으면 해. 진주 따위엔 관심 없어, 하지만 그 유출에 대해 더 알아내야 해. 상관들께 완전한 보고를 못 올리면 나를 가만두지 않을 거야.";
			link.l1 = "당신을 위해 만남을 주선해 드리고 싶지만, 서둘러야 합니다! 지금 이 순간에도 드 쉬에부스의 프리깃이 과들루프로 향하고 있는데, 그곳에서 선주가 현지 총독의 보호 아래 머물고 있습니다.\n그가 자신이 저지른 일을 알고 있을 테니, 가능한 한 빨리 신세계에서 도망칠 것이라고 확신합니다.";
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = "이건 아주 중대한 인물들에 대한 아주 심각한 고발이오, 선장. 자네, 이게 어떤... 큰 소동으로 번질지 알고 있나? 동맹국의 깃발을 단 배를 노린 강도들의 습격이라니? 이 일로 두 강대국 사이의 관계가 심각하게 꼬일 수도 있소. 도대체 그자가 자네 속을 얼마나 뒤흔들었기에 이렇게 큰 위험까지 감수하려는지, 상상하기 어렵군.";
			link.l1 = "그 자가 제게서 뭔가를 빼앗아갔습니다, 나리. 제 목숨보다도 소중한 것을요. 반드시 되찾아야 합니다. 전쟁이 벌어진다 해도, 저는 조국의 깃발 아래서 복무할 것입니다. 그래도 드 시에부는 반드시 응분의 대가를 치를 것이고, 모든 책임은 오직 그 자에게 있습니다!";
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = "누가 당신에게, 당신이 아주 위험한 사람이라고 말한 적 있소, 선장? 목적을 이루기 위해 세계 절반에 전쟁을 일으킬 각오가 되어 있군. 좋아, 당신 방식대로 해보지. 내가 바세테르까지 함께 가겠소. 이런 흔적을 그냥 놓칠 수는 없으니. 내가 배를 준비하는 동안 서기를 보내 증거를 기록하게 하겠소.";
			link.l1 = "감사합니다, 나리. 하지만 여기서 머뭇거릴 시간은 없소, 경고하겠소!";
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = "de Maure 선장, 우리는 제시간에 도착할 거요. 나는 그대가 해낼 거라 믿어 의심치 않소. 하지만, 이번 모험이 실패한다면... 내 말 뜻 알겠지? 제대로 된 무덤조차 약속할 수 없소.";
			link.l1 = "예, 나리. 완전히 이해했습니다.";
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = "주사위는 던져졌소, 선장. 내가 앙제랑 드 시에부와의 만남을 요구했소. 그의 프리깃은 도착하는 즉시 수색될 것이오. 프랑수아 드 리옹은 의심을 품고 있지만, 내 문서의 봉인이 그를 당분간 막고 있소. 상황이 정리될 때까지 도시에 머물러 주길 바라오.";
			link.l1 = "물론입니다, 나리, 이해했습니다.";
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = "그렇다면 이것도 이해해 주길 바라오. 저기 있는 신사들에게 칼을 넘기고 그들을 따라가시오, 그래야 자네가 약속을 지킬 거란 걸 내가 확신할 수 있겠소.";
			link.l1 = "믿을 수가 없군... 코트니 나리, 정말이십니까?!";
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = "진심이야. 넌 여전히 내 주요 용의자 중 하나로 남아 있고, 이런 상황에서 널 그냥 풀어주는 건 내게 정말 어리석은 짓이겠지. 네 말이 사실로 드러난다면, 그리고 그때가 오면 내가 적절하다고 생각하는 방식으로 사과하마.";
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = "인사드립니다, de Maure 나리. 가시겠습니까?";
			link.l1 = "기꺼이 하겠소, 규칙이 뭐요? 솔직히 말해서, 나는 음식에 정신이 팔려서 조건을 제대로 못 들었을지도 모르겠소.";
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = "규칙은 간단하다. 카드 한 장당 10,000페소, 우리 중 한 명이 항복할 때까지 계속하지. 영수증이나 외상은 안 받아.";
			link.l1 = "나야 좋지. 합시다, 대령님.";
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "젠장! 다시는 안 해! 좋아, 드 모르 나리, 다음 판에서 행운을 빌지.";
				link.l1 = "기쁩니다, 대령님. 안녕히 가십시오.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "잘 싸웠지만, 운명의 여신께서 따로 계획이 있으셨군. 안녕히 가시오, 드 모르 나리. 게임 고마웠소.";
					link.l1 = "그래, 내가 이번엔 내 자신을 과대평가했던 것 같군. 안녕히 계시오, 대령.";
				}
				else
				{
					dialog.text = "당신은 경기를 포기하기로 결정했고, 그로써 패배를 인정했소! 용감하게 싸웠지만, 운명이 달랐던 것이오. 안녕히 가시오, de Maure 나리, 그리고 좋은 경기였소.";
					link.l1 = "그래, 이번엔 내가 내 자신을 과대평가했던 것 같군. 안녕히 계시오, 대령.";
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "샤를 드 모르 선장, 이런 젠장 깜짝 놀랐군!";
					link.l1 = "선장. 모레노, 웃기고 있네! 여기엔 무슨 일로 온 거야?!";
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = "샤를 드 모르 선장, 만나서 반갑소.";
						link.l1 = "전에 만난 적 있소, 모레노 나리...?";
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = "샤를 드 모르 선장, 만나서 반갑소.";
						link.l1 = "전에 만난 적 있소, 모레노 나리...?";
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Charles de Maure 선장, 반갑소.";
				link.l1 = "전에 만난 적이 있던가, 모레노 나리...?";
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = "긴 얘기야. 늘 그렇듯이, 선장. 당신 눈을 보니 궁금한 게 있다는 걸 알겠어. 그냥 조용히 하고, 평범한 선원을 놀리는 척만 해.";
			link.l1 = "그래, 이 멋진 옷이 잘 어울리네, 내 단순한 친구. 옷 입는 법 좀 아는구나.";
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = "운이 좋을 때만 아주 가끔 있지. 오늘이 바로 그날이야. 한 판 해보자고, 선장. 사람들이 지켜보고 있으니, 너무 오래 기다리게 하면 실례지.";
			link.l1 = "좋아, 나중에 이야기하지. 거래는... 모레노 선장, 부탁하지.";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = "너를 좀 알긴 하지만, 그건 상관없어. 카드를 돌려, 드 모르 선장, 사람들은 구경거리를 원하니까.";
			link.l1 = "흥미롭군. 특히 그 스페인 억양, 그리고 보토 부인께서 칭찬하신 것도 말이야. 좋아. 바다와 바다의 대결, 해보자고!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = "네 놈을 기억하지. 너랑 내 전 선장이 르 프랑수아에서 내 부하들을 찔러 죽였지. 그 개자식은 결국 자업자득이었지만, 네 도움이 없었으면 그렇게 되진 않았을 거다. 하지만 내 고마움을 기대하지 마라. 네가 프란츠 가르케를 죽였으니, 그건 절대 용서 못 한다.";
			link.l1 = "포르투갈 쿼터마스터 말인가? 피의 돈, 맞지? 오늘 밤 점점 더 재밌어지네. 가자!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "더 이상 게임을 하지 않기로 했군. 그걸로 패배를 인정한 셈이지! 행운의 여신께서 한마디 하신 모양이네. 잘 가게, 선장.";
				link.l1 = "저도 반갑습니다, Moreno 나리. 게임 즐거웠습니다.";
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "운명의 여신께서 이미 말씀하신 것 같군. 안녕히 가시오, 선장님, 언젠가 다시 만날지도 모르겠소.";
					link.l1 = "저도 마찬가지입니다, Moreno 나리. 게임 감사합니다.";
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = "운명의 여신이 이미 말씀하신 것 같군. 안녕히 계시오, 선장. 아마 다음엔 다른 상황에서 다시 만날지도 모르지, 헤헤.";
						link.l1 = "기대하고 있소, Moreno 나리.";
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = "그렇군. 운명이 정해졌소, 선장님. 작별이오.";
						link.l1 = "안녕히 가십시오, Moreno 나리.";
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "그렇군. 운명이 결정했소, 선장님. 안녕히 가시오.";
				link.l1 = "안녕히 가십시오, Moreno 나리.";
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = "만나서 정말 반갑습니다, de Maure 선장 나리! 솔직히 말해서, 저는 무장 경비대까지는 예상했지만, 나리께서 직접 오실 줄은 몰랐습니다.";
			link.l1 = "모레노 나리, 현지 관리들과 무슨 문제라도 있소? 그런데 나도 반가워, 하하!";
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = "이봐, 우리 여주인의 초대는 거절할 수 없지. 적어도 그런 종류의 초대라면 말이야. 자, Charles, 그만 좀 장난치고. Marquise께서 내 진짜 정체를 알고 있다는 걸 분명히 내게 알리셨거든.";
			link.l1 = "...";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = "부인, 정말 매력적이십니다! 이 새 친구분이 전에 저를 한 번 넘기려고 했었죠. 사실 그리 잘 되진 않았고, 오히려 이 친구가 제 목숨을 몇 번이나 구해줘서 이제는 셀 수도 없습니다. 어쨌든, 이제 제가 이 친구에게 신세를 졌으니, 협박 같은 건 필요 없어요. 걱정 마십시오.";
			link.l1 = "고맙다, Bartholomew. Angerran de Chievous가 나를 정말 곤란한 상황으로 몰아넣었어. 반드시 그 자를 끌어내려야 해. 내게 아주 소중한 사람의 목숨이 달려 있거든. 믿어줘, 이번에는 어떤 것도 날 막지 못할 거야.";
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = "그만하게, 선장. 우리 친구 아니었나? 군도 반을 가로지르며 경주했던 거 기억나지? 나한텐 정말 큰 의미였어. 최선을 다해 도와주겠네. 머큐리호에 대해 들어본 적 있나?";
			link.l1 = "이게 뭐지? 배인가?";
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = "정확히 말하자면, 영국 브리건틴이었지. 그 배의 임무는 도일리 대령의 사략선들이 서인도 스페인 진주 채취장을 약탈해서 얻은 전리품을 운반하는 거였어. 가끔 전설의 흑진주를 잡으러 다니는 놈들, 들어본 적 있나? 내 정보가 맞다면, 그 흑진주 몇 개가 머큐리 호에 보관되어 있었다더군. 한 달 전에 나는 마르티니크와 과들루프 사이에서 매복을 깔고 그 고상한 신사들을 기다렸지. 하지만 헛수고였어! 우리는 바다에서 일주일을 허비하다가 결국 실패로 끝내야 했지.";
			link.l1 = "그래, 결국 네 정보원은 믿을 만하지 않았고 너 자신에겐 아무런 보상도 없었군. 그런데 이 모든 일에 드 시에부스가 무슨 상관이야?";
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = "나도 똑같이 생각했지. 그런데 머큐리가 앤티과에 나타나지 않았다는 걸 알게 됐어. 그런데 그녀가 퀴라소 근처에서 목격됐다니, 내가 마르티니크 근처에서 놓쳤을 리가 없는데 말이야. 영국 놈들 완전 분통 터뜨리고 있더군! 그런 노획선을 놓쳤으니 당연하지. 어쨌든, 나도 궁금해져서 조사를 시작했지. 모두의 재미를 망쳐놓은 그 특별한 놈에 대해 말이야. 그런 전리품은 금방 팔 수가 없으니, 르 프랑수아로 가서 그 자식을 찾아 내가 받아야 할 걸 받아내려고 했지.";
			link.l1 = "네 얘기, 어디서 들어본 것 같군. '카르마'라는 말 들어봤나? 넌 정말 스스로 문제를 잘 찾아내는구나. 그런데 그게 나한테 무슨 도움이 된다는 건지 아직 모르겠는데?";
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = "서두르지 마시오, 선장. 이제야 내 이야기에서 가장 재미있는 부분을 말하려 하오. 그 씻지도 않은데 멀끔하게 차려입은 당신 친구 말이오 – 그 친구 부하들이 이 근처 상점에 고운 진주를 잔뜩 흘리고 다녔소. 스페인산 진주 보물이었는데, 엄청난 양을 흥청망청 써버렸지.";
			link.l1 = "...";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "들었어, 선장?";
			link.l1 = "자네는 드 시에부스가 자크 더 카인드와 그 일당에게서 훔친 진주를 샀다고 생각하나? 내 걱정되는군... 이 정도로는 부족해.";
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = "그래, 선장. 그 자는 산 게 아니라 팔고 있었어! 이 일에 대해 바르바존과 얘기해 봤는데, 바르바존이 자기 파트너 중 한 명에게서 완벽한 진주를 상당량 샀다고 확인해 줬지. 그걸 나중에 유럽으로 보냈다고 하더군. 우리에겐 목걸이에 박힌 그 흑진주도 있고, 드 쉬에부스의 배가 수리 작업을 받았다는 사실도 있지. 일꾼들이 그러는데, 그의 프리깃에는 12파운드짜리 포탄 구멍이 뚫려 있었다더군. 누가 제정신으로 그런 꼬마 포로 프리깃을 공격하겠어?";
			link.l1 = "우리 브리건틴 얘기 같군! 게다가 드 시에부스가 자기 프리깃이 얼마나 빠른지 자랑하던 것도 기억나. 그런데 왜 이런 미친 짓을 하는 거지? 우리는 영국과 평화 상태인데, 왜 이렇게 큰 위험을 감수하는 거야, 대체 무엇 때문에? 흑진주는 정말 희귀하긴 하지만, 아예 없는 건 아니잖아.";
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = "바로 그게 그의 실수였지! 영국놈들은 이미 머큐리호 실종 사건에 공식 조사를 시작했어. 물론 그들은 머큐리호를 중요한 문서를 실은 사라진 우편선이라고 부르지만 말이야. 단서가 있으면 후하게 보상하고, 책임자는 엄하게 벌주겠다고 하더군. 제일 재밌는 건, 특별한 귀족 관리까지 앤티과에 보냈다는 거야. 지금 그놈이 사건을 파헤치느라 아주 바쁘지. 이름은 기억 안 나, 잘난 척하는 얼굴만 번드르르했거든. 그래도 다행히 나를 쫓는 건 아니라서 속이 시원하다!";
			link.l1 = "이거 참 대단한데! 저놈들이 흑진주를 엄청나게 원하나 보군. 머큐리호에 몇 개나 있었는지, 그리고 이 모든 정보가 나한테 어떻게 쓸모가 있을지 궁금하군?";
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = "왜, 그 인간 쓰레기가 당신도 화나게 했소, 마르키즈? 저주받을 놈! 이번 일도 나도 함께하겠소, 드 모르 선장! 바르톨로메우 포르투갈 놈한테서 전리품을 훔칠 자는 아무도 없지!";
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = "이렇게 말이 많았으니 한잔 제대로 해야겠군. 이제 우리가 친구가 되었으니, 마르키즈...";
			link.l1 = "이 집엔 럼이 하나도 없는 것 같아, 바솔로뮤.";
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = "그래, 그래. 저 영국 조사관의 시선을 그의 프리깃에 딱 끌어주자는 거지! 이게 우리 계획이라면, 난 우리 옛날의 좋은 드 모르 선장을 더 이상 알아볼 수가 없겠군!";
			link.l1 = "웃기겠지만, 그게 바로 계획이오. 두 분 모두의 도움이 필요하오. 부인, 당신은 내가 고용한 해적의 포로가 될 거요. 바로 바르톨로뮤, 그게 자네 역할이네.";
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = "그리고 내 이 악행에 대해서도 말이야! 포르투갈인 바르톨로메오는 여자를 납치한 적이 없어!";
			link.l1 = "그리고 그는 그렇게 하지 않을 거지만, 드 시에비우스의 부하들 눈에는 그렇게 보일 거다. 게다가 네 이름을 그들에게 말할 필요도 없어. 우리 숙녀를 배에 태우고 앙제랑의 프리깃함을 케이프 스콧 헤드 근처에서 만나. 줄리아나를 내 장교와 교환한 뒤 마르티니크로 돌아가. 그리고 후작 부인과 나를 기다려.";
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = "이거 다 정말 흥미롭긴 한데, 너는 타고난 기사야, Charles. 그런데 도대체 우리가 어떻게 그녀를 교환 후에 돌려보내야 하지?";
			link.l1 = "내가 처리하겠다. 시간도 없으니 흩어지자. 너와 후작부인은 도미니카로 가고, 나는 세인트 존스로 급히 가겠다. 나는 도일리 대령이나 그 영국 조사관을 찾아가 머큐리호 실종의 책임자가 누구인지 말하겠다.";
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = "선장, 이런 사건 뒤에 무슨 난리가 벌어질지 생각이나 해봤소? 지금 이 순간 앤티과는 벌집이나 다름없는데, 거기에 돌을 던지라고 하는 거요. 이보다 사소한 일로도 전쟁이 난 적이 있다는 걸 기억하오!";
			link.l1 = "한 번에 하나씩 해결하지... 무슨 수를 써서라도 그녀를 데려오겠다! 소문대로 그렇게 대단하다면 드 레비 반타두르가 혼자서 이 모든 난장판을 수습하게 두지. 그리고 드 시에부스도 마담 보토가 어떻게 자기 배에 타게 됐는지 설명하느라 고생 좀 할 거다.";
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "준비됐나? 기도부터 하게! 마르키즈, 납치될 준비는 됐소?";
			}
			else
			{
				dialog.text = "준비됐소? 기도 한 번이면 되겠지! 마르키즈, 짐 싸는 데 얼마나 걸리겠소?";
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+", 드 모르 나리. 내 이름은 "+GetFullName(npchar)+", 그리고 이쪽은 "+GetFullName(characterFromId("GG_SecundantGG_2"))+". 각하께서 우리에게 당신과 드 시에부 나리의 결투를 목격하라고 요청하셨소.";
			link.l1 = "좋은 저녁이오, 신사 여러분. 오늘 밤 아무 일 없이 모두 무사하길 바라오. 하지만 만약을 위해 항상 대비하시오. 이 '신사'란 자가 실망을 안겨줄 수도 있으니.";
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = "그대의 불안은 근거 없소. 이번 결투의 정해진 조건에 따르면, 어떠한 경우에도 참관인들은 개입할 수 없소. 그래도 경고해 줘서 고맙소. 상대가 도착했소. 행운을 빕니다, 선장님. 각하께서 신중함을 위해 기도하시겠다고 전해 달라고 하셨소.";
			link.l1 = "틀림없이 나에게 큰 도움이 될 거야. 어쨌든, 시작하자.";
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = "선장, 문제 생겼어. 우리 배가... 글쎄, 없어졌어.";
			link.l1 = "잠깐, 뭐라고?! 어떻게, 누구한테? 거기엔 감시조가 전부 배치되어 있었어, 도대체 무슨 소리를 하는 거야?!";
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "아니요, 선장님, 그 배 말고요. 그 배는 멀쩡해요. 어제 선장님이 얻은 프리깃함 말입니다, 이제 우리 배도 된 거잖아요, 맞죠? 거기엔 상금 선원 열두 명만 보냈어요. 그녀가 그 정도면 충분하다고 했거든요.";
			link.l1 = "그만 좀 하고 처음부터 무슨 일이 있었는지 똑바로 말해!";
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "모르겠소, 선장님. 프리깃이 아침 안개 속에서 출항했소. 안개가 걷힌 몇 시간 뒤에야 감시병이 그녀가 없어진 걸 알아챘지.";
			link.l1 = "이럴 리가 없어! 걔가 나한테 이럴 리가 없지! 그런데... 젠장, 우리 얼마 전에 싸웠었지. 설마 걔가...";
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "더 심각한 것 같소, 선장. 오늘 아침 일찍 어부들이 우리 전리품 선원 중 두 놈을 발견했소. 둘 다 목이 그어져 죽었소.";
			link.l1 = "젠장 악몽이군! 드 시에부스! 내가 후작부인과 한창일 때 그 자식이 배를 훔쳐 갔어! 제발 그녀가 무사하길... 머리카락 한 올이라도 다치면, 나 정말...";
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = "애들한테 준비하라고 명령 내릴 거야, 선장? 두 시간 뒤면 출항할 수 있어. 아침 내내 다들 신경이 곤두서 있었어, 특히 당신 부선장이 말이야; 우리가 간신히 그 녀석을 말려서 쫓아가지 못하게 했지.";
			link.l1 = "아직은 이르다. 제대로 생각을 정리해야 하고, 누군가와 이야기도 해야 해. 그래! 배를 준비해! 모두 준비시키고, 내가 돌아오자마자 출항할 거다.";
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = "de Maure 선장, 무슨 일이오? 누가 부인님을 공격했소?";
			link.l1 = "여기 오지 말았어야 했어. 뭐, 하느님이 증인이시니, 나도 이런 일은 원치 않았어.";
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = "나리, 당신이 여기 오기를 거의 포기할 뻔했소. 당신의 작은 배에 보토 마르키즈가 타고 있는 것이 보이는군. 어떻게 된 일인지는 묻지도 않겠소. 당신의 동료가 기다리고 있소. 그녀는 무사하니, 데리고 어서 이곳을 떠나시오.";
			link.l1 = "네가 그녀한테 손끝이라도 댔다면, 네 낡은 배를 산산조각 내버릴 거야!";
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = "이렇게 신경 써줄 줄은 몰랐군. 걱정 마, 그녀는 마치 감금된 여왕처럼 지냈어. 네 협박 따윈 신경도 안 써. 그런데, 슈발리에 드 쉬부가 안부를 전하더군.";
			link.l1 = "그 자식 안부 따위 집어치워. 내... 장교는 어디 있지? 이제 교환을 시작하자.";
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = "나리, 여기 오시길 거의 포기할 뻔했습니다. 당신의 동료가 기다리고 있습니다. 그녀는 무사합니다... 잠깐, 이 자식은 누구지? 후작부인은 어디 있습니까?";
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = "칼을 내놓으시오, 나리. 그리고 장난칠 생각 마시오, 내 부하들이 요즘 신경이 곤두서 있거든. 총알 맞고 싶진 않을 테지?";
			link.l1 = "진심이야? 좋아, 가져가. 하지만 조심히 다뤄, 네 막사보다 비싼 거니까. 나는 코트니 준남작과의 면담을 요구하오, 각하!";
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = "걱정하지 마, 분명히 그가 시간을 내서 너를 찾아올 거야.";
			link.l1 = "누군가를 도우려 할 때...";
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = "나도 이 상황이 마음에 들지 않소, 나리. 유감스럽게도 저 건방진 영국 놈이 워낙 권세가 세서 리옹 나리조차 어쩔 도리가 없소. 미안하오, 선장님, 검을 넘겨주시오.";
			link.l1 = "나는 드 시에부 나리와 같은 감방에 갇히지 않길 바란다. 가자, 신사 여러분, 나는 정말 피곤하다. 드디어 좀 잘 수 있겠군.";
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Cortny");
			sld.lifeday = 0; // Captain Beltrop, убираем Кортни
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = "무례하게 굴 생각은 없소, 나리, 하지만 지금 무슨 일이 벌어지고 있는지 보시다시피 당장 이야기할 시간이 없소. 아무것도 놓치고 싶지 않으니!";
			link.l1 = "원하시는 대로 하겠습니다, 나리.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = "오늘 밤은 역사에 남을 거요, 느낌이 와! 여기서 베르사유까지 모두 이 이야기를 하게 될 거요! 내 마리안느도 분명 기뻐하며 모든 세부사항을 알고 싶어할 거요. 제발, 나리, 비켜 주시오, 내 시야를 가리고 있소.";
			link.l1 = "난 이제 가네, 나리, 구경 잘 하시고, 잊지 못할 마리안에게도 안부 전해 줘... 그게 누군지 몰라도.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = "하! 여기 있었군, 드 모르 나리! 실례... 샤를 드 모르 선장! 이리 오시게, 훌륭한 구세계 와인들이 준비되어 있네. 오늘 밤을 어떻게 시작하고 싶으신가? 새로운 맛, 우리 사랑하는 지롱드 강가에서 온 카베르네 소비뇽으로 할까, 아니면 시대를 초월한 고전, 이탈리아의 산지오베제로 할까?\n";
			link.l1 = "고맙소, 나리, 나중에 같이 한잔하겠소.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = "오, 드 모르 선장! 와인 좀 더 드시겠습니까... 히끅? 방금 우리에게 나온 걸 한번 보십시오 - 론 계곡 북쪽 언덕에서 온 1643년산 시라입니다. 이건, 젠장, 진짜 보물이에요! 그리고 그 해는 모든 면에서 훌륭했지요, 내가 말하건대... 케이프 갯에서 스페인 놈들이 패배한 것만 해도 충분히 값어치가 있지! 그런데... 왜 다들 저렇게 소란을 피우는지 아십니까? 누가 몸이 안 좋은가요? 뭐 - 어쨌든, 건배...";
			link.l1 = "그래도 누군가는 대접에 감사하는군. 잘 가시오, 나리.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = "오, 샤를 드 모어 선장님, 이 도시의 모든 사람들처럼 저도 선장님에 대해 들었습니다! 제 소개를 하겠습니다 - "+GetFullName(npchar)+", 당신을 만나게 되어 큰 영광입니다, 믿어주십시오! 정말로 우리 총독님과 친분이 있으신가요? 저희를 소개해 주실 수 있겠습니까? 그분께 깊은 존경을 표하고 싶어서요, 그리고...";
			link.l1 = "나중에 하죠. 좋은 저녁 보내시오, 나리.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = "드 모르 나리, 이것 봤소?! 우리 존경하는 총독님과 드 시에부 나리 본인까지 - 둘이 여기서 서로 죽일 줄 알았소! 대단했지! 보토 마르키즈께서 오늘 제대로 한 건 하셨군 - 정말 미치게 흥분되는걸! 다음 이야기가 몹시 기다려져. 그런데, 혹시 지금이 바로 그 순간 아닐까? 나를 소개해 주기로 약속했잖아... ";
			link.l1 = "나는 아무것도 약속한 기억이 없어. 미안하지만, 이제 가봐야겠어.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = "마우르 나리, 마침내 위대한 보토 부인 살롱에 오셨군요! 그분께서 이미 여러 번 당신을 보고 싶다고 하셨답니다.\n그분의 '제자들'을 평가해 보셨습니까? 예, 마르키즈 같은 별들은 저희 같은 평범한 인간이 넘볼 수 없는 존재지요. 하지만 믿으십시오, 이 숙녀들은 진정한 예술 작품입니다. 어쩌면 덜 놀라울지 몰라도, 그래도 미켈란젤로나 티치아노 같은 거장들의 작품과 다를 바 없습니다.";
			link.l1 = "흥미로운 비유로군, 나리. 그럼, 밤을 즐기시게....";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = "아니, 여긴 늘 시끌벅적하지만, 지금은 대단한 스캔들의 기운이 공기 속에 가득해, 느껴지나? 자클린 부인이 위층에서 날 기다리고 있는데도, 도박판에서 도저히 발길이 떨어지질 않아! 그분과 드 쉬에부 나리 둘 다 만만치 않은 상대고, 승부욕도 대단하지. 오늘 밤의 내기는 별에 닿는 걸 넘어서, 하늘 자체를 박살내고 악마들 품까지 떨어질 것 같군!\n";
			link.l1 = "악마들은 아래에 있습니다, 나리. 천상의 창공 너머에는 틀림없이 천사들이 있을 겁니다.";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = "그래도 적어도 한 번은 유쾌한 만남이군! 우리는 이미 만난 적이 있소, 드 모르 선장. 아마 기억 못 하실 테지만. "+GetFullName(npchar)+" - 나는 주둔지 육군 6중대의 선장이었소, 당신과 함께 우리 거리에서 스페인 놈들과 싸웠지. 사실 말하자면, 무릎에 총을 맞아 전투 내내 이 바로 그 사창가가 불타는 걸 도랑에 누워 지켜봤소. 그리고 지금 나는 여기 있소 – 또다시 내전이 벌어졌고, 이번에도 감탄하고 있지, 하지만 이번에는 안에서 말이오.";
			link.l1 = "만나서 반갑소, 나리. 그날은 정말 더운 날이었지만, 인정하자면 그 이후로 이곳이 훨씬 더 아름다워졌소!";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = "여기 분위기는 어떠신가요, 선장? 이 세속의 바보들이 피바람을 일으킬 작정인 것 같소! 궁금하군, 총독 자리도 카드 내기처럼 걸 수 있는 건가? 내 말 명심하시오 – 결국 칼부림으로 끝날 거요. 안타깝게도, 내 무릎 때문에 이런 유흥은 이제 나와는 거리가 멀지. 그런데 자클린을 어딘가에서 봤소 – 그녀의 신사는 지금 벌어지는 일에 푹 빠진 것 같더군... 아직 여기 분위기가 조용할 때, 나도 운을 시험해보러 가야겠소.";
			link.l1 = "좋은 결정이오, 성공을 빌겠소, 나리. 그리고 나는 다시... 월리스로 돌아가야 하오.";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
