// Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "명백한 버그다. 개발자들에게 알려라.";
			link.l1 = "그래, 그렇게 할게.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "carpenter":
			DelMapQuestMarkCity("Fortfrance");
			LAi_SetImmortal(npchar, false);
			npchar.lifeday = 0;
			DelLandQuestMark(npchar);
			dialog.text = TimeGreeting()+", 선장님. 제 소개를 하겠습니다 - "+GetFullName(npchar)+". 얼마 전에 만났지만, 내가 기억나지는 않을 것 같군.";
			link.l1 = "인사하오, 나리. 어디서 전에 뵌 적이 있던가?";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
			sTemp = "lugger 'Adeline'";
			if (pchar.questTemp.Sharlie.Ship == "sloop") sTemp = "sloop 'Black Dog'";
			dialog.text = "우리 조선소야. 네가 물건을 샀지\n "+sTemp+". 이제 기억나? 거기서 내가 목수였잖아.";
			link.l1 = "그래, 그 배 내가 진짜로 샀어. 그래서 뭐 원하는 거야, 나리 "+GetFullName(npchar)+"?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
			sld = characterFromId("FortFrance_shipyarder");
			AddLandQuestMark(sld, "questmarkmain");
			dialog.text = "우리 배목수 "+GetFullName(sld)+" 당신과 이야기하고 싶어 해요. 뭔가 사업 제안을 하려는 것 같아요. 당신의 배가 우리 항구에 들어온 걸 보고 저를 보내 당신을 찾으라고 했어요. 초대를 받아 주시겠습니까?";
			link.l1 = "좋아. 내가 마을에서 볼일을 끝내면 네 상사한테 찾아가 주지.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQM = "begin";
			AddQuestRecord("FMQ_Martinique", "1");
			SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;
		
		case "officer":
			PlaySound("Voice\English\soldier_arest_4.wav");
			dialog.text = "흠, 흠... 내 그물에 새로 걸린 밀수꾼들이군!";
			link.l1 = "에...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			dialog.text = "헛소리 집어치워! 이 조선소 안에 송진 통이 여러 개 있지. 선장, 너는 그걸 네 공범에게 넘겼어. 둘 다 체포한다! 그리고 나는 법의 이름으로 그 화물을 압수하겠다!";
			link.l1 = "...";
			link.l1.go = "officer_2";
		break;
		
		case "officer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_3":
			dialog.text = "모르는 척하지 마라, 나리! 무슨 통 말이냐고? 네가 방금 이 선원의 배에서 내린 바로 그 통들 얘기하는 거 다 알잖아! 둘 다 감옥에서 썩게 될 거다! 움직여, 이 자식들아...\n";
			link.l1 = "";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\soldier\soldier arest-02.wav");
			dialog.text = "이 송진은, 사랑하는 조선소장 나리, 우리 총독이 직접 관리하는 전략적 가치가 있는 물자요! 그걸 전부 자기 것이라 주장하니, 좋을 대로 하시오. 자, 체포하겠소. 오늘 밤은 우리 안락한 지하 감옥에서 보내게 될 것이고, 내일은 이걸 어떻게, 무슨 목적으로 손에 넣었는지 자세히 보고해야 할 거요. 걱정 마시오, 결국엔 모든 걸 알아낼 테니. 그리고 자네, 선장, 자네는 가도 좋소. 오늘은 운이 좋은 날이군.";
			link.l1 = "";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;
		
		case "officer_7":
			PlaySound("Voice\English\soldier_arest_2.wav");
			dialog.text = "이 배에 뭔가 문제가 있다는 걸 알았지... 내가 널 과소평가했나 보군, 선장.";
			link.l1 = "정확해, 부관. 내가 그렇게 멍청하진 않아. 이제 네가 조선공과 짜고 친 일은 들통났어.";
			link.l1.go = "officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "officer_8":
			dialog.text = "알겠군. 축하하지. 나를 이렇게 찾아내서 기습까지 했으니 재주가 있나 보군. 이제 말해 봐라, 뭘 원하는 거지.";
			link.l1 = "그거 분명하지 않나? 내 송진을 돌려줘야겠어. 너랑 네 친구가 내 송진을 훔쳐 갔잖아.";
			link.l1.go = "officer_9";
		break;
		
		case "officer_9":
			dialog.text = "좋아. 가져가도 돼, 하지만 네 몫의 절반만 줄 수 있어. 여기 숨겨둔 건 그게 전부야. 그걸로 충분하길 바라, 내가 줄 수 있는 건 그게 다니까.";
			link.l1 = "아직도 나를 속이려고 하는 거야? 나머지 절반은 금이나 네 뒤에 숨겨둔 물건으로 보상해.";
			link.l1.go = "officer_10";
		break;
		
		case "officer_10":
			dialog.text = "방법 없어. 나머지 절반은 우리 공통 친구한테 물어봐.";
			link.l1 = "장난하냐? 그걸 진짜 믿는 거야? "+GetFullName(characterFromId("FortFrance_shipyarder"))+" 내 통을 돌려주겠다고? 말도 안 되는 소리군.";
			link.l1.go = "officer_11";
		break;
		
		case "officer_11":
			dialog.text = "선장, 내가 가진 송진 전부 가져가고, 목숨 부지해서 당장 여기서 꺼져. 이 거래에 한 가지 더 얹자면, 생피에르에서 너한테 문제 안 일으키겠다는 약속도 해주지. 이게 내 마지막 제안이야.";
			link.l1 = "내 인생이 언제부터 거래의 일부였지? 하!";
			link.l1.go = "officer_12";
		break;
		
		case "officer_12":
			dialog.text = "싸움 끝나고도 아직 자신이 무적이라고 생각하는 모양이군, 선장. 내가 설명해 주지. 방금 상대했던 놈들은 풋내기들이고, 훈련도 안 됐고, 의지도 없었지. 내 부하들과는 상대도 안 돼. 네놈을 여기서 바로 죽일 수도 있지만, 난 내 부하들의 목숨을 소중히 여긴다. 널 죽이는 과정에서 내 부하들 중 몇몇이 다치거나 죽을 수도 있으니까. 그러니 내 후한 제안을 받아들이든가, 아니면 영원히 여기 남아 있든가. 이제 선택해.";
			link.l1 = "엿이나 먹어, 중위 나리, 하지만 어쩔 수 없이 네 조건을 받아들일 수밖에 없군. 여기선 내가 완전히 밀리니까.";
			link.l1.go = "officer_13";
			link.l2 = "너무 자만하는군, 중위? 너랑 네 용병들에게 본때를 보여줘야겠어. 이 피투성이 송진 개 자식아!";
			link.l2.go = "officer_15";
		break;
		
		case "officer_13":
			dialog.text = "당신은 이성적인 사람이군, 선장. 네 통들을 챙겨서 꺼져. 한 가지 경고하지, 총독 앞에서 나를 지목해도 소용없을 거야. 오늘 내 은닉처를 옮길 거거든. 시간 낭비하지 마.";
			link.l1 = "그럴 생각 없었어. 당국에 말해봐야 소용없다는 거 나도 알아.";
			link.l1.go = "officer_14";
		break;
		
		case "officer_14":
			dialog.text = "서둘러, 나한텐 시간이 별로 없어.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;
		
		case "officer_15":
			DialogExit();
			AddDialogExitQuestFunction("FMQM_BattleExit");
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_02.wav");
			dialog.text = "오! 이런 우연이! 반갑소, 나리! 오늘 밤 즐겁게 보내고 있소?";
			link.l1 = "좋은 밤이오... 아, 그대였군! 기억하오, 내가 카리브에 처음 도착한 날에 만났지. Gregoire Valinnie 나리.";
			link.l1.go = "greguar_1";
		break;
		
		case "greguar_1":
			dialog.text = "아직도 기억하고 있다니 다행이군. 이제 보니 선장이 되었구나. 선장 "+GetFullName(pchar)+". 축하하오.";
			link.l1 = "고마워...";
			link.l1.go = "greguar_2";
		break;
		
		case "greguar_2":
			dialog.text = "근심이 있어 보이시는군요, 선장님. 여기서 무슨 일이 있었습니까? 무슨 문제라도 있나요?";
			link.l1 = "뭔가 이상한데...";
			link.l1.go = "greguar_3";
		break;
		
		case "greguar_3":
			dialog.text = "나리, 길 한복판에 서 있지 말고 선술집에 가는 게 어때요? 맥주 한두 잔 마시면 좋을 거예요. 거기서 얘기합시다. 어서 가요!";
			link.l1 = "...";
			link.l1.go = "greguar_4";
		break;
		
		case "greguar_4":
			DialogExit();
			NextDiag.CurrentNode = "greguar_5"; 
			FreeSitLocator("Fortfrance_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;
		
		case "greguar_5":
			LAi_SetSitType(Pchar);
			dialog.text = "따라요, 선장...";
			link.l1 = "해 봐...";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,20);
			RecalculateJumpTable();
			dialog.text = "휴... 이제 무슨 일인지 말해 봐. 지난주에 교수형 당한 놈처럼 보이네. 그 자도 교수대에 서 있을 때 딱 너 같은 표정이었지.";
			link.l1 = "있잖소, Gregoire 나리... 그냥 내 일에 문제가 좀 있다고만 해두지.";
			link.l1.go = "greguar_7";
		break;
		
		case "greguar_7":
			dialog.text = "선장님, 저한테 뭐든 다 털어놓으셔도 됩니다. 제가 선장님을 총독이나 사령관한테 고자질할 일은 없으니, 그 점은 믿으셔도 됩니다. 저 못 믿으시겠어요?";
			link.l1 = "믿고 있소, 나리.";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			dialog.text = "그럼 자백하고 마음의 짐을 덜어. 내가 도와줄 수도 있으니까.";
			link.l1 = "현지 조선공이 나를 고용해서 트리니다드에서 출항한 스페인 선단을 약탈하라고 했지. 그 자는 송진이 절실히 필요하다며 그게 내 목표였고, 한 통당 두블룬 열다섯 개를 주겠다고 약속했어. 나는 선단을 쫓아가서 약탈했고, 물건을 여기로 가져왔지. 내 배는 수리를 위해 들어갔고, 배럴들은 조선소에 내렸어. 우리가 거래를 마무리하려던 참에 그 장교가 나타난 거야... 대체 어떻게 알았는지 궁금하군?";
			link.l1.go = "greguar_9";
		break;
		
		case "greguar_9":
			dialog.text = "";
			link.l1 = "그게 다였어, 우리가 딱 걸렸지. 조선공에게는 고마움을 표해야 할 것 같아 – 모든 책임을 자기한테 돌리고, 송진이 자기 물건이라고 하면서 내가 관련 없다고 했거든. 결국 그는 체포됐고 내 돈도 사라졌지. 스페인 대상단 건은 시간과 돈만 낭비였어, 그래도 감옥에 가지 않은 게 다행이지. 한 잔 더 따라줘, Gregoire 나리.";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			dialog.text = "그래서, 조선공이 체포된 거야?";
			link.l1 = "그래, 맞아. 내가 말한 바로 그 장교가 그를 감옥으로 데려갔지. 너도 그 장면을 봤어야 했어.";
			link.l1.go = "greguar_11";
		break;
		
		case "greguar_11":
			dialog.text = "그래, 둘 다 봤어. 하지만 펠리시앵 그로니에 중위가 옛 친구를 체포할 수도 있다는 건 전혀 몰랐지.";
			link.l1 = "뭐... 뭐라고 방금 말했지?";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "잘 들었어. 펠리시앵 그로니에 중위랑 조선공이야 "+GetFullName(characterFromId("FortFrance_shipyarder"))+" 오랜 친구들이지. 예전에 유럽에서 함께 군 복무를 했었어. 그로니에는 계속 군대에 남았고\n "+GetFullName(characterFromId("FortFrance_shipyarder"))+" 자기 사업을 시작하는 데 성공했다.";
			link.l1 = "그래서 서로 아는 사이였군... 이제야 알겠네...";
			link.l1.go = "greguar_13";
		break;
		
		case "greguar_13":
			dialog.text = "내 사랑 "+pchar.name+", 속은 것 같군. 너 아직 여기선 풋내기라서 그걸 이용당한 거야. 백 더블룬을 걸지, 나리\n "+GetFullName(characterFromId("FortFrance_shipyarder"))+" 3일 이내로 다시 조선소를 돌아다닐 거야.";
			link.l1 = "나리, 당신 말이 맞는 것 같소. 놈들이 날 속였군. 그 장교가 송진에 대해 알 리가 없었지. 타이밍도 완벽했어.";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			dialog.text = "여기는 카리브 해요, 나리 "+pchar.name+". 익숙해져라. 겉모습은 잊어버려, 여기서 제일 더러운 놈들도 항상 존경받는 귀족처럼 보이니까.";
			link.l1 = "이 대사는 어디서 들어본 적이 있는데... 저놈들을 어떻게 해야 하지? 총독에게 보고해야 하나?";
			link.l1.go = "greguar_15";
		break;
		
		case "greguar_15":
			dialog.text = "이 경우에는 두려워. "+GetFullName(characterFromId("FortFrance_shipyarder"))+" 딴 소리를 해댈 테니 너는 감옥에 처넣어질 거야.";
			link.l1 = "역시 그렇군. 좋아, 법이 내 편이 아니라면 내 방식대로 하지, 젠장! 이렇게 쉽게 포기하진 않을 거야.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			dialog.text = "진정하십시오 "+pchar.name+". 이건 네 분노와 럼주가 하는 소리지, 네가 아니야. 좀 자고 나서 다시 생각해 봐. 그냥 잊어버리는 게 너한테 제일 좋을지도 몰라. 펠리시앵 그로니에 중위와 "+GetFullName(characterFromId("FortFrance_shipyarder"))+" 여기엔 힘 있는 사람들이 있어, 네가 상대할 급이 아니야. 멍청한 짓 하지 마라.";
			link.l1 = "두고 보지. 내게 깨우쳐 줘서 고맙다. 너를 만나서 다행이야.";
			link.l1.go = "greguar_17";
		break;
		
		case "greguar_17":
			dialog.text = "조심해라. 내가 한 말을 명심해.";
			link.l1 = "그러지. 이제 마지막으로 한 잔 더 하자!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_OutTavern");
		break;
		
		case "greguar_18":
			PlaySound("Voice\English\LE\Greguar\Greguar_03.wav");
			dialog.text = "Captain "+GetFullName(pchar)+"!";
			link.l1 = "오, Gregoire 나리! 또 오셨군요!";
			link.l1.go = "greguar_19";
		break;
		
		case "greguar_19":
			dialog.text = "그래. 우리가 선술집에서 얘기한 뒤에, 나는 펠리시앵 그로니에 중위에 대해 알아봤지. 얼마 전에 열흘간의 휴가를 신청했다더군. 그 신청이 승인됐어. 오늘 그를 봤는데, 긴 노선을 타고 타르탄선으로 갔고, 그 배는 곧 과들루프로 출항했어. 이름은 토파즈야. 내가 아는 건 다 말했으니, 이제 네가 결정할 차례다. 그로니에가 갑자기 휴가를 요청하고 새로 지은 타르탄선을 타고 섬을 떠난 걸 보면, 무슨 패턴인지 알겠지.";
			link.l1 = "젠장, 이제야 완전히 알겠어, 그건 확실하지! 이 타르탄에 내 송진이 화물창에 실려 있었군! 그레구아르 나리, 고맙소, 정말 큰 도움을 받았네! 내가 보답으로 해줄 수 있는 일이라도 있소?";
			link.l1.go = "greguar_20";
		break;
		
		case "greguar_20":
			dialog.text = "아, 이보게, 친구. 우리는 귀족이니 서로 도와야 하네. 이게 우리 삶의 방식이지. 자네가 내 입장이었어도 똑같이 했을 거라 믿네. 시간 낭비 말고, 북쪽으로 항해해서 그 장교를 찾아. 전투는 하지 말고, 그저 그가 무슨 일을 꾸미는지 알아보게. 서두르게, 선장!";
			link.l1 = "다시 한 번 고마워!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_HurryToSea");
		break;
		
		case "pirate":
			dialog.text = "뭘 보고 있어? 여기서 뭐 하려고?";
			link.l1 = "이봐, 친구, 내 물건 가지러 왔어. 저기 있는 통들 보이지? 저게 내 송진인데, 아직 한 푼도 못 받았다고.";
			link.l1.go = "pirate_1";
			DelLandQuestMark(characterFromId("FMQM_Enemy_crew_2"));
		break;
		
		case "pirate_1":
			dialog.text = "너 바보냐 뭐냐? 아직 기회 있을 때 꺼져!";
			link.l1 = "이 수지를 얻으려고 내가 얼마나 애썼는데, 몇몇 더러운 놈들 때문에 포기할 수는 없지.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "네 화려한 옷 여기서 묻어주지!";
			link.l1 = "오, 장례를 제안해 주다니 참 친절하군. 하지만 유감스럽게도 널 그냥 이 해변에 내버려 두고 갈 수밖에 없겠어. 갈매기들이 네 내장을 쪼아 먹게 말이지!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
