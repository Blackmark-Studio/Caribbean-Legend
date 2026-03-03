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
					dialog.text = RandPhraseSimple("兄弟たちよ、異端審問官の中に敵がいるぞ！","警報を鳴らせ、同志たち！");
					link.l1 = "確かに、異端審問の敵どもは警戒しているようだな……";
					link.l1.go = "fight";			
			}
			else
			{	
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「やあ、」 "+GetSexPhrase("息子よ","娘よ")+"……何の用でここに来たんだ…… ","「我々の住処へようこそ、お会いできて嬉しいです」 "+GetSexPhrase("息子よ","娘よ")+"……何の用でここに来たんだ？"),""+GetSexPhrase("息子よ","娘よ")+"、今日はもう話しただろう。他に用でもあるのか？",""+GetSexPhrase("息子よ","「娘よ」")+"、我らの修道会の侍者たちは無限の忍耐力で知られているわけではありません。\nそれでは、もう一度聞きますが、何かご用ですか？",RandPhraseSimple("お前は他の者たちの仕事の邪魔をしている。これ以上お前とは話さない。",""+GetSexPhrase("息子よ","「娘よ」")+"、俺は無駄で意味のない話が好きじゃねえ。もうお前とは話さねえぞ。"),"ブロック",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("ちょっと立ち寄っただけだ……","「仕事で手一杯だな……」"),"「ああ、いやだ、神父様……」","いいえ、神父様、ただ話がしたかっただけです……",RandPhraseSimple("ふむ……","「まあ、お望みなら、神父様……」"),npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "武器を取れ！スパイだ！あいつを捕まえろ！";
					link.l1 = "「カランバ！」";
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase("ここは監視付きの牢屋だ、そして立ち入りは厳禁だ。","入ることなど考えるな、死刑に処されるぞ。","この牢屋に一歩でも踏み込めば、お前の人生は終わりだ。");
					link.l1 = RandPhraseSimple("なるほど、兵士。","了解だ…");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("ホッホー、「聖人」どもがまっすぐ地獄に落ちていくのを見るのはおかしいじゃねえか！？","まあまあ、誰か本当にあの連中に挑んだのかしら！？","奴らは俺を死ぬ寸前まで拷問した……もうすぐ俺は死ぬだろうが、あんたのおかげで人生で最後に幸せを感じられた……");
					link.l1 = RandPhraseSimple("へっ！","どういたしまして…");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("あいつら偽善者どもはまったく人間じゃねえ。俺たちにしたこと、全部地獄で焼かれるに決まってる…","毎日奴らに拷問され、苦しめられたんだ！\nだが、私は我らの主の御前では無実だ！","俺の同房者は昨日死んじまった…やつは二日間も拷問台で責められてたんだ…俺があとどれだけ耐えられるか、誰にもわからねえ…");
					link.l1 = RandPhraseSimple("うーん……そうだな、俺にはわからねえな……","「ああ、そうか……」");
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
