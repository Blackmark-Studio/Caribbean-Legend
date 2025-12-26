void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("형제들아, 종교재판소 안에 적이 있다!","경보를 올려라, 형제들아!");
					link.l1 = "확실히, 종교재판소의 적들이 경계하고 있군...";
					link.l1.go = "fight";			
			}
			else
			{	
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("이봐, "+GetSexPhrase("아들아","내 딸")+". 무슨 일로 여기 왔나?.. ","우리 거처에 오신 것을 반갑게 맞이합니다, "+GetSexPhrase("아들아","내 딸")+"... 무슨 일로 여기 온 거지?"),""+GetSexPhrase("아들아","딸아")+", 오늘 이미 이야기했소. 또 필요한 것이 있소?",""+GetSexPhrase("아들아","딸아")+", 우리 교단의 시종들은 무한한 인내심으로 유명하지 않소. 그러니 다시 한 번 묻겠소: 필요한 것이 있소?",RandPhraseSimple("너 때문에 다른 사람들이 자기 일에 집중을 못 하고 있네. 더 이상 너와 이야기하지 않겠어.",""+GetSexPhrase("아들아","딸아")+", 나는 쓸데없고 의미 없는 말은 좋아하지 않아. 더 이상 너와 이야기하지 않을 거야."),"block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("그냥 들렀다네...","완전히 일로 가득 차 있군..."),"아, 안 돼요, 신부님......","아니오, 신부님, 그냥 이야기나 좀 하고 싶어서요...",RandPhraseSimple("흠...","그래요, 아버지 뜻대로 하겠습니다..."),npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "무장하라! 저건 첩자다! 잡아라!";
					link.l1 = "카라암바!";
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase("여기는 경비가 삼엄한 감방이니, 출입이 엄격히 금지되어 있다.","들어올 생각도 하지 마라, 들어오면 사형이다.","이 감방에 한 발짝만 더 들어오면 끝장이다.");
					link.l1 = RandPhraseSimple("알겠다, 병사.","알겠어...");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("호호, 저 '성인'들이 지옥으로 곧장 가는 걸 보는 게 정말 웃기지 않아?!","이런, 정말로 누가 그들에게 도전했단 말이야?!","그놈들이 나를 거의 죽을 때까지 고문했어, 곧 죽겠지만, 네가 내 인생 마지막으로 나를 행복하게 해줬어...");
					link.l1 = RandPhraseSimple("헤헷!","천만에...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("저 위선자들은 정말 인간 같지 않아. 우리한테 한 짓 때문에 지옥불에 떨어질 거야...","매일 나를 고문하고 괴롭혔소! 하지만 나는 우리 주님 앞에서 죄가 없소!","내 감방 동료가 어제 죽었어... 이틀 동안 형틀에 묶여 고문당했지... 내가 얼마나 더 버틸 수 있을지 누가 알겠어...");
					link.l1 = RandPhraseSimple("흠... 글쎄, 잘 모르겠는데...","아, 그렇군...");
					link.l1.go = "exit";
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
	}
}
