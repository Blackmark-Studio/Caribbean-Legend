void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold, NextMonth;
	string attrL, sStr, Month;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "무슨 일이라도 있습니까?";
			link.l1 = "아니, 아무것도 아니야.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// диалоги в ПУ
		case "SharlieEpilog_Pikar_1":
			dialog.text = "이거, 이게 누구야! "+GetTitle(NPChar,true)+" "+pchar.lastname+" 실제로!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				link.l1 = ""+npchar.name+"! 아니, 너를 여기서 다시 볼 줄은 정말 몰랐어... 솔직히 아직 살아 있을 거라고는 생각도 못 했거든!";
				link.l1.go = "SharlieEpilog_Pikar_2";
			}
			else
			{
				link.l1 = "내 눈을 믿을 수가 없어... 잘생겼다고? 그런데... 어떻게?";
				link.l1.go = "SharlieEpilog_PikarResurrected_1";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\LE\Rocur\Rocur_03.wav");
		break;
		
		case "SharlieEpilog_Pikar_2":
			if (IsStateTitle())
			  {
				dialog.text = "하하! 뭐, 그렇게 걱정할 필요 없었지. 보다시피 나는 멀쩡하게 잘 살아 있어. 기분 좀 내려고 멋지고 '깨끗한' 배도 하나 장만했지. 그런데 너는... 말해 봐, 어떻게 이렇게 된 거야, 친구?";
			  }
			  else 
			  {
				dialog.text = "하하! 뭐, 그렇게 걱정할 필요 없었지. 보다시피 난 멀쩡하게 잘 살아 있어. 내 기분 좀 내려고 '흠 하나 없는' 작은 배도 장만했지. 그런데 너는... 자, 여기까지 온 이유가 뭐야, 친구?";
			  }
			link.l1 = "여기서 말고. 선술집으로 가자—일은 나중에 해도 돼.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_1":
			dialog.text = "쉬... 소리 지를 필요 없어. 그 잘생긴 애는 사라졌어, 아마 그 왕자처럼 말이야. 그치?";
			link.l1 = "하지만 내 두 눈으로 똑똑히 봤어...";
			link.l1.go = "SharlieEpilog_PikarResurrected_2";
		break;

		case "SharlieEpilog_PikarResurrected_2":
			dialog.text = "내가 어떻게 끝장났냐고? 그렇게 간단했으면 좋겠지, 친구. 내 말 믿어.";
			link.l1 = "선술집으로 가자. 거기서 다 말해 줘.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_Captain_1":
			dialog.text = "...";
			link.l1 = "그래서, 이제 그 핀네스 '"의 새 주인인가"+GetShipName("Ulysse")+"'?'";
			link.l1.go = "SharlieEpilog_Captain_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\z_arest_02.wav");
		break;
		
		case "SharlieEpilog_Captain_2":
			dialog.text = "나. "+GetFullName(npchar)+", 그렇게 궁금하다니. 그런데 너는 누구지?";
			link.l1 = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+", 그리고 이 배를 당신에게서 사고 싶소.";
			link.l1.go = "SharlieEpilog_Captain_3";
		break;
		
		case "SharlieEpilog_Captain_3":
			dialog.text = "물론이지, 물론이야, 네 소문은 들었어. 이 배를 노리는 자들은 이제 다 따돌린 줄 알았는데. 유감이지만, 널 실망시켜야 할 것 같군. "+GetTitle(NPChar,true)+" - '"+GetShipName("Ulysse")+"'은 이제 내 것이니, 곧 저 배를 타고 보르도로 항해할 거야. 첫 거래부터 망치려고 장사에 뛰어든 건 아니거든. 그건 불운을 부르는 짓이야, 알지?";
			link.l1 = "보르도라고 했나? 흥미롭군... 어쩌면 자네에게 이익이 될 만한 제안이 있을지도 모르겠어. 럼주 한 잔 하면서 이야기해 볼까?";
			link.l1.go = "SharlieEpilog_Captain_4";
		break;
		
		case "SharlieEpilog_Captain_4":
			dialog.text = "럼이나 좋은 제안을 거절하는 건 내 성격이 아니지. 가자.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		// диалоги в таверне
		case "SharlieEpilog_Pikar_5":
			if (IsStateTitle())
			  {
				dialog.text = "그럼, 당신을 위해, "+GetTitle(npchar,false)+" "+pchar.lastname+". 너 같은 녀석이 티락스의 심부름이나 오래 할 리 없다고 생각했지. 그런데 이렇게 큰 인물이 될 줄이야... 정말 나를 깜짝 놀라게 하는구나, 젠장.";
				link.l1 = "하하. 누가 할 소리인데. 그래서, 이제 상인이 되기로 한 거야?";
			  }
			  else 
			  {
				dialog.text = "다시 만난 걸 축하하오! 우리가 또 마주칠 것 같은 예감이 들었소.";
				link.l1 = "하하. 그녀에게! 그래서, 이제 상인이 되기로 한 건가?";
			  }
			
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;

		case "SharlieEpilog_Pikar_6":
			dialog.text = "글쎄, 평생 목숨 걸고 두블룬 몇 닢 위해 살 수는 없지. 적당한 사람에게 뇌물 좀 주고, 입 다물어야 할 놈들만 조용히 시키면—그렇게 나는 도둑도 해적도 아닌, 존경받는 상인이 되는 거야.";
			link.l1 = "이거 참, 예상 밖이군. 이제 막 새로 임명된 피나스 선장에게 제안하려던 걸 어떻게 꺼내야 할지 모르겠네."+GetShipName("Ulysse")+"'."";
			link.l1.go = "SharlieEpilog_Pikar_7";
		break;

		case "SharlieEpilog_Pikar_7":
			dialog.text = "아, 그만 좀 돌려 말하고 그냥 솔직하게 말해. 우리 서로 안 지 얼마나 됐는데.";
			link.l1 = "있잖아... 내가 여기 카리브 해에 온 것도 네가 인수한 피나스 덕분이야. 그 배가 경매에 나온다는 소식을 듣고, 내가 직접 값을 흥정해서 프랑스로 다시 가져가고 싶었거든.";
			link.l1.go = "SharlieEpilog_Pikar_8";
		break;

		case "SharlieEpilog_Pikar_8":
			dialog.text = "하하하하! 잠깐만... 아하하하하하!..";
			link.l1 = "그래서, 뭐가 그렇게 웃긴데?";
			link.l1.go = "SharlieEpilog_Pikar_9";
		break;

		case "SharlieEpilog_Pikar_9":
			dialog.text = "경매에서 내가 이기자마자 저 멋쟁이가 다가오더군—젊고 잘 차려입은 친구였지—자기랑 짐을 보르도로 데려다 달라면서 꽤 두둑한 돈을 제시했어. 그리고 그게 단순한 돈이 아니라, 자그마치 한 자루 가득한 동전이었지.";
			link.l1 = "그래? 하하. 정말 재미있군. 그래서 어떻게 했지? 동의했어?";
			link.l1.go = "SharlieEpilog_Pikar_10";
		break;

		case "SharlieEpilog_Pikar_10":
			dialog.text = ""+pchar.name+", 뭐, 대서양 한 번 건너는 걸로 금덩어리를 마다할 바보는 아니지. 그치? 몇 달 동안 딱딱한 건빵이랑 소금에 절인 고기나 씹어야겠지만, 사실 그보다 훨씬 적은 걸로도 목숨을 걸어본 적 있으니까. 그러니 당연히 할 거야.";
			link.l1 = "그렇다면, 같은 제안을 하겠소. 나를 보르도로 데려가면, 똑같은 금화를 받게 될 것이오.";
			link.l1.go = "SharlieEpilog_Pikar_11";
		break;

		case "SharlieEpilog_Pikar_11":
			dialog.text = "승객이 될 준비는 됐어? 규칙 알지 – 배에는 선장이 한 명뿐이야. 그리고 내 배에서는 그게 바로 나야.";
			link.l1 = "왜 안 되겠어? 숨 좀 돌리고, 인생에 대해 생각도 해보고. 어쩌면 정말 정착해서, 이 들뜬 영혼을 좀 가라앉혀야 할지도 모르지. 지금은 상상이 잘 안 되지만, 뭔가 이유가 있긴 하겠지. 결국 너조차도 전투에서 멀어지기로 했으니까.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Pikar_12_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Pikar_12";
			}
		break;
		
		case "SharlieEpilog_Pikar_12_wife":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				dialog.text = "아, 나도 자네처럼 아름다운 아내가 있다면 바다를 포기하고 어디 조용한 곳에 정착해서 집도 짓고, 와인 장사나 좀 하며 살았을지도 모르지. 이제는 그럴 여유도 있네—자네가 나를 스페인 놈들 손아귀에서 구해준 뒤로는 한순간도 허투루 쓰지 않았으니까.";
			}
			else
			{
				dialog.text = "아, 나도 자네처럼 아름다운 아내가 있었다면, 아마 바다를 떠나 한적한 곳에 정착했을 걸세. 집도 짓고, 포도주 장사도 좀 하면서 말이야. 그리고 그 플랜터 과부의 유산까지 있으니, 먹고사는 데는 아무 걱정 없겠군.";
			}
			link.l1 = "아내라니! 젠장, "+npchar.name+", 아직 그녀에게 그 이야기는 하지 않았어.";
			link.l1.go = "SharlieEpilog_Pikar_13_wife";
		break;
		
		case "SharlieEpilog_Pikar_13_wife":
			dialog.text = "그건 나중에 해도 돼. 나는 내 낡은 배부터 제대로 손봐야 하거든. 네 일 다 끝내면 이리로 와. 우리가 출항하기 전에 성대한 연회를 열자고.";
			link.l1 = "그래, 이제 좀 낫군! 걱정 마, 오래 기다릴 필요 없을 거야.";
			link.l1.go = "SharlieEpilog_Pikar_14_wife";
		break;
		
		case "SharlieEpilog_Pikar_14_wife":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_1");}
			else {AddQuestRecord("SharlieEpilog", "11_5");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_12":
			dialog.text = "아, 만약 내가 아내가 있었다면 바다를 떠나 어디 한적한 곳에 정착해서 집을 짓고, 포도주나 좀 팔며 살았을지도 모르지. 하지만 지금은... 바다가 내 집이야.";
			link.l1 = "내 소유 농장에서 직접 만든 와인이라네, 하하! 보르도에서, "+npchar.name+", 저 아가씨들은 정말 눈이 즐거울 정도라니까! 어쩌면 거기서 마음에 드는 연인을 찾을 수도 있을 거야 – 사랑의 기술이 아주 능숙하거든. 있잖아, 생각해보니까 앞으로 몇 달 동안 우리가 보게 될 얼굴은 네 선원들뿐이잖아. 출항하기 전에 현지 사창가에서 제대로 한 번 잔치를 벌여야 하지 않겠어?\n";
			link.l1.go = "SharlieEpilog_Pikar_13";
		break;
		
		case "SharlieEpilog_Pikar_13":
			dialog.text = "그리고 자네, 나리, 뭘 제안해야 할지 정확히 알고 있군. 일이 정리되면 얼른 여기로 돌아와. 그럼 우리가 창관으로 갈 거야—믿어도 돼.";
			link.l1 = "좋아, 그럼 시간 낭비하지 말고 바로 시작하자!";
			link.l1.go = "SharlieEpilog_Pikar_14";
		break;
		
		case "SharlieEpilog_Pikar_14":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_2");}
			else {AddQuestRecord("SharlieEpilog", "11_6");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_3":
			dialog.text = "자유를 위하여!";
			link.l1 = "그리고 자네에게도, Jean! 죽음에서 돌아온 걸 축하하네! 아직도 믿기지가 않아. 어떻게 된 일인가?";
			link.l1.go = "SharlieEpilog_PikarResurrected_4";
		break;

		case "SharlieEpilog_PikarResurrected_4":
			dialog.text = "그놈들이 나를 전장에서 질질 끌고 갔지—간신히 살아 있었고, 머리부터 발끝까지 피범벅이었어. 날 막사에 내던지고는 썩은 고기처럼 죽으라고 내버려뒀지. 노예들 중에 머리 좋은 녀석이 하나 있었어—모코라는 녀석. 그 녀석이 내 목숨을 구했지. 내 셔츠 조각으로 상처를 동여매고 물도 줬어.";
			link.l1 = "그 모든 일 후에 스페인 놈들이 널 그냥 살려뒀단 말이야?";
			link.l1.go = "SharlieEpilog_PikarResurrected_5";
		break;

		case "SharlieEpilog_PikarResurrected_5":
			dialog.text = "보시다시피요. 하지만 그들이 그렇게 한 건 결코 선의에서가 아니었어요. 복수를 원했죠—심문, 고문. 불태우고, 때리고, 베고. 내 눈을 태워 없애겠다고 협박했어요—정말이지 저에 대한 깊은 애정에서 나온 행동이었죠. 그런데 누군가 해적들이 저를 위해 복수할 거라는 소문을 퍼뜨렸고, 벌써 칼을 갈고 있다는 얘기까지 돌았어요. 플랜테이션 주인은 신경이 곤두서서 몸을 떨기 시작했죠. 우리 동료들이 찾아오기 전에 기다리지도 않고, 급히 캄페체에 있는 자기 영지로 도망쳤어요. 저랑 모코, 그리고 다른 사람들도 데리고 갔죠. 목격자를 남기지 않으려고요. 나머지 사람들에겐 제가 죽었다고 전했고—그걸로 끝이었어요.";
			link.l1 = "그 다음엔 어떻게 됐어? 어떻게 빠져나온 거야? 도대체 어떻게 여기까지 오게 된 거야?";
			link.l1.go = "SharlieEpilog_PikarResurrected_6";
		break;

		case "SharlieEpilog_PikarResurrected_6":
			dialog.text = "운이었지, 친구. 그저 눈먼, 더러운 운이었어. 날 플랜테이션으로 보냈고—고문은 계속됐지. 그 자식은 내가 고통받는 매 순간을 음미하려 들었지만, 날이 갈수록 점점 약해졌어... 결국 열병이 그를 죽이고 말았지. 그 뒤로는 아무도 나한테 신경 쓰지 않았어. 소처럼 들판으로 내몰렸고, 채찍질할 기회만 있으면 절대 놓치지 않았지.";
			link.l1 = "아직도 네가 거기서 어떻게 빠져나온 건지 이해가 안 돼?";
			link.l1.go = "SharlieEpilog_PikarResurrected_7";
		break;

		case "SharlieEpilog_PikarResurrected_7":
			dialog.text = "크리스토퍼 밍스에 대해 들어봤나?";
			link.l1 = "알론소가 뭔가 말했었지... 캄페체 습격 말이야! 그때 정말 스페인 놈들 제대로 혼쭐냈다더군. 그래서 그 사람들이 널 풀어줬던 거야?";
			link.l1.go = "SharlieEpilog_PikarResurrected_8";
		break;

		case "SharlieEpilog_PikarResurrected_8":
			dialog.text = "정확히는 아니야. 우리가 스스로 탈출했지. 경비병들이 영국 버커니어들과 싸우는 동안, 모코랑 나는 병영 지붕을 통해 빠져나갈 길을 찾아내서 반란을 일으켰어. 우리는 무기고와 죽은 그 개자식 플랜터 부인의 금고를 손에 넣었지.";
			link.l1 = "금고라고?! 이거 참 뜻밖이군.";
			link.l1.go = "SharlieEpilog_PikarResurrected_9";
		break;

		case "SharlieEpilog_PikarResurrected_9":
			dialog.text = "우리는 고민할 시간도 아까워서 바로 무기와 보급품을 챙겨 정글로 들어갔다. 이틀 동안 덤불을 헤치며 나아가다가 카안 페치 인디언 마을을 발견했다. 그들의 주술사는 스페인인들에게 순종하는 척했지만, 사실 별로 신경 쓰지 않았다. 모코가 그와 금세 의기투합해서, 우리는 무기 절반과 앞으로 닥칠 전쟁에서 도와주겠다는 약속을 대가로 그들에게 받아들여졌다. 그렇게 나는 그곳에서 1년 반을 살게 되었다.";
			link.l1 = "Jean, 예전의 네가 아니구나. 이제부터 넌 럭키다.";
			link.l1.go = "SharlieEpilog_PikarResurrected_10";
		break;

		case "SharlieEpilog_PikarResurrected_10":
			dialog.text = "하하. 신경 안 써. 그 뒤에 프랑스 신부가 우리 바타빌에 오게 됐지. 우리는 곧 알아챘어. 이건 족쇄 없이 여기서 빠져나갈 기회라는 걸. 우리는 그를 호위하던 사람을 매수했고, 곧 토르투가로 항해하게 됐어.\n그리고, 아마 짐작했겠지만, 나는 더 이상 죽음과 술래잡기하는 게 질렸다고 결심했지. 예전 일은 그만두고… 운 좋게도, 내 배를 하나 샀어."+GetShipName("Ulysse")+"'.\n"+"너는? 어떻게 이렇게 된 거야? 너처럼 대담한 녀석이 오래도록 Tyraks의 심부름꾼으로 남아 있을 리 없다는 건 항상 알고 있었지. 그런데 이렇게 큰 인물이 될 줄이야... 정말 넌 끝없이 나를 놀라게 하는구나, 젠장.";
			link.l1 = "하하. 누가 할 소리인데. 그래서, 이제 상인이 되기로 한 거야?";
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;
		
		case "SharlieEpilog_Captain_5":
			dialog.text = "바다에 있는 이들에게!";
			link.l1 = "그리고 행운의 여신께!";
			link.l1.go = "SharlieEpilog_Captain_6";
		break;

		case "SharlieEpilog_Captain_6":
			dialog.text = "그치? 이제 본론으로 들어가자. 나한테 무슨 제안을 하고 싶었던 거야?";
			link.l1 = "보르도로 가는군요... 사실 저도 그리로 가는 중입니다.";
			link.l1.go = "SharlieEpilog_Captain_7";
		break;

		case "SharlieEpilog_Captain_7":
			dialog.text = "내가 태워주길 원하는 거야? 내가 알기로는 네 배가 따로 있잖아. 어쩌면 함대까지 있을지도 모르고. 그런데도 남의 배를 타기로 한 거네. 내가 맞지?";
			link.l1 = "그래, 맞아. 최근 일들을 겪으면서 이제 닻을 내리고 정착할 때가 된 건 아닌가 생각하게 됐어... 네 배에서 그냥 승객으로 지내보면 새로운 삶의 속도에 익숙해질 수 있을지 알 수 있을 것 같아.";
			link.l1.go = "SharlieEpilog_Captain_8";
		break;

		case "SharlieEpilog_Captain_8":
			dialog.text = "흠... 그래서 이제 더 이상 아무 이유 없이 목숨을 거는 게 지겨워졌나? 그 기분 나도 잘 알지. 나 역시... 뭐, 됐다. 네 자리는 배에 마련되어 있고, 네 일행 모두도 마찬가지다. 이미 어떤 젊은 멋쟁이가 네 항해 비용을 다 치렀으니, 속도도 추가로 지불했더군. 그러니 화물은 싣지 않을 거다. 대금에 관해서는...\n";
			link.l1 = "걱정 마시오, 선장님. 나는 당신 고용주만큼이나 관대하니, 같은 금액을 지불할 준비가 되어 있소.";
			link.l1.go = "SharlieEpilog_Captain_9";
		break;

		case "SharlieEpilog_Captain_9":
			dialog.text = "훌륭하군! 그럼, 거래가 성사된 거요?";
			link.l1 = "거래 성사! 이건 한잔할 만하지!";
			link.l1.go = "SharlieEpilog_Captain_10";
		break;

		case "SharlieEpilog_Captain_10":
			dialog.text = "그래, 이 럼주 정말 괜찮네... 배를 제대로 손보고 필요한 물자를 다 채우려면 이 주일은 걸릴 거야. 그다음에 출항할 수 있어.";
			link.l1 = "그럼 2주 후에 여기서 다시 만납시다.\n자, 다음에 또 봅시다, 선장.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Captain_11_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Captain_11";
			}
		break;
		
		case "SharlieEpilog_Captain_11_wife":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_3");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Captain_11":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_4");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "자, 친구, 모든 일 다 정리했나? 이제 이 닭장에 제대로 노는 법을 보여줄까?";
				link.l1 = "아직 아니오, "+npchar.name+", 아직 처리해야 할 일이 조금 남아 있소.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "선장님, 배에 오를 준비가 되셨습니까?";
				link.l1 = "안타깝게도, 친구여, 아직 처리해야 할 일이 남아 있네.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_Pikar_WaitInTavern";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				// только если знаком с Пикаром и поговорил с женой
				link.l2 = "이봐, 주인장! 모두에게 술 한잔씩 돌려라, 내가 쏜다! 그리고 아무 술이나 말고, 제일 좋은 걸로 가져와!";
				link.l2.go = "SharlieEpilog_Pikar_WaitInTavern_2";
			}
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern_2":
			dialog.text = "...";
			link.l1 = "우리에게, 친구여. 짠 바람과 끝없는 바다, 그리고 영원히 부르고 또 영원히 닿을 수 없는 수평선에…";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_FrameInSea":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_FrameInSea");
		break;
		
		case "SharlieEpilog_Mary_1":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", 자기야, 아버지에 대해 이야기하고 싶어.";
			link.l1.go = "SharlieEpilog_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_2":
			dialog.text = "무슨 일이야, 자기야? 그 사람 괜찮길 바래, 그치?";
			link.l1 = "글쎄, 기대만큼 좋지는 않네. 아버지께서 오래 버티시지 못할 것 같다는 생각이 들고, 마지막 길을 떠나시기 전에 나를 보지 못할까 봐 깊이 괴로워하고 계셔.";
			link.l1.go = "SharlieEpilog_Mary_3";
		break;

		case "SharlieEpilog_Mary_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "알아요, 내 사랑, 알아요... 하지만 그게 인생이죠. 당신이 그분을 만날 수 있으면 좋겠어요. 내가 얼마나 훌륭한 아내를 뒀는지 보여드리고, 우리에게 축복을 내려주셨으면 해요.";
			link.l1.go = "SharlieEpilog_Mary_4";
		break;

		case "SharlieEpilog_Mary_4":
			dialog.text = "그 사람이 날 마음에 들어 하지 않으면 어쩌지, 그치? 난 귀족 출신도 아닌데...";
			link.l1 = "말도 안 돼, "+npchar.name+", 어떻게 당신을 안 좋아할 수 있겠어요? 당신은 정말 멋진 사람이에요! 제 마음을 사로잡았다면, 아버지 마음도 사로잡을 수 있을 거예요.";
			link.l1.go = "SharlieEpilog_Mary_5";
		break;

		case "SharlieEpilog_Mary_5":
			dialog.text = "정말 그렇게 생각해요, 자기야? 그럼 최대한 빨리 그분께 가야겠네요.";
			link.l1 = "바로 그걸 할 생각이야. 우리 배도 이미 구해 놨어. 이주 후에 출항한다.";
			link.l1.go = "SharlieEpilog_Mary_6";
		break;

		case "SharlieEpilog_Mary_6":
			dialog.text = "배? 우리 배로 항해하는 게 아니야?";
			link.l1 = "아니요, 내 사랑. 우리는 피나스선 '"을(를) 타고 항해할 거예요\n"+GetShipName("Ulysse")+"'. 나는 이 배를 타고 카리브에 왔으니, 이 배를 타고 떠날 것이오.'";
			link.l1.go = "SharlieEpilog_Mary_7";
		break;

		case "SharlieEpilog_Mary_7":
			dialog.text = "그리고 이제 선장이 아니게 되는 건가?";
			link.l1 = "조만간 이 역할을 내려놓아야 했을 거야. 잠시뿐이길 바라. 그래도 앞으로 내게 어떤 미래가 기다리고 있는지 미리 알아두는 것도 나쁘지 않겠지.";
			link.l1.go = "SharlieEpilog_Mary_8";
		break;

		case "SharlieEpilog_Mary_8":
			dialog.text = "그럼 우리 장교들은 어떻게 하지? 전부 데리고 갈 수는 없잖아. 그리고 여기서 당신을 기다릴 것 같지도 않은데.\n";
			link.l1 = "음... 그래, 네 말이 맞아. 모두 한 명씩 만나서 이야기해야겠지, 그리고 아마 영영 작별 인사를 해야 할 거야. 우리가 함께 겪은 일들을 생각하면 쉽지 않겠지만 말이야.";
			link.l1.go = "SharlieEpilog_Mary_9";
		break;
			
		case "SharlieEpilog_Mary_9":
			dialog.text = "작별 파티라도 선술집에서 열어 볼까?";
			link.l1 = "나도 그 생각 해봤어, 자기야. 있잖아... 네 말이 맞는 것 같아. 사실 좋은 생각이야.";
			link.l1.go = "exit";
			link.l2 = "그건 좋은 생각이 아닌 것 같아. 성대한 작별 인사는 생략하자... 이게 모두에게 더 나을 거야. 가까운 친구들만 초대하는 게 어떨까...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		case "SharlieEpilog_Helena_1":
			dialog.text = "...";
			link.l1 = "여보, 아버지에 대해 이야기하고 싶어요.";
			link.l1.go = "SharlieEpilog_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_2":
			dialog.text = "물론이지, "+pchar.name+". 무사하길 바라는데?";
			link.l1 = "정확히는 아니야. 아버지는 꽤 오랫동안 병을 앓으셨고, 곧 병세가 더 악화될까 봐 걱정돼... 아버지는 모든 걸 용감하게 견디고 계셔. 정말로 아버지를 괴롭게 하는 건 나를 다시는 못 볼지도 모른다는 생각뿐이야. 아버지를 찾아뵙고 싶어... 그리고 너를 아버지께 소개해 드리고 싶어. 우리 결혼에 대한 축복도 받고 싶고.";
			link.l1.go = "SharlieEpilog_Helena_3";
		break;

		case "SharlieEpilog_Helena_3":
			dialog.text = "그분을 만나게 되어 기쁠 거야, 내 사랑. 언제 출항해?";
			link.l1 = "2주 후야. 하지만 그게 다가 아니야.\n우린 우리 배로 항해하지 않아. 핀네스가 우릴 구세계로 데려다줄 거야. "+GetShipName("Ulysse")+"' - 바로 나를 이곳에 데려왔던 그 사람이지.'";
			link.l1.go = "SharlieEpilog_Helena_4";
		break;

		case "SharlieEpilog_Helena_4":
			dialog.text = ""+pchar.name+", 하지만 긴 항해를 앞두고 배를 바꾸는 건 불운을 부르는 일이오.";
			link.l1 = "배는 바꾸지 않을 거예요, 내 사랑. 우리는 승객으로 갈 거예요.";
			link.l1.go = "SharlieEpilog_Helena_5";
		break;

		case "SharlieEpilog_Helena_5":
			dialog.text = "하지만... 자기야, 나는 이해가 안 돼...";
			link.l1 = "원래 그렇게 되어야 하는 거야, "+npchar.name+". 언젠가는 내가 선장 자리에서 물러나야 할 테지. 그리고 미리 내가 어떤 감정을 마주하게 될지 알고 싶어.";
			link.l1.go = "SharlieEpilog_Helena_6";
		break;

		case "SharlieEpilog_Helena_6":
			dialog.text = "그게 당신의 결정이라면... 하지만 우리 장교들은 어쩌죠? 전부 데려갈 수는 없어요. 그리고 그들이 여기서 당신을 기다리고 싶어 할 것 같지도 않은데요.";
			link.l1 = "음... 그래, 네 말이 맞아. 한 명 한 명 직접 만나서, 아마 영영 작별 인사를 해야겠지. 우리가 함께 겪은 일들을 생각하면 쉽지 않을 거야.";
			link.l1.go = "SharlieEpilog_Helena_7";
		break;
			
		case "SharlieEpilog_Helena_7":
			dialog.text = "작별 파티라도 선술집에서 열어볼까?";
			link.l1 = "나도 같은 생각을 하고 있었어, 자기야. 있잖아... 정말 그게 우리가 해야 할 일인 것 같아. 정말 좋은 생각이야.";
			link.l1.go = "exit";
			link.l2 = "그건 좋은 생각이 아닌 것 같아. 성대한 작별 인사는 생략하자... 이게 모두에게 더 나을 거야. 가까운 친구들만 초대하는 건 어떨까...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		// Диалог с Алонсо в таверне Сен-Пьера
		case "SharlieEpilog_AlonsoInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				dialog.text = "선장님... 이미 주점 주인한테 말해 놨어요 – 제일 좋은 술을 준비해 뒀대요. 언제 시작할까요?";
				link.l1 = "지금 당장이다! 이봐, 주인장! 모두에게 술 한잔씩 돌려라, 내가 쏜다!";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_1";
			}
			else
			{
				dialog.text = "선장님, '율리시스'에 대해 어떻게 알게 되었는지 이야기해 주기로 약속하셨잖아요.";
				link.l1 = "기억나, 기억나. 이봐, 주인장! 이 테이블에 제일 좋은 럼을 가져와.";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_3";
			}
			link.l2 = "너무 이르군, "+npchar.name+". 아직 처리해야 할 급한 일이 남아 있습니다.";
			link.l2.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_AlonsoInTavern";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_1":
			dialog.text = "...";
			link.l1 = "자, 친구여, 다른 녀석들도 불러와. 우리가 진짜 바다의 사나이들이 어떻게 축하하는지 생피에르에 보여 주자!";
			link.l1.go = "SharlieEpilog_AlonsoInTavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_AlonsoInTavern_2":
			dialog.text = "하하! 선장님, 믿기지 않으시겠지만 – 내가 벌써 그들을 불렀어요!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_FrameInSea";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_3":
			dialog.text = "...";
			link.l1 = "우리에게, "+npchar.name+". 행운의 여신과, 우리의 돛을 가득 채우는 바람을 위하여!";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		// На пинасе Улисс
		case "SharlieEpilog_Alonso_1":
			dialog.text = "우리가 제대로 한 판 벌였네, 선장. 하하. 선술집이 완전히 박살나지 않은 건 주인장이 몰래 숨겨둔 럼주 덕분인 것 같아.";
			link.l1 = "상기시키지 마시오, "+npchar.name+", 이제서야 좀 나아진 기분이야.";
			link.l1.go = "SharlieEpilog_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "SharlieEpilog_Alonso_2":
			dialog.text = "원하시는 대로 하겠습니다, 나리 "+pchar.lastname+". 하하. 그래도 적어도 우리는 마르티니크를 왕족처럼 떠났지. 거기선 당신의 출항 이야기가 오래도록 회자될 거야.";
			link.l1 = "우리가 주점 주인을 작은 배에 태워서 르 프랑수아로 술을 더 사 오라고 보낸 건 좀 지나쳤던 것 같군.";
			link.l1.go = "SharlieEpilog_Alonso_2_1";
		break;
		
		case "SharlieEpilog_Alonso_2_1":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2)
				{
					dialog.text = "하하하. 그 사람 걱정은 하지 마시오. 며칠 사이에 금을 잔뜩 벌어서, 이제는 플랜테이션 하나쯤은 살 수 있을 거요—어쩌면 작위까지 따라올지도 모르지.";
				}
			else
				{
					dialog.text = "하하하. 그 사람 걱정할 필요 없어. 요 며칠 사이에 그는 플랜테이션을 살 만큼, 그리고 그에 어울리는 작위까지 살 만큼의 금화를 벌었으니까. 다만 네가 장교들하고 한 번도 이야기해보지 못했다는 게 아쉬울 뿐이야. 그들이 그리울 거야.";
				}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;
		
		case "SharlieEpilog_Alonso_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
				{
					sld = CharacterFromID("Helena");
					locCameraFromToPos(-8.97, 6.39, -12.78, true, -8.54, 4.94, -13.90);
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
				{
					sld = CharacterFromID("Mary");
					locCameraFromToPos(-3.62, 4.03, 2.30, true, -4.98, 2.62, 3.26);
					// locCameraFromToPos(-4.13, 4.23, 2.55, true, -5.71, 2.54, 3.58);
				}
				dialog.text = "그런 것 같군, "+sld.name+" 밤의 절반이나 사라졌던 일 때문에 아직도 너에게 화가 나 있어.";
			}
			else
			{
				dialog.text = "그리고 그 상인 일은... 정말 너무 심했어요, 선장님.";
			}
			link.l1 = "제기랄, 내가 왜 Jean이랑 그 동네 가게를 기웃거렸던 거지…";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;
		
		case "SharlieEpilog_Alonso_4":
			dialog.text = "어떻게 안 잡혔지? 그랬으면 정말 웃겼을 텐데 - "+GetTitle(PChar,true)+" 와인 몇 병을 훔치려다 잡혔다.";
			link.l1 = "재미있다고 생각하는군, "+npchar.name+", 그리고 절반도 기억이 안 나. 이렇게 많이 마신 건... 음... 사실 한 번도 없었지.";
			link.l1.go = "SharlieEpilog_Alonso_5";
			locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
		break;
		
		case "SharlieEpilog_Alonso_5":
			dialog.text = "자, 그럼 좋은 시작을 위해 건배하지, 선장. 하하. 꽤 즐거웠어. 또 해도 되겠는걸. 그래서, 언제 다시 돌아간다고 했지?";
			link.l1 = "우리 짐 좀 확인해 줄래? 다 챙겼나? 나는 나중에 내려갈게—지금은 창고 안 공기가 나한테 별로 좋지 않을 것 같아.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_UlysseInSea_8");
		break;
		
		// диалог с Алонсо у горы золота
		case "SharlieEpilog_Alonso_11": // этап 1
			dialog.text = "...";
			link.l1 = "저것 좀 봐... 배가 정말 심하게 당했네.";
			link.l1.go = "SharlieEpilog_Alonso_12";
			SharlieEpilog_GoldInTheDeck_1_1();
		break;
		
		case "SharlieEpilog_Alonso_12":
			dialog.text = "여기 금이 산더미처럼 쌓여 있어요, 선장님!";
			link.l1 = "그렇군, "+npchar.name+". 이 모든 걸 선원들이 보기 전에 바로 상자에 숨겨야 해. 저런 유혹은 필요 없으니까.";
			link.l1.go = "SharlieEpilog_Alonso_13";
		break;
		
		case "SharlieEpilog_Alonso_13":
			dialog.text = "아니, 참을 수가 없어...";
			link.l1 = "뭐라고?";
			link.l1.go = "exit";
			locCameraFromToPos(-1.28, 7.70, -10.26, true, 0.74, 5.42, -9.49);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_2");
		break;
			
		case "SharlieEpilog_Alonso_21": // этап 2
			dialog.text = "...";
			link.l1 = "이봐, 너 왜 그래?";
			link.l1.go = "SharlieEpilog_Alonso_22";
			// SharlieEpilog_GoldInTheDeck_6();
		break;
		
		case "SharlieEpilog_Alonso_22":
			dialog.text = "...";
			link.l1 = "일어나, 어서. 참 좋은 때를 골랐구나...";
			link.l1.go = "SharlieEpilog_Alonso_23";
		break;
		
		case "SharlieEpilog_Alonso_23":
			dialog.text = "함께 하자, 선장.";
			link.l1 = "일어나, 그만 장난쳐.";
			link.l1.go = "SharlieEpilog_Alonso_24";
		break;
		
		case "SharlieEpilog_Alonso_24":
			dialog.text = "긴장 풀어. 그냥 느끼기만 하면 돼.";
			link.l1 = "그치? 네 뜻대로 해. 이제 비켜.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_7");
		break;
		
		case "SharlieEpilog_Alonso_31": // этап 3
			dialog.text = "나는 항상 이걸 해보고 싶었어...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_32";
			SharlieEpilog_GoldInTheDeck_10();
		break;
		
		case "SharlieEpilog_Alonso_32":
			dialog.text = "멋진 기분이지, 선장?";
			link.l1 = "하하하. 그냥 카리브에 와서 형님 안부만 확인하고 갈 줄 알았는데, 이게 무슨 일인가. 아버지도 이런 결말은 상상도 못하셨겠지. 하하!";
			link.l1.go = "SharlieEpilog_Alonso_33";
		break;
		
		case "SharlieEpilog_Alonso_33":
			dialog.text = "Sir "+GetTitle(NPChar,false)+" "+pchar.lastname+"... 하하! 자네가 처음 군도에 도착했을 때 어땠는지 기억하나?";
			link.l1 = "물론 기억하지. 하하. 지금 갑판을 거들먹거리며 돌아다니는 저 녀석처럼 나도 한때 멋 부리던 놈이었다니, 참 믿기지 않는군. 이 빌어먹을 카리브 해에서 정말 많은 일이 있었지… 음모, 언데드, 쿠쿨칸 형제까지…\n";
			link.l1.go = "SharlieEpilog_Alonso_34";
		break;
		
		case "SharlieEpilog_Alonso_34":
			dialog.text = "운이 정말 좋으셨군요, 선장님. 그런 큰돈을 벌고도 살아남다니… 그걸 해내는 사람이 얼마나 되겠습니까.";
			link.l1 = "그래, 그치? 이제 빈둥거리는 건 그만하자. 누가 우리를 진짜로 알아보면 곤란하잖아.";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_11");
		break;
		
		// диалоги в катсцене с брашпилем
		case "SharlieEpilog_windlass_1":
			dialog.text = "...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "이봐, 친구, 난 이 배의 윈들라스 안전장치가 마음에 안 들어. 너무 믿을 수가 없거든. 누가 실수로 건드리기라도 하면 금방 빠질 수 있잖아.";
			}
			else
			{
				link.l1 = "듣으세요, 선장님, 이 배의 윈들라스 안전장치는 마음에 들지 않습니다. 너무 믿을 수가 없어요. 누가 실수로 쉽게 건드릴 수도 있겠군요.";
			}
			link.l1.go = "SharlieEpilog_windlass_2";
			locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
		break;
		
		case "SharlieEpilog_windlass_2":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "아, 그만해, "+pchar.name+", 배에서는 모두가 다 안다니까…";
			}
			else
			{
				dialog.text = "아, 그만해요, 선장님. 누가 그런 생각이나 하겠어요...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_windlass_3");
		break;
		
		case "SharlieEpilog_windlass_3": // диалог Пикара и дворянина
			dialog.text = "이봐, 이 멍청아... 도대체 뭘 하는 짓이야? 아무도 네 서툰 발을 쓸데없는 데 들이밀지 말라고 안 가르쳤냐?";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_4";
			locCameraFromToPos(-10.28, 9.94, -22.90, true, -9.29, 7.86, -21.36);
			NPCsLookEachOther("SharlieEpilog_Pikar", "SharlieEpilog_Bernard_Clone");
			CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Bernard_Clone"));
		break;
		
		case "SharlieEpilog_windlass_4":
			dialog.text = "...";
			link.l1 = "진정해, 너무 흥분하지 마! 나는 귀족이니, 이런 건 용납 못 하오…";
			link.l1.go = "SharlieEpilog_windlass_5";
		break;
		
		case "SharlieEpilog_windlass_5":
			dialog.text = "내 배에서는 네가 아무것도 아니야. 내 선원들이 여기선 너보다 더 많은 권리를 가지고 있지. 그러니 조용히 있고 방해하지 않든가, 아니면 내가 직접 너를 바다에 던져버릴 거다.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_6";
		break;
		
		case "SharlieEpilog_windlass_6": // диалог Пикара и Шарля
			dialog.text = "...";
			link.l1 = "하하하. 마치 내가 내 자신을 밖에서 바라본 것 같군.";
			link.l1.go = "SharlieEpilog_windlass_7";
			SharlieEpilog_windlass_9_1();
		break;
		
		case "SharlieEpilog_windlass_7":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "무슨 소리를 하는 거야?";
				link.l1 = "그치, 상관없어. "+npchar.name+". 우리 승객에게 너무 심하게 굴지 마. 이 모든 게 아직 그에겐 낯설잖아. 우리도 하루아침에 바다의 노련한 사내가 된 건 아니었으니까.";
			}
			else
			{
				dialog.text = "무슨 소리야?";
				link.l1 = "신경 쓰지 마시오, "+npchar.name+". 그리고 그 손님을 너무 심하게 판단하지 마시오. 이 모든 게 그에게는 처음이오. 결국 우리도 처음부터 바다 사나이는 아니었으니까.";
			}
			link.l1.go = "SharlieEpilog_windlass_8";
		break;
		
		case "SharlieEpilog_windlass_8":
			dialog.text = "저 재주로는 선원이 되기는커녕 캡스턴에 더 엉켜버릴 게 뻔하지. 그런 생각을 하다니, 참…";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "누가 알겠소, 누가 알겠소. 나는 이 군도에 도착할 때도 여전히 아무 걱정 없고, 호기심 많으며, 거만한 젊은이였지.";
			}
			else
			{
				link.l1 = "누가 알겠어. 내가 처음 이 군도에 도착했을 때도 나 역시 똑같이 걱정 없고, 호기심 많고, 오만한 청년이었지.";
			}
			link.l1.go = "SharlieEpilog_windlass_9";
		break;
		
		case "SharlieEpilog_windlass_9":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "그래, 그치, 비교가 되겠냐고.\n"+"기다려\n"+"그래서 자네가 그 녀석에게서 자신을 본다는 건가? 하하하. 그럼 자네가 돌봐 주게. 나는 애 봐줄 생각 없네.";
				link.l1 = "내가 그를 지켜볼게. 적어도 네가 그를 산 채로 가죽 벗길 때까지는 말이야.\n하지만 그는 닻값은 전부 치러야 해.";
			}
			else
			{
				dialog.text = "그래서 그 녀석에게서 네 자신을 봤다는 거야? 하하. 그럼, 선장, 이제 그 녀석은 네 책임이야. 내가 더 이상 애 봐주진 않을 거다.";
				link.l1 = "내가 그를 지켜볼게. 적어도 네가 산 채로 그의 가죽을 벗길 때까진 말이야.\n하지만 닻에 관해서라면—그 값은 제대로 치르게 해.";
			}
			link.l1.go = "SharlieEpilog_windlass_10";
		break;
		
		case "SharlieEpilog_windlass_10":
			dialog.text = "닻을 내려라. \n바람을 기다려라. \n진로를 유지해라.";
			link.l1 = "...";
			link.l1.go = "exit";
			SharlieEpilog_windlass_10();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_1");
		break;
		
		// диалоги Старшего матроса и Алонсо		
		case "SharlieEpilog_AlonsoTrollingHighSailor_2": // Алонсо
			dialog.text = "";
			link.l1 = "닻을 올려라. 바람을 받아라. 북동쪽으로 항로를 잡아라.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_3";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_3": // Старший матрос
			dialog.text = "";
			link.l1 = "닻 올려라! 앞돛 내리고, 바람을 잡자. 모두 일해라...";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_4";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_4": // Алонсо
			dialog.text = "";
			link.l1 = "뭐 하고 있어?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_5";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_5": // Старший матрос
			dialog.text = "";
			link.l1 = "뭐 하고 있어?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_6";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_6": // Алонсо
			dialog.text = "";
			link.l1 = "아니, 뭐 하는 거야?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_7";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_7": // Старший матрос
			dialog.text = "";
			link.l1 = "아르... 뭐 하는 거야? 고참 선원이 선장 명령을 다시 전하고 있잖아.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_8";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_8": // Алонсо
			dialog.text = "";
			link.l1 = "그래서 고참 선원은 그냥 그들을 따라 말하지.";
			link.l1.go = "exit";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_2");
		break;
		
		// Шарль ругает Алонсо
		case "SharlieEpilog_AlonsoTrollingHighSailor_9":
			dialog.text = "...";
			link.l1 = "진정해, Alonso. 우리는 여기서 그냥 승객일 뿐이야. 잊었어?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_10";
			locCameraFromToPos(-8.00, 4.49, -1.91, true, -9.97, 2.64, -1.90);
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_10":
			dialog.text = "크흠... 미안해, 선장. 나도 모르게 그랬어\n그래도 후회 안 해. 옛날로 돌아간 기분이었거든.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_5");
		break;
		
		// Диалог Шарля с Пикаром о всяком (можно попасть в Поместье де Монпе)
		case "SharlieEpilog_PikarOnUliss":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... 무엇을 도와드릴까요?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A"))
				{
					link.l1 = "그래, 친구, 기분이 어떤가?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_A_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_B"))
				{
					if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
					{
						link.l2 = "인정해, "+npchar.name+", 티락스에서 벗어나기로 결심했을 때 이미 상인이 되려고 계획하고 있었지, 그렇지?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
					else
					{
						link.l2 = "인정해, "+npchar.name+", 그때 이미 플랜테이션에서 상인이 될 생각을 하고 있었던 거요?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_C"))
				{
					link.l3 = "어떤 사자가 나에게 말을 걸려 했던 건 분명히 기억나오. 하지만 아무리 생각해도 무슨 이야기였는지는 전혀 기억이 나지 않소. 혹시 이 일에 대해 아는 것이 있소?";
					link.l3.go = "SharlieEpilog_PikarOnUliss_C_1";
				}
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_E"))
				{
					link.l1 = "보르도에 가본 적 있으신가요, 선장님?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_E_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_F"))
				{
					link.l2 = "선장님, 솔직히 말해서 우리가 마르티니크를 어떻게 떠났는지 거의 기억이 나지 않습니다.\n누군가에게서 중요한 편지를 받기로 되어 있었는데, 결국 받지 못한 것 같아요.\n혹시 이 일에 대해 누가 선장님께 이야기한 적 있습니까?";
					link.l2.go = "SharlieEpilog_PikarOnUliss_F_1";
				}
			}
			link.l4 = "산들바람이 불기 시작한 것 같군. 이제 출항할 시간이야. (바다로 나간다)";
			link.l4.go = "SharlieEpilog_PikarOnUliss_D_1";
			link.l5 = "아직 아무 소식도 없어. 내가 다녀올게.";
			link.l5.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_A_1":
			dialog.text = "하하... 이보다 더 좋을 수 없지! 힘도 넘치고 건강도 최고야.";
			link.l1 = "정말이야? 상어한테 씹혔다 나온 사람처럼 보여.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_A = true;
		break;

		case "SharlieEpilog_PikarOnUliss_A_2":
			dialog.text = "누가 할 소리래. 너야말로 채찍질당한 개처럼 보이거든.";
			link.l1 = "나도 똑같이 느껴. 하하. 젠장, 우리가 언제 어떻게 출항했는지도 기억이 안 나네.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_3";
		break;

		case "SharlieEpilog_PikarOnUliss_A_3":
			dialog.text = "아, 정말 멋진 파티였지. 다만, 악마처럼 돈이 많이 들었어. 내 바보들이 거의 사창가에 불을 낼 뻔해서, 소문이 퍼지지 않게 금화 자루를 내줘야 했지. 이제 그 멍청이들은 평생 나한테 빚진 셈이야.\n그래, 손님 신세는 어때? 아직 심심해서 울부짖기 시작하진 않았겠지?";
			link.l1 = "이제 내 운명이 더 이상 내 손안에 있지 않은 것 같아. 그런데도 동시에 이상하게도 안도감이 들어. 마치 어깨에 짊어졌던 포탄 상자를 이제 막 내려놓은 기분이야.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_4";
		break;

		case "SharlieEpilog_PikarOnUliss_A_4":
			dialog.text = "하하. 그래, 혹시라도 심심해지면 언제든 내 장교로 받아줄 준비가 되어 있어.";
			link.l1 = "정말 후하시군요만, 사양해야겠습니다. 카리브 해 전체의 럼주를 다 모아도 우리의 흥을 채우기엔 부족할 테니까요.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_1":
			if (IsStateTitle()) 
			{
				dialog.text = "정확히는 아니야, 친구. 가끔 그런 생각이 스쳤지만, 딱히 신경 쓰진 않았지. 그런데 한 번 더 그 생각이 떠올랐어. Tyrax의 충직한 개 떼가 흔적도 없이 사라졌다는 소문을 들었거든. Cleaver, Baldy, 그리고 그 늙고 냄새나는 놈 Leprechaun까지 전부 말이야.\n그리고 네가 이룬 모든 일들에 대한 이야기를 들었을 때, 드디어 결심이 섰지. 언제까지나 동전 몇 푼 때문에 목숨을 걸 순 없잖아.\n이제는 금도 충분히 모았으니, 분가루 바른 자식들 앞에서 비굴하게 굽실거릴 필요도 없어. 하지만 바다를 떠난다는 건... 아직 마음의 준비가 안 됐더군. 그래서 새로운 일을 택했지.";
			} 
			else 
			{
				dialog.text = "정확히는 아니야, 친구. 가끔 그런 생각이 스치긴 했지만, 별로 신경 쓰지 않았지. 그런데 어느 날 소문을 들었어—Tyrax의 충직한 개 무리가 흔적도 없이 사라졌다는 거야. Cleaver, Baldy, 그리고 그 늙은 악취 나는 Leprechaun까지, 전부 다 말이야.\n그리고 적의 포탄이 한 전투에서 두 번이나 내 머리를 날려버릴 뻔했을 때, 드디어 이제는 그만해야겠다고 결심했지. 동전 몇 푼 때문에 목숨을 계속 내놓을 순 없잖아.\n이제는 가발 쓴 놈들 앞에서 굽실거릴 필요 없을 만큼 금도 모았어. 하지만 바다를 떠난다는 건... 아직 준비가 안 됐더라고. 그래서 새로운 걸 해보기로 했지.";
			}
			link.l1 = "클리버, 대머리, 레프리콘... 걔네들 어디로 사라졌는지 알아?";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_B = true;
		break;

		case "SharlieEpilog_PikarOnUliss_B_2":
			dialog.text = "아니, 몰라. 솔직히 말해서—그 자식들이 어디로 갔든 전혀 신경 안 써. 지옥에나 떨어져도 상관없어.";
			link.l1 = "내가 그들을 보낸 곳이 대략 거기야.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_3";
		break;

		case "SharlieEpilog_PikarOnUliss_B_3":
			dialog.text = "그래서 그 선원들을 전부 쓸어버린 게 바로 너였단 말이냐? 이런 젠장! 그런데도 Marcus가 널 용서해줬다고?";
			link.l1 = "그는 그것에 대해 모른다. 그리고 아마 앞으로도 절대 알지 못할 것이다.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_4";
		break;

		case "SharlieEpilog_PikarOnUliss_B_4":
			dialog.text = "그래, 젠장, 내가 딱 맞춰서 그놈들을 떠났지, 하하. 너도 내 목을 살려두진 않았을 거야\n그런데 한 가지 도무지 이해가 안 가—대체 이 모든 걸 왜 한 거지?";
			link.l1 = "네 말이 맞았어 – 이 놈들은 금 한 조각 때문에 서로 목을 조를 놈들이야, 누구든 배신하거나 죽일 수 있지. 우리는 남부 본토의 어느 지하 감옥으로 유인당했어, 어마어마한 보물이 있다는 헛소리를 들으면서 말이야. 아주 치밀하게 짜인 함정이었고, 저 멍청이들은 아무 생각 없이 미끼를 덥석 물었지. 전리품을 공평하게 나누는 대신, 굳이 나눌 필요가 없다고 생각했는지, 그냥 나를 없애고 전부 자기들이 가지는 게 더 쉽다고 여긴 거야.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_5";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_5":
			dialog.text = "걔네는 절대 성공 못 했지, 하하! 잠깐만, 애초에 그 함정 판 게 누구였더라?";
			if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l1 = "어떤 조로라는 스페인 민중의 복수자가 있었지—카르타헤나의 복수를 노렸어. 그 학살에서 살아남은 자들은 모두 영원히 지하 감옥에서 썩어야 했지—모든 출구가 봉쇄됐거든. 하지만 그 자식은 운이 없었어—내 장교가 그놈을 한 수 앞질렀거든.";
			}
			else
			{
				link.l1 = "어떤 Zorro라는 자가 있었지, 스페인 민중의 복수자였어—카르타헤나의 복수를 위해 움직였지. 그 지옥 같은 학살에서 살아남은 자들은 모두 영원히 지하 감옥에 갇히도록 되어 있었어—모든 출구가 완전히 봉쇄됐거든. 나는 간신히 탈출했지. 하지만 대가가 너무 컸어.";
			}
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_6";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_6":
			dialog.text = "적어도 살아서 나왔군. 그리고 네 목숨값으로 치를 뻔한 그 금도 다 챙겼겠지?";
			link.l1 = "거기엔 금이 없었어. 그냥 금칠한 납덩이였지...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_7";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_7":
			dialog.text = "...";
			link.l1 = "그 모든 일이 있고 나서, 나는 티락스를 떠나기로 결심했어. 이 얘기를 한 건 네가 처음이야. 음, 내 장교들은 빼고.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_8";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_8":
			dialog.text = "내가 '거 봐, 내가 뭐랬어'라는 말은 별로 안 좋아하지만... 그래도 경고는 했었지.";
			link.l1 = "언제 멈춰야 하는지 아는 건 내 장기가 아니지. 그러니 내가 좀 배워야겠군.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_9";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_9":
			dialog.text = "나 알잖아 – 좋은 럼주 두 잔만 주면 내가 금화 숨겨둔 곳까지 다 말해줄걸, 헤헤.";
			link.l1 = "글쎄, 나한테 그런 관대함은 기대하지 마, 하하하. 네가 가진 보급품으로 버텨야 할 거야.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_C_1":
			dialog.text = "맞아. 그가 너한테 편지 몇 통을 주려고 했지—Ben인가, 아니면 Benedict라는 사람한테서 온 거였어. 그런데 너는 Ben이라는 사람은 모른다고 딱 잘라 말하고, 계속 분위기 망치면 당장 이 선술집에서 쫓아내겠다고 위협했지.";
			link.l1 = "제기랄... 이건 베누아 수도원장에게서 온 편지들이었군. 중요한 편지들이었어.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_C = true;
		break;

		case "SharlieEpilog_PikarOnUliss_C_2":
			dialog.text = "그래, 내가 그걸 가져온 게 다행이군. 헤헤. 그 꼬마 녀석이 제대로 된 사람을 골랐다는 예감이 들었거든. 자, 여기 있다.";
			link.l1 = "정말 큰 도움을 줬어, "+npchar.name+", 감사합니다.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_3";
		break;

		case "SharlieEpilog_PikarOnUliss_C_3":
			dialog.text = "고맙다는 말 한마디로는 부족하지, 친구. 나한테 술 한잔 빚졌어—그것도 아무 술 말고, 보르도에서 제일 좋은 걸로 줘야 해.";
			link.l1 = "술은 줄 테니, 이 거지 녀석아. 우리 럼주는 카리브 해의 럼주에 비할 바는 못 되지만, 와인은... 그건 네가 한 번도 맛본 적 없는 거야.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_E_1":
			dialog.text = "...한 번도 해본 적 없었지...";
			link.l1 = "당신이 부럽소. 나도 다시 처음으로 보르도를 볼 수 있다면 좋겠군. 당신은 아마 럼주를 더 좋아하겠지만, 그래도 시청 근처에서 열리는 와인 박람회는 꼭 가보길 권하오. 카리브의 감식가들이라면 우리 클라레 와인에 거금을 지불할 테니.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_E = true;
		break;

		case "SharlieEpilog_PikarOnUliss_E_2":
			dialog.text = "조언해 주셔서 감사합니다. 한 가지 여쭤봐도 되겠습니까?";
			link.l1 = "물론이지.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_3";
		break;

		case "SharlieEpilog_PikarOnUliss_E_3":
			dialog.text = "수년 동안 키를 잡다가 이제는 승객이 된 기분이 어떤가요? 새로운 역할에는 벌써 익숙해졌나요?";
			link.l1 = "흠... 이제 내 운명을 더 이상 내가 쥐고 있지 않은 것 같은 기분을 떨칠 수가 없군. \n그런데도 이상하게 마음이 한결 가벼워졌어. 마치 어깨에 짊어졌던 포탄 상자를 이제 막 내려놓은 것처럼 말이야. \n아직은 성급하게 결론을 내릴 때가 아닌 것 같군.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_4";
		break;

		case "SharlieEpilog_PikarOnUliss_E_4":
			dialog.text = "이 지독한 무풍지대에 들어왔으니, 시간은 남아돌 거요.";
			link.l1 = "좋은 동료들과 함께라면, 잔잔한 바다도 전혀 힘들지 않지요. 그리고 인정해야겠군요, 선장님. 저는 정말 훌륭한 동료들을 만나는 행운을 누렸습니다.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_F_1":
			dialog.text = "그래, 전령이 왔었어. 어떤 수도원장이 보냈다더군. 자꾸 너한테 이 편지들을 주는 걸 깜빡했네. 자, 받아.";
			link.l1 = "훌륭하군요. 정말 큰 도움을 주셨습니다, 선장님. 감사합니다.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_F = true;
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A")){dialog.text = "맞아.";}
			else {dialog.text = "맞아.";}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_D_2";
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_2":
			dialog.text = "우현에서 바람이 분다! 앞돛부터 미즌돛까지 모든 돛을 올려라! 전속력 앞으로!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InEstateDeMonpe";
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(CharacterFromID("SharlieEpilog_Pikar"), "quest", "quest10");
		break;
		
		case "SharlieEpilog_InEstateDeMonpe":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe");
		break;
		
		//Матрос 1 на верхней палубе
		case "SharlieEpilog_Sailor_1":
			dialog.text = "좋은 검이군, "+GetTitle(NPChar,true)+". 제가 좀 봐도 되겠습니까?";
			link.l1 = "다음에 기회가 되면 하죠.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_1";
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer05.wav");
		break;
		
		//Матрос 2 на верхней палубе
		case "SharlieEpilog_Sailor_2":
			dialog.text = "모래시계는 언제 울릴 거지? 나 진짜 혀를 삼킬 지경이야.";
			link.l1 = "인내심을 가져, 선원.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-07.wav");
		break;
		
		//Матрос 3 на орудийной палубе
		case "SharlieEpilog_Sailor_3":
			dialog.text = "저 쥐가 달려가는 거 봤어? 평생 그렇게 큰 쥐는 처음 봤다니까!";
			link.l1 = "음...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_3";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-04.wav");
		break;
		
		//Матрос 4 на орудийной палубе
		case "SharlieEpilog_Sailor_4":
			dialog.text = "이제 어쩌란 말입니까, 나리? 너무 취해서 어떻게 이 배에 오게 됐는지도 기억이 안 납니다. 저는 뱃사람이 아니에요... 그리고 고향에는 아내와 아이 둘이 기다리고 있습니다.";
			link.l1 = "술을 좀 덜 마셨어야지. 이제 늦었으니, 뱃사람이 되어야겠군.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_4";
			PlaySound("Voice\" + LanguageGetLanguage() + "\Ransack_2.wav");
		break;
		
		//Старший матрос
		case "SharlieEpilog_HighSailor_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". 우리 배에 타 주셔서 영광입니다.";
			link.l1 = "정말 예의가 바르시군요, 선임 선원 나리. 바다에서 오래 산 뱃사람들에게선 예의가 흔한 덕목은 아니지요. 하지만 선원들 앞에서 민망하게 만들진 맙시다 – 여긴 폐하의 궁정이 아니니까요. 그냥 나를 선장이라고 부르시오.";
			link.l1.go = "SharlieEpilog_HighSailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;

		case "SharlieEpilog_HighSailor_2":
			dialog.text = "글쎄요, 저는 선원이 된 지 얼마 안 됐어요. 원래는 르바쇠르 나리 밑에서 서기로 일했죠. 그런데 그분이… 에hem… 사라지고 나서 새로운 총독이 부임했어요. 르네 드 부아뒤플 드 레스트르 나리가 얼마나 악당인지, 그 소문이 특정 계층에 금세 퍼졌죠.\n그때 깨달았어요. 이제는 다시는 정직한 일자리를 못 구하겠구나. 사람들은 내가 모든 걸 알고도 입 다물었다고 생각할 테니까요.";
			link.l1 = "그렇지 않았소?";
			link.l1.go = "SharlieEpilog_HighSailor_3";
		break;

		case "SharlieEpilog_HighSailor_3":
			dialog.text = "당연히 아니오. 나는 남의 일에 참견하는 버릇이 없었소. 게다가 르바쇠르는 호기심을 가혹하게 벌주었으니.";
			link.l1 = "그건 충분히 믿을 수 있지.";
			link.l1.go = "SharlieEpilog_HighSailor_4";
		break;

		case "SharlieEpilog_HighSailor_4":
			dialog.text = "그래서 네가 그 자를 처리한 뒤, 나는 눈에 띄는 첫 해적선에 선원으로 들어갔어. 그런데 이상하게도 꽤 빨리 적응하고 변하더라. 심지어 가장 무자비한 악당들에게도 존경을 받게 됐지. 하지만 그들이 하는 짓은... 내 길이 아니었어. 그래서 이렇게 여기까지 오게 된 거야.";
			link.l1 = "그래서, 내가 르바쇠르의 운명에 관여한 걸 알고 있었던 건가?";
			link.l1.go = "SharlieEpilog_HighSailor_5";
		break;

		case "SharlieEpilog_HighSailor_5":
			dialog.text = "물론이죠, 선장님. 그리고 그 괴물을 세상에서 없애줘서 기뻐요. 동시에 저를 답답한 작은 방에서 꺼내주셨죠. 제 삶을 완전히 새로운 시각으로 보게 해주셨어요.";
			link.l1 = "세상이 이렇게 좁을 줄이야...";
			link.l1.go = "SharlieEpilog_HighSailor_6";
		break;

		case "SharlieEpilog_HighSailor_6":
			dialog.text = "모순처럼 들릴 수도 있지만, 세상은 넓은 만큼이나 좁기도 하다.";
			link.l1 = "재밌네. 그런 건 한 번도 진지하게 생각해본 적 없었어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
		break;
		
		case "SharlieEpilog_HighSailor_7":
			dialog.text = "Captain "+pchar.lastname+"... 참 멋진 저녁이지 않소?";
			link.l1 = "그럴지도. 북서쪽에서 부는 산들바람만 있으면 더할 나위 없겠지.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;
		
		//Диалог с боцманом Моко
		case "SharlieEpilog_Moko_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Captain "+pchar.lastname+"...";
				link.l1 = "사실은... 아니, 됐다. 기억나! 네 이름은 모코였지. 한 번에 럼주 한 통을 다 비운 게 너 아니었어?";
				link.l1.go = "SharlieEpilog_Moko_2";
			}
			else
			{
				dialog.text = "무엇을 원하십니까... 나리?";
				link.l1 = "너처럼 거한은 매일 만나는 게 아니지. 이름이 뭐지?";
				link.l1.go = "SharlieEpilog_Moko_4";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Kapitani Korabley-07.wav");
		break;

		case "SharlieEpilog_Moko_2":
			dialog.text = "나... 그리고 이틀 뒤에야 깨어났어.";
			link.l1 = "네 자리에 다른 누구였어도 두어 시간도 못 버텼을 거야. 네가 술 마시는 것처럼 싸운다면, Jean은 정말 운 좋은 거지, 너 같은 갑판장을 두게 돼서.";
			link.l1.go = "SharlieEpilog_Moko_3";
		break;

		case "SharlieEpilog_Moko_3":
			dialog.text = "내 선장님을 만난 것도 참 행운이었지. 그분 덕분에 자유를 찾았어. 그리고 너 덕분이기도 해. 네가 Jean을 도와주지 않았다면 난 아직도 플랜테이션에서 썩고 있었을 거야.";
			link.l1 = "정말 대단한 모험이었지. 그리고 일이 더 나쁘게 끝나지 않아서 다행이야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_4":
			dialog.text = ""+npchar.name+". 나는 이 배의 보선장이야.";
			link.l1 = "하하, 감히 당신을 건드릴 자가 누군지 한번 보고 싶군. 선장 밑에서 일한 지 오래됐나?";
			link.l1.go = "SharlieEpilog_Moko_5";
		break;

		case "SharlieEpilog_Moko_5":
			dialog.text = "몇 해 됐지. 그에게 진 빚이 많아. 그가 아니었으면 나는 저기서 썩고 있었을 거야...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Moko_6";
		break;

		case "SharlieEpilog_Moko_6":
			dialog.text = "...";
			link.l1 = "플랜테이션에서 말인가?";
			link.l1.go = "SharlieEpilog_Moko_7";
		break;

		case "SharlieEpilog_Moko_7":
			dialog.text = "...";
			link.l1 = "가자, "+npchar.name+", 물론 나한테 아무 말도 안 해도 되지만, 아직 눈치 못 챘다면, 나는 그 가루 바른 가발 귀족들과는 달라. 선장님이 너를 구해줬어?";
			link.l1.go = "SharlieEpilog_Moko_8";
		break;

		case "SharlieEpilog_Moko_8":
			dialog.text = "우리는 함께 도망쳤어. 마라카이보의 플랜테이션에서 말이야. 장이 없었으면 절대 성공 못 했을 거야. 그때부터 난 그의 선원이 됐지. 처음엔 그냥 뱃사람이었고, 지금은—갑판장이야.";
			link.l1 = "선장이 노예였다고? 전혀 몰랐네. 뭐, 나도 숨기고 싶은 과거가 좀 있지. 어쨌든 스페인놈들 손아귀에서 잘 빠져나와서 다행이야,\n "+npchar.name+". 자, 선원이 된 기분이 어떤가?";
			link.l1.go = "SharlieEpilog_Moko_9";
		break;

		case "SharlieEpilog_Moko_9":
			dialog.text = "예전에는 진짜로 살아본 적이 없는 것 같아. 이제 바다가 내 집이야.";
			link.l1 = "여기서는 네 마음을 이해해, 친구야. 누구보다도 말이야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_repeat":
			dialog.text = "Captain "+pchar.lastname+"... 무엇을 도와드릴까요?";
			link.l1 = "감사합니다, "+npchar.name+", 지금은 아무것도 필요하지 않아.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		//Диалог с дворянином Бернардом
		case "SharlieEpilog_Bernard_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! 이 배에서 적어도 한 명은 이성적인 얼굴을 보게 되어 얼마나 기쁜지 모르겠군. 이... 선원들... 전부 야만인들이오.";
			link.l1 = "내가 너라면 남의 배에서 그렇게 말하지 않을 거야. 네가 어떻게 카리브에 오게 됐는지는 모르겠지만, 여기서는 사정이 다르거든. 선원들에게는 예의를 좀 갖추는 게 좋을 거야.";
			link.l1.go = "SharlieEpilog_Bernard_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;

		case "SharlieEpilog_Bernard_2":
			dialog.text = "존경하라고? 저런 자들을? 그들은 야만인일 뿐이오! 나는 귀족이오, "+GetTitle(NPChar,true)+", 나는 명령하는 데 익숙하고, 시중받는 것도, 그리고… 문명이라는 것도 익숙하오! 감히 내 앞길을 막아보라지—아버지께서…";
			link.l1 = "네 아버지께서는 네가 오는 길에 열병으로 죽었다는 소식을 듣게 될 거다. 그리고 그분이 그게 사실이 아니라는 걸 증명하기는 힘들겠지.";
			link.l1.go = "SharlieEpilog_Bernard_3";
		break;

		case "SharlieEpilog_Bernard_3":
			dialog.text = "저주받을 Fox 대령! 전부 그 자 때문이야! 그 딸 때문에 내가 대서양을 건너고, 내 안락함을 포기하고, 곁눈질을 견디고, 끔찍한 음식도 먹고, 이... 끝없는 흔들림까지 참았는데! 그런데 이제 남의 배를 타고 항해하고 있다니!";
			link.l1 = "폭스 대령…";
			link.l1.go = "SharlieEpilog_Bernard_4";
		break;

		case "SharlieEpilog_Bernard_4":
			dialog.text = "그 사람을 아시오, "+GetTitle(NPChar,true)+"?";
			link.l1 = "음... 그 사람에 대해 들었소.";
			link.l1.go = "SharlieEpilog_Bernard_5";
		break;

		case "SharlieEpilog_Bernard_5":
			dialog.text = "글쎄, 그럼 별로 놓친 건 없겠군. 그 사람은 맹목적인 군인 고집과 편견의 화신이지.";
			link.l1 = "그는 군인이야...";
			link.l1.go = "SharlieEpilog_Bernard_6";
		break;

		case "SharlieEpilog_Bernard_6":
			dialog.text = "정확히 그래! 그게 전부를 말해 주지. 내가 그의 딸을 만나게 해 달라고 왔을 때, 뭘 했는지 알아? 알아? 나를 내쫓았어! 한마디 말도 없이!";
			link.l1 = "하지만 물러서지 않았지, 그치?";
			link.l1.go = "SharlieEpilog_Bernard_7";
		break;

		case "SharlieEpilog_Bernard_7":
			dialog.text = "당연하지! 나는 일주일 내내 면담을 요청하려고 애썼어! 자존심도 버렸지! 심지어... 경비병들에게 뇌물까지 주려고 했어! 결국 초대장도 없이 몰래 들어갔지. 그냥 대화만 하고 싶었을 뿐이야!";
			link.l1 = "그 일에 대해 그가 그다지 기뻐하지는 않았던 것 같아.";
			link.l1.go = "SharlieEpilog_Bernard_8";
		break;

		case "SharlieEpilog_Bernard_8":
			dialog.text = "나를 봐서 기뻐? 아, 아버지는 정말 난리를 치셨지! 나는 쫓겨났고, 저택 근처에도 못 오게 금지당했어. 아버지 배도 압수당했고, 심지어 영국 선장들한테는 나를 배에 태우지 말라고까지 했지! 결국 마르티니크에서 프랑스 배를 찾아야 했어... 정말 악몽이었어.";
			link.l1 = "정말 그 사람을 화나게 만든 것 같군.";
			link.l1.go = "SharlieEpilog_Bernard_9";
		break;

		case "SharlieEpilog_Bernard_9":
			dialog.text = "그는 항상 나를 반대했지. 그가 가장 좋아하던 말이 있었어. '장교의 딸은 장교의 아내가 된다.' 너, "+GetTitle(NPChar,true)+", 그는 훨씬 더 어울리는 혼처라고 여겼다.";
			link.l1 = "아마 이번에는 그에게 다른 이유도 있었겠지...";
			link.l1.go = "SharlieEpilog_Bernard_10";
		break;

		case "SharlieEpilog_Bernard_10":
			dialog.text = "...";
			link.l1 = "그래서, 당신이 사랑하는 이를 만나러 여기 온 것이군.";
			link.l1.go = "SharlieEpilog_Bernard_11";
		break;

		case "SharlieEpilog_Bernard_11":
			dialog.text = "그래. 그녀가 유럽을 떠난 이후로 편지 한 통도 받지 못했어. 분명 그녀 아버지가 내 편지를 가로채고 있는 거야. 그녀가 날 잊었을 리 없어! 물론, 그녀는 나에게 항상 조심스러웠지... 심지어 차갑기도 했고... 하지만 그녀가 내 존재를 완전히 지워버렸다는 건 믿을 수 없어.";
			link.l1 = "애도를 표합니다, 나리. 마음의 상처는 육신의 상처보다 훨씬 더디게 아물지요. 그런데... 잠깐만요. 당신은 영국인인데, 왜 보르도로 가는 겁니까?";
			link.l1.go = "SharlieEpilog_Bernard_12";
		break;

		case "SharlieEpilog_Bernard_12":
			dialog.text = "나는 수치스럽게 집으로 돌아갈 생각 없어. 일이 진정될 때까지 보르도에 계신 삼촌 댁에 머물러야겠지. 그래도 삼촌의 영지는 우리 집보다 훨씬 넓고 우아하거든. 게다가 하인들도 훨씬 더 잘 훈련되어 있어.";
			link.l1 = "글쎄, 이 정도면 최악은 아니겠지. 어쩌면 새로운 연인을 만나게 될지도 몰라. 보르도에는 젊고 아름다운 아가씨들이 넘쳐나니까, 내 말 믿어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
		break;
		
		case "SharlieEpilog_Bernard_repeat":
			dialog.text = "도대체 언제쯤 도착하는 거지, "+GetTitle(NPChar,true)+"? 저는 이 모든... 신사들에 둘러싸여 견딜 수 없이 괴롭습니다. 당장 목욕을 해야겠어요.";
			link.l1 = "두 달 동안은 그녀를 그리워하며 꿈꾸는 수밖에 없을 것 같소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;
		
		//Диалог с Книппелем на корабле Улисс
		case "SharlieEpilog_Knippel_1":
			dialog.text = "이 죽은 듯한 무풍을 저주한다, 체인 샷이나 맞아라.";
			link.l1 = "투덜거리지 마, "+npchar.name+", 머지않아 바람이 불어올 것이오.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "그럼 그때까지 나는 뭘 해야 하오, 나리? 대포 점검도 못 하고... 어차피 남의 배에 타고 있으니 말이오.";
			link.l1 = "그냥 좀 쉬어봐. 항상 일만 할 필요는 없어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		case "SharlieEpilog_Knippel_repeat":
			dialog.text = "젠장, 이 고요함...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		//Диалог с Лонгвэем на корабле Улисс
		case "SharlieEpilog_Longway_1":
			dialog.text = "나쁘지 않은 배군요, 선장님. 당신도 그렇게 생각하나요?";
			link.l1 = "메이펑보다도 더 나아?";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = "For "+npchar.name+" 메이펑보다 더 나은 배는 없어. 이 배만큼 바람을 가까이 가르며 달릴 수 있는 배는 다시 없을 거야.";
			link.l1 = "진정해, "+npchar.name+", 그냥 농담이었어. 물론 Meifeng은 차원이 다르지. 하지만 Ulysses도 훌륭한 배야. 튼튼하지.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = ""+npchar.name+" 키를 잡는 것. 배가 내 손길에 반응하는 걸 느끼는 것...";
			link.l1 = "안타깝지만, 친구여, 이 배는 다른 사람의 것이오. 저기 저 큰 사내에게 가서 결투를 신청해 보시오. 둘 다에게 도움이 될 것이오.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		case "SharlieEpilog_Longway_repeat":
			dialog.text = "바람이 우리 편이라면 얼마나 빨리 갈 수 있을까?";
			link.l1 = "확실히 말할 수는 없소, "+npchar.name+". 그들의 항해사에게 직접 물어보는 게 낫겠어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		//Диалог с Тонзагом на корабле Улисс
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "여기 보선장으로 뽑힌 거인 봤어? 한 손으로 코코넛을 으깨버린다던데.";
			link.l1 = "하하. 너 그 사람 좀 무서워하는 것 같은데, 그렇지?";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "그게 왜 중요하지? 크기가 전부는 아니야. 나 예전에도 훨씬 더 큰 걸 다뤄본 적 있어.";
			link.l1 = "그럼 그에게 주먹다짐으로 도전해 보는 게 어때? 일대일로, 정정당당하게.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "아으...";
			link.l1 = "얼굴이 좀 창백해졌군. 하하. 뭐, 싫으면 어쩔 수 없지. 자네 그리 젊지 않은 뼈라도 아껴주자고.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		case "SharlieEpilog_Tonzag_repeat":
			dialog.text = "이 바다엔 물고기가 너무 많아서 배로 퍼올릴 수도 있지. 그런데 이 게으름뱅이들은 그물 한 번 던질 생각도 안 하더군.";
			link.l1 = "그쪽 보선장한테 가서 말해 봐. 네 말에 꽤 감탄할걸, 헤헤.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		//Диалог с Тичингиту, охраняющим золото
		case "SharlieEpilog_Tichingitu_21":
			dialog.text = "금은 안전합니다, 선장님 "+pchar.name+". 티칭이투가 그를 잘 지켜줄 것이오.";
			link.l1 = "고마워, 친구야. 곧 Alonso가 네 일을 넘겨받을 거야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tichingitu_21";
		break;
		
		//Диалог с Книппелем, охраняющим золото
		case "SharlieEpilog_Knippel_21":
			dialog.text = "이런 젠장, 나리, 이 배엔 내가 평생 본 쥐보다 더 많은 쥐가 있소.";
			link.l1 = "배는 너무 오랫동안 항구에 방치되어 제대로 관리받지 못했다.\n새 선원들이 곧 그것들을 치워버릴 것이다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_21";
		break;
		
		//Диалог с Лонгвэем, охраняющим золото
		case "SharlieEpilog_Longway_21":
			dialog.text = "Longway가 쇠사슬 소리를 듣고 있어요. 선장님, 닻을 내리신 겁니까?";
			link.l1 = "도화선을 터뜨린 건 우리 승객이었소. 지금은 바람이 아직 약하지만, 오래 가지 않기를 바라오.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_21";
		break;
		
		//Диалог с Тонзагом, охраняющим золото
		case "SharlieEpilog_Tonzag_21":
			dialog.text = "그래, 젠장... 지금 당장 진한 럼주 한 잔이면 좋겠는데.";
			link.l1 = "곧 저녁이 준비될 테니 조금만 참아. 알론소가 네 일을 대신할 거야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_21";
		break;
		
		//Диалог с Мэри перед походом в каюту
		case "SharlieEpilog_Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", 내 사랑, 기분이 어떠신가요?";
			link.l1.go = "SharlieEpilog_Mary_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_12":
			dialog.text = "...";
			link.l1 = "자기야, 나 그냥 포도주 사러 가게에 다녀온 것 때문에 정말 나한테 화난 거야?";
			link.l1.go = "SharlieEpilog_Mary_13";
		break;

		case "SharlieEpilog_Mary_13":
			dialog.text = "와인 사러 가게에 간 거였어? 최소한 말이라도 해주지! 네가 창관에 간 줄 어떻게 알아—어떤 여자랑… 아니면 전부랑 한꺼번에 있었는지 내가 어떻게 아냐?!";
			link.l1 = "여보, 내가 정말 그런 위험을 감수하겠어? 나는 이 군도에서 가장 아름답고, 똑똑하고, 또 엄청나게 질투심 많은 아내를 두고 있잖아. 내가 정말로 시시한 부두 근처 처녀들에게 시간 낭비할 거라 생각해?";
			link.l1.go = "SharlieEpilog_Mary_14";
		break;

		case "SharlieEpilog_Mary_14":
			dialog.text = "나한테 한마디라도 해줄 수 있었잖아, 그치! 난 거기 앉아서…";
			link.l1 = "다음번엔 말로만 하지 않고 꼭 데려가겠다고 약속할게. \n하지만 지금은… 갑자기 선장실 가구가 제대로 있는지 궁금해졌어. 특히 침대 말이야. 같이 확인해 볼까?";
			link.l1.go = "SharlieEpilog_Mary_15";
		break;

		case "SharlieEpilog_Mary_15":
			dialog.text = ""+pchar.name+"... 그런데 누가 들어오면 어쩌지?\n흠... 이제 더 하고 싶어졌는데.";
			link.l1 = "그럼 한순간도 낭비하지 말자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Элен перед походом в каюту
		case "SharlieEpilog_Helena_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", 내 사랑, 기분이 어때?";
			link.l1.go = "SharlieEpilog_Helena_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_12":
			dialog.text = "...";
			link.l1 = "자기야, 설마 내가 그냥 포도주 사러 가게에 다녀온 것 때문에 정말 화난 거야?";
			link.l1.go = "SharlieEpilog_Helena_13";
		break;

		case "SharlieEpilog_Helena_13":
			dialog.text = "나도 데려갈 수 있었잖아. 아니면 네 그 하찮은 범죄 동료들보다 내가 더 못할 거라고 생각한 거야?";
			link.l1 = "당신이라면 그들을 쉽게 압도할 것 같군요. 하지만 그때는 와인이 내 머릿속에서 마지막으로 떠오를 거요.";
			link.l1.go = "SharlieEpilog_Helena_14";
		break;

		case "SharlieEpilog_Helena_14":
			dialog.text = "그건 또 뭐에 대해서?";
			link.l1 = "그때 당장 당신과 함께 몰래 빠져나가는 상상에 대해… 지금도 그 생각이 머릿속에서 떠나질 않아.";
			link.l1.go = "SharlieEpilog_Helena_15";
		break;

		case "SharlieEpilog_Helena_15":
			dialog.text = "그래? 그런데 대체 어디에서 호기심 많은 시선들을 피해서 숨을 생각이야?";
			link.l1 = "선장 선실에서. 그의 침대가 얼마나 튼튼한지 시험해 봐야겠지.";
			link.l1.go = "SharlieEpilog_Helena_16";
		break;

		case "SharlieEpilog_Helena_16":
			dialog.text = "하하. 선장님이 우리를 잡으면 어쩌지?\n그래도… 그런 상상만 해도 가슴이 두근거려.";
			link.l1 = "그럼 시간 낭비하지 말자!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Мэри в каюте
		case "SharlieEpilog_Mary_21":
			dialog.text = "정말 멋졌어요, 내 선장님...\n당신께 전할 소식이 있어요.";
			link.l1 = "소식인가? 듣고 있네.";
			link.l1.go = "SharlieEpilog_Mary_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Mary_22":
			dialog.text = ""+pchar.name+"... 우리 아이가 생겼어. 나 임신했어, 그치?";
			link.l1 = "내 사랑... 정말이야?";
			link.l1.go = "SharlieEpilog_Mary_23";
		break;

		case "SharlieEpilog_Mary_23":
			dialog.text = "아버지가 될 거예요, "+pchar.name+"!";
			link.l1 = ""+npchar.name+"... 이건 믿을 수가 없군!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Mary_31":
			dialog.text = "행복해요, 내 사랑?";
			link.l1 = "행복하냐고? 농담하지 마! 젠장, 난 세상에서 제일 행복한 남자야! 그런데... 왜 진작 말 안 했어?";
			link.l1.go = "SharlieEpilog_Mary_32";
		break;

		case "SharlieEpilog_Mary_32":
			dialog.text = "우리 출발을 미루자고? 나는 정말 네 아버지를 만나고 싶은데, "+pchar.name+".";
			link.l1 = ""+npchar.name+"... 사랑해요!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		//Диалог с Элен в каюте
		case "SharlieEpilog_Helena_21":
			dialog.text = "당신은 언제나처럼 최고였어요, 자기야. 당신에게 전할 소식이 있어요.";
			link.l1 = "소식인가? 듣고 있네.";
			link.l1.go = "SharlieEpilog_Helena_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Helena_22":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", 몽페 기사 나리 - 곧 아버지가 되실 겁니다.";
			link.l1 = "정말... 정말이야?";
			link.l1.go = "SharlieEpilog_Helena_23";
		break;

		case "SharlieEpilog_Helena_23":
			dialog.text = "내가 지닌 이름만큼이나 진실하게 "+npchar.name+". 6개월도 안 되어 우리에게 아이가 생길 거예요—작은 드 모르 나리일 수도 있고, 아니면 마드모아젤일 수도 있죠.";
			link.l1 = "헬렌... 믿을 수가 없군!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Helena_31":
			dialog.text = "...";
			link.l1 = "그래서 우리가 출항을 축하하며 마실 때 같이 안 했던 거군! 하지만… 왜 진작에 말하지 않았지?";
			link.l1.go = "SharlieEpilog_Helena_32";
		break;

		case "SharlieEpilog_Helena_32":
			dialog.text = "당신이 위험을 감수하지 않고 군도에 머물기로 결정할까 봐 걱정했어요.\n아버지의 부탁을 꼭 들어줬으면 했고요.\n그리고… 저도 정말로 그분을 직접 만나보고 싶어요.";
			link.l1 = ""+npchar.name+"… 사랑해!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		// Диалог с Пикаром
		case "SharlieEpilog_PikarInCabin_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "오, 이거 참... 여기서 뭘 하고 계시나? 작은 가스코뉴 녀석들이라도 만들 셈인가?";
				link.l1 = "하하하! 이제 곧 내 아들이 생기겠군, "+npchar.name+"! 나 아버지가 될 거야!";
				link.l1.go = "SharlieEpilog_PikarInCabin_1_1";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". 선장도 모르게 선장실을 쓰는 건, 아무리 당신 같은 신분이라도 좀 지나치지 않소?";
				link.l1 = "죄송합니다, 선장님. 하지만 그럴 만한 이유가 있어요! 곧 아버지가 될 거거든요!";
				link.l1.go = "SharlieEpilog_PikarInCabin_12";
			}
			SharlieEpilog_PikarInCabin_camera_2();
		break;
		
		case "SharlieEpilog_PikarInCabin_1_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_2":
			dialog.text = "아니면 딸일 수도 있지!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_2_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_2_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_3", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_3":
			dialog.text = "이걸 나한테 숨겼단 말이냐, 이 못된 녀석! 나는 네가 내 친구인 줄 알았는데!";
			link.l1 = "나도 방금 알았어! 믿어지니? 내가! 나 아빠가 된대!";
			link.l1.go = "SharlieEpilog_PikarInCabin_4";
		break;

		case "SharlieEpilog_PikarInCabin_4":
			dialog.text = "하하하! 정말 기뻐 보이는구나, 친구! 이렇게 행복한 너는 처음 본다네\n자, 두 분은 계속 이야기 나누시고, 나는 축포를 위해 대포를 준비하겠네. 명령 내릴 준비가 되면 알려주게.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;

		case "SharlieEpilog_PikarInCabin_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				sld = CharacterFromID("Mary");
			}
			dialog.text = "하... 믿으시오, 왜 여기 온 건지 느낌이 왔소.";
			link.l1 = "아니, 당연히 아니지! "+sld.name+" 나 임신했어! 아들을 가지게 됐어!";
			link.l1.go = "SharlieEpilog_PikarInCabin_12_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_12_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_13":
			dialog.text = "아니면 딸일 수도 있지!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_13_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_13_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_14", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_14":
			dialog.text = "음... 진심으로 축하드립니다!\n제가 준비하겠소—모든 대포로 축하 사격을 하도록 하겠소. 명령을 내릴 준비가 되면 말씀만 하시오.\n그동안... 선실은 마음껏 쓰시오.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;
		
		// Диалог с Пикаром после интима с женой
		case "SharlieEpilog_PikarZalp_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "에헴... 저기, 아버지... 또 바로 후계자를 만드실 생각이신가 보군요?";
				link.l1 = "하하! 내 마음대로라면 한 번에 열두 발도 쏠 수 있지! 자, 친구, 우리 모든 대포로 일제 사격 해볼까?";
				link.l1.go = "SharlieEpilog_PikarZalp_2";
				link.l2 = "유감이지만 세상일이 그렇게 되진 않아, 친구. 그래도 우리는 최선을 다했지.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"...";
				link.l1 = "그럼, 선장님, 모든 포로 일제사격을 할까요?";
				link.l1.go = "SharlieEpilog_PikarZalp_3";
				link.l2 = "지금은 안 돼.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_PikarZalp_1";
		break;
		
		case "SharlieEpilog_PikarZalp_2":
			dialog.text = "선원들이 당신의 명령만 기다리고 있습니다! 말씀만 하십시오, "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_3":
			dialog.text = "선원들은 준비됐소. 명령을 내리시오.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_final":
			dialog.text = "...";
			link.l1 = "포수들! 전포 발사! 쏴라!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_ZalpInSea");
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(pchar, "quest", "quest10");
			CharacterTurnToLoc(npchar, "quest", "quest10");
		break;
		
		// Диалог с отцом в поместье де Монпе
		case "SharlieEpilog_HenriDeMonper_1":
			NextMonth = GetDataMonth() + 2;
			if (NextMonth == 13) NextMonth = 1;
			else if (NextMonth == 14) NextMonth = 2;
			Month = XI_ConvertString("MonthVoc_" + NextMonth);
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... 아들아, 이렇게 다시 보게 되어 얼마나 기쁜지 모르겠구나!";
			if (GetDataMonth() >= 4 && GetDataMonth() <= 10)
			{
				link.l1 = "아버지... 다시 집에 돌아오다니 믿기지 않아요... 눈이 어떻게 생겼는지도 거의 잊어버릴 뻔했어요. 여긴 아무것도 변하지 않은 것 같아요...\n";
			}
			else
			{
				link.l1 = "아버지... 다시 집에 오다니 믿기지 않아요... 이럴 때를 맞춰 눈까지 내리는군요. "+month+". 여긴 아무것도 변한 게 없군...";
			}
			link.l1.go = "SharlieEpilog_HenriDeMonper_2";
			locCameraFromToPos(-8.76, 7.86, 0.75, true, -7.41, 6.11, 0.18);
			Achievment_Set("ach_CL_202");
		break;
		
		case "SharlieEpilog_HenriDeMonper_2":
			dialog.text = "너는 전혀 그렇지 않지! 네가 걷는 모습, 몸가짐, 그 흉터들\n"+"아니, 내 앞에 서 있는 이는 더 이상 내가 먼 땅으로 보냈던 그 버릇없는 소년이 아니구나.";
			link.l1 = "카리브에선 빨리 철이 들어요, 아버지. 하지만 그 이야기는 나중에 해도 되겠지요. 그런데 건강은 어떠십니까? 이렇게 정복을 갖춰 입고 제 앞에 서 계신 걸 보니, 병세는 좀 나아지신 건가요?";
			link.l1.go = "SharlieEpilog_HenriDeMonper_3";
		break;
		
		case "SharlieEpilog_HenriDeMonper_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				dialog.text = "아아, "+pchar.name+", 그녀는 내 목을 더 꼭 껴안았지. 하지만 내가 사랑하는 아들을 평상복 차림으로 맞이할 수 있겠느냐? 내게는 오늘이 대단히 특별한 날이거든, "+pchar.name+"\n"+"저에게 소개할 분이 있는 것 같군요.";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_10");
			}
			else
			{
				dialog.text = "아아, "+pchar.name+", 세월이 흐를수록 그녀의 영향력은 더욱 강해진다네. 하지만 내가 평상복 차림으로 사랑하는 아들을 만날 수 있겠는가? 내게는 오늘이 대단히 특별한 날이네, "+pchar.name+"\n"+"혼자 오지 않았군\n"+"여행하느라 배고플 테지? 수잔이 자네가 좋아하는 방식대로 거위 간을 준비해 두었네!\n"+"식탁으로 오게나 – 가는 길에 우리를 소개해 주게!";
				link.l1 = "인정해야겠군, 저택에 다가가면서부터 그 향기를 이미 맡았어!";
				link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "...";
			link.l1 = "아버지, 제 아내를 소개하겠습니다 - "+sld.name+" "+pchar.lastname+". "+sld.name+", 이분이 내 아버지, 슈발리에야 "+GetCharacterName("Henri")+" "+GetCharacterName("드 몽페르")+".";
			link.l1.go = "SharlieEpilog_HenriDeMonper_5";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
				dialog.text = ""+pchar.name+", 정말 감탄스럽군요! 당신의 신부는 이곳에서 우리가 흔히 보는 버릇없는 사교계 숙녀들과는 전혀 다릅니다. 감히 말씀드리자면, 그녀는 제 아들의 마음을 다루는 것만큼이나 배도 능숙하게 다루는군요.";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_1";
				CharacterTurnByChr(npchar, sld);
			}
			else
			{
				sld = CharacterFromID("Mary");
				dialog.text = "만나 뵙게 되어 큰 기쁨입니다, 부인. 제 아들이 안목이 뛰어나다는 것을 제가 보증하오!";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_1";
				CharacterTurnByChr(npchar, sld);
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2":
			dialog.text = "과찬이십니다, 슈발리에! 말씀대로 저는 가장 거센 폭풍 속에서도 키를 잡을 수 있지요. 하지만 당신 아드님의 마음에 대해서는 조종할 필요가 없습니다. 우리는 목표와 열망에서 하나가 되었으니까요.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_2_1";
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_3":
			dialog.text = "베누아 아빠스께서 당신을 현명하고 용감한 젊은 여성이라 말씀하셨소 – 그리고 그분의 말씀이 과장이 아니었던 것 같소. 나는 기쁘오, \n "+pchar.name+" 나는 그대에게서 단순한 아내가 아니라, 진정한 마음의 동반자를 찾았소\n"+"여행하느라 배고플 테지. 수잔이 네가 좋아하는 방식대로 거위 간 요리를 준비해 두었단다!\n"+"자, 모두들, 우리 식탁에 함께해 주시지요! 가는 길에 서로 더 잘 알게 되기를 바랍니다.";
			link.l1 = "인정해야겠군, 저택에 다가가면서부터 그 향기를 이미 맡았어!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2":
			dialog.text = "만나서 반갑소, 슈발리에 나리! "+pchar.name+" 당신 얘기 정말 많이 들었어, 그리고 딱 이렇게 생겼을 거라고 상상했지, 그치!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_2_1";
			CharacterTurnByChr(pchar, npchar);
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_3":
			sld = CharacterFromID("Mary");
			dialog.text = ""+pchar.name+", 황홀하구나! 그대의 신부는 살롱의 분가루 바른 숙녀들과는 전혀 다르니, 바로 그 점이 진정한 가치라네\n"+"당신은 응석받이 변덕스러운 백합 대신 아름다운 장미를 선택했다고 생각합니다.";
			link.l1 = "야생 장미호예요, 아버지… "+sld.name+"  - 진정한 보물이오. 좀 더 알게 되면 내 말에 동의할 것이오.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_4";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_4":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "ты познакомишь меня с остальными";
			else sStr = "ты представишь меня нашему гостю";
			dialog.text = "그럼 이 순간을 미루지 맙시다! 긴 여행 끝에 배고플 테지요. 수잔이 당신이 좋아하는 방식대로 거위 간 요리를 준비해 두었습니다!\n"+"모두들, 식탁으로! 가는 길에, 나는 바라네\n "+sStr+"";
			link.l1 = "인정해야겠군, 저택에 다가갈 때부터 그 향기가 느껴졌어!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			CharacterTurnByChr(CharacterFromID("HenriDeMonper"), pchar);
		break;
		
		case "SharlieEpilog_HenriDeMonper_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_14");
		break;
		
		case "SharlieEpilog_HenriDeMonper_7":
			dialog.text = "...";
			link.l1 = "여보, 이거 꼭 먹어봐요—우리 집안 비법으로 만든 거위 간 요리만큼 맛있는 건 없어요! 할아버지 때부터 내려온 레시피인데, 지중해 어느 나라에서 선물로 받으셨다더라고요.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_15");
		break;
		
		// диалог на ужине в поместье де Монпе
		case "SharlieEpilog_InKitchenDeMonpe":
			dialog.text = "";
			link.l1 = "우리의 연회를 침울하게 시작하고 싶진 않지만, 가족으로서 우리보다 먼저 이 자리에 있었던 이들을 기억해야 하오. 미셸을 위해 잔을 들어주길 바라오. 주님께서 그의 영혼에 평화를 내리시길.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_2":
			dialog.text = "";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "добрых друзей";
				else sStr = "соратника";
				dialog.text = "";
				link.l1 = "당신께 여쭤보고 싶은 것이 정말 많습니다, "+pchar.name+"... 하지만 먼저, 당신의 아내가 할 말을 하게 하고\n "+sStr+". 제발, 어떻게 Charles를 만났는지 말씀해 주십시오.";
			}
			else
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "твоих добрых друзей";
				else sStr = "твоего друга";
				dialog.text = "";
				link.l1 = "당신에게 물어보고 싶은 게 정말 많아요, "+pchar.name+"... 하지만 먼저 한마디 하겠소\n "+sStr+". 제발 말씀해 주십시오, 어떻게 Charles를 만나게 되었습니까?";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		// if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
		
		case "SharlieEpilog_InKitchenDeMonpe_4":
			dialog.text = "";
			link.l1 = "나도 당신만큼이나 이 이야기를 듣고 싶어요!";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "내 목숨이 위태로웠어... "+pchar.name+", 진짜 신사답게 나쁜 일 하나도 안 생기게 해줬어! 나를 지켜주고 그 악당들도 처리했지, 그치!";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = ""+pchar.name+" 영국 악당에게 납치당할 뻔했는데 당신이 나를 그 손아귀에서 구해줬어요. 당신이 한 시간만 늦게 왔어도 우리는 절대 만날 수 없었을 거예요.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5_1":
			dialog.text = "";
			link.l1 = "나는 그가 진정한 귀족답게 행동할 것임을 한 번도 의심하지 않았다네. 우리 가문에게 명예란 단순한 말이 아니지. 자랑스럽구나, 아들아.";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = ""+sld.name+" 창백한 얼굴 놈의 집에 몰래 들어가서 먹을 걸 찾는다. 그런데 그 놈한테 들켜 "+sld.name+" - 그리고 감옥에 던져졌소. 선장 "+pchar.name+" 와서 구해줘 "+sld.name+" 감옥에서 나온 뒤로\n "+sld.name+" 선장을 모시다 "+pchar.name+" 내 마지막 숨이 다할 때까지 충실하겠습니다.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6_1":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = "내 아들이 귀족일 뿐만 아니라 인정을 아는 사람이라는 사실에 마음이 따뜻해지는구나. 그리고 그 곁에 너처럼 충직한 친구들이 있어 기쁘다네,\n "+sld.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "그 선장은 한때 일자리를 찾아 내 집에 찾아왔지. 내가 일을 하나 맡겼는데, 아주 잘 해냈어. 주인양반이 그를 마음에 들어 해서 점점 더 자기 일에 끌어들였고, 나는 그 배로 보내져서 상황을 감시하게 되었지... 그러다가 그... 양반이 조용히 닻을 올리고, 대포알이 내 수염을 스치듯, 선장에게 한마디 말도 없이 군도에서 떠나버렸어. 자기가 저지른 난장판에 선장만 홀로 남겨두고 말이야. 나는 선장에게 내 힘을 빌려주겠다고 했고, 리처드가 그를 더럽게 대했어도—대포알이 그의 고물에 박히듯—선장은 나를 내치지 않았지.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Longway와 훌륭한 선장은 같은 사람을 위해 일했소. 하지만 그 사람이 Longway를 배신했지. 그래서 Longway는 다시는 그 사람을 섬기지 않기로 결심했소. 훌륭한 선장은 나를 자기 배의 장교로 받아주었고, Longway를 위해 많은 일을 해주었소.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "우리가 처음 마주친 곳은 브리지타운의 선술집이었지:\n "+pchar.name+" 그는 명분을 찾고 있었고, 나는 믿을 만한 조수가 필요했지. 그 만남이 시작에 불과했어—곧이어 우리의 운명을 함께 엮는 일들이 벌어졌거든. 나는 그의 부하가 되었고, 이제는 주저 없이 그를 내 친구라 부를 수 있어—내 목숨을 걸 수 있는 그런 남자야.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7_2":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "상황 뒤에 있는 사람을 볼 줄 아는 것은 드문 재능이지. 내 아들이 분별력 없는 것은 아니라는 뜻이겠구나.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "나는 내 아들이 무정한 군인에 그치지 않고, 동료를 돌볼 줄 아는 진정한 지도자가 되어 기쁘구나.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "그런 말을 매일 듣는 건 아니지. 내 아들이 뛰어난 선원일 뿐만 아니라 진정한 친구라는 최고의 증거라고 생각하네.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8":
			dialog.text = "";
			link.l1 = "우리는 보르도에서 만났소. 그 선장님이 승객으로 우리 배에 올라타셨고, 우리는 그를 마르티니크까지 데려다주었지. 그때부터—여기로 보내질 때까지—나는 그의 선원들의 목소리로 남아 있었고, 지켜보았소\n "+GetFullName(pchar)+" 한 걸음 한 걸음씩, 그는 오늘날의 자신이 되었다.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8_1":
			dialog.text = "";
			link.l1 = "그렇다면, 자네는 내가 집에서 내보내라고 고집했던 그 참을 수 없는 젊은 시절의 샤를을 알고 있었군? 내 생각에, 나리, 자네와 나는 할 이야기가 많을 것 같소.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_9";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_9":
			dialog.text = "";
			link.l1 = "내 사랑 "+pchar.name+", 그대는 길고도 영광스러운 여정을 걸어왔구나... 토끼 가죽 하나 얻으려고 황야로 나섰다가, 결국 사자와 맞서 싸워 그 가죽을 어깨에 메고 승리하여 돌아왔지. 이제야말로 우리 가문과 모든 영지의 운명에 대해 마음이 한결 놓이는구나.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_10";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_10":
			dialog.text = "";
			link.l1 = "나는 하루라도 빨리 우리 집안의 모든 일을 너에게 넘기고 싶구나. 할 일이 부족하지는 않을 테지만, 주님께서 친히 너를 축복하신다고 믿는다. 너는 맡겨진 유산을 지키는 것에 그치지 않고, 드 몽페 가문의 명예와 재산을 더욱 키워줄 것이라 믿는다.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_11";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_11": //выбор Шарля
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = "아버지의 아들이자 후계자가 된 것은 제게 큰 영광입니다. 우리 가문을 위해 모든 책임을 기꺼이 맡겠습니다. 제 아내도 이 일에 든든한 힘이 되어줄 것이라 확신합니다. 우리 가문의 명예를 더욱 빛내기 위해 제가 할 수 있는 모든 것을 다하겠다고 약속드립니다... 그리고 우리 집안의 번영을 위한 첫걸음은 아이의 탄생이 될 것입니다!\n";
				link.l1.go = "SharlieEpilog_ChooseEstate_HaveWife_1";
			}
			else
			{
				link.l1 = "아버지의 아들이자 후계자가 된 것은 제게 큰 영광입니다. 우리 가문을 위해 모든 책임을 기꺼이 맡겠으며, 가문의 명성을 더욱 드높이기 위해 제 힘이 닿는 한 모든 것을 다하겠다고 약속드립니다.";
				link.l1.go = "SharlieEpilog_ChooseEstate_Single_1";
			}
			link.l2 = "아버지, 신세계에서 보낸 세월이 저를 바꿔놓았습니다. 이제는 더 이상 이 유럽의 느긋한 삶에 안주할 수 없을까 두렵습니다.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_HaveWife_1";
			}
			else
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_Single_1";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		// --> Выбрал остаться в поместье с женой
		case "SharlieEpilog_ChooseEstate_HaveWife_1":
			dialog.text = "";
			link.l1 = ""+pchar.name+", 혹시...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_HaveWife_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "네, 아버지. "+sld.name+" 임신했어.";
			link.l1.go = "SharlieEpilog_HaveWife_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_13":
			dialog.text = "";
			link.l1 = "정말로 기쁜 소식이구나, 사랑하는 아들아! 주님께서 내 기도를 들어주셨도다! 여기 모인 모두가 증인이 되라! 새로 태어난 아이를 기리며, 우리 영지에서 가장 성대한 무도회를 열겠노라! 모두 잔을 들어라—상속자를 위하여!";
			link.l1.go = "SharlieEpilog_HaveWife_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_HaveWife_14":
			dialog.text = "";
			link.l1 = "아니면 상속녀일 수도 있지!";
			link.l1.go = "SharlieEpilog_HaveWife_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_15":
			dialog.text = "";
			link.l1 = "우리 가문의 새로운 장을 위하여!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_16":
			dialog.text = "";
			link.l1 = "미래의 전사가 되거나 좋은 딸이 되기를 위하여!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_HaveWife_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "갓 태어난 아이의 건강을 위하여!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "당신들을 만나게 해준 우연에 건배!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "당신 가문의 밝은 미래를 위하여!";
			}
			link.l1.go = "SharlieEpilog_HaveWife_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_HaveWife_18":
			dialog.text = "";
			link.l1 = "미래의 알론소 드 모르 또는 작은 알론시타 드 모르에게!";
			link.l1.go = "SharlieEpilog_HaveWife_19";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_HaveWife_19":
			dialog.text = "";
			link.l1 = "아-하-하!";
			link.l1.go = "SharlieEpilog_HaveWife_20";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_20":
			dialog.text = "";
			link.l1 = "하하!";
			link.l1.go = "SharlieEpilog_HaveWife_21";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_21":
			dialog.text = "";
			link.l1 = "하하하!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_toast":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_toast");
		break;
		// <-- Выбрал остаться в поместье с женой
		
		// --> Выбрал остаться в поместье будучи холостяком
		case "SharlieEpilog_ChooseEstate_Single_1":
			dialog.text = "";
			link.l1 = "제가 아들이자 후계자가 된 것은 제게 큰 영광입니다. 우리 가문을 위해 모든 책임을 기꺼이 맡겠으며, 가문의 명예를 더욱 빛내기 위해 제 힘이 닿는 한 모든 것을 다하겠다고 약속드립니다.";
			link.l1.go = "SharlieEpilog_ChooseEstate_Single_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_ChooseEstate_Single_2":
			dialog.text = "";
			link.l1 = "말해 보시오, "+pchar.name+", 내 제안, 이본과 결혼하는 것에 대해 생각해 보았소?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_13":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean"))
			{
				link.l1 = "인정하겠어요, 아버지… 이본은 제 마음에 진정 가까운 사람이 아니었어요. 하지만 신세계에는 훌륭한 여인들이 많아요. 약속드리죠—진짜 인연을 만나면, 주저하지 않겠어요.";
			}
			else
			{
				link.l1 = "인정하겠어요, 아버지... 이본은 제 마음에 가까운 사람이 아니었어요. 하지만 프랑스에는 훌륭한 아가씨들이 많잖아요. 진정으로 가치 있는 사람을 만나면, 주저하지 않겠다고 약속드려요.";
			}
			link.l1.go = "SharlieEpilog_Single_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_14":
			dialog.text = "";
			link.l1 = "네 기백이 마음에 드는구나, 사랑하는 아들아. 자, 잔을 들어라—너를 위해, 네가 이룬 업적을 위해, 그리고 네가 마땅히 돌아온 이 집을 위해!";
			link.l1.go = "SharlieEpilog_Single_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_15":
			dialog.text = "";
			link.l1 = "진정한 친구들에게, 그들이 없이는 신세계에서 살아남을 수 없으니!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_Single_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_16":
			dialog.text = "";
			link.l1 = "찰스 선장과 그의 넓은 마음을 위하여!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_Single_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "선장의 강철 같은 의지에!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "우리 선장님의 지혜를 위하여!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "충성과 대의를 위하여!";
			}
			link.l1.go = "SharlieEpilog_Single_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_Single_18":
			dialog.text = "";
			link.l1 = "언제나 무사히 빠져나오기를!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		// <-- Выбрал остаться в поместье будучи холостяком
		
		// Шарль губернатор разговаривает с зелёным капитаном
		case "SharlieEpilog_GreenCaptain":
			dialog.text = "";
			link.l1 = "당신이 면담을 꼭 요청했다고 들었소. 그래서, 마르티니크 총독을 찾아온 이유가 무엇이오?";
			link.l1.go = "SharlieEpilog_GreenCaptain_1";
			locCameraFromToPos(-1.80, 3.84, -9.08, true, -2.38, 2.21, -7.33);
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer_common_2.wav");
		break;
		
		case "SharlieEpilog_GreenCaptain_1":
			dialog.text = "프랑스 왕실의 이익을 위해 봉사하는 일에 대해 이야기하고 싶소.";
			link.l1 = "그래, 네 모든 기지와 해상 전투 실력이 필요한 임무가 있네. 스스로를 증명할 준비가 되었나?";
			link.l1.go = "SharlieEpilog_GreenCaptain_2";
		break;

		case "SharlieEpilog_GreenCaptain_2":
			dialog.text = "각하, 곧 맡게 될 임무의 성격에 대해 좀 더 자세히 설명해 주시겠습니까?";
			link.l1 = "물론이지. 스페인 특송선 '산타 에스페란사'를 찾아서, 그 배에 올라 선장 선실에서 발견하는 모든 문서를 나에게 가져와야 하네. 내가 말한 그 배는 약 열이틀 후 트리니다드 근처를 지나갈 걸세.";
			link.l1.go = "SharlieEpilog_GreenCaptain_3";
		break;

		case "SharlieEpilog_GreenCaptain_3":
			dialog.text = "그치? 내가 이 일을 맡을게. 어떤 서류를 찾아야 하는 거야?";
			link.l1 = "우편물 말이오. 그 안에는 내게 아주 중요한 서류들도 있을 것이오. 하지만 서류를 일일이 확인할 필요는 없으니, 그냥 봉투째로 모두 가져오면 되오. 이 일의 대가로 만오천 페소를 주겠소... 그러니 결과를 가지고 내 저택에서 기다리겠소.";
			link.l1.go = "SharlieEpilog_GreenCaptain_4";
		break;

		case "SharlieEpilog_GreenCaptain_4":
			dialog.text = "오래 기다리게 하진 않겠사옵니다, 각하.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_5");
		break;
		
		//Шарль разговаривает с комендантом форта
		case "SharlieEpilog_KomendantFort":
			dialog.text = "각하... 보고드려도 되겠습니까?";
			link.l1 = "보고하라, "+GetAddress_Form(NPChar)+" "+npchar.lastname+".";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) link.l1.go = "SharlieEpilog_KomendantFort_1";
			else link.l1.go = "SharlieEpilog_KomendantFort_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\military02.wav");
		break;
		
		case "SharlieEpilog_KomendantFort_1":
			dialog.text = "에헴...";
			link.l1 = "편하게 말하게. 내 아내에게는 비밀이 없으니.";
			link.l1.go = "SharlieEpilog_KomendantFort_2";
		break;
		
		case "SharlieEpilog_KomendantFort_2":
			dialog.text = "첩보 보고: 윌렘스타트에서 함대가 출항했다네. 함대의 선두에는 2등급 전열함 ‘Gouden Leeuw’가 있는데, 진정한 바다의 괴물이지. 이 함대는 250문이 넘는 대포와 1,500명 이상의 병력을 자랑한다네. 그들의 목표는 생피에르라네.";
			link.l1 = "흠... 그럼 준비할 시간이 거의 없겠군.";
			link.l1.go = "SharlieEpilog_KomendantFort_3";
		break;

		case "SharlieEpilog_KomendantFort_3":
			dialog.text = "명령을 내리시지요, 총독 나리?";
			link.l1 = "우리에겐 여러 척의 배가 정박지에 닻을 내리고 있어. 적의 후방을 기습할 준비가 되어 있지...\n";
			link.l1.go = "SharlieEpilog_KomendantFort_4";
		break;

		case "SharlieEpilog_KomendantFort_4":
			dialog.text = "양쪽에서 그들을 공격할 생각이오?";
			link.l1 = "정확하오. 요새가 그들의 포화를 끌어낼 것이오. 그리고 밤이 되면, 내 지휘 하의 함대가 바다에서 공격할 것이오. 우리가 그들의 주의를 분산시키고, 그 다음엔 역청과 판자로 가득 찬 화선이 항구에서 출격할 것이오. 그들의 함대는 나뭇조각 하나 남지 않을 것이오.";
			link.l1.go = "SharlieEpilog_KomendantFort_5";
		break;

		case "SharlieEpilog_KomendantFort_5":
			dialog.text = "훌륭한 계획이십니다, 각하! 준비를 시작하라고 명령을 내릴까요?";
			link.l1 = "시작하자. 주님께서 우리와 함께하시길.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_11");
		break;
		
		// Стражник вызывает Алонсо
		case "SharlieEpilog_Guard":
			dialog.text = "";
			link.l1 = "경비병들, 알론소를 불러라.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoArrive");
		break;
		
		//Шарль разговаривает с Алонсо после коменданта
		case "SharlieEpilog_Alonso35":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
			{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
				dialog.text = "총독 나리...";
				link.l1 = ""+npchar.name+", 네덜란드 함대가 곧 도착해서 포위를 시작할 것이다. 내 명령을 잘 들어라: 필리프를 데리고 "+sld.name+", 그리고 즉시 그들을 수도원장에게 데려가게. 그가 모든 여자와 아이들, 노인들을 모아 그들의 안전을 책임지도록 하라.";
				link.l1.go = "SharlieEpilog_Alonso36_Wife";
				break;
			}
			dialog.text = "총독 나리...";
			link.l1 = ""+npchar.name+", 네덜란드 함대가 언제든 도착해 도시를 포위할 거요. 수도원장에게 가서 모든 여자와 아이, 노인들을 모아 안전을 확보하라고 전하시오. 자네는 화선 지휘를 맡길 생각이네. 자세한 내용은 추후에 알려주겠네. 무엇보다 민간인 보호가 최우선이네.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;

		case "SharlieEpilog_Alonso36_Wife":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "그렇지 않다고 생각해\n "+sld.name+" 다른 여자들과 합류하는 데 동의할 거야. 지루해서 죽을 지경이거든.";
			link.l1 = "흠... 그럼 그녀에게 전투 준비를 하라고 전해라. 너도 가만히 있진 않을 거다 — 화선의 지휘를 맡게 될 테니. 자세한 건 나중에 알려주마. 지금은 내 아들을 잘 돌봐라.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;
		
		case "SharlieEpilog_Alonso37":
			dialog.text = "영광입니다! 진행할까요?";
			link.l1 = "허락하오. 어서 가게. 우리에겐 매 순간이 소중하니.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_13");
		break;
		// --> Выбрал отправиться назад на Карибы с женой
		case "SharlieEpilog_ChooseCaribbean_HaveWife_1":
			dialog.text = "";
			link.l1 = "음... 솔직히 그렇게 말할 줄 알았소 – 물론 다른 대답을 기대하긴 했지만. 하지만 그대의 선택을 존중하겠소, 더 이상 설득하려 하진 않겠소.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_2":
			dialog.text = "";
			link.l1 = "내가 너를 실망시킨 거 알아. 하지만 이전에 했던 모든 말을 잊게 할 소식이 있어.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_3":
			dialog.text = "";
			link.l1 = "잘 듣고 있소.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "나는 여기서 적어도 1년은 머물 생각이야. "+sld.name+" 그녀의 상태로는, 흔들림은 절대 안 되지.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_5";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_5":
			dialog.text = "";
			link.l1 = ""+pchar.name+", 설마...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		// <-- Выбрал отправиться назад на Карибы с женой
		
		// --> Выбрал отправиться назад на Карибы один
		case "SharlieEpilog_ChooseCaribbean_Single_1":
			dialog.text = "";
			link.l1 = "음... 솔직히 말하자면, 네가 그렇게 말할 줄 알았어 – 물론 다른 대답을 기대하긴 했지만. 그래도 네 선택을 존중하니 더 이상 설득하려 하진 않겠네. 그런데 말이야,\n "+pchar.name+", 내 제안, 이본과 결혼하는 것에 대해 생각해 보았소?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		// <-- Выбрал отправиться назад на Карибы один
		
		//Диалог Шарль и Мишеля на Рифе Скелета
		case "SharlieEpilog_Mishelle_1":
			dialog.text = "참지 못했군, 그치?";
			link.l1 = "너?! 이게 꿈이란 말이야?";
			link.l1.go = "SharlieEpilog_Mishelle_2";
			SharlieEpilog_OnReefs_6();
			PlaySound("Voice\" + LanguageGetLanguage() + "\sharlie\mishelle-04.wav");
		break;

		case "SharlieEpilog_Mishelle_2":
			dialog.text = "쉬운 이득에 대한 갈증, 권력, 무적이라는 환상... 이 중 무엇이 너를 파멸시켰지, 형제여? 무엇이 네 정신을 흐리게 했나, 모든 백인들의 정신을 흐리게 하듯이?";
			link.l1 = "나가! 넌 그냥 유령일 뿐이야! 여긴 네가 있을 곳이 아니야!";
			link.l1.go = "SharlieEpilog_Mishelle_3";
		break;

		case "SharlieEpilog_Mishelle_3":
			dialog.text = "아직도 이해하지 못하겠나? Spectra sunt memoria peccatorum. 그 유령이 바로 자네야... 탐욕과 눈먼 허영에 사로잡힌 카리브의 전설적인 사내. 금을 위해 몇이나 죽였지, "+pchar.name+"?";
			link.l1 = "그래, 사랑하는 형제여, 너를 두 번 죽이는 것도 상관없지! 이건 네가 자초한 일이야!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_OnReefs_9");
		break;
		
		
		
		
		
	}
}