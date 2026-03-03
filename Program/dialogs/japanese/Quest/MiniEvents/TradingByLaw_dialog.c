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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "「何もない。」";
			link.l1.go = "exit";
		break;

		case "Kristian":
			dialog.text = "俺のつましい住まいへようこそ！俺はクリスチャン。クリスチャン・デルースだ、よろしく頼むぜ。 今日はどうして俺の家まで来たんだ？";
			link.l1 = "名は船長だ "+GetFullName(pchar)+"。俺は大量の酒を手に入れたいんだ。言いたいことは分かるだろう？";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_2":
			dialog.text = "なんだと！？誰がそんなデタラメを広めたんだ？とんでもない誤解だ、断言する！俺はどんな酒とも無縁だぜ！";
			link.l1 = "ほうほう……どうやら俺が探していた相手を見つけたようだな。";
			link.l1.go = "Kristian_3";
		break;

		case "Kristian_3":
			dialog.text = "おお、なんてことだ、いやいやいや！なんて濡れ衣を着せるんだ！酒の取引だと？俺が？いや、その、ええと、つまり……わかった、確かに多少の酒は持ってるが、全部ちゃんと合法なもんだ！俺はただ、一般市民のために、ええ……宴会やささやかな集まり用の飲み物を用意してるだけさ！";
			link.l1 = "なぜそんなに震えているんだ、旦那？俺はお前の看守として来たんじゃねえ、恩人として来たんだぜ。 お前の運が上向くかもしれねえし、ついでに俺の財布もドゥブロン金貨で少し重くなるって寸法よ。";
			link.l1.go = "Kristian_4";
		break;

		case "Kristian_4":
			dialog.text = "俺が？き、緊張してるだと？馬鹿な！俺が緊張する理由なんてあるか？俺は潔白な人間だぜ――住まいは総督邸のすぐそばだしな！名誉にかけて、法なんざ一切破っちゃいねえよ！";
			link.l1 = "つまり、酒の取引には関わっていないってわけか？そりゃあ、まったく残念だぜ。俺はな、 大きな儲け話を持ってきたんだ。しがない裏商人じゃ想像もできねえほどのドゥブロンが手に入るチャンスだったのによ。 だが、お前が俺の相手じゃねえなら、これ以上は邪魔しねえで立ち去るとするさ。……ただし、もしや……？";
			link.l1.go = "Kristian_5";
		break;
		
		case "Kristian_5":
			dialog.text = "「ああ……ちょっと待て……」 "+GetAddress_Form(NPChar)+"…申し訳ありません、嵐の中のカモメのように頭が混乱してしまって、 あなたのご立派なお名前をすっかり忘れてしまいました。";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "Kristian_6";
		break;

		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" "+pchar.lastname+"…実を言うと、私…その…あなたがお探しの人物の居場所を知っているかもしれません。その方に…あなたの寛大なご提案をお伝えすることはできます。";
			link.l1 = "伝言役？冗談だろう。本当に、こんな繊細な事柄を余計な手を介して伝えるべきだとお思いか？";
			link.l1.go = "Kristian_7";
		break;

		case "Kristian_7":
			dialog.text = "おっしゃる通りだ。しかし…神よお助けを…もう運命は決まった…そうだ、俺は確かにあんたの男だ。";
			link.l1 = "これで話が通じたな、クリスチャン。酒場は酒が深刻に不足していてな、 この状況から俺たち二人ともたっぷり儲けられると思うぜ。";
			link.l1.go = "Kristian_8";
		break;

		case "Kristian_8":
			dialog.text = "船長、宿屋の主人の悩みはよく知っております。人々が私のもとに押しかけてきて、今では商売を続けるのが怖いのです――あまりにも多くの目がこちらを見張っていますから。できればあなたに……いえ、あなたほどの地位の方なら、もしかして……";
			link.l1 = "「自分で宿屋の主人に商品を持ち込んでみたらどうだ？」";
			link.l1.go = "Kristian_9";
		break;

		case "Kristian_9":
			dialog.text = "あいつは……俺と取引するくらいなら、ハンセン病患者を抱きしめる方がマシだと思ってやがる。あのうぬぼれ屋は、 俺みたいな身分のしがない商人なんざ、軽蔑しかしてねえんだ。";
			link.l1 = "確かに、彼の評判はすでに知れ渡っている。あなたの申し出を直接受け取れば、彼は軽蔑するかもしれない。しかし、 俺を通して差し出せば――それはまったく別の話だ。";
			link.l1.go = "Kristian_10";
		break;

		case "Kristian_10":
			dialog.text = "お前が仲介役を買って出るのか？その取り決め、俺は大いに気に入ったぜ……最近、途方もない量の積荷を手に入れたんだ――こんな大量は初めてだ！半年は地下倉庫が満杯になるほどだったろうよ。だが全能なる神のご加護で、 間一髪で発覚を免れたんだ\nいまだにどうやって総督の網をすり抜けたのか理解できねえ。こんな真似を二度もやったら、身の破滅ってもんだぜ。";
			link.l1 = "ならば、そろそろ表に出る時かもしれねえな。全部じゃなくてもいい、 だが少しは危険を減らして自分の用事を済ませられるくらいにはな。";
			link.l1.go = "Kristian_11";
		break;

		case "Kristian_11":
			dialog.text = "光の中へ…だと？だが…それには強力な後ろ盾が必要だぜ！それに相当な金もな！何のためだ？まさか、自分の船を持つ海の船長であるお前が、 ずっと錨を下ろしてただの酒場の納入業者になるつもりじゃねえだろうな？\n";
			link.l1 = "繋がりについては、俺の手が届く範囲はあんたの及ばぬ所まで広がっている。\n資金面だが……投資額は控えめで済むはずだ。\nそして最後の懸念について――心配はいらねえ。あんたはこの件で俺の代理人として動くんだ。俺があんたの盾となり、 あんたは俺の安定した供給源となる。\nこの取り決めは長く続き、お互いに利益をもたらすだろう。あんたは信頼できる取引先を得て、 俺は確かな商品を手に入れる。\nこんな商売話、どう思う？";
			link.l1.go = "Kristian_12";
		break;

		case "Kristian_12":
			dialog.text = "これは何か巧妙な罠だと確信していた。しかし実のところ、あなたの提案は……実に魅力的に聞こえる。安定、信頼……まさかこんな幸運が自分に訪れるとは思いもしなかった。 "+GetSexPhrase("Monsieur","Mademoiselle")+"、全面的に賛成だ！どれくらいの量を購入したいんだ？";
			link.l1 = "まずは貴殿の商売をきちんと軌道に乗せましょう。それから詳細について話し合います。\n現在、貴殿の倉庫にはラム酒とワインがそれぞれどれほどありますかな？";
			link.l1.go = "Kristian_13";
		break;

		case "Kristian_13":
			dialog.text = "まさに今この瞬間か？ああ……それなら私の地下貯蔵庫を見てみるべきかもしれませんね。そこで在庫を正確にご確認いただけますよ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// спускаемся в погреб
		break;
		
		// погреб
		case "Kristian_15":
			dialog.text = "さて……どんな宝が眠っているかな？ああ、そうだ\n今の在庫は上質なラム酒がちょうど百本、そして極上のワインも百本あるぜ。";
			link.l1 = "まずまずの出だしだと言えるな。君の輸入の問題が解決したら、毎月必ずこの納品を続けられるか？";
			link.l1.go = "Kristian_16";
		break;

		case "Kristian_16":
			dialog.text = "もちろんでございます、船長！いや、三倍でもやれますぞ、いやいや……四倍でも大丈夫です！遅れなど決してございません――常に十分な備蓄を維持し、どんな不運があろうとも、供給に支障が出ぬよう即座に対応いたします。";
			link.l1 = "この積み荷の値段を言え。";
			link.l1.go = "Kristian_17";
		break;

		case "Kristian_17":
			dialog.text = "俺が考える公正な支払いは、ワイン十本ごとにドゥブロン金貨十枚、ラム酒十本ごとに三枚だ。\nつまり、積み荷すべてで百三十ドゥブロンってわけだ。";
			link.l1 = "承知した。宿屋の主人と話をつけて、すぐ戻ろう。";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "船長、何か知らせは？宿屋の主人との話し合いはどうだったんだ？";
			link.l1 = "まだ彼とは話していない。次は彼に会いに行くつもりだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;

		case "Kristian_21":
			dialog.text = "どうだった、船長？宿屋の主人と合意に達することができたか？";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "見事にやってのけたぞ、クリスチャン。あいつはこれと今後の全ての積荷を二百四十ドゥブロンで買うと言っている。 最初の荷物については、お前が要求した百三十を払って、残りは俺の報酬としてもらう。だが、 今後の利益はすべてお前のものだ。";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "俺はうまくやったぜ、クリスチャン。あいつはこれと今後の積荷を二百ドゥブロンで買うってさ。最初の分は、 お前が要求した百三十ドゥブロンを払う。差額は俺の正当な報酬としてもらっておくぜ。今後の利益は全部お前のものだ。 ";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_22":
			dialog.text = "それは驚くべき知らせだぜ、船長！こんな取引、夢にも思わなかった――感謝する！\nだが……もしかして急ぎすぎたんじゃねえか？総督が……俺は……その……";
			link.l1 = "総督はよく承知している。これからは毎月百ドゥブロンの料金を支払い、正式な交易報告書を提出してもらうぞ。";
			link.l1.go = "Kristian_23";
		break;

		case "Kristian_23":
			dialog.text = "信じられない！どうやってやったんだ、船長？総督は厳格な男で、闇商人の手強い敵なんだぞ……";
			link.l1 = "そういうことなんだ、クリスチャン――あいつは不正な取引には反対だが、正当な商売には口を出さない。俺の話をちゃんと聞いてくれて、 島での酒取引について明確な条件を提示してくれた。これからは俺の名の下で動くことになる。何かやらかせば、 お前だけじゃなく俺も責任を負う。だから絶対にしくじるなよ、さもないと死んだ後でもお前を追い詰めてやるからな。";
			link.l1.go = "Kristian_24";
		break;

		case "Kristian_24":
			dialog.text = "誓いますぜ、船長、絶対に後悔はさせません！";
			link.l1 = "これから宿屋の主人との話を片付けて、それから俺たちの取り決めの詳細を詰めようぜ。";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "もちろんでございます、船長。今すぐ荷物を受け取るご準備はできておりますか？ それでしたら百三十ドゥブロンになります。";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "「ああ、これがあんたのドゥブロン金貨だ。」";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "今は必要な資金が足りない。ここで待っていてくれ——支払いを持って戻ってくる。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_25_1":
			dialog.text = "船長！品物を受け取りに戻ったのか？値段は百三十ドゥブロンのままだぜ。";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "確かに受け取ったぜ！ほら、報酬だ。";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "残念ながら、まだ資金が足りません。後ほどまた参ります。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_26":
			dialog.text = "助かったぜ！持っていけ！約束通り、ワイン百本とラム酒百本だ。";
			link.l1 = "俺の船員たちが積荷の世話をする。\nその間に、俺は宿屋の主人と話をしなきゃならねえ。";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = ""+pchar.name+"！こんなに早く戻ってきたのか！どうだ、我々の取り決めはうまくいったのか？";
			link.l1 = "すべて見事に運んだな、クリスチャン。酒場の主人は今後、月に二度同じ量の品を求めるそうだ。 彼の店に酒を絶やさず届け続ければ、すぐにでも「貧しさ」などという考えとはおさらばできるだろう。";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_32":
			dialog.text = "船長……あなたが……まるで天の導きで私の元へ来てくださったかのようです！まさしく奇跡が目の前で起きたのです――この幸運が信じられません！\nいかなる善行で私はこのようなご慈悲にあずかったのでしょうか？感謝の言葉もございません！";
			link.l1 = "だが、キリスト教徒よ、俺が教えてやろう。毎月、お前の最上級の商品から選りすぐりの一部を、 俺専用に取り置きするんだ。他の誰にも売ってはならん。俺はお前が提示した値段――ワイン十本につき十ドゥブロン、ラム十本につき三ドゥブロン――で買い取るぞ。";
			link.l1.go = "Kristian_33";
		break;

		case "Kristian_33":
			dialog.text = "「この上ない喜びでございます」 "+pchar.name+"、あんた専用の仕入れ分を確保しておくぜ！俺の名誉にかけて、絶対に期待は裏切らねえ！どれくらい必要なんだ？ 五十本か？それとも百本か？欲しい数を言ってくれよ！";
			link.l1 = "その量は今の私の必要を超えております。各種二十本ずつで十分でございますわ。もし必要が増えましたら、 すぐにお知らせいたしますわ。";
			link.l1.go = "Kristian_34";
		break;

		case "Kristian_34":
			dialog.text = "かしこまりました、かしこまりました！では決まりですね――ワイン二十本とラム二十本で二十六ドゥブロン。毎月十五日には商品をご用意してお待ちしております。ご挨拶だけでも、 いつでもお越しいただければ光栄です！";
			link.l1 = "素晴らしい！最後にもう一つ強調しておきたいことがある、クリスチャン。私はお前の誠実さに自分の評判を賭けたんだ。 裏切るなよ、さもなくばその報いを思い知ることになるぞ。";
			link.l1.go = "Kristian_35";
		break;

		case "Kristian_35":
			dialog.text = "俺……ど、どういうご提案をなさるんですか、船長……まさか……い、いや、絶対にご期待は裏切りません！すべてはこの魂にかけて、完璧な礼儀をもって行いますとも！";
			link.l1 = "では、またどこかで道が交わるその時まで！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = "おせっかいなやつ "+GetSexPhrase("「cur」","あばずれ")+"！自分に関係ないことに首を突っ込むと不幸を招くだけだって教わらなかったのか？";
			link.l1 = "俺の船に勝手に乗り込んできたのはお前だろうが、今さら俺を邪魔したとでも言うつもりか？頭がどうかしちまったのか？ ";
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			dialog.text = "「雷に俺のフォアマストを吹き飛ばされちまえ！さて、お前、」 "+GetSexPhrase("惨めな子犬野郎","役立たずのあばずれ")+"、お前がどんな厄介ごとに首を突っ込んだか、まるで見当もついてねえのか？ 酒場の物資がただ偶然に消えたとでも思ったのか？";
			link.l1 = "あの蒸留所を灰にした責任を自分が負うつもりか？";
			link.l1.go = "Pirate_3";
		break;

		case "Pirate_3":
			dialog.text = "ははは、やっとその分厚い頭に真実が突き刺さったか、俺の腹を鎖弾がぶち抜きやがれ！そうさ、全部俺の仕業だ！ あの納入業者はこの商売に根を張りすぎてたんだよ。だが見ての通り、俺はいつだってライバルを叩き潰してきた。 そしてお前も同じ運命を辿るのさ、俺の帆を霰弾がズタズタにしやがれ！";
			link.l1 = "実に愉快だな。さて、お前の腕前を見せてもらおうじゃねえか。ネプチューンの獣どもがその死体を食らうがいい！ ハッハッハ！";
			link.l1.go = "Pirate_4";
		break;
		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Kristian_41":
			dialog.text = "「ごきげんよう。」 "+pchar.name+"！どんな順風に乗って俺のもとへ来たんだ？";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // торговля вином и ромом
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "ごきげんよう、クリスチャン。俺の品物は用意できてるか？";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "ごきげんよう、クリスチャン。あなたの用事が順調に進んでいるか確かめたかっただけです。これ以上はお邪魔しません。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;

		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "もちろんでございます、船長！私の勤勉さに少しでも疑いをお持ちですか？";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "一瞬たりとも疑っていない、クリスチャン。約束通りの支払いだ。では、今から酒をいただくとしよう。";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "まったくその通りだ。残念ながら、今は財布が軽すぎて困っている。また資金が整ったら戻ってくるとしよう。";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "もちろんでございます、船長！私の勤勉さに少しでも疑いをお持ちになるのですか？";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "一瞬たりとも疑わなかったぞ、クリスチャン。約束通りドゥブロン金貨だ。今から酒は俺が受け取るぜ。";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "まったくその通りだ。あいにく、今はまともな支払いができないのだ。財布が十分に重くなったら、 また戻ってくるとしよう。";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // увеличить объём поставок вина и рома
			{
				link.l4 = "クリスチャン、定期注文を増やしたいんだ。正確にはラム酒とワインをそれぞれ毎月百本ずつ頼みたい。";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000) // увеличить объём поставок вина и рома, если в первый раз не принесли
			{
				link.l4 = "クリスチャン、俺たちの取り決めを拡大する件、もう一度考え直したいんだ。";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
			dialog.text = "素晴らしい。いつも通り、新しい品は十五日にご用意いたします。次のお越しを楽しみにしております。";
			link.l1 = "俺の帰還を信じて待っててくれ。\nまたどこかで会おうぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}
			
			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // счётчик покупок
		break;

		case "UpgradeVino":
			dialog.text = "船長、そうした拡張は商売にとって大いに歓迎すべきことですが、かなりの出費を伴いますぞ！ 大量の注文には追加の労働者や倉庫の拡張、より大きな船の手配が必要になります……しかるべき投資がなければ、これほど大口の注文を期日通りに届ける保証はできません。";
			link.l1 = "「そういった取り決めには、どれほどの金が必要なんだ？この拡大した事業が順調に回るためには、 どれくらい投資すればいい？」";
			link.l1.go = "UpgradeVino_2";
		break;

		case "UpgradeVino_2":
			dialog.text = "五万ペソあれば十分だ。それ以上の費用は私が自分の懐から負担しよう。";
			link.l1 = "五万か？まったく……そりゃあ並大抵の額じゃねえな。もっと控えめな資金じゃ本当にやっていけねえのか？";
			link.l1.go = "UpgradeVino_3";
		break;

		case "UpgradeVino_3":
			dialog.text = "深く遺憾ではございますが、船長、この金額が絶対的な最低限であることを強く申し上げます。もし手を抜けば、我々 の事業は……そうですね、悲惨な方向へ逸れてしまうかもしれません。そのような災難は、 あなた様にも私にも何の益ももたらさないでしょう。";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "これが全額の支払いだ。この信頼に値する者だと証明してみせよ、キリスト教徒よ。";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "さらに考えてみると、クリスチャン、この拡張は少し時期尚早かもしれん。状況がもっと好転した時に、 改めてこの件を話し合おう。";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_4":
			dialog.text = "承知しました、船長。もしご考慮が変わりましたら、いつでもお力になります。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;
		
		case "UpgradeVino_Agreed":
			dialog.text = "船長、なんと素晴らしい知らせでしょう！すぐに進めるよう、五万枚の銀貨を持ってきてくれましたか？";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "これが全額の支払いだ。この信頼にふさわしい者だと証明してみせろ、キリスト教徒よ。";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "現在、私の金庫には必要な資金が不足しておる。財政が許すようになったら、また戻ってくるとしよう。";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_5":
			dialog.text = "「俺の名誉にかけて、」 "+pchar.name+"、この決断を後悔させはしませんぞ！すぐに準備に取りかかります。次回の集荷から、 最高級のラム酒百本と同量の極上ワインを、ひとまとめで百三十ドゥブロンというお値段でお渡しいたします。";
			link.l1 = "まことに満足でございます。しかし、肝に銘じておきなさい――何事にも最大限の慎重さを持って行動なさいませ。あなたの振る舞いは、 この海域における私の立場に直結しておりますのよ。";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}