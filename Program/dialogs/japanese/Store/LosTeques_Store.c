void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("町で警報が鳴っているぞ。みんなお前を探してる！俺ならここに長居はしねえな。","町中の衛兵があんたを探して町をくまなく捜索してるんだ。俺は馬鹿じゃないし、あんたと話すつもりはないぞ！","逃げろ、相棒、兵隊どもにミンチにされる前にな…"),LinkRandPhrase("何の用だ、このろくでなしめ！？今まさに町の衛兵がお前を追っているぞ。汚い海賊風情が、 そう遠くへは行けねえからな！","「俺の家から出て行け、殺人者め！衛兵！！」","俺はお前なんか怖くねえぞ、この悪ガキめ！すぐにお前は絞首刑だ、逃げられやしねえ…"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("へっ、警報なんざあんまり気にしちゃいねえよ……","奴らが俺を捕まえるなんて無理だぜ。"),RandPhraseSimple("黙ってろ "+GetWorkTypeOfMan(npchar,"")+"、さもねえと、その汚え舌を引っこ抜いてやるぞ！","へっ、 "+GetWorkTypeOfMan(npchar,"")+"、お前も海賊狩りをしたいのか！いいか、相棒、落ち着いていれば命は助かるぜ……"));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"「！お前さんの顔は初めて見るな、旦那。もしかして船長かい……当たりか？私の名は」 "+GetFullName(npchar)+"、そして私の店はあなたのご用命をお待ちしております。金銀はもちろん、 好奇心旺盛な方の興味をそそる品も多数ございます。";
				Link.l1 = "なるほど。私は "+GetFullName(pchar)+"。お会いできて光栄です "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+"、旦那！また私の店にお越しいただき嬉しいです。金塊をお求めですか？それとも今日は鉱石にご興味がありますか？";
				link.l1 = "「商品を見せてくれ」 "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "いいえ、何も必要ありません。 "+npchar.name+"。ちょっと挨拶に立ち寄っただけです。";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "私も同じ気持ちですよ、旦那。私の品物をご覧になりますか？きっとご興味を引くものがございます。";
			link.l1 = "ここに来るのは初めてなので、この居留地についてもう少し知りたいのですが。";
			link.l1.go = "info";
			link.l2 = "それでは、売り物を見せてくれ。";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "この小さな町は金鉱のおかげで築かれたんだ。ここでは金鉱石や銀、それに金塊を採掘している。 時には宝石が出ることもある。昔は駐屯兵しかいなかったが、 友好的なインディアンや白人の入植者が加わってくれたんだ\nイグナシオ・オルテガが酒場を建ててくれて、我々の暮らしも少し明るくなった。いろんな冒険者がここを訪れては、 俺たちを襲おうなんて愚かな考えを持ってくる。ここには裁判所がないから、 町のど真ん中で何人かの馬鹿を吊るしてからは、そういう連中も減ったよ\n金鉱石は兵士や友好的なインディアンの護衛のもとで船に運ばれるが、金塊ならこの店で直接買うことができる\nそれに、時々とても珍しい鉱石も扱っているから、時間があるときはぜひ寄ってくれ。 いつも新しい品を仕入れているからな。";
			link.l1 = "興味深い話をありがとう！覚えておくよ。";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("白昼堂々の強盗だと！！！ここで一体何が起きてるんだ！？待て、ちょっと待ってくれ、友よ…","おい、そこで何してやがる！？俺を盗もうってのか？もう終わりだな……","待て、てめえ、何してやがる！？やっぱり盗人だったか！ここで終わりだ、この野郎…");
			link.l1 = LinkRandPhrase("「悪魔め！！」","「カランバ！！」","「ああ、くそっ！」");
			link.l1.go = "fight_owner";
		break;
		
		case "fight_owner": // лесник . выход из диалога . если копался в сундуках. 
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
