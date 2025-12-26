// диалоги НПС по квесту 'В поисках Стража Истины'
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
		case "First time":
			dialog.text = "어떻게 도와드릴까요?";
			link.l1 = "미안해, 아무것도 아니야.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// пленный испанец
		case "spa_prisoner":
			PlaySound("Voice\English\Ransack_1.wav");
			dialog.text = "뭘 원하지? 또 심문하려고? 지옥이나 꺼져!";
			link.l1 = "나리, 성함이 어떻게 되시오?";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "네가 교수형에 처하거나 총으로 쏴 죽일 놈의 이름이 뭐가 그리 중요하냐? 이 개자식아! 결국 네 손에 잡힐 만큼 내가 방심했지...";
			link.l1 = "나리, 신분을 밝히시오. 이름도 모르는 자와는 대화할 수 없소.";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "Don "+GetFullName(npchar)+". 자, 이제 만족하나? 이제, 누구와 대화하게 된 영광이 있지?";
			link.l1 = "내 이름은 "+GetFullName(pchar)+". 전에 내 얘기 들어본 적 있나?";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "아니, 젠장! 내가 서인도 제도 돌아다니는 부랑자들 전부 아는 놈처럼 보여?\n";
			link.l1 = "그만하시오. 모욕은 그만두고 신사답게 행동합시다. 그대의 운명은 내게 무슨 말을 하느냐에 달려 있소. 흥미로운 이야기를 해 준다면, 내가 그대를 내 보호하에 풀어 달라고 청원하겠소. 그러면 지금 당장 닥친 총알이나 교수대에서 벗어날 수 있을 것이오.";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "세상에, 그건 거절할 수 없는 제안이군. 무엇을 알고 싶으신가, 나리?";
			link.l1 = "누가 이렇게 대규모로 생피에르를 공격하도록 조직한 거지, 그리고 그 이유는 무엇이지?";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "프로비던스 섬 주둔군 사령관 라몬 데 멘도사 이 리바 남작. 그가 우리에게 분견대를 보내 마을을 습격하고 약탈하며, 찾을 수 있는 귀중품을 모두 빼앗으라고 명령했지.";
			link.l1 = "공격 당시 네가 맡은 즉각적인 임무는 무엇이었지? 구체적으로 어떤 명령을 받았나?";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "나는 해병 대대의 지휘관이오. 우리 임무는 요새를 점령하고 포대를 확보하여, 상륙정이 마을에 접근할 때 그들이 사격하지 못하게 하는 것이었소. 그 후 내 부하들은 생피에르 공격에도 참여했소.";
			link.l1 = "도시에 있는 귀중품들에 대해 들었소? 그 수량과 품질에 대해서도 말이오?";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "정확한 양에 대한 정보는 없었지만, 멘도사 이 리바 남작이 우리에게 요새 아래에 은이 보관되어 있고, 항구 창고에는 전쟁에 필수적인 전략적 원자재인 철목과 선박용 비단이 있다고 말했소.";
			link.l1 = "그 귀중품들 찾았나?";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "아니. 둘 다 찾지 못했어. 창고에는 평범한 식민지 상품들만 가득했고, 요새 아래에는 화약과 무기, 납이 있었지. 하지만 더 철저하게 수색할 시간은 부족했어... 프랑스 증원군이 들이닥쳐서 전투를 벌일 수밖에 없었거든.";
			link.l1 = "귀중품을 못 찾은 게 이상하지 않았어?";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "물론 했지. 하지만 나는 보통 명령에 토 달지 않아.";
			link.l1 = "내가 지금부터 하는 말을 잘 들으시오. 생피에르 요새에는 은이 있었던 적이 없고, 그 창고들에도 철목이나 비단이 저장된 적이 없소. 대답하기 전에 곰곰이 생각하시오, 나리. 내 마음에 들지 않는 대답을 한다면, 나는 돌아서서 이곳을 떠날 것이오. 그러면 그대는 자신의 운명에 맡겨지겠지... 비참한 운명 말이오.";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "듣고 있소.";
			link.l1 = "네 습격의 유일한 목적이 단순한 약탈이었다고는 믿지 않네. 생피에르는 그리 눈에 띄지 않고 비교적 가난한 식민지라서, 일등 전열함이 이끄는 함대를 전부 보낼 이유가 없지. 분명 자네나, 자네의 상관, 혹은 다른 누군가가 추가 명령이나 지시를 받았을 거야. 무슨 말을 들었나? 대답하기 전에 신중히 생각하게나...\n";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "입 다물겠다고? 좋아. 잠깐 생각해 봐, 기다릴 테니까.";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "나리, 제 대답에 제 목숨이 달려 있습니까?";
			link.l1 = "맞소.";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "나한테 뭔가 있어... 하지만 여기서 날 꼭 데리고 나가 스페인으로 몸값을 치르고 돌려보내겠다고 맹세해야 해.";
			link.l1 = "내 관심을 끌 만한 말을 한다면, 나는 성십자가에 맹세코 너를 내 배에 태워 몸값을 받을 때까지 살려두고 처형은 면하게 해주겠다.";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "알겠소. 돈 디에고 데 몬토야가 우리 해병대에게 극비리에, 그리고 최대한 신속하게 미겔 디초소라는 자를 찾아내어 생포하라고 명령했소. 그자는 생피에르 어딘가에서 당국의 보호를 받고 있소.";
			link.l1 = "계속해. 디에고 데 몬토야가 누구지?";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "함대를 지휘하던 장교요. 당신의... 극적인 등장 직후 곧 도망쳤소.";
			link.l1 = "그 자가 누구지, 이 돈 디에고란 놈은?";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "나는 그가 멘도사 이 리바 남작의 공식 대리인이자, 그의 오른팔이자 중요한 임무를 맡는 대행자라는 것만 알고 있소.";
			link.l1 = "흥미롭군... 그런데 이 모든 재앙이 덫을 놓기 위해 꾸며졌다는 그 미겔 디초소란 자가 누구지? 꽤 위험한 놈인가 보지, 응?";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "맹세를 기억하시오, 나리?";
			link.l1 = "그래. 그리고 네가 계속해서 이야기를 한다면, 널 내 배로 데려가 주요 증인으로 삼을 거야. 그리고 나중에는... 뭐, 스페인 식민지로 데려갈 방법을 찾겠지. 하지만 네가 아는 모든 것을 말하기 전에는 안 돼.";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "미겔 디초소는 남작의 옛 전우였으나, 미겔이 그를 배신했다는 소문도 있소. 멘도사 이 리바 나리께서 미겔을 반드시 산 채로 데려오라 하셨으니, 어떤 상황에서도 디초소를 죽이지 말라는 명령을 받았소.";
			link.l1 = "디초소도 스페인 사람인가?";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "그래. 돈 디에고 데 몬토야가 우리에게 대략적인 인상착의를 알려주고, 디초소와 닮은 자가 있으면 곧장 자기에게 넘기라고 명령했지. 하지만 네가 반격해 오기 전까지 시간이 너무 짧아서, 우리가 수색할 기회는 없었어.";
			link.l1 = "직접 Dichoso를 알았소?";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "아니, 소문으로만 들었지. 그자를 직접 본 적은 없어. 내 동료 장교 몇몇은 그와 개인적으로 알던 사이였지. 그들 모두 죽었어.";
			link.l1 = "디초소가 도대체 얼마나 심하게 멘도사 돈을 배신했기에, 그를 쫓으려고 전대까지 보낼 생각을 한 거요?";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "말해주지. 남작은 얼마 전에야 스페인에서 카리브로 도착했네. 그의 임무는 스페인 보물선 호위대의 안전을 보장하는 것이었지만, 그는 내륙으로 눈을 돌렸지... 인디언의 금을 찾아서 말이야. 숨겨진 보물에 대한 소문에 마음이 흔들린 거지. 그는 유카탄 정글 깊숙한 어딘가에 고대 마야 도시, 전설의 황금 도시인 타야살이 존재한다고 믿게 되었네\n남작은 그 도시를 찾으려고 여러 차례 원정을 보냈지만, 모두 야생 셀바에서 완전히 전멸했지. 그곳에 사는 전투민족 이차족에게 하나도 남김없이 도륙당했음이 틀림없네\n결국 인퀴지터 빈첸토는 돈 멘도사의 망상과 쓸데없는 병사들의 죽음에 질려버렸지. 인퀴지터는 마드리드에 상황을 알렸고, 부왕은 돈 멘도사에게 신화 속 도시를 찾는 것을 금지하고 본연의 임무에 집중하라고 명령했네. 바로 그때 미겔 디초소가 나타났지\n그는 남작을 설득해 또 한 번의 원정을 조직하게 했고, 놀랍게도 이번엔 성공했네. 그들은 고대 도시의 폐허와 보석이 박힌 금 더미를 발견했지. 하지만 돌아오는 길에 모스키토 부족의 습격을 받았네\n미겔을 제외한 모두가 죽었지; 인디언의 화살촉에는 현지 독이 묻어 있어서, 작은 상처만 입어도 며칠 내에 고통스럽게 죽게 된다네. 디초소는 들고 올 수 있는 보물을 가지고 프로비던스로 돌아왔지\n카라호! 남작은 이루 말할 수 없이 기뻐하며 급히 마드리드와 산티아고의 빈첸토 신부에게 편지를 보냈네; 분명히 자신의 성공을 신부의 코앞에 들이밀고 싶었던 거겠지. 그리고 보물을 스페인으로 실어 보낼 프리깃이 준비됐네. 디초소가 호송을 자원했지.";
			link.l1 = "짐작해보지. 금을 전달하지 않았군?";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "맞소, 나리! 그 프리깃함은 디초소를 포함한 모든 화물과 선원들과 함께 흔적도 없이 사라졌소. 남작은 분노에 휩싸였지. 그는 다시 한 번 에스코리알 앞에서 망신을 당했고, 빈첸토 신부는 그걸 무척이나 흡족해했소. 이제 멘도사 돈은 상처 입은 자존심과 잃어버린 보물, 그리고 미겔 디초소를 되찾는 데 집착하는 사내가 되었소.";
			link.l1 = "프리깃함이 그냥 폭풍에 휘말려 침몰했거나, 아니면 해적들에게 붙잡혔을 가능성은 없소?";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "바론은 흥분한 나머지 디초소가 자신을 배신했다고 확신한다며 맹세했소. 자세한 내용은 모르오. 몇 주가 지난 후, 돈 디에고 데 몬토야가 미겔 디초소가 생피에르에 있을지도 모른다는 새로운 정보를 가지고 도착했소.";
			link.l1 = "흠. 흥미롭군. 또 그 인디언 보물인가. 모든 게 수상하게 그 보물과 얽혀 있는 것 같아... 그래서, 디초소를 못 찾았나?";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "아니오. 그리고 솔직히 그가 여기에 온 적이 있다면 내가 더 놀랄 거요. 남작은 디초소를 잡겠다는 생각에 너무 집착해서, 아무리 터무니없는 이야기라도 다 믿을 판이오.";
			link.l1 = "말해 보시오, "+npchar.name+", 도 멘도사가 이... 어... 타야살 도시 이야기를 어떻게 알게 된 거지? 그냥 꿈에서 본 건 아닐 테고, 무슨 증거나 다른 단서라도 있었나?";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = "테야살과 황금 도시의 존재에 대해 처음 들은 사람은 빈첸토 신부였소. 그가 어디서 그 소식을 들었는지는 나도 전혀 모르겠군...";
			link.l1 = "흥미로운 전개로군. 빈첸토 신부가 테야살의 존재에 대한 이론을 스스로 세우고, 스페인에 직접 알린 다음, 남작의 계획에 훼방을 놓기 시작했지...";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "같은 가톨릭 신자로서, 당신도 성스러운 심문소의 신부님들이 어떻게 움직이는지 알 테지... 그가 마드리드에 보고한 건 괜한 일이 아니야. 뭔가 꿍꿍이가 있는 모양인데, 남작의 도착은 그의 계획에 없었던 것 같아. 어쨌든, 그 이상은 나도 몰라. 나는 한 번도 종교재판소와 엮이고 싶었던 적이 없어.";
			link.l1 = "좋아. 흥미로운 정보를 많이 주었군, "+npchar.name+", 그리고 내 맹세대로, 널 여기서 데리고 나가겠다. 나중에 다시 오마, 하지만 지금은... 네가 한 말을 잠시 곱씹어보게...";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("Voice\English\Ransack_2.wav");
			dialog.text = "나리? 약속을 지키실 건가요?";
			link.l1 = "나는 항상 약속을 지키지. 오늘은 네 운 좋은 날이야, "+npchar.name+". 너는 나와 함께 쿠바의 산티아고로 간다네. 도착하면 내 계획에 대해 더 이야기해 주지. 하지만 지금은, 배에 탄 것을 환영하네. 항구까지 호위받아 내 배로 안내될 걸세.";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "감사합니다, 선장님. 약속을 지키는 신사라서 기쁩니다.";
			link.l1 = "감사는 나중에 해도 된다. 넌 내 손님이지만, 경호를 받게 될 거다.\n오해하지 마라, 아직 네가 필요하니까.";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "알겠소, 나리. 나는 스페인 장교로서 맹세하오, 도망치려는 시도는 결코 하지 않겠소.";
			link.l1 = "신중한 자를 신이 돌보시지. 배에서 보세.";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = "선장님, 쿠바에서 무슨 의도로 오셨습니까? 저를 여기 내려주러 오신 겁니까? 감히 그런 기대는 하지도 못하겠지만요...";
			link.l1 = "바로 그거요. 나는 당신을 동포들에게 돌려보내러 왔소. 하지만, 내가 여기 온 이유는 그보다 좀 더 복잡하오. 그러나 이제 그건 당신과는 상관없는 일이오. 지금 당장 몸값 없이 풀어주겠소, 하지만 두 가지를 맹세한다는 조건이 있소.";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "그게 뭐지?";
			link.l1 = "첫째는 내가 너에게 봉인된 편지를 줄 거라는 점이다. 그 편지를 산티아고의 종교재판관 빈첸토 신부에게 직접 전달해야 한다. 그가 그 편지가 누구에게서 왔는지, 어떻게 받았는지 묻거든, 사실대로 말하거라...\n";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "";
			link.l1 = "두 번째 조건은, 적어도 일주일 동안 나를 찾거나 내 배를 공격하려는 어떤 시도에도 협조하거나 돕지 않는 것이오. 동의하겠소?";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "그게 전부인가?";
			link.l1 = "그래, 그게 전부다. 내 조건을 이행하면 자유롭게 가도 된다.";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "맹세하오, 나리. 반드시 직접 빈센토 신부께 편지를 전할 것이며, 산티아고 주둔군이 당신이나 당신의 배에게 적대적인 행동을 하게 만들 어떤 일도 결코 하지 않겠소. 내 약속은 반드시 지키리다. 나는 스페인 사람이오, 강인하고 고귀한 적을 존중하지.";
			link.l1 = "알겠소, 돈 "+GetFullName(npchar)+", 나는 그대의 맹세를 받아들이고 지금 바로 풀어주겠소. 여기, 이 서신을 종교재판관에게 가져가시오. 이제 그대는 자유요.";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("You've given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "안녕히 가시오, 나리. 전장에서 다시는 만나지 않기를 바라오. 그리된다면 나는 몹시 슬플 것이오.";
			link.l1 = "안녕히 가시오...";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "세상에, 이런 행운이 또 있을까! 안녕하오, 나리 "+GetFullName(pchar)+"! 산티아고에서 환영받는 손님이 되셨군요. 성스러운 종교재판소를 위해 일하고 계십니까?";
			link.l1 = "안녕하시오, 나리 "+npchar.name+". 우리 다시는 못 볼 줄 알았어, 적어도 이렇게 우호적인 상황에서는 말이야! 아니, 나는 그냥 빈첸토 신부님을 뵈러 잠깐 들른 거야. 그런데 너는? 이제 산티아고에서 근무하고 있는 거야?";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "당신이 나를 체포에서 풀어준 후, 나는 산티아고에 머물 수밖에 없었소. 프로비던스로 돌아가는 건 내게 위험하오... 하지만 보다시피, 나는 약속을 지켰소. 당신을 뒤쫓는 스페인 배는 없으니...";
			link.l1 = "우리가 둘 다 약속을 지키는 사람이라서 기쁘군.";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "듣게, 선장. 말하자면 우리 재회를 기념해서 럼 한 잔 들지 않겠나? 프랑스 놈한테 이런 제안을 할 줄은 꿈에도 몰랐지만, 자네, 나리는 예외야.";
			link.l1 = "물론이지! 럼주로 입 좀 헹구는 것도 나쁘지 않겠군. 선술집으로 가자.";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "아, 살루!";
			link.l1 = "무엇을 위해 마시는 거요, 나리 장교?";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "우리 둘 다 관련 있는, 하지만 중립적인 것에 건배하세. 예를 들면, 각자의 조국을 위한 용감하고 성공적인 봉사 말이오! 우리 모두 각자의 나라가 있지 않소!";
			link.l1 = "그리고 우리 군주들께서 서로 합의에 이르시고, 프랑스와 스페인이 본국과 카리브 해에서 싸움을 멈추기를 위해서도 한잔하자.";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "잘 말했소, 선장! 평화를 위하여! 스페인식으로 술 마시는 법을 보여주겠소! 아리바, 아바호, 알 센트로, 이 빠 덴트로!";
			link.l1 = "평화를 위하여... (마시며)";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "아하! 쿠바 럼은 정말로 카리브 해에서 최고지...";
			link.l1 = "동의하오. 말해보시오, 생피에르에서 붙잡힌 일로 처벌을 받으려 한 자들이 있었소?";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "다행히도, 나는 가벼운 처벌만 받았지. 그 재앙은 이제 다 지난 일이야. 어차피 이 식민지엔 장교가 필요하거든.";
			link.l1 = "그리고 네 지휘관... 이름이 뭐였더라... 디에고 맞지? 그 헛된 습격은 그에게 어떻게 끝났나? 강등이라도 당했어?";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "이런, 이런! 우리 사랑하는 디에고 데 몬토야는 돈 라몬 데 멘도사 이 리바가 뒤에 있는 한 건드릴 수 없는 존재야. 그런데 말이지, 돈 디에고는 어제까지만 해도 산티아고에 있었어. 산호세에서 막 도착했지.";
			link.l1 = "정말인가? 흥미롭군! 길거리에서 마주치지 않은 게 다행이야. 그 일로 결투까지 갔을지도 모르거든, 하하!";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "지금은 돈 디에고가 당신에게 신경 쓸 시간이 없소, 선장. 지금은 목숨을 걸고 결투할 만큼 위험을 감수할 처지가 아니오. 서부 본토에서 멘도사 남작과 함께 무슨 계략을 꾸몄다더군. 아바나에서 함대를 모아 곧 스페인으로 돌아가려 하고 있소.";
			link.l1 = "너도 그 녀석 선원인가?";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "아니. 내일 나는 푸에르토리코에 있는 산후안 주둔지로 떠난다네. 이제 프로비던스에는 멘도사 돈이 있어서 더는 환영받지 못하지.";
			link.l1 = "그럼, 자네의 새 임지에 건배하세. 그곳엔 즐거운 일과 아름다운 아가씨들만 가득하길 바라네.";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "정말 감사합니다, 나리. 당신께도 온갖 좋은 일이 함께하길 바랍니다. 아, 이제 슬슬 가야 할 것 같군요. 이 술 한 잔만 마저 비우고 인사드리겠습니다.";
			link.l1 = "신의 가호가 함께하길, 나리 "+npchar.name+". 어쩌면 우리가 평화롭게 다시 만날 수도 있겠군.";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("Voice\English\other\OZGi-01.wav");
			dialog.text = "내가 말했잖소, 돈 디에고. 물고기가 미끼를 덥석 물었지, 바늘까지, 줄까지, 추까지 전부... 오, 또 만나는군, 나리. 유감스럽게도 우리가 바라던 평화로운 분위기에서가 아니오.";
			link.l1 = ""+npchar.name+"? 이런! 이럴 줄은 몰랐군. 왠지 그대가 정직하고 고귀한 장교라고 생각했었지. 내가 착각했나 보군.";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "무슨 근거로 자네가 옳다고 생각하지? 나는 약속을 지켰고, 자네에게 영원한 우정을 맹세한 적도 없네. 달라진 건 아무것도 없어, 나리. 자네는 여전히 에스파냐의 적이자 내 개인적인 원수일 뿐이야. 여기는 산티아고가 아니고, 빈첸토 신부도 없어. 그의 그 보잘것없는 통행증 따위로는 자네를 구할 수 없을 걸...\n";
			link.l1 = "오, 그런가? 럼주 한잔하면서 친근하게 대화하는 척하다가 나를 함정에 빠뜨리려는 건 꽤나 교활한 짓이라고 생각하지 않나, 나리\n "+npchar.name+"?";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "감히 나를 배신자라고 부르다니, 이 마리콘 녀석아?!";
			link.l1 = "...";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// посланец Винсенто
		case "vinsentoagent":
			PlaySound("Voice\English\other\OZGi-02.wav");
			dialog.text = "이봐, 너! 그래, 그래, 너 말이야! "+GetFullName(pchar)+"?";
			link.l1 = "그래, 이봐. 나야.";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "중요한 인물에게서 편지를 받았어. 누군지 이미 알고 있겠지.";
			link.l1 = "알아, 이리 줘.";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "자, 여기 있소. 내 수고에 동전 몇 닢 주는 건 어떻겠소?";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "은화 좀 가져가. 네가 정당하게 번 돈이야.";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "나한테 사기 치려고 하는 거냐, 이봐? 배달비는 이미 받았잖아.";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "고맙다, 친구. 이렇게 관대한 신사와 거래하게 되어 기쁘군.";
			link.l1 = "좋아, 꺼져. 여기서 무슨 일이 있었는지 한 마디도 꺼내지 마라.";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "아바나의 늑대는 네 친구야...";
			link.l1 = "어? 아직도 여기 있었어...";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		// боцман Гая Марше
		case "boatsvandega":
			dialog.text = "'아드미라블'호에 오신 것을 환영합니다, 선장님 "+GetFullName(pchar)+"!";
			link.l1 = TimeGreeting()+"! 놀랍군. 나를 아는가?";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "프랑스 식민지에서 위대한 선장이라는 이름을 들어보지 못한 사람이 어디 있겠소 "+GetFullName(pchar)+", 전함을 이끌고 생피에르를 공격하던 스페인 함대를 박살내고 적 습격대를 모조리 쓸어버린 그 사람! 당신은 나라의 영웅이오!";
			link.l1 = "아, 그만 좀 하시오. '영웅'이라니... 나는 그저 프랑스를 위해 임무를 다하는 병사일 뿐이오.";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "많은 병사들이 선장님처럼 해낼 수 있었다고는 생각하지 않소... 에이, 선장님께 선술집에서 럼주라도 한잔 대접하고 싶은데, 유감스럽게도 선장님께서 병사들에게 럼 한 방울도 마시지 말라고 금하셨으니, 내가 나쁜 본보기가 되고 싶지는 않소...";
			link.l1 = "흠... 그럼 자네는 직접 선장은 아니란 말인가?";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "내가 선장처럼 보여? 허허! 아니, 난 그냥 보선장이야. 이름은 세르주 드가. 우리 선장 가이우스 마르셰는 하루 종일 선술집에 처박혀 있고, 우리는 여기서 '상인' 무리를 기다리며 빈둥거리고 있지. 선장이 선원들 월급도 밀렸고, 우리도 마찬가지야, 선원들 전부가 한 푼도 못 받고 있다니까..\n ";
			link.l1 = "무슨 일 있나? 스페인 바닐라 상단이 털릴 시간인데 아직 안 나타났어?";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "말도 안 돼! 우리 선장은 이 갈레온을 나포한 뒤로 해적질을 그만뒀어. 있잖아, 유럽으로 가는 무역 캐러밴이 곧 과들루프에 들를 거라는 소문을 들었거든. 그들이 바닐라를 산다더라지. 그래서 브리지타운에서 우리 창고를 바닐라로 꽉 채웠지! 상자당 삼백 페소에 팔 수 있을 거라 생각했는데 — 퍽이나!\n물론 우리가 도착했을 때, 바닐라 캐러밴 따윈 없었고, 현지인한테 바닐라를 팔면 손해였지. 그래서 이렇게 '상인들'을 기다리고 있는 거야 — 언젠가는 오겠지, 아니면 삼 년 뒤에나... 선장은 하루 종일 선술집에 틀어박혀서 왕짜증을 내며 모두를 귀찮게 해. 배로 돌아오는 건 쓰러지러 올 때뿐이지. 이제는 본전만 건지려고 상자당 이백 페소에라도 팔 준비가 됐어.\n우리 돈은 전부 그 화물에 들어갔어. 언젠가는 선원들이 선장을 묶어서라도 바닐라를 헐값에 팔아 빚을 갚으려 들 거야... 맹세컨대, 그날이 곧 올 것 같아.";
			link.l1 = "아이... 선장님, 무슨 걱정이라도 있으신가?";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "일을 하려면 제대로 해야 하는 법이지. 그런데 저자는 둘 다 못 해. 흥정도 형편없고. 화물 운송이라도 제대로 했으면 또 모르겠는데, 괜히 진짜 상인인 척하고 싶었던 거야. 언젠가 밤에 갑판에서 굴러떨어지길 바란다...\n";
			link.l1 = "이해해, Serge. 걱정하지 마, 언젠가는 네... 대상이 나타날 거라고 확신해.";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "오, 나는 기적 같은 건 믿지 않소, 선장. 언젠가 다시 만나서 럼주나 한잔할 수 있겠지... 지금 당장이라도 럼 한 모금이면 뭐든 주겠는데...";
			link.l1 = "행운을 빌어, 친구야.";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// активируем каракку
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "이봐, 선장, 럼 한 모금 진짜 필요하다고!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// Гай Марше
		case "marshe_tavern":
			PlaySound("Voice\English\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("호! 자네 상선에서 온 사람 아니었나? 아니라고? 아, 미안하네. 물론 아니지... 내 실수였어.","지금은 기분이 아니니, 나리, 딴 사람한테 가서 말 걸도록 하시오.","아, 또 너냐?!","음...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("걱정하지 마, 친구. 그런 일도 있는 법이지.","럼 한잔 하시죠, 선장님. 조금이나마 근심이 덜어질 겁니다...","긴장하지 마, 친구. 건강에 안 좋아.","알겠어, 알겠어. 나 간다.",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("Voice\English\citizen\convict-03.wav");
			dialog.text = "아으... 으음... 이게 뭐야, 대체 뭐지?..";
			link.l1 = "조용히 해, 이봐... 소리 내지 마...";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("Voice\English\citizen\convict-02.wav");
			dialog.text = "어? 뭐야? 젠장!";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("Voice\English\EvilPirates07.wav");
			dialog.text = "아아악! 누구야? 나한테서 뭘 원하는 거지?";
			link.l1 = "입 다물지 않으면 이빨 다 부숴버릴 거야, 알아들었어? 이 배를 점령할 때 가져간 성물들은 어디 있지?";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "무슨 배? 무슨 소린지 하나도 모르겠어! 이건 내 배야!";
			link.l1 = "네 배라고? 얼마 전까지만 해도 그 배는 '산타 마르가리타'라 불렸고 스페인 깃발 아래 항해했지... 묻겠다, 그 성스러운 성물들은 어디 있나? 금으로 된 성광, 청금석이 박힌 십자가, 그리고 금향로 말이다. 그걸 어떻게 했지? 설마 팔아버린 건 아니겠지?";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "오, 맙소사, 내 귀를 의심하게 만드는군... 너 스페인 놈이냐? 아, 아니... 스페인 놈도 아니고 프랑스 놈이구나! 그게 더 최악이지! 네놈, 그 더러운 카스티야 놈들에게 영혼을 팔아넘겼군! 요즘 프랑스 놈들 영혼 값이 얼마냐? 난 아무것도 말 안 해, 배신자야! 그 장신구들은 절대 네 손에 못 들어가!";
			link.l1 = "한 마디도 안 하겠다는 건가? 뭐, 나야 상관없지. 어차피 여기서 심문하기엔 별로 좋은 장소도 아니니까... 네가 소리 지르지 못하게 입을 막을 거다. 그리고 내 작은 배로 가자... 결국엔 네 입에서 말이 나오게 될 거다. 그건 확신하지.";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "이 스페인 배신자 놈! 가만두지 않겠어...";
			link.l1 = "조용히 해라, 이 악당아... 내 뒤를 바로 따라오지 않으면, 널 때려눕혀서 발목을 잡고 갑판을 질질 끌고 다닐 거다.";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// капитан каракки - Карлос Геварра
		case "gevarra":
			dialog.text = "무엇을 도와드릴까요, 나리?";
			link.l1 = "어떻게 지내십니까, 선장님? 무슨 일로 바세테르에 오셨습니까? 내가 알기로는, 당신은 네덜란드 깃발 아래 항해하는 스페인 사람이라던데요?";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "무슨 문제라도 있소, 나리? 그래, 나는 스페인 사람이오. 내 이름과 내 배만 봐도 쉽게 알 수 있겠지. 하지만 나는 여기 합법적으로 와 있소. 네덜란드 서인도 회사의 허가증도 가지고 있으니...";
			link.l1 = "흥분하지 마시오, 나리! 사실 우리는 당신이 스페인 사람이라서 매우 기쁩니다... 자, 말씀해 보시오, 수입 때문에 오셨소, 아니면 수출 때문에 오셨소?";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "나는 아바나에서 상품을 가져와 현지 시장에서 팔았소.\n이제 빈 창고로 돌아가지 않으려고 이익이 될 만한 화물을 기다리고 있소.";
			link.l1 = "나리, 당신께 사업 제안을 하나 드리고 싶소! 저를 도와주시면 좋은 돈을 벌 수 있소. 이야기 좀 나눠볼까요? 그런데, 성함이 어떻게 되시오?";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "카를로스. 카를로스 게바라 선장이다. 제안이 뭐지?";
			link.l1 = "바닐라 한 묶음을 구입해서 쿠바에 있는, 이름이 \n인 남자에게 보내야 해 "+pchar.questTemp.Guardoftruth.LMname+", 산티아고 등대의 망꾼이오. 하지만 지금 심각한 문제가 있소. 우선, 내가 필요한 만큼의 바닐라를 가진 상점이 하나도 없소...";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = "";
			link.l1 = "둘째로, 나는 즉시 세인트 크리스토퍼로 떠나야 하오. 얼마나 오래 비울지 나도 모르니, 날마다 손해를 보고 있지 않겠소? 이거 정말 억울한 일이오!";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "알겠습니다. 안타깝군요, 나리. 세상 모든 돈을 가질 수는 없는 법이지요. 그래서 저에게 바라는 게 뭡니까?";
			link.l1 = "저기 좀 봐. 저 갤리온 보이지? 내가 정말 필요로 하는 바닐라로 가득 차 있지. 문제는, 그 갤리온 선장이 곧 향신료 대상단이 여기 도착해서 자기 화물을 한 상자에 거의 삼백 페소나 되는 이익으로 사갈 거라는 헛소리를 믿고 있다는 거야.";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "요즘 세상엔 순진한 남자들이 참 많지; 바보와 그의 돈은 금세 갈라지게 마련이지...";
			link.l1 = "순진한 거야 이해하겠는데, 저 녀석은 그냥 바보야! 내가 바닐라를 210페소에 사겠다고 했더니, 여기 가게에선 200도 못 받을 물건이거든. 그런데 믿어지나? 나보고 꺼지라고 하더군! 250페소 아니면 안 판다나!";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "하하! 참 바보구나!";
			link.l1 = "그래! 내가 그에게 한 말이 딱 그거였지. 물론 그가 나한테 화를 냈지만... 난 정말 그 바닐라가 필요하거든! 내 제안을 들어보시오, 나리. 나는 상인은 아니지만, 당신은 진정한 거래의 달인이라 생각하오. 그리고 당신 배의 창고도 넉넉하고...";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "저 멍청한 놈을 설득해서 화물을 네가 사도록 해. 내가 면전에서 모욕을 줬으니 이제 나한테는 절대 안 팔 거야. 상자당 210페소까지는 지불할 생각이야. 네가 값을 깎으면, 그 차액은 네가 가져도 돼. 그리고 그 대가로, 네 배를 빌려 바닐라를 산티아고까지 실어주게.";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "그 화물에 대해 나에게 얼마나 지불할 생각이지?";
			link.l1 = "얼마를 원하는가?";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "산티아고는 꽤 멀리 있지... 삼만 페소다.";
			link.l1 = "그건 너무하잖아, 아미고. 좀 봐주라.";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "좋아, 어차피 가는 길이니까... 이만오천, 한 푼도 깎아줄 수 없어.";
			link.l1 = "좋소. 갤리온의 선장은 가이우스 마르셰라는 자요. 하루 종일 선술집에서 뾰로통하게 앉아 있지. 그에게서 향신료를 넘기도록 설득할 수 있기를 바라오.";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "나는 예전에도 더 멍청한 놈들과 거래해 본 적 있지. 그에게 누가, 말도 안 되는 비싼 값에 물건을 사려고 했다는 대상단 소문을 퍼뜨리고 있는지 전부 얘기해 줄 거야.\n그게 다 자기 망상이라는 걸 확실히 믿게 만들면, 결국 팔 거야. 난 확신해.";
			link.l1 = "그럼, 거래하는 거지?";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "바닐라와 운송비를 지불할 현금만 있다면 거래 성사요. 매력적인 아일랜드 속담에도 있지 않소: '돈을 보여줘.'";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "여기 있어, 한번 봐. 다 들어있어.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "내 배에 은이 있어. 내가 가서 가져올게, 금방 돌아올 테니!";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "돈 가져왔나?";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "여기 있어, 한번 봐. 다 들어 있어.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "지금 바로 가져올게!";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "tomorrow";
				iTemp = 1;
			}
			else
			{
				sTemp = "today";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "훌륭하군! 나는 이성적인 동업자와 거래하는 걸 정말 즐기네. 다시 오게나 "+sTemp+" 아침 열 시까지. 그때쯤이면 우리 공동의 친구 가이우스도 정신을 차렸을 거라 생각하오.";
				link.l1 = "좋아! 나중에 보자!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "훌륭하군! 나는 이성적인 동업자와 거래하는 걸 참 좋아하지. 이제 나는 해안으로 간다네. 세 시간 후에 다시 오게. 그쯤이면 우리 공통의 친구 가이우스도 정신을 차렸을 거라 생각하네.";
				link.l1 = "좋아! 나중에 보자!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "나리, 제 역할은 잘 기억하고 있소. 걱정 마십시오, 그가 아무리 만만치 않아도 제가 반드시 굴복시키겠소.";
			link.l1 = "감사합니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "끝났소, 나리. 그 불쌍한 사내는 내가 그의 바닐라를 사겠다고 하니 너무 기뻐서 손이 떨릴 지경이었소. 내가 선금을 세어줄 때 그의 손이 행복에 겨워 떨렸소 – 아니면 그저 럼주 때문이었을지도 모르지. 항구의 세관원들에게 괜한 관심을 받지 않으려면 내일 정오에 캡스터 해변에서 화물을 싣기로 했소\n화물을 배에 싣는 즉시 산티아고로 바로 출항하겠소. 등대에서 당신의 동료와 접선해, 거기서 바닐라를 넘겨주고 서명할 것이오. 그에게 전할 메시지라도 있소?";
			link.l1 = "그래. 여기 편지가 있네. 내일 정오에 캡스터 해변에서 거래가 있을 거라고 했지? 알겠어, 그럼 나는 곶 근처에 닻을 내리고 섬에서 멀리 떨어져 대기하겠네, 만약 무슨 일이 생길 경우를 대비해서.";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("You handed the letter over");
			PlaySound("interface\important_item.wav");
			dialog.text = "나를 믿으셔도 됩니다, 나리. 나는 정직한 사람이오. 게다가 당신과 다툴 생각도 없고, 상인은 평판 없이는 아무것도 아니지요. 하지만 지켜보고 확인하고 싶으시다면, 나에게는 아무 어려움도 아니오.";
			link.l1 = "감사합니다, 나리. 내일 거래를 지켜볼 것이며, 당신이 출항하자마자 나는 세인트 크리스토퍼에서 내 일을 볼 것이오.";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "선장님, 장담합니다. 절대 실망시키지 않을 것이며, 우리 거래의 조건을 반드시 모두 이행하겠습니다.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// матросы Марше
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("히끅! 만세! 우리 좋은 선장님이 드디어 월급을 주셨다! 선장님 만세 삼창! 히끅!","파인트로도 나와?! 나도 한 잔 마실 거야!","우리 주머니는 두둑하고, 우리 여인들은 더 통통하길! 만세!","그리고 거기 누워 있었지, 모두 훌륭한 죽은 놈들, 힉! 술집 새벽녘처럼 말이야. 요호호, 그리고 럼 한 병!","요호호, 럼주 한 병이다!");
			link.l1 = LinkRandPhrase("그래, 이봐.","너 럼주 이미 충분히 마신 거 아니냐?","술과 악마가 나머지 놈들을 끝장냈지...");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "멈춰라! 누구냐? 경보! 적이 배에 올라탔다!";
			link.l1 = "...";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// англичане в бухте
		case "dominica_hunter":
			dialog.text = "하하! 너도 롤리 선장의 보물을 찾으러 왔구나? 우리는 계속 찾고 또 찾았지만, 도저히 못 찾겠더라. 이 멍청이들 중에 한 놈이라도 폭포 뒤로 헤엄쳐서 바위 턱으로 올라갈 생각을 했으면 좋겠는데!";
			link.l1 = "너, 폭스 대령 부하 중 한 명이지?";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "내가 바다여우단과 연이 있을지도 몰라. 너는 알 필요 없어, 알면 뭐하겠어. 지금은 아무것도 알 필요 없어. 네가 내 보물을 찾아냈으니, 이제 우리가 너한테 크게 감사해야겠군...";
			link.l1 = "알겠군. 넌 바다여우가 아니라, 차라리 바다개... 아니면 자칼에 가깝지. 뭐가 더 어울리냐?";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "녀석들, 우리한테 자연 철학자가 한 명 생긴 것 같군. 동물의 왕국에 대해선 아주 전문가야!";
			link.l1 = "내 검의 날카로움을 시험해 볼래, 자칼?";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Белинда Риберо
		case "belinda":
			dialog.text = TimeGreeting()+", 나리. 무엇을 도와드릴까요?";
			link.l1 = "안녕하세요. 도냐 벨린다 데 리베로이십니까?";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "네, 그렇소. 누구와 말씀을 나누는 영광을 누리고 있소?";
			link.l1 = "Captain "+GetFullName(pchar)+", 부인. 제 프랑스 성 때문에 불편해하지 마십시오; 지금 저는 산티아고의 고결하신 심문관 빈첸토 신부님의 임무를 수행 중입니다.";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "정말 흥미롭군! 나는 성심 재판소와 예수회에 온갖 계급과 국적의 사람들이 가득하다는 이야기를 들었지만, 지금까지 그곳에서 일하는 외국인을 직접 만난 적은 없었소. 내가 무엇을 도와주면 되겠소, 나리?";
			link.l1 = "당신은 신부님께서 매우 관심을 가지신 물건을 가지고 있소. 금으로 된 성광, 즉 당신이 최근 빌렘스타드의 은행가에게서 얻은 성체현시대 말이오.";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "정말 잘 알고 있군, 나리. 뭐, 그대가 누구를 위해 일하는지 알기에 놀랄 일도 아니지. 그래, 내가 성합을 샀다네. 그런 귀중한 물건이 도둑맞은 장신구나 전당포 물건들 옆에서 하찮은 잡동사니처럼 상점에 방치되어 있을 이유는 없지.";
			link.l1 = "성체현시대를 가지고 계십니까, 부인?";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "예. 원래는 우리 교구 성당에 그것을 기증하려 했으나, 여기서 너무 많은 일이 있었어요... 할 수가 없었어요... 아, 미안해요...";
			link.l1 = "부인, 우시고 계십니까? 제 말이 슬픔을 드렸습니까? 그렇다면 부디 용서해 주십시오.";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "아, 제발 나리... 우리 대화를 계속하지. 내가 알기로는 비첸토 신부께서 이 성광이 필요하신가? 내가 당신께 드릴까?";
			link.l1 = "이 귀중한 성배는 산티아고 대성당에 바쳐질 예정이었으나, 평범한 해적에게 빼앗겨 다른 성물들과 함께 고리대금업자에게 팔렸소. 내 임무는 도난당한 것을 제자리로 돌려놓는 것이오. 물론, 경비는 전액 보상해 드릴 것이오.";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "오, 그러시면 안 됩니다! 정말 이 돈이 저에게 그렇게 중요하다고 생각하십니까? 이 성체현시대는 성모 교회를 위해 산 것이니, 정당한 주인에게, 더군다나 빈첸토 신부님을 섬기는 예수회 회원에게라면 주저 없이 넘기겠습니다. 하지만 저를 깊이 괴롭히는 다른 일이 있습니다. 교회의 충실한 딸이 곤경에 처했으니, 도와주실 수 있겠습니까?";
			link.l1 = "당신은 귀부인이십니다, 부인. 무슨 고민이 있으십니까? 제가 어떻게 도와드릴까요?";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "아, 하지만 나리... 제가 예수회 형제님께 직접 도움을 청하다니 감히 못 하겠어요. 항상 너무 바쁘시잖아요...";
			link.l1 = "이미 했잖아. 무슨 일이야?";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "성스러운 교회의 대표로서, 내가 당신에게 부탁하는 일을 아무도 절대 알지 못하리라고 약속할 수 있습니까?";
			link.l1 = "엄숙히 맹세하오, 세뇨라. 고해성사의 비밀은 아니지만, 이 일에 대해 누구에게도 한마디도 하지 않겠소.";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "좋소. 그대를 믿겠소. 내 소중한 친구 에스테반 소사가 곤경에 처했소. 여행 중에 산적들에게 붙잡혔고, 그들이 백천 페소의 몸값을 요구하고 있소. 나는 그만한 돈이 없어 용돈을 모아 겨우 절반 정도만 마련했소. 이런 일로 누구에게 도움을 청할 수도 없소. 만약 그러면 그들이 그를 죽이겠다고 맹세했기 때문이오\n게다가 나는 내 소중한... 친구가 걱정되어 최악의 사태를 두려워하고 있소. 그들이 돈을 받자마자, 입막음을 위해 그를 죽일 수도 있지 않겠소. 어쩌면 그대처럼 용감한 선장이자, 신실한 그리스도인이며, 우리 단체의 형제라면, 내가 모은 돈을 받아들이고 그를 해치지 않도록 산적들을 설득할 수 있지 않겠소...";
			link.l1 = "교환은 언제, 어디서 이루어지지?";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "두목은 바르티 더 내커라는 놈이야. 그자가 에스테반의 몸값을 매일 밤 11시부터 자정까지 정글 동굴 입구에서 기다리겠다고 했어...\n";
			link.l1 = "그거 참 유난히 구체적인 조건들이군...";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "분명 그 자들은 내가 몸값 전부를 빨리 모으길 원했고, 누구에게도 도움을 청하지 않길 바랐던 것 같아... 하지만 그런 돈은 도저히 구할 수 없어, 평생 해도 못 할 거야!";
			link.l1 = "울지 마시오, 부인. 내가 도와드리도록 하겠소. 예수회 형제라면 결코 의로운 그리스도인 여인을 위험에 내버려두지 않을 것이오.";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "당신을 믿어야겠군요... 하지만 선장님, 바티 더 내커가 몸값을 가져오는 사람이 혼자 오지 않거나 제가 경비병들에게 가면 불쌍한 에스테반을 바로 죽이겠다고도 했어요!\n";
			link.l1 = "명심하겠소.";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "여기, 이걸 가져가. 내가 간신히 모은 오만 페소야. 저 도적놈들에게 적어도 이 돈이라도 받아 달라고 설득해 줘. 내가 가진 돈은 이게 전부라고 꼭 전해 줘! 에스테반을 꼭 데려와 줘! 그러면 기꺼이 빈센토 신부님께 드릴 성체함을 내주겠네.";
			link.l1 = "최선을 다하겠습니다, 부인. 좋은 결과를 바라지요.";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "신께서 도와주시길, 용감한 선장님! 당신을 위해 기도하겠습니다!";
			link.l1 = "...";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//закрыть карту
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = "소식이 있소, 선장?";
			link.l1 = "아직 아니오. 잠시만 기다리시오, 세뇨라. 실망시키지 않겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "소식이 있소, 선장?";
			link.l1 = "예, 부인. 유감스럽게도 좋은 소식이 아닙니다.";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "말해 줘, 기다리게 하지 말고! 산적들을 만났어?";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "자, 오만을 돌려주지. 필요 없었어. 이 반지도 가져가. 익숙할 거라 생각하네.";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "여기, 이 반지를 가져가시오. 익숙할 것이라 생각하오.";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "이건... 그래, 익숙해. 에스테반에게 무슨 일이 있었지?";
			link.l1 = "네가 말한 대로 동굴에서 그 악당들을 찾았어. '도살자 바르티'와 에스테반 소사는 같은 사람이야. 그는 너를 협박하려고 납치를 꾸몄지. 그리고 네... 관계에 대해서도 내게 말했어. 더 이상 너를 보고 싶지 않다고도 했어. 증거로 네가 그에게 준 반지도 가져왔어.";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "이건... 그래, 그래, 나도 알아. 에스테반에게 무슨 일이 있었지?";
			link.l1 = "동굴에서 그 도적들을 찾았소, 말씀하신 대로였지. 놈들이 나를 공격해서 묶고, 당신 돈을 빼앗아 갔소. '도살자 바르티'와 에스테반 소사는 같은 인물이오. 그가 당신을 협박하려고 납치를 꾸민 거요. 그는 당신과의... 관계에 대해 내게 말했소. 에스테반은 나를 풀어주며 이 반지를 증거로 주었소. 그는 당신이 다시는 자신을 볼 수 없을 거라고 했소.";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "I taught him a lesson, but I didn't kill him out of respect to you.";
			dialog.text = "세상에! 내 귀를 의심하겠군! 왜 이런 일들이 다 나한테 일어나는 거지, 도대체 왜?! 내가 그에게 뭘 했다고....\n";
			link.l1 = "나리, 제발 이 일로 자책하지 마십시오. 그 망나니는 나리의 눈물 한 방울도 아깝소. "+sTemp+"";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "And besides that, here's a gift to keep up your courage.";
			dialog.text = "오... 진정하도록 하겠소. 나리, 도와주셔서 감사하오. 자, 당신의 성광을 가져가시오. "+sTemp+" 신의 가호가 함께하길.";
			link.l1 = "감사합니다, 부인. 걱정 마십시오, 동굴에서 있었던 일은 아무도 알지 못할 것입니다. 저희 예수회는 항상 약속을 지킵니다. 이제 실례하겠습니다, 가봐야 하오.";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("You've received a gold ostensory");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("You've received an amulet");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// бандит Эстебана
		case "bandos_mush":
			PlaySound("Voice\English\other\OZGi-04.wav");
			dialog.text = "거기서 멈춰!";
			link.l1 = "나 여기 바로 서 있어.";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "돈 가져왔나?";
			link.l1 = "정말 어리석은 질문이군. 아니, 내가 여기서 망가 로사를 따러 나왔다고 생각하나... 내가 여기 온 이유가 뭐라고 생각하지?";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "오호호! 웃기는 녀석이군! 어서 동굴로 들어가라, 바티가 널 기다리고 있거든.";
			link.l1 = "분명히 경험 많은 경비군이군... 그 태도라면 필리프 왕 직접 호위해도 되겠어. 내가 알아서 들어가마.";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// Эстебан-Барти
		case "barty":
			PlaySound("Voice\English\other\OZGi-03.wav");
			dialog.text = "날 너무 오래 기다리게 했군... 돈은 가지고 왔나?";
			link.l1 = "너 바르티 더 내커냐? 내 눈엔 평범한 도적 같아 보이지 않는데.";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "내가 어떻게 생겼는지가 뭐가 그렇게 중요해? 피 같은 돈은 가져왔어, 아니면 어쩔 건데?";
			link.l1 = "인질은 어디 있지?";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "인질은 곧 넘겨주지. 자, 돈 내놔. 괜히 화나게 하지 마라, 꼬마야.";
			link.l1 = "바르티, 내가 바보로 보여? 에스테반 소사가 살아서 멀쩡히 있는 걸 내 눈으로 보기 전엔, 너한테 페소 한 푼도 안 줄 거야. 어디 있지?";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "오, 끝까지 버티겠다는 거냐? 좋아, 제대로 맛 좀 보여주지... 얘들아, 이 똥꾸멍 새끼 혼쭐내 주자!\n";
			link.l1 = "개자식!";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// офицеров насильно
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //офицеров пускать
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("Voice\English\other\Plennie-02.wav");
			dialog.text = "";
			link.l1 = "이 정도면 춤은 충분하지? 에스테반 소사는 어디 있지? 어서 말해, 아니면 네 머리를 물에 처박아서 거품이 안 나올 때까지 눌러버릴 거야!";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "안 돼... 제발 나를 해치지 마! 나는 에스테반 소사야.";
			link.l1 = "뭐?";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "그래, 그래. 난 바티 도살꾼 같은 놈이 아니야. 난 그냥...";
			link.l1 = "이 악당아! 그래서 네놈이 스스로를 '납치'해서 리베로 부인에게서 십만 페소를 뜯어내기로 한 거냐?!";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "나를 이해해 줘야 해, 남자 대 남자로 말이야. 벨린다는... 그 집착적인 사랑 때문에 정말 질렸어. 밤낮으로 나한테 들러붙는다고, 이봐! 심지어 그녀 남편도 우리 사이를 의심하기 시작했어, 그 양반은 반쯤 장님인데도!";
			link.l1 = "이런, 그거 참! 그래서, 너희 둘이 연인 사이란 말이지?";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "이제 아니야. 방금 그녀에게서 도망쳤어.";
			link.l1 = "길에 쓸 동전 좀 챙기기로 했나, 응? 이제 너를 어쩌면 좋을까? 네가 나한테 하려던 것처럼 네 시체를 정글에 숨겨야 하나?";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "안 돼! 피를 원한 게 아니었어, 맹세해!";
			link.l1 = "그래서 나한테 부하들을 풀어놓은 거요?";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "우린 그냥 네 주머니나 뒤져보려고 했을 뿐이야, 그게 다라고!";
			link.l1 = "그리고 나를 셀바에 알몸으로 버려두라고? 내 배에서 제일 높은 돛대에 널 매달아버려야 마땅하지, 이 악당아! 하지만 그러지 않겠다. 네 꼴을 보다 불운하게도 너와 엮인 그 착한 여인을 존중해서 말이지. 있잖아? 내가 널 그 여자에게 데려가서, 네 운명을 그녀가 결정하게 해야겠군.";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "안 돼, 그것만은 싫어! 쿠마나로 다시는 안 돌아갈 거야!";
			link.l1 = "영원히 이 동굴에 남고 싶다는 거야?";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "살려주시오, 나리! 제발 보내주시면 여기서 떠나 다시는 쿠마나에 돌아오지 않겠소! 벨린다의 남편이 결투에서 저를 베어버리거나 암살자를 보내는 걸 기다릴 생각 없소!";
			link.l1 = "좋아. 리베로 부인을 위해서, 널 그녀에게 데려가진 않겠다. 하지만 이 일이 그냥 넘어갈 거라고는 꿈도 꾸지 마라. 그녀는 자기가 추근댄 그 한심한 놈이 누구였는지 반드시 알게 될 거다. 그녀가 알아볼 만한 증표라도 있나?";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "여기. 이 터키석 반지 말이야. 그녀가 직접 내게 줬어.";
			link.l1 = "완벽하군. 이리 내놔, 그리고 내 눈앞에서 꺼져!";
			link.l1.go = "barty_15";
			// belamour legendary edition -->
			link.l2 = "완벽하군. 그리고 있잖아, 소사, 내 마음이 바뀌었어 - 이제 나는 예수회에 봉사하지. 성경에도 이렇게 쓰여 있지, '너희 가운데서 악한 자를 내쫓으라.' 너야말로 사악한 나르시시스트이자 범죄자, 그리고 쓸모없는 쓰레기지. 내 생각엔 이 동굴에서 너를 익사시키는 게 좋겠군. 평안히 잠들어라.";
			link.l2.go = "barty_15a";
		break;
		
		case "barty_15a":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Sosa", 1.0); 
		break;
			
		case "barty_15":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			// <-- legendary edition
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// охотники
		case "spa_hunter":
			dialog.text = "우리가 필요한 걸 가졌군...";
			link.l1 = "정말인가? 그게 뭔데?";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "묻지도 않았어, 부잣집 도련님. 난 네가 가진 모든 걸 죄다 가져오라는 명령만 받았거든. 쉽게 할래, 어렵게 할래? 선택은 네 몫이야.";
			link.l1 = "네가 전사라고 생각하나? 네가 누구랑 상대하는지 전혀 모르는군. 너 같은 놈은 아침밥으로도 모자라지.";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "꽤나 익살꾼이구나, 개구리 녀석? 좋아, 그럼 네 피가 땅에 흐르는 모습 한번 보자고!";
			link.l1 = "네 것도 똑같이 생겼거든, 바보야. 해부학 강의라도 해줄까!";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "허허, 좋아, 친구... 당장 주머니 뒤져 봐! 얌전히 말 잘 들으면 멀쩡히 살아남을 수 있을 거야, 알겠어?";
			link.l1 = "젠장, 또 너희들이냐? 여기까지 따라온 거야? 도대체 누가 너희를 고용한 거지?!";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "네 알 바 아니다. 이제 항복해서 살든가, 아니면 덤벼서 죽은 뒤에 우리가 네 전리품을 챙기든가 해라. 이 정도면 괜찮은 거래 아니냐?";
			link.l1 = "내가 역제안을 하지. 네 시체에서 전리품을 가져가는 건 어때?";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// командир абордажников
		case "batabano_officer":
			dialog.text = "명령만 내리십시오, 선장님!";
			link.l1 = "정글을 지나 산 안토니오 곶으로 가라. 왼쪽 길로 들어서서 곧장 가라. 머리를 숙이고, 해안에서 매복에 대비해라. 준비해라. 나는 바다로 그리로 가서 거기서 만나겠다. 거기까지 가는 데 얼마나 걸릴 것 같나?";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "여섯 시간 후면 도착합니다, 선장님!";
			link.l1 = "좋아. 움직여!";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// на мыс
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// на время, специально для дебилов, не читающих диалоги и СЖ
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// наёмник Патерсона
		case "housemercen":
			dialog.text = "질긴 놈이군! 아직도 살아 있다니... 화약을 더 썼어야 했다는 걸 알았지! 좋아, 좋아, 내가 끝장내주마, 이 개자식아...";
			link.l1 = "...";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			bDisableCharacterMenu = false;//разлочим F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
