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
			dialog.text = "俺たちに話すことなんてねえ！";
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
			dialog.text = NPCStringReactionRepeat("こんにちは！私の名前は  "+GetFullName(npchar)+"。何かご用ですか？","また会ったな！","この辺境では客なんて滅多に来ねえんだよ……","新しい顔と話せるなんて本当に嬉しいわ！あの古くさい連中にはもううんざりしてるのよ……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「ああ、なんでもないさ……」","俺もだ……","なるほど……","へっ……",npchar,Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "ここで真珠を集めて、奉公している  "+NationNameGenitive(sti(npchar.nation))+"……だよな……";
			link.l1 = "ああ、知ってるさ…";
			link.l1.go = "exit";
			link.l2 = "おい、聞いてくれよ、こういう小物を何個か“作り手”から直接買うことってできるのか？どう思う？";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "「いやいや、とんでもない！小さな真珠一粒の盗みでも死罪になるんだ！」";
				link.l1 = "ここは残酷な命令ばかりだな、まったく……";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "ああ、ここじゃ厳しい命令があって、何かやらかせばすぐに首が飛ぶんだ。俺はこの件には関わってねえが、 地元のインディアンたちに話を聞いてみるといいぜ。奴らは何かあれば逃げる場所があるから、 俺たちよりも大胆なはずさ…";
				link.l1 = "なるほど……わかった、ありがとう。";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("「お前は本当に」  "+GetSexPhrase("「狂ってる？消え失せろ、この馬鹿野郎」","狂ってる？消え失せろ、この馬鹿野郎")+"!",""+GetSexPhrase("「何だと！？正気じゃねえのか、このバカ野郎」","「なんだと！？正気じゃねえのか、この馬鹿女」")+"！？うるせえな、質問ばっかしやがって……",""+GetSexPhrase("気でも狂ったのかい、あんた？どんな海賊だって？ここに！？さっさと消えな、この間抜け","気でも狂ったの、あなた？どんな海賊よ？ここに！？さっさと消えなさい、この馬鹿な娘ったら\n")+"...");
			link.l1 = RandPhraseSimple("無礼にする必要はないぞ……","舌の使い方に気をつけろ！");
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","「白い女インディアン」")+" 話がしたいのか？","「またお前か。」 "+GetSexPhrase("色白","「白い女インディアン」")+".",""+GetSexPhrase("青白い顔のやつはよくしゃべるな。まるで女みたいだぜ。","白人女はおしゃべりが好きだな。")+"","精霊が俺の青白い顔をここへ運んだ "+GetSexPhrase("兄弟","姉妹")+" 私に。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「ああ。」","ああ、また俺だ。","とても詩的だな。","俺も会えて嬉しいぜ",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "教えてくれ、なぜ来たんだ？";
			link.l1 = "ああ、別に用はないさ。ただ、お前の話を聞きたかっただけだ。";
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "船長、何をしているんだ？大事になる前に武器をしまえ！";
			link.l1 = LinkRandPhrase("「よし。」","「いいだろう。」","心配するな、もう片付けてるところだ…");
			link.l1.go = "exit";
		break;  

	}
}
