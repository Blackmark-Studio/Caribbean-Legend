void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

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

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- леди в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && sti(npchar.nation) == SPAIN) {
				link.chickengod = "Senora, please excuse me, but I was asked to tell you that you have... a date inside an old pagan pyramid.";
				link.chickengod.go = "chickengod";
			}
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("なんてこと！私の部屋にこんな卑劣な男が！出ていきなさい、さもないと衛兵を呼びますわ！","こんなことがあってたまるか……誰がこのネズミを俺の家に入れやがったんだ？出て行け、この野郎！お前に用はねえ！さっさと消えろ！","奇妙な時代になったもんだ。俺の寝室にまでネズミが入り込んできやがる！出ていけ！");
				link.l1 = RandPhraseSimple("落ち着けよ……","口の利き方に気をつけろ……");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("俺の寝室で何してやがる？さっさと出ていけ！","なんてことだ！すぐにここを立ち去ってくれ！","失礼ですが、旦那、ここには招待されていません。どうか、私の部屋から出てください！");
				link.l1 = RandPhraseSimple("失礼する……私はこれで失礼します。","すまねえ、部屋を間違えた。行かなくちゃ。");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "ああ、今のは何だ！？俺はなんて間抜けなんだ！歩き回ってて、何も見えなかった……衛兵！！";
			link.l1 = "黙れ！";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("ここから失せろ、このクソネズミめ！","すぐに総督の屋敷から出て行け、このネズミ野郎！","お前が総督の屋敷で何をしていようが俺には関係ねえ "+XI_ConvertString("Colony"+npchar.city+"Gen")+"だが俺の忠告だ、今すぐ消えな！");
				link.l1 = RandPhraseSimple("気楽にしろよ、相棒……","言葉に気をつけろ！");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("ごきげんよう！私は総督の召使いです。私の名前は "+GetFullName(NPChar)+".","「俺がこの場所を見張ってるんだ」 "+GetAddress_Form(NPChar)+".","「知ってるか、」 "+GetAddress_Form(NPChar)+"、うちの総督はいい人で、俺たちにもちゃんと報酬をくれるんだ…");
				link.l1 = RandPhraseSimple("いいね。","ふむ、よかろう……");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "まさか総督を襲うつもりだったのか！？\n衛兵ども、この盗人を捕まえろ！！";
			link.l1 = "黙れ！";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("ここから出て行ったほうがいいぜ。 "+GetSexPhrase("相棒","少女")+"...","「消え失せろ！」","「ドアを外したな」 "+GetSexPhrase("相棒","少女")+"？ ？この領地は総督のものだ "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				link.l1 = RandPhraseSimple("俺が出ていくのは俺が好きな時だぜ！","お前には関係ねえ……");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("今日はここで勤務するよう命じられたんだ。いい場所だな……","私は～の領地を守っている "+GetAddress_Form(NPChar)+".","私の命令は総督の屋敷を守ることだ。");
				link.l1 = RandPhraseSimple("それじゃあ、幸運を祈るぜ……","ふむ、なるほど……");
				link.l1.go = "exit";
			}
		break;
		
		case "chickengod":
			pchar.questTemp.ChickenGod.Tasks.o2.Counter = sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3) {
				dialog.text = "ああ、そうだ。やっとだな！"+pchar.name+"船長、一緒に行く準備はできてるぜ。";
				link.l1 = "「そんなに簡単に？旦那、これが本当にご希望ですか？」";
				link.l1.go = "chickengod_accept";
			} else {
				sld = CharacterFromID(npchar.city + "_Mayor");
				dialog.text = "「なんだと！？酔ってるのか、旦那？なんて馬鹿げた冗談だ！お願いだから、どこかへ行ってくれ、頼む！」 "+sld.name+"「おい！衛兵！助けてくれ！」";
				link.l1 = "くそっ、行く時間だ。";
				link.l1.go = "chickengod_decline";
			}
			npchar.quest.chickengod = true;
		break;
		
		case "chickengod_accept":
			dialog.text = "もちろんだとも！ああ、アルバ旦那と私は長い間、文通をしているんだよ！";
			link.l1 = "それなら、どうぞ乗船してください！";
			link.l1.go = "chickengod_accept_take";
			link.l2 = "いいえ、旦那、それはいけません。俺の名誉が女性を危険にさらすことを許さないし、あなたは明らかに騙されている！";
			link.l2.go = "chickengod_accept_nottake";
		break;
		
		case "chickengod_accept_take":
			DialogExit();
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
			AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;
		
		case "chickengod_accept_nottake":
			dialog.text = "その場合はね、親愛なる船長さんよ、お前の田舎臭い名誉心なんざ尻の穴にでも突っ込んじまいな！ 俺は他の使者を待つぜ、お前みたいに頭の固くねえ奴をな！";
			link.l1 = "魅力的だな！";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			SetFunctionTimerCondition("ChickenGod_NotTakeLadyConsequence", 0, 1, 0, false);
		break;
		
		case "chickengod_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_LadyRefuse");
		break;
		
	}
}
