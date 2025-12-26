void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "우리 사이에 더 이상 할 말 없어!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("안녕하세요! 제 이름은  "+GetFullName(npchar)+". 무엇을 도와드릴까요?","또 다시 인사하오!","이런 외진 곳엔 손님이 정말 드물지...","새로운 얼굴과 이야기하니 정말 즐겁네요! 저 늙은 주둥이들은 이제 지긋지긋하거든요...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("아, 아무것도 아니야...","나도 그래...","그렇군...","헤헷...",npchar,Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "여기서 진주를 모으고, 시중을 들고 있지  "+NationNameGenitive(sti(npchar.nation))+", 있잖아...";
			link.l1 = "그래, 나도 알아...";
			link.l1.go = "exit";
			link.l2 = "이봐, 들어봐, 이런 작은 장신구들을 '제작자'한테서 직접 여러 개 살 수 있을까? 어떻게 생각해?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "아니, 절대 아니지! 작은 진주 한 알만 훔쳐도 사형이야!";
				link.l1 = "여기 명령이 참 잔혹하군, 그건 확실하지...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "그래, 여기서는 명령이 엄격해서 잘못하면 금방 목이 날아가. 나는 이 일에 관여하지 않았지만, 현지 인디언들과 이야기해 보라고 조언해 줄 수 있어. 뭔가 잘못되면 그들은 도망칠 곳이 있으니 우리보다 더 대담할 거야...";
				link.l1 = "알겠어... 좋아, 고마워.";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("너 완전히  "+GetSexPhrase("미쳤어? 꺼져, 이 멍청아","미쳤어? 꺼져, 이 멍청한 놈아")+"!",""+GetSexPhrase("뭐?! 제정신이야, 이 바보야","뭐?! 미쳤어, 이 멍청한 계집애야")+"?! 질문 그만하고 꺼져...",""+GetSexPhrase("정신 나갔어, 자기야? 무슨 해적? 여기서?! 그냥 꺼져, 이 멍청아","정신 나갔어, 자기야? 무슨 해적? 여기서?! 그냥 꺼져, 이 바보 같은 계집애야")+"...");
			link.l1 = RandPhraseSimple("무례하게 굴 필요는 없어...","말 조심해라!");
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","백인 여자 인디언")+" 이야기하고 싶은가?","또 너냐, "+GetSexPhrase("창백한 얼굴","백인 여자")+".",""+GetSexPhrase("창백한 얼굴은 말이 많군. 인디언 여자처럼 보이네.","하얀 여자놈은 말하는 걸 좋아하네.")+"","영혼들이 내 창백한 얼굴을 데려왔지 "+GetSexPhrase("형제","자매")+" 나에게.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그래.","그래, 또 나야.","참 시적이군.","나도 당신을 다시 보게 되어 기쁩니다",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "말해 보시오, 왜 왔소?";
			link.l1 = "아, 별건 아니고, 그냥 네가 무슨 말을 하나 듣고 싶어서.";
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "선장님, 뭐 하십니까? 큰일 나기 전에 무기를 집어넣으십시오!";
			link.l1 = LinkRandPhrase("좋아.","좋아.","걱정 마, 이미 치우고 있어...");
			link.l1.go = "exit";
		break;  

	}
}
