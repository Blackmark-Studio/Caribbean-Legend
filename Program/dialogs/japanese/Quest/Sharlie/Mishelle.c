// Брат Шарля, Мишель де Монпе, он же Дичозо, он же воплощение Кукулькана, он же главный злодей
void ProcessDialogEvent()
{
	ref NPChar, sld;
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
			if (pchar.questTemp.Sharlie == "takeknife")
			{
				dialog.text = "ようこそ、旅人シャルル！マルティニーク東岸であの海賊どもを打ち破った話はすべて聞いているぞ。 これでお前のことを見込んで間違いなかったと心から確信したよ、兄弟。";
				link.l1 = "クソ野郎どもが俺を罠にはめやがった。だが、奴らは俺たちを甘く見てたんだ。俺の航海士も、乗組員も、そして俺も、 最後には勝ち残った。\nもっとも、正直に言うとよ、兄貴……最初は絶望的に見えたぜ。";
				link.l1.go = "trial";//промежуточная стадия
				break;
			}
			if (pchar.questTemp.Sharlie == "gambitstage")
			{
				bool bFMQM = CheckAttribute(pchar,"questTemp.FMQM") && pchar.questTemp.FMQM != "fail" && pchar.questTemp.FMQM != "end";
				bool bFMQN = CheckAttribute(pchar,"questTemp.FMQN") && pchar.questTemp.FMQN != "fail" && pchar.questTemp.FMQN != "end";
				bool bFMQT = CheckAttribute(pchar,"questTemp.FMQT") && pchar.questTemp.FMQT != "fail" && pchar.questTemp.FMQT != "end";
				bool bFMQP = CheckAttribute(pchar,"questTemp.FMQP") && pchar.questTemp.FMQP != "fail" && pchar.questTemp.FMQP != "end";
				bool bFMQG = CheckAttribute(pchar,"questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && pchar.questTemp.FMQG != "end";
				bool bFMQL = CheckAttribute(pchar,"questTemp.FMQL") && pchar.questTemp.FMQL != "fail" && pchar.questTemp.FMQL != "end";
				if(bFMQM || bFMQN || bFMQT || bFMQP || bFMQG || bFMQL)
				{
					if (sti(pchar.rank) < 12)
					{
						dialog.text = "やあ、兄弟！ここから俺を出そうとするお前の熱意には感謝するが、まだ次の段階に進むには早いぞ。 俺の計画には経験豊富な船長が必要なんだ。カリブをもっと冒険して、報酬を稼ぎ、学ぶんだ！準備ができたら、 また先へ進もう。";
						link.l1 = "まあ、どう言おうと兄さんがここに座ってるんだ、俺じゃないさ。";
						link.l1.go = "exit";
					} 
					else 
					{
						dialog.text = "会えて嬉しいよ、兄さん。他人への約束を忘れないでくれよ。\n自由になったらすぐに来てくれ——次の一手について考えがあるんだ！";
						link.l1 = "了解だ、兄さん。自分の責任は果たすけど、すぐ戻ってくるぜ！";
						link.l1.go = "exit";
					}
					break;
				}
				if (sti(pchar.rank) < 12)
				{
					Log_info("Level 12 is required");
					dialog.text = "航海者シャルル！お前の冒険の噂は聞いているぞ！俺の計画の次の段階に進むには、もう少し経験を積めば十分だ。 もっと経験を積んだらすぐ戻ってこい。";
					if (sti(pchar.rank) < 7)
					{
						dialog.text = "やあ、兄弟よ！ここから俺を出そうとするお前の誠実な熱意には感謝するが、次の段階に進むにはまだ早い。 俺の計画には経験豊富な船長が必要なんだ。カリブをもっと探検し、賞金を稼いで学ぶんだ！準備ができたら、 また続きをやろう。";
					} 
					else 
					{
						if (sti(pchar.rank) < 10)
						{
							dialog.text = "会えて嬉しいぞ、兄弟！順調に進んでいると聞いたぜ！だが、まだ俺の計画の次の段階に進むには早いな。 今まで通り続けて、準備ができたらまた俺のところに来い。";
						}
					}
					link.l1 = "まあ、どう言おうと勝手だよ、兄貴。ここに座ってるのは俺じゃなくて、あんただからな。";
					link.l1.go = "exit";
					if(sti(pchar.rank) > 8)
					{
						link.l2 = "そうは思わないよ、兄さん。君はもうこの檻に慣れちまったのかもしれないけど、僕は長居するつもりはない――父上だっていつまでも待っていられないんだ。さあ、話してくれ。";
						link.l2.go = "gambitA";
					}
					break;
				}
				else
				{
					dialog.text = "こんにちは、シャルル。あなたの姿を見ると心が喜びますわ。確かに、あなたは良い方向に変わってきていますのね。";
					link.l1 = "そうか？で、どうしてそう思うんだ？";
					link.l1.go = "gambit";//переход на Гамбит
					break;
				}
			}
			if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector"))//признак, что Гамбит пройден или провален
			{
				dialog.text = "なるほど。何か知らせがあるんだな、シャルル！さて、どうした？できれば悪い話じゃないといいが？";
				link.l1 = "前回あなたがくれた助言に従いました……";
				link.l1.go = "saga";//переход на Сагу
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3"))//признак, что Гамбит провален по всем трем вариантам
			{
				dialog.text = "やっと来たか……どうしたんだい、兄さん？";
				link.l1 = "前回あなたがくれた助言に従いました……";
				link.l1.go = "gambit_fale";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle")//Сага готова к старту
			{
				dialog.text = "お会いできて嬉しいぞ、シャルル！シュヴァリエ・ド・ポアンシーに会ったか？面会はどうだった？";
				link.l1 = "ああ、兄上。お会いしましたよ。そして、良い知らせと悪い知らせ、二つあります。まずは良い方から。 ポワンシーへの借金は私が片付けました。\n悪い知らせですが、あなたが異端者との問題を解決するという約束を私が果たすまで、彼はあなたを解放しないそうです……";
				link.l1.go = "saga_5";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && !CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью
			{
				dialog.text = "ラ・ベガではどうだった、兄さん？";
				link.l1 = "自慢できることなんて、別にないさ。タイレックスは派手な奴だが、あいつのやり方は俺には合わねえんだ。";
				link.l1.go = "saga_17e";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью, но дальше 4 квеста
			{
				dialog.text = "ラ・ベガではどうだったんだ、兄さん？噂を耳にしたけど、正直言って、あまり嬉しくない内容だよ……チャーリー・プリンス。";
				link.l1 = "その噂が何についてだったか、心当たりがある。だが、もう過去のことさ。俺はもうタイレックスとは組んでねえ、 あの仕事は俺にはあまりにも汚すぎたんだ。";
				link.l1.go = "saga_17f";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // пиратская линейка пройдена полностью
			{
				dialog.text = "さて、ごきげんよう……コルセア・チャーリー・プリンス。教えてくれ、シャルル、お前はどうしてここまで落ちぶれたんだ？信じられないよ。 かつて俺がスペインの商船ガレオンを襲う話をしただけで顔をしかめていた兄貴が、 今やこの地域で最も指名手配されている危険な海賊の一人になってるとはな！俺ですら、 クソまみれで座り込んでるってのに、お前の悪名が耳に入るたびに顔が赤くなるぜ。 お前をラ・ベガに送り出した日を呪ったさ。情けない！フランス貴族が海賊になり、 しかもあっという間に最悪の海賊になっちまうなんて！さて、これからどうするんだ、兄弟？ 海賊男爵の椅子でも狙ってるのか？";
				link.l1 = "いや。俺はもう二度と海賊なんかやらねえ。";
				link.l1.go = "saga_17g";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			
			dialog.text = "他に何かあるか、シャルル？もう全部話し合ったと思うぞ。時は金なりだ、兄弟よ――急げ！";
			link.l1 = "はいはい、行きますよ……";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "Mishelle_prisoner":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Maltie_officer"));
			QuestPointerDelLoc("FortFrance_Dungeon", "quest", "quest1");
			SetCurrentTime(13, 30);
			dialog.text = "シャルル！…会えて嬉しいぜ、兄弟！信じがたいかもしれねえが、こうしてお前が来てくれて、俺は本当に嬉しいんだよ…";
			link.l1 = "ははっ！見ろよ、あいつ！嬉しそうじゃねえか！お前が『秩序』だなんだと偉そうにしてる間、シャルルは家族の恥、 しがない絵描きで、女たちの金で食ってるし、宮廷の『騎士様』気取りだったんだろ？ でも今じゃ自分の仲間にぶち込まれて、その出来損ないの弟に会えて『死ぬほど幸せ』ってわけか！";
			link.l1.go = "Mishelle_prisoner_1";			
		break;
		
		case "Mishelle_prisoner_1":
			dialog.text = "シャルル、あなた……";
			link.l1 = "まだ終わってないぞ！なぜ自分のことをフランスに何も報告しなかったんだ！？書簡を送る権利でも奪われたのか！？ 父上はお前のことで心配しすぎてすっかり病気になってしまったんだぞ！ それでせめてお前の消息だけでも知ってこいと頼まれたんだ！…";
			link.l1.go = "Mishelle_prisoner_1a";
		break;
		
		case "Mishelle_prisoner_1a":
			dialog.text = "シャルル、どうして父上に自分の身に起きたことを話せるだろうか？何を書けばいい？いや、兄さん、辛いけれど、 今は父上に何も知らせない方がいい。君に手紙を書いても無駄だろう――パリでいつも居場所が違うからな…どうやって僕を見つけたんだ…";
			link.l1 = "お父上のご依頼で、私はマルタへ赴きました。そこで、 あなたのご友人であるシュヴァリエ・ド・ラ・ブリニエからいくつか情報を受け取りました。 彼はあなたの困難について私に手紙を書き、あなたがマルティニークのどこかにいる可能性が高いと伝えてきました。 その後、私はフランスへ戻り、お父上を訪ねました。そうしてようやく、この灼熱の地獄、 蚊が文字通り人を食い殺すような場所に来たのです…";
			link.l1.go = "Mishelle_prisoner_1b";
		break;
		
		case "Mishelle_prisoner_1b":
			dialog.text = "このことを全部お父上に話したのか？";
			link.l1 = "いいや。それに、ラ・ブリニエ騎士は不幸な結果を恐れて手紙に返事をしなかった……父上はまだお前の運命を何も知らない。私はお前を探し、この件の真相を突き止めることにしたんだ。 念のため言っておくが、私はお前のためじゃなく、哀れな父上のためにマルティニークへ来たんだぞ！";
			link.l1.go = "Mishelle_prisoner_2";
		break;
		
		case "Mishelle_prisoner_2":
			dialog.text = "本当か？シャルル、お前が家族のことを気にするようになったのはいつからだ？正直に言おう、兄弟よ、 パリ中の誰もがお前の父親が誰か知っている。お前はド・モール家の名を名乗っているが、 ド・モンペールの名が汚されるのは嫌なんだろう？そうなったら、 自分の家柄を使って英雄譚を吹聴することもできなくなる。そうじゃないか？パリの一流の館の扉はお前に閉ざされ、 ルーヴルにも近づけなくなるだろう。戦場で祖国のために戦っている夫たちを尻目に、お前が寝取った愛人や情婦たちが、 国賊の兄を持つ男と喜んで密会すると思うか？どうせまた人妻のベッドから直行してきたんだろう、違うか？シャルル、 その顔はどうした？図星だったか？";
			link.l1 = "お前…お前か…";
			link.l1.go = "Mishelle_prisoner_3";
		break;
		
		case "Mishelle_prisoner_3":
			dialog.text = "わかったよ、兄さん。もう皮肉の応酬は十分だ。俺が完璧じゃないのは認めるよ。でも、兄さんだって聖人じゃないだろ。 シャルル、今は喧嘩してる場合じゃない。俺たちには共通の目的がある――モンペール家の名誉と誇りを守ることだ……動機が何であれ。兄さん、人生で一度くらいは、争いを脇に置いて平和を選ぼうぜ。どうだ？";
			link.l1 = "試してみよう……でも、君が何の罪で訴えられているのか説明してくれないか？";
			link.l1.go = "Mishelle_prisoner_4";
		break;
		
		case "Mishelle_prisoner_4":
			dialog.text = "表向きは協会の資金の使い道についての話らしい。\n実際は、もっと深い事情があるんだ。";
			link.l1 = "ほう、自分の組織の金を横領したのか？ふむふむ……";
			link.l1.go = "Mishelle_prisoner_5";
		break;
		
		case "Mishelle_prisoner_5":
			dialog.text = "それが正式な罪状だと話しただろう。俺はルイドールを一枚たりとも取っていない。こうなった経緯を話そう……ただな、今は牢の中だから詳しく説明するわけにはいかないんだ。俺たち協会の秘密を明かす道義的な権利が、 今の俺にはないんだよ。";
			link.l1 = "どうか説明してくれよ、兄さん。僕にも知る権利があると思わないか？";
			link.l1.go = "Mishelle_prisoner_6";
		break;
		
		case "Mishelle_prisoner_6":
			dialog.text = "いいだろう。私はカリブの政治的均衡を揺るがす、とても危険で繊細な作戦のために金を受け取った。 その作戦はフランス領植民地の総督フィリップ・ド・ポワンシーの直接命令だった。しかし、 私がどれだけ努力しても作戦は失敗した。\nポワンシーは、すべての綱渡りの計画が崩れたことで激怒した。彼は自ら私の逮捕命令に署名し、 それが確実に実行されるよう手配した。そしてここにやって来て、もし私や親族が作戦に使った金を返さなければ、 横領と騎士団への反逆で告発すると宣言したのだ。";
			link.l1 = "こりゃまた面倒なことになったな。で、その金はどこにあるんだ？俺の理解では、 家族があんたのヘマのせいで払わなきゃならないって話だけどよ。";
			link.l1.go = "Mishelle_prisoner_7";
		break;
		
		case "Mishelle_prisoner_7":
			dialog.text = "作戦の準備に使われたんだ。\n賄賂や遠征の手配、あらゆる商品や装備の購入に費用がかかった。\nかなりの出費だったよ。\n言った通り――一枚も自分の懐には入れていない。";
			link.l1 = "「それで、要求されている金額はいくらだ？」";
			link.l1.go = "Mishelle_prisoner_8";
		break;
		
		case "Mishelle_prisoner_8":
			dialog.text = "「百万円。」";
			link.l1 = "くそっ！冗談だろ！？";
			link.l1.go = "Mishelle_prisoner_9";
		break;
		
		case "Mishelle_prisoner_9":
			dialog.text = "俺が冗談を言う気分に見えるか？いや、兄上、これが苦い現実だ。 俺たちはド・ポアンシーに百万ペソを渡さなきゃならないんだ。";
			link.l1 = "くそっ！うちの家にはそんな大金なんてあるわけないだろう！二十年かけたって、そんな額はかき集められやしないんだ！ ";
			link.l1.go = "Mishelle_prisoner_10";
		break;
		
		case "Mishelle_prisoner_10":
			dialog.text = "もし俺が鉄格子の中にいなくて、ソサエティへの義務に縛られていなければ、半年から一年、 長くても一年半でやれるだろう。\nシャルル、ここは新世界だ。すべてが違う。やる気と野心さえあれば、ヨーロッパのように一生を捧げなくても、 ここでは一財産築けるんだ。";
			link.l1 = "半年で百万だと！？正気か？そんなに自信があるなら、その話をポワンシーに言ってみろよ。あいつにお前を釈放させろ。 せいぜい頑張るんだな……";
			link.l1.go = "Mishelle_prisoner_11";
		break;
		
		case "Mishelle_prisoner_11":
			dialog.text = "「ああ、馬鹿なことを言うな、シャルル！ポワンシーが俺をこの牢から出すわけがないだろう。そんなに簡単なら、 お前に助けなんて頼まないさ。」";
			link.l1 = "つまり、お前の自由のための金を俺が用意しなきゃならねえのか！？";
			link.l1.go = "Mishelle_prisoner_12";
		break;
		
		case "Mishelle_prisoner_12":
			dialog.text = "私の自由だけじゃないぞ。忘れたのか？宮殿や舞踏会、そして貴族の娼婦との情事についての話に戻ろうか？そうだ、 シャルル、お前がやらなきゃならないんだ。もちろん、今まで通りパリでうわべだけの人生を続けたいならな。 そうしたいんだろう、兄弟よ？";
			link.l1 = "「くそっ、一体どこでそんな金を手に入れろってんだ！？ この辺に葉っぱの代わりにルイドールが生る古い森でもあるのか？」\n";
			link.l1.go = "Mishelle_prisoner_13";
		break;
		
		case "Mishelle_prisoner_13":
			dialog.text = "新世界全体が金のなる木の森だというのに、人々は愚かにも頭を上げて枝に手を伸ばそうともしない。心配するな、 シャルル、お前ならきっとうまくやれるさ。子供の頃からお前のことは知っているし、 お前が愚かだったり怠け者だったりしたら、父上に頼んでまでここに送らせたりはしなかっただろう。\n前にも言った欠点はあるにせよ、お前は勇敢で野心家、頭も切れるし、口も達者だ。それにレイピアの扱いも心得ている――ここではそれが何より大事な技術なんだ…";
			link.l1 = "ありがとうございます。本当にあの兄上が私を褒めてくださったのですか？私はてっきり、哀れな芸術家であり、 ただの宮廷人にすぎないと思っておりましたのに…";
			link.l1.go = "Mishelle_prisoner_14";
		break;
		
		case "Mishelle_prisoner_14":
			dialog.text = "くだらねえことはやめろ。話はまとまったのか、どうなんだ？";
			link.l1 = "悪いな、兄貴。つい口が滑ったんだ。お前からそんな言葉を聞くのに慣れてなくてさ。 まるで街娼が魂の救済を説教してるみたいだぜ。";
			link.l1.go = "Mishelle_prisoner_15";
		break;
		
		case "Mishelle_prisoner_15":
			dialog.text = "進もう、兄弟。言っただろう、君にはここで成功するためのすべてが備わっている。\nそれだけじゃない、一人じゃないんだ。何をどうすればいいか、俺がしっかり助言してやる。\n俺の言うことを聞けば、きっと見事にやり遂げられるさ。俺の経験に並ぶ奴なんて、そうそういないぜ。\nそろそろくだらない口論はやめて、本題に入る準備はできたか？";
			link.l1 = "ああ、しばらくここに滞在することになりそうだな……\nよし。話を聞こう、ミシェル。";
			link.l1.go = "Mishelle_prisoner_16";
		break;
		
		case "Mishelle_prisoner_16":
			dialog.text = "ああ、兄さん、しばらくここにいることになるんだ。今それが分かってよかったじゃないか。だから、 もしパリで君の帰りを待っている高級娼婦がいるなら、もう忘れたほうがいいぜ。でも気を落とすなよ、 ここの娘たちにも独特の魅力があるんだ。\nただし、こいつらは本物の男、強くて押しが強い、ちょっと荒っぽいくらいが好きなんだ。 だから植民地の女と寝たいなら、詩や絵画の話、月夜の散歩なんかは期待しないほうがいい。 あいつらはそんなの認めちゃくれねえよ。";
			link.l1 = "わかったよ、兄貴。今度は口から出まかせの嵐にでも打たれたのか？要点に行こうぜ。忠告なら聞いてやるが、 下品なあてこすりはごめんだ。";
			link.l1.go = "Mishelle_prisoner_17";
		break;
		
		case "Mishelle_prisoner_17":
			dialog.text = "素晴らしい。何かで成功したいなら、まず自分の船を持たねばならん。カリブは群島だ。知っているだろう？ 人生は海と切っても切れない。自分の船を持つ男には、稼ぎの可能性が無限に広がっているのさ。";
			link.l1 = "でも俺は水夫じゃないんだ！";
			link.l1.go = "Mishelle_prisoner_18";
		break;
		
		case "Mishelle_prisoner_18":
			dialog.text = "では、そろそろ一人前になる時だな。他に選択肢はねえんだ。まさか港の事務員になるとか、 守備隊に登録するなんて考えてねえだろ？違うか？なら、お前は船長になるしかねえよ。";
			link.l1 = "なんて波乱万丈な俺の人生だ！それで、俺はどこで船を手に入れればいいんだ？";
			link.l1.go = "Mishelle_prisoner_19";
		break;
		
		case "Mishelle_prisoner_19":
			dialog.text = "うちの造船所に素晴らしいラガー船が待っているんだ。大きくはないが、とても快適な船で、 航海の世界に初めて踏み出すにはぴったりだよ。このラガー船は特別に私のために建造されたんだ。 友人たちの助けも借りて、五千ペソの頭金を入れてある。造船所の親方のところへ行って、 「ミシェル・ド・モンペルから来た」と伝えてくれ。何の用か、すぐに分かってくれるはずだ。";
			link.l1 = "その船がたった五千で買えるのか？ちょっと妙じゃないか…";
			link.l1.go = "Mishelle_prisoner_20";
		break;
		
		case "Mishelle_prisoner_20":
			dialog.text = "兄さん、聞いてるか？五千はあくまで手付金だぜ。ラガー船の値段は二万ペソくらいするんだ。 だから残りは自分で稼がなきゃならねえ。それに、乗組員や航海士を雇う金も必要だぞ。";
			link.l1 = "素晴らしい！それで、どうやって手に入れるんだ？";
			link.l1.go = "Mishelle_prisoner_21";
		break;
		
		case "Mishelle_prisoner_21":
			dialog.text = "別に驚くことじゃねえさ。自分で稼げよ。他にどうするんだ？ここじゃ金なんてそこら中に転がってる、 どこを探せばいいか知ってて、困難を恐れなけりゃな。いろんな店を回ってみろ。地元の連中と話してみな。 何かしら仕事は見つかるはずだ。ただし気をつけろよ、正直者より詐欺師の方がずっと多いからな。 もしお前が正直者じゃねえなら、家から何か価値のあるもんを盗むって手もあるぜ。";
			link.l1 = "「でも、私たちは貴族ですよね？」";
			link.l1.go = "Mishelle_prisoner_22";
		break;
		
		case "Mishelle_prisoner_22":
			dialog.text = "ここじゃ肩書きなんて意味はねえ。みんなと同じように働いて、戦って、盗むんだ。船を買ったら、まずは乗組員を雇え。 最初は自分ひとりじゃ船を操縦できねえから、航海士が必要になるぜ。こういう話は全部酒場の主人に相談しな。 あいつが手を貸してくれるさ。もちろん、道に迷うんじゃねえぞ。\n海に出たら、そのままグアドループへ向かって航海しろ…";
			link.l1 = "それは何だ？町か？";
			link.l1.go = "Mishelle_prisoner_23";
		break;
		
		case "Mishelle_prisoner_23":
			dialog.text = "ここからほぼ二日かかる島だ。できるだけ早く諸島の地図を手に入れて、「主の祈り」のように覚えておけ。 町と島の違いも分かる連中に馬鹿にされないためにな。これから諸島をかなり航海することになるんだから、 前もって準備しておけよ。\n";
			link.l1 = "ふむ。まあいいだろう。それで、この…グアドループで俺は何をすればいいんだ？";
			link.l1.go = "Mishelle_prisoner_24";
		break;
		
		case "Mishelle_prisoner_24":
			dialog.text = "そこに「ファディ」という名の男を探せ。桟橋からそう遠くない場所に自分の家を持っている。\n私の知り合いだと伝えて、借金を返すように言え――あいつはカード勝負で私に大負けしたんだ。\n受け取った金で立て直せ。それを使って物事を始めるんだ。";
			link.l1 = "「どういう意味だ、始めろって？」";
			link.l1.go = "Mishelle_prisoner_25";
		break;
		
		case "Mishelle_prisoner_25":
			dialog.text = "つまり、この金を使ってさらに稼げ、ということだ。例えば交易とかでな。\nこの話はまた後でしよう。今は船の準備をして、グアドループへ向かい、あの太っちょのモスコビットを探して、 借金を回収してこい。ただし、文字通り取り立てるわけじゃないぞ。 ファデイはグアドループでも非常に評判のいい人物で、地元総督の友人でもある。だから揉め事は無意味だ。むしろ、 仲良くなるように努めろ。金を手に入れたらすぐに俺のところへ戻ってこい。わかったな、兄弟？";
			link.l1 = "了解だ。ああ、なぜだ……俺が何をしたっていうんだ、こんな罰を受けるなんて……";
			link.l1.go = "Mishelle_prisoner_26";
		break;
		
		case "Mishelle_prisoner_26":
			dialog.text = "悲しまないで、シャルル。これは避けられぬ災いだと受け入れるんだ、あるいは…災い転じて福となすってやつさ。後になれば、人生がこう転んだことを運命に感謝する日が来るだろう。お前はな、 兄弟よ、ついに本当の男であることを証明する機会を手に入れたんだ。もしかしたら、 まともな人間になれるかもしれないぞ…";
			link.l1 = "（チュートリアル開始）またそのくだらねえ話か？";
			link.l1.go = "Mishelle_prisoner_27";
			link.l2 = "（チュートリアルをスキップ）兄さん、こんなのに付き合ってる暇はないよ。退屈な部分は飛ばして、 すぐに大海原に出たいんだ。俺に船があれば、あんたもこんなクソみたいな所から早く出られるだろ？それとも、 もっとここにいたいのかい？";
			link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Mishelle_prisoner_27":
			dialog.text = "いや、違う、違う。誤解しないでくれ……よし、シャルル、時間を無駄にするな。やるべきことは分かっているだろう。ファディの金を持って、 自分の船の船長としてグアドループから戻ってくるのを待っているぞ。\n幸運を祈る、弟よ。頼りにしているからな。";
			link.l1 = "期待を裏切らないように頑張るよ。\nよし、ミシェル。また会おう！";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_28":
			DialogExit();
			pchar.questTemp.Sharlie = "ship";//флаг на старт мини-квестов для сбора денег
			//LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);// таверна закр
			if(!bHardcoreGame) LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", true);// ЦЕРКОВЬ закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", true);// ростовщик закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", true);// тюрьма закр
			bDisableFastReload = false;//open быстрый переход
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5");
			//Sharlie_CreateGigoloMan();//мини-квесты на бордель и на джунгли
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
				QuestPointerToLoc("Fortfrance_town", "reload", "reload3_back");
			}
			QuestPointerToLoc("Fortfrance_town", "reload", "reload6_back");
			/*pchar.quest.CreateGigoloMan.win_condition.l1 = "Hour";
			pchar.quest.CreateGigoloMan.win_condition.l1.start.hour = 17.00;
			pchar.quest.CreateGigoloMan.win_condition.l1.finish.hour = 18.00;
			pchar.quest.CreateGigoloMan.function = "Sharlie_CreateGigoloMan";*/
			/* pchar.quest.SharlieremoveLocks.win_condition.l1 = "HardHour";
			pchar.quest.SharlieremoveLocks.win_condition.l1.hour = 23;
			pchar.quest.SharlieremoveLocks.win_condition.l2 = "location";
			pchar.quest.SharlieremoveLocks.win_condition.l2.location = "FortFrance_Town";
			pchar.quest.SharlieremoveLocks.function = "Sharlie_removeLocks"; */
			//устанавливаем прерывание на джунгли
			pchar.quest.Jungle_jew.win_condition.l1 = "location";
			pchar.quest.Jungle_jew.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Jungle_jew.function = "Junglejew_CreateIndians";
			
			ref location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
		break;
		
		case "Mishelle_prisoner_29": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "へっ！この「退屈な部分」がいつかお前の命を救うかもしれねえぞ……まあいい。今すぐ金を手に入れる簡単な方法がある。\n地元の教会に行ってブノワ修道院長に話せ。あいつは俺たちの父上の古い友人だ。事情を説明して、 ひざまずいて船を買うのに必要な金を貸してくれと頼み込め。";
			link.l1 = "（チュートリアルをスキップ）今はずっと良くなった！これから修道院長のところへ向かう。";
			link.l1.go = "Mishelle_prisoner_31";
			link.l2 = "（チュートリアル開始）最初からお前の借金をもっと増やしてやろうか？俺を馬鹿だと思ってるのか、兄貴？ これじゃ全然助けにならないのは分かってる。つまり、全部俺がやるしかないってことだな。";
			link.l2.go = "Mishelle_prisoner_30";
		break;
		
		case "Mishelle_prisoner_30":
			dialog.text = "おおっ！やっぱりお前のことは見誤ってなかったな、兄弟。ファディの金を手に、 自分の船の船長としてグアドループから帰ってくるのを楽しみにしてるぜ。幸運を祈る！";
			link.l1 = "じゃあな。ここで楽しんでくれよ。";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_31":
			DialogExit();
			AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
			pchar.questTemp.Sharlie = "ship_fast"; // ускоренный старт
			pchar.questTemp.Sharlie.FastStart = "true";
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5-1");
			location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			Sharlie_removeLocks("");
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "怖かったって言いたいのか？肩の力を抜けよ、兄弟。全然大丈夫だ。 俺だって最初の海戦じゃ英雄気分なんて全くなかったさ。気にするな。あと一、二ヶ月もすれば、 こんな出来事は日常茶飯事に思えてくるさ……ファディにはもう行ったか？";
			link.l1 = "俺はやったさ…だが、こんな結果じゃ…一体何のために頑張ったんだ？";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "ふむ。なぜだ？";
			link.l1 = "あいつは今、どん底なんだ。最近盗みに遭って、自分自身も金に困ってるらしい。だから代わりに、 自分のコレクションから短剣を一本くれると言われたんだ。価値が高くて、借金の総額を上回るってさ。だから、 俺はそれを受け取った……";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "ファデイ？無一文で困ってるのか？金の問題か？ははは！お前には笑わせてもらったぜ、可愛い弟よ！あの忌々 しいモスコビット野郎はお前の素人ぶりを一目で見抜いて……ああ、あの野郎め！親父が借金の代わりにくれた短剣、見せてみろよ。";
			if (CheckCharacterItem(pchar, "knife_01"))
			{
				link.l1 = "「はい、どうぞ…」";
				link.l1.go = "trial_3";
				PlaySound("interface\important_item.wav");
			}
			else
			{
				link.l1 = "今は持っていない。見た目はただの普通の短剣だ。ファディが言うには、インディアンのシャーマンが魔法をかけて 「酋長の爪」と呼ばれているらしい。";
				link.l1.go = "trial_4";
			}
		break;
		
		case "trial_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "ふむ。さてと……あの小太りの熊は神が裁くだろう。シャルル、そんなガラクタならどこの店でも買えるぜ。お前の未熟さにつけ込んで、 うまくやられたんだな……ほらよ、この鉄くずを返してやる。記念に取っておけ。船室のベッドの上にでも飾るといいさ。";
			link.l1 = "くそったれめ！ああ、どうでもいい…グアドループに戻ってあの脂ぎった野郎を叩き起こしてやるぜ！";
			link.l1.go = "trial_5";
		break;
		
		case "trial_4":
			dialog.text = "呪術師に魅了されたのか？酋長の爪だと？ああ…なるほどな。あの小太りの熊は神が裁くだろう。そんなガラクタ、シャルル、どこの土産物屋でも買えるぜ。 お前の未熟さにつけ込んで、うまく騙されたんだよ…俺にもおとぎ話みたいなことを言ってきたが、きっちり黙らせてやったさ。だからその爪は、 思い出として船室のベッドの上にでも飾っておけよ…まだゴミ箱に捨ててなければな。";
			link.l1 = "くそ野郎め！ああ、どうでもいい……グアドループに戻ってあの脂ぎった野郎を揺さぶってやるぜ！";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			dialog.text = "落ち着けよ、兄上、リラックスしろ。バステールの牢屋で何ヶ月も過ごしたいんじゃなければ、 そんなことする必要はないんだ。\n俺が言ったこと、もう忘れたのか？あの偉そうな熊野郎は、 グアドループ総督クロード・フランソワ・ド・リヨンの友人なんだぞ。ここを出たら、俺が直接話をつけてくるさ……腹を割ってな。あいつはどこにも行きやしない。";
			link.l1 = "わかった。お前があいつを片付けたほうがよさそうだな…俺は約束された初期資金なしで放り出されるってことか？";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "そうみたいだな、シャルル。でも元気を出せ。このカリブじゃ、船としっかりした頭があれば、道を誤ることはねえ。 お前はその両方を持ってるだろう？";
			link.l1 = "何が言いたいんだ？この短剣でしくじったっていうのか、じゃあ俺はどうすれば……";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "落ち着けよ、兄上！どうして急にそんなに慌てるんだ？冷静になれ、長生きできるぞ。何もほのめかしてないさ。 そんなこと、考えたこともないよ！";
			link.l1 = "すまない、ミシェル。ちょっとその……まあ、俺の気持ちもわかってくれよ！";
			link.l1.go = "trial_8";
		break;
		
		case "trial_8":
			dialog.text = "わかりました。そして、本当にあなたの力になりたいんです！だから、よく聞いてください。もっと経験を積んで、 少なくとも少しはお金を貯めてから、もっと重大なことに取りかかるべきです。準備もせずに冒険に飛び込むのは、 まさに自殺行為ですよ。この場所にあなたが押しつぶされるのは、まだ見たくありません。";
			link.l1 = "とても感動的だね。どんな冒険について語っているんだい、ミシェル？なぜか君の話についていけなくなってしまったよ。 ";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "兄上、念のために言っておくが、私――いや、正確には我々は、ド・ポワンシーに百万ペソの借りがあるんだ。君は本当に、 それを正直に稼げると思っているのか？もちろん、取引でその額を稼ぐことはできるさ、運が良ければな。 でもカリブでの商売なんて、決して穏やかなものじゃない。\n冒険は望もうが望むまいが向こうからやってくる――問題は、その時に君が備えられているかどうかだ。ならば、先手を打つ方がいい。シ・ウィス・パケム、パラ・ベッルム、 シャルル……";
			link.l1 = "また小難しい言葉か？頼むから、もっと分かりやすく話してくれよ…";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "ラテン語だよ、兄上。「平和を望むなら、戦争に備えよ」と言ったのさ。この言葉は、 行動するための指導者の心構えとして受け取ってくれ。航海日誌に書き留めて、祈りの後に毎朝読み返すといい。 学ぶべきことも、身につけるべきことも、まだまだたくさんあるんだぞ…";
			link.l1 = "よし、もう十分だ。お前の学術論文にはもう飽きた。要点を話せ。";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			dialog.text = "私は具体的に話しているんだが、お前がまだ理解していないだけだ。まあいい。まずは諸島に慣れ、 船長としての新しい生活に馴染むことだ。自分自身の安泰と乗組員の給料のために、しっかり働かなくちゃならない。 金を稼ぐ方法はいくらでもある。\n貨物や乗客を乗せるのが一番手っ取り早い。店の商人が貨物契約をくれるし、 乗客は自分から街で声をかけてくることもある。港の事務所も覗いてみるといい。ラガーや速い船を持っていれば、 運び屋としていい稼ぎができるぞ。\nもっと大きな船を手に入れれば、港長がかなり儲かる貨物契約をくれるようになる。人と話すときは、 家柄をひけらかさず、愛想よくしていればうまくいくさ。植民地の総督も訪ねてみろ。 やつらはよく高給の仕事を出してくる。\n交易に挑戦するのもいいが、その場合は腕のいい会計士を雇ったほうがいい。海では用心しろよ。 スペインの軍艦や戦隊は避けるんだ。もしスペインの商船や護衛のいない船団を見つけたら、 拿捕を狙ってみるのも手だな。";
			link.l1 = "「何だって！？ミシェル、俺の耳はどうかしちまったのか？お前、俺に海賊稼業をやれって言ってるのか？ お前はソシエテの誇りであり、神と三位一体に仕える身なのに、そんな生き方を俺に勧めるのか？」";
			link.l1.go = "trial_12";
		break;
		
		case "trial_12":
			dialog.text = "ああ、シャルル……この際、潔癖さは捨てた方がいいわよ。ここじゃ誰もそんなもの評価しないんだから。それから、騎士団のことだけど……兄さん、あまりにも純粋すぎるわ。ヨーロッパじゃルーヴルもエスコリアルも一応平和かもしれないけど、ここは戦場よ。 スペインの私掠船なんて、あんたの船を襲って、あんたも乗組員も容赦なくヤードアームに吊るすわよ。\nだから、敵対国の商船を襲っても誰も咎めたりしないわ。保証する。私掠免状があれば、 当局からお墨付きまで貰えるんだから……";
			link.l1 = "私はあなたの人生の信条がだんだん分かってきました。半年で百万を「稼ぐ」方法も、どうやら理解できましたよ。";
			link.l1.go = "trial_13";
		break;
		
		case "trial_13":
			dialog.text = "「そして、これらの手段を使わざるを得なくなるだろう、シャルル。結局のところ、これは公然と、 あるいは密かに当局に支持されているのだ。たとえ貿易に徹していても、 いつかは海賊やスペインの襲撃者と戦わされることになる。彼らにとってお前は獲物だからな。\n自分のこれまでの人生観は忘れるのが、お前のためだ。信じてくれ、兄弟よ。面目を失わずにできることは山ほどあるし、 むしろ当局のご機嫌も取れて、民衆の人気も得られるんだ。」";
			link.l1 = "お前にはいつも驚かされるよ、ミシェル。今度は俺に海賊になれって言うのか。次は何だ？";
			link.l1.go = "trial_14";
		break;
		
		case "trial_14":
			dialog.text = "大げさにするな、シャルル。話は単純だ――狩るか、狩られるか。それがすべての哲学さ。俺は前者を選ぶし、お前にもそうしてほしい。\nそれに、俺はお前に海賊になれと言っているわけじゃない。敵対国に対して軍事行動を取れと言っているんだ――しかも、正当な理由がある時だけな。";
			link.l1 = "「援助金のことか？」";
			link.l1.go = "trial_15";
		break;
		
		// Rebbebion, небольшое изменение диалога
		case "trial_15":
			dialog.text = "ほら、やっぱり分かってるじゃないか、兄弟。でももう言葉は十分だ。自分を試す時だぜ。準備ができたと感じたら、 俺のところに来い。まともな金を稼いで、もっといい船を手に入れ、この諸島を学び、腕を磨け。\nだがな、もしこの先数ヶ月を酒場や売春宿で無駄に過ごして、何も身につけずに終わったら……その時は戻ってくるな。いいな、シャルル？";
			link.l1 = "心配するな。遊びに来たわけじゃない……その後はどうなるんだ？";
			link.l1.go = "trial_16";
		break;
		
		case "trial_16":
			dialog.text = "後でその後どうすればいいか教えてやる。すでに計画は立ててあるんだ。私の助言と勧告にしっかり従えば、"+pchar.name+"、お前には明るい未来が待っているぞ。";
			link.l1 = "私はそんな輝かしく壮大な未来よりも、自分のささやかな過去の方が好ましい……";
			link.l1.go = "trial_17";
		break;
		
		case "trial_17":
			dialog.text = "信じてくれ、兄さん。自分のくだらない過去を笑い飛ばして、運命がそこから救ってくれたことに感謝する日が来るさ。 前向きに、楽観的にいこう。この人生をきっと好きになるよ。すぐに分かるさ。\nああ、それからもう一つ。共通の友人ファディに会いに行って、仕事を紹介してもらえ。あの熊野郎は顔が広いから、 きっと何か見つけてくれるはずだ。ぐずぐずしてるとチャンスを逃すぞ。それと、 頼むから俺をがっかりさせないでくれよ。";
			link.l1 = "また道徳の説教か……神よ、いつになったらこんなこと終わるんだ？わかったよ、ミシェル……もう行ってもいいか？";
			link.l1.go = "trial_18";
		break;
		
		case "trial_18":
			dialog.text = "待て。もう少し戦術的な助言をしておこう。どこかの国を敵に回して無法者になった場合は、 地元の教会に行ってブノワ修道院長に会い、「私からの紹介だ」と伝えろ。 彼はカトリックとカルヴァン派の両方にコネがあって、私も何度も世話になった。ただし、簡単でも安くもないから、 できるだけ敵を作らないように気をつけろ。\nああ、もう一つ！俺たちは貴族だが、特にここでは自分の手で物を作るのを嫌がるのは愚かだ。 必要な道具と材料さえあれば、役立つ物をいろいろ作れるんだ……ところで兄弟よ、お前はどうやってピストルに弾を込めている？";
			link.l1 = "ふむ。いつも通り、弾丸とひとつまみの火薬だな。";
			link.l1.go = "trial_19";
		break;
		
		case "trial_19":
			dialog.text = "はっ！他の返事が聞けるとは思ってなかったぜ。";
			link.l1 = "「他に道を知っているのかい、兄上？」";
			link.l1.go = "trial_20";
		break;
		
		case "trial_20":
			dialog.text = "もちろんだ。しかし、それをやる者は少ない。無知と単なる怠惰のせいでな。\n数時間かければ、火薬と弾丸から紙製のカートリッジを作れるんだ。これを使えば銃の装填時間が半分になる。 感心したか？";
			link.l1 = "ふむ。そうかもしれないな。面白い。";
			link.l1.go = "trial_21";
		break;
		
		case "trial_21":
			pchar.alchemy.known = 1;
			AddQuestRecordInfo("Recipe", "cartridge");
			SetAlchemyRecipeKnown("cartridge");
			dialog.text = "この紙薬莢の製作手順書を受け取って、暇なときにしっかり勉強しておけよ。それから、 新しく得た知識をちゃんと活かすのをサボるなよ。\n待てよ、兄弟。うちの大事な総督のところにも忘れずに顔を出していけよ。";
			link.l1 = "何か特別な用事でも？";
			link.l1.go = "trial_22";
		break;
		
		// Rebbebion, намёк на "Травлю крысы"
		case "trial_22":
			dialog.text = "総督たちとは常に連絡を取っておくのがいいさ、特に自分の親族がその島で投獄されている場合はなおさらだな。";
			link.l1 = "彼のことを教えてくれ。";
			link.l1.go = "trial_23";
		break;
		
		case "trial_23":
			dialog.text = "マルティニークの玉座にしがみつける者はそう多くない。修道会の利害、王冠の思惑、海賊たちの野望……そして貴族は自分自身の利益も忘れてはならん。パルケがもう少し締まりがあって、誘惑に負けなければ、 ポワンシーも彼をもっと真剣に扱ったかもしれん。";
			link.l1 = "「私が彼にとって何の役に立つというのだ？」";
			link.l1.go = "trial_24";
		break;
		
		case "trial_24":
			dialog.text = "役人どもはいつだって自由船長に仕事を回してくるもんだ。ただし、報酬はケチだし、 しかも公共の利益に関わる時だけで、個人的な用事じゃ金は出さねえ。\nとはいえ、カリブで名誉を守り、国同士の関係を良くするには、総督のために働くのが一番の近道だぜ。今がチャンスだ、 特にパルケが今ちょっと厄介なことに巻き込まれてるからな。\nどんな厄介事だ？";
			link.l1 = "どんなトラブルだ？";
			link.l1.go = "trial_25";
		break;
		
		case "trial_25":
			dialog.text = "すまない、兄さん。騎士団の利害が絡んでいるんだ。これだけは言っておく、 手っ取り早く金持ちになりたいのは俺たちだけじゃない。";
			link.l1 = "また意味深なことを言ってるな……まあ、時間があるときに寄るよ。";
			link.l1.go = "trial_26";
		break;
		
		case "trial_26":
			dialog.text = "さあ行け。幸運を祈るぜ、兄弟！";
			link.l1 = "ありがとう……またな、ミシェル。";
			link.l1.go = "trial_27";
		break;
		
		case "trial_27":
			DialogExit();
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Sharlie_Mishelle_OpenWorld");
		break;
		
		case "gambitA":
			dialog.text = "好きにしろよ。それでも俺はお前を信じてるぜ、兄弟。今のお前を見ると、 きっと良い方向に変わっているって分かるんだ。";
			link.l1 = "そうかい。どういうことだ？";
			link.l1.go = "gambit";
		break;
		
		case "gambit":
			dialog.text = "見えるぞ、兄上。歩き方も、顔の表情もはっきりと分かる。ついに、 私を本当に気が狂いそうにさせたあのうぬぼれた若造の仮面が、あなたから消えたのだ。新しい人生が、 今やあなたに良い影響を与えたのは明らかだな。";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "兄さん、君の言葉が褒め言葉なのか侮辱なのか、さっぱり分からないよ。\nでも本当のことを言おう。君が向こうから僕をどう思おうが、僕には全く興味がない。\n君の借金を返すために必要な百万を集めたから、もうすぐ自由の身になれるさ。\nで、ド・プアンシーはどこにいる？";
				link.l1.go = "gambit_1_1";
			}
			else
			{
				link.l1 = "兄上、あなたの言葉が褒め言葉なのか侮辱なのか、私にはさっぱり分かりません。\nですが、本当のことを言いましょう。そちらから私をどう思おうと、私は全く興味がありません。私には山ほど――いや、海ほどの用事があるのです。ここであなたと口論している暇などありません。\n何か要点があるなら聞きますが、そうでないなら私は行かせてもらいますよ……";
				link.l1.go = "gambit_1";
			}
			DelLandQuestMark(npchar);
			DeleteQuestCondition("Sharlie_GambitStage_level_9");
			DeleteQuestCondition("Sharlie_GambitStage_level_12");
			// уберем маркеры, если ФМК не стали проходить
			DelMapQuestMarkCity("Baster");
			DelMapQuestMarkCity("Fortfrance");
			DelMapQuestMarkCity("Charles");
			DelMapQuestMarkCity("Tortuga");
			DelMapQuestMarkCity("Portpax");
			
			if(CharacterIsAlive("FMQG_pass_1"))
			{
				sld = CharacterFromID("FMQG_pass_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQM_carpenter"))
			{
				sld = CharacterFromID("FMQM_carpenter");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQN_seafox_1"))
			{
				sld = CharacterFromID("FMQN_seafox_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQT_girl"))
			{
				sld = CharacterFromID("FMQT_girl");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") 
			{
				DeleteAttribute(pchar, "questTemp.FMQP");
				sld = CharacterFromID("PortPax_waitress");
				DelLandQuestMark(sld);
			}
			if(CharacterIsAlive("FMQG_cureer"))
			{
				sld = CharacterFromID("FMQG_cureer");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("Guide_y"))
			{
				sld = CharacterFromID("Guide_y");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
		break;
		
		case "gambit_1_1":
			dialog.text = "百万も用意できたのか？素晴らしいぞ、シャルル、まさに見事だ！\nだが残念ながら、フィリップ・ド・ポワンシーはもう邸宅にはいない。 ソサエティの用事で秘密の遠征に出発してしまったんだ。\nだから、彼に会いに行くには少し待たなければならないぞ。";
			link.l1 = "くたばれ、お前とその裏取引なんか！これで全部終わってパリに帰れると思ってたのに、今さら……";
			link.l1.go = "gambit_1_2";
		break;
		
		case "gambit_1_2":
			dialog.text = "そして今や、もっと大きな金を稼ぐチャンスまで手に入れたわけだ、しかもそれだけじゃない。兄さん、 あの老獪な狐が要求した額を集めたのは見事だけど、そんなに自信満々で落ち着いていられるとは思わないほうがいい……デ・ポワンシーは相当狡猾な奴で、君のささやかな存在にかなり興味を示しているし、それに……\n";
			link.l1 = "それで今度は、百万でも奴には足りないんじゃないかとビビってるのか！？それとも、前回何か隠してたことがあるのか？ ";
			link.l1.go = "gambit_1_3";
		break;
		
		case "gambit_1_3":
			dialog.text = "俺は何も怖くねえが、ポワンシーはただの男じゃねえってことは警告しておくぜ。あいつが留守の間に、 自分の地位を築くチャンスがあるんだ。そうすりゃ、あいつと対等に話せるようになる、主従じゃなくてな。だからこそ、 これから説明する俺の計画に従うことを強く勧めるぜ。";
			link.l1 = "仕方ないな。過ぎたことを悔やんでも意味がねえ。この地獄みたいな場所でもう少し身を潜めるさ。 デ・ポワンシーもいつまでも好き勝手やれるわけじゃねえだろう。お前の計画について教えてくれ。";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_1":
			dialog.text = "おお！立派な返答だ。シャルル、お前が一人前の男になったことを嬉しく思うよ。だが、兄にあまり厳しくするでないぞ。 さて、伝えたいことがある。再会を心待ちにしていたし、次にお前がすべきこともすでに考えてあるのだ。\n";
			link.l1 = "いいね。それじゃ、詳しく教えてくれ。";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_2":
			dialog.text = "見てみろ。確かにカリブでも金は大きな力を持つが、金だけで全てが解決するわけじゃない。この世界で成功する者は、 分厚い財布だけでなく、幅広く多様な人脈を持っていなければならん。しかも、それは下賤な連中じゃなく、 この世で影響力を持つ者たちとの繋がりだ。\n国籍や身分なんて関係ない。人脈は金だけでは開かない扉を開いてくれる。『金と人脈』の組み合わせこそが、 人にとって最も価値あるもの――すなわち権力をもたらすのだ。\nお前もそういった人脈を築くことを考えるべきだ。だが、それはただの運送仕事や商売、小さな海賊稼業、 あるいは総督に取り入る程度じゃ到底無理だぞ。";
			link.l1 = "どうするつもりだ？";
			link.l1.go = "gambit_3";
		break;
		
		case "gambit_3":
			dialog.text = "カリブ海にはそれほど多くの強力な組織は存在しない。その中の一つがオランダ西インド会社だ。 君もそこに加わることができる。彼らの本部はキュラソー島のウィレムスタッドにある。会社はよく外部の船長を雇い、 特に役立つ者には特別な長期契約を提示することもある。\n運が良ければ、そこで立派なキャリアを築けるかもしれない。今は大変な問題を抱えていると聞いた――イギリスの私掠船が会社に刃向かい、次々と船を沈めているそうだ。彼は海軍士官で、会社には手も足も出せないらしい。 \nどうやらイギリスの軍事情報部と何らかの繋がりがあるらしく、そいつらは相当手強い連中だ。だから、 この船長の側についた方がもっと儲かるかもしれないが、問題は――名前が分からないことだ。ただ、アンティグアが彼の拠点だということだけは知っている。\nそこへ航海して、現地で情報を集めてみるといい。それから、この英蘭の争いに関わっている奇妙な組織の噂も聞いたが、 どちら側なのかは分からない。ただ、手がかりはバルバドス、ブリッジタウンに続いているようだ……";
			link.l1 = "つまり、オランダ人に仕官しろとか、怪しい船長やさらに胡散臭い「組織」を探せって言うのか？";
			link.l1.go = "gambit_4";
		break;
		
		case "gambit_4":
			dialog.text = "選ぶのはお前だ。いずれにせよ、カリブで他人の運命を左右し、大きな権力を持つ連中と素早く繋がる手段は他にないぜ。 まさか、総督に二、三の恩を売ればすぐに王立海軍に入れるなんて思ってないだろうな。";
			link.l1 = "兄上、ご存じでしょう。私、フランス海軍で軍人になるなんて、最初から望んでいませんでしたよ。神よ、 どうか私が兄上のように、任務に失敗して牢屋にぶち込まれる羽目になりませんように……\nわかりました。オランダ東インド会社の総司令部くらいなら、すぐに見つかると思いますが、他の連中の探し方なんて、 まるで見当もつきませんよ。";
			link.l1.go = "gambit_5";			
		break;
		
		case "gambit_5":
			dialog.text = "イギリスの私掠船については、アンティグアのセントジョンズで聞き込みをするといい。 誰かがきっと教えてくれるはずだ。イギリス艦隊で働きたいと伝えればいいさ。\n「第三勢力」については、ブリッジタウンの人々に話を聞いてみるといい。 あそこにはきっとこの組織と繋がりのある者がいるはずだ。";
			link.l1 = "彼らの働きには少なくとも報酬が出るのか？会社やこの私掠船者は……それとも全部「コネ」のためってわけか？";
			link.l1.go = "gambit_6";			
		break;
		
		case "gambit_6":
			dialog.text = "シャルル、君には驚かされるよ。オランダ西インド会社は王様も羨むほどの金額を動かしているんだ。 私が話したあの私掠船長は、オランダ船を山ほど襲って、すでに財宝が溢れているはずさ。それに「組織」の連中は、 ただ金持ちなだけじゃない。奴らは血塗られた大富豪だ。奴らの下で働けば、必ずうまい汁にありつける。 ああいう連中は、いつだって大きく賭けるんだよ。そして、もし君が賢ければ、自分のゲームを仕掛けて、 さらに儲けることだってできるさ。";
			link.l1 = "わかった。少し考えて自分にとって一番いい方法を決めるよ。他に指示はあるか？";
			link.l1.go = "gambit_7";
		break;
		
		case "gambit_7":
			dialog.text = "そうだ。航海用の道具の使い方を学ぶべきだな。残念ながら、 多くの航海士は羅針盤や星だけで方角を知ることはできても、自分の座標を割り出すことができない。 そしてこれは非常に重要なことだ。\nさて、緯度を測るにはブソールを使うんだ。これはかなり珍しい道具で、店では手に入らないが、 コンパスとアストロラーベという二つのありふれた道具を使えば自分で作れる。ほら、作り方の説明書をやろう。\n経度を測るのは少し厄介だ。等級付きクロノメーターが必要になる。 普通の船用クロノメーターを砂時計で調整すれば作れるぞ。ただし、この道具は誤差が大きくなるため、 効率よく使えるのはせいぜい一ヶ月だけという問題がある。\nクロノメーターは常にリセットが必要だ。砂時計はオランダ西インド会社の事務所で買える。 クロノメーターもそこで手に入れた。これも作り方の説明書だ、受け取れ。";
			link.l1 = "ありがとうございます。すぐに勉強に取りかかります。";
			link.l1.go = "gambit_8";
		break;
		
		case "gambit_8":
			AddQuestRecordInfo("Recipe", "bussol");
			SetAlchemyRecipeKnown("bussol");
			AddQuestRecordInfo("Recipe", "clock2");
			SetAlchemyRecipeKnown("clock2");
			dialog.text = "できるだけ早くこれらの道具をすべて手に入れるようにしなさい。経験豊富で尊敬される船長たちは皆、 緯度と経度で航海しているのだ。その数字の意味が分かるまでは、航海術の初心者と思われるぞ。\nさて、最近話し合った件で成果が出たら、すぐに自慢しに戻ってきなさい。幸運を祈る、シャルル！";
			link.l1 = "ありがとう、親愛なる兄さん。きっと役に立つ気がするよ！";
			link.l1.go = "gambit_9";
		break;
		
		case "gambit_9":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Sharlie = "gambit";//флаг на Голландский Гамбит
			pchar.questTemp.HWIC.CanTake = "true"; //Голландский Гамбит доступен для взятия
			AddQuestRecord("Sharlie", "20");
			npchar.greeting = "mishelle_3";
			AddMapQuestMarkCity("Bridgetown", false);
			AddMapQuestMarkCity("Villemstad", false);
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			// Rebbebion, убираем марки
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "gambit_fale":
			dialog.text = "「それで、お前は何を自慢できるんだ？」";
			link.l1 = "今のところ何もない。三つの組織すべてを見つけて協力しようとしたが、 葉巻みたいに最初の段階で全部煙のように消えちまった。まるで運命が俺に味方してくれねえみたいだ…";
			link.l1.go = "gambit_fale_1";			
		break;
		
		case "gambit_fale_1":
			dialog.text = "やはり噂は本当だったか……兄上よ、運命があなたに味方しないのではない。鈍い頭と不器用な手のせいだ。私を失望させたな。フランスへ帰れ、 ここでお前にできることはもう何もない。";
			link.l1 = "「しかし、どうやって……」";
			link.l1.go = "gambit_fale_2";			
		break;
		
		case "gambit_fale_2":
			dialog.text = "もうお前の出る幕じゃねえ。俺が自分で片付ける。他にもっと役に立つ奴らがいるんだ。お前に打ち明けたら、 一生ここに縛られるんじゃないかと怖かったんだよ。\nとにかく、さっさと出て行け。お前の愛人たちのところに戻るんだな。";
			link.l1 = "いいさ、地獄に落ちろ…";
			link.l1.go = "gambit_fale_3";
		break;
		
		case "gambit_fale_3":
			DialogExit();
			NextDiag.CurrentNode = "gambit_fale_4";
			npchar.lifeday = 30;
		break;
		
		case "gambit_fale_4":
			dialog.text = "お前と話すことなんてねえ。行け。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gambit_fale_4";
		break;
		
		case "saga":
			switch(pchar.questTemp.HWIC.Detector)
			{
				case "holl_win": sTemp = "I've entered service with the Dutch West India Company and become a special tasks agent and close friend of the vice administrator of the Company, Lucas Rodenburg. I managed to carry out several serious missions, in particular, I liquidated the actual English privateer. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "holl_fail": sTemp = "I've entered service with the Dutch West India Company, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "eng_win": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship' and did away with Lucas Rodenburg himself, vice administrator of the Company. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "eng_win_half": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship'. Of course, Fleetwood departed to England and my service with him is over, but still..."; break;
				
				case "eng_fail": sTemp = "I've entered service with the English privateer from Antigua, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "self_win": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, and achieved quite a bit: I did away with that English privateer, Richard Fleetwood, put Lucas Rodenburg, the vice administrator of the Company, behind bars, become a close friend of governor Matthias Beck and the company's director Peter Stuyvesant. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "self_fail": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, however it all went down in dust at the moment of truth..."; break;
			}
			dialog.text = "で、どうなんだ？さあ、兄上、もったいぶらずに早く教えてくれよ。何か熱心に働いているって噂は耳にしたけど、 全部あなたの口から聞きたいんだ。";
			link.l1 = sTemp;
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "素晴らしい！よくやったな、シャルル！お前のことは最初から疑ってなかったぞ！きっと大物になるさ、弟よ…そんなふうに自分を忙しくして、あんな大物たちと関係を築くなんて――正直、驚いたよ。おめでとう！";
			}
			else
			{
				dialog.text = "落ち込むな、シャルル。うまくいかなかったなら、仕方ないさ。\n必要な結果を得るために、他の手段を使おう。";
			}
			link.l1 = "これからどうする、ミシェル？シュヴァリエ・ド・ポアンシーに会いに行く時か？ 彼と話す準備は十分できている気がする。";
			link.l1.go = "saga_2";	
		break;
		
		case "saga_2":
			dialog.text = "もう必要な百万円のペソを用意できたのか？";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "はい、今は必要な金額を持っております。";
				link.l1.go = "saga_3_1";
			}
			else
			{
				link.l1 = "いいえ、まだそんなにお金は持っていません。";
				link.l1.go = "saga_3_2";
			}
		break;
		
		case "saga_3_1":
			dialog.text = "素晴らしい！これで俺もこの地下牢に長居せずに済みそうだな……さあ、カップスターヴィルへ向かえ。サン・クリストファー島にある町だ。そこでド・ポワンシーに謁見を求めろ。 やつは総督官邸にいるはずだ。あとは状況を見て判断してくれ。ただし覚えておけ、ポワンシーは抜け目ない、 相当な食わせ者だ……この一件、そう簡単には終わらない気がしてならない。行け、弟よ、そして気をつけろ！";
			link.l1 = "注意は心得ておくよ、ミシェル。心配するな、俺だって昨日生まれたわけじゃない。さて、 あの老狐のところへ行ってくる。じゃあ、またな！";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_3_2":
			dialog.text = "じゃあ、デ・ポワンシーに話しても無駄だな。あいつはお前を中にすら入れやしない。金を集めろ、兄弟よ。 もう十分経験を積んでいるんだから、大した問題じゃないだろう。 金が揃ったらすぐにセントクリストファーのキャップスターヴィルへ航海しろ。\nシュヴァリエは総督の宮殿にいるはずだ。謁見を求めれば中に通してくれる。それから自分の目で確かめて、気をつけろ。 デ・ポワンシーは狡猾だ、すごくな……どうもこの話、そう簡単には終わらない気がするぜ。";
			link.l1 = "注意はちゃんと覚えておくよ、ミシェル。心配するな、俺だって世間知らずじゃねえさ。金が揃い次第、 すぐにあの老いぼれ狐のところへ行くぜ。じゃあ、またな！";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			DialogExit();
			AddMapQuestMarkCity("Charles", false);
			AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
			npchar.quest.givelink_saga = "true";
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "saga";//флаг на Пиратскую Сагу
		break;
		
		case "saga_5":
			dialog.text = "なんてこった！まさにそれが俺の恐れていたことだ。ポワンシーはずっとお前の後を追っていたんだ、シャルル。 それでお前にあんなに目をつけていたのさ！カリブでお前はすっかり名を上げたから、 奴はお前を使って失敗した任務を片付けさせようと決めたんだよ…";
			link.l1 = "ミシェル、君は前からちゃんと知っていて、わざと俺に知らせなかったんじゃないかという気がするよ。 すべてがうまく行きすぎてる……最初は金、今度は君の仕事……偶然でこんなことにはならないさ。";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "シャルル、ないところに秘密のメッセージを探そうとするな。\nもしお前が到着したその日にポワンシーに金を渡していれば……まあ、金があったとしての話だがな。シュヴァリエはそれ以上何も頼まなかっただろう。だが今や、 あいつはお前に興味を持ち、ここでいかに楽に馴染み、何を成し遂げたかを見て、 お前の才覚を利用することに決めたんだ。";
			link.l1 = "そうか……つまり、お前の腕前じゃもうあいつの期待に応えられなくなったってことか？くそっ！分かった。 もう手詰まりってわけだな。で、その異端者って誰だ？どうやって見つければいい？";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "彼を探す必要はない！奴は決してトルトゥーガを離れず、自ら築いた要塞と、 彼の守備隊で兵士として仕える忠実なユグノー教徒の大群の庇護下にいるのだ。だから、 すべての兵士が奴に忠誠を誓っている。プアンシーが言っていたのは、 トルトゥーガ総督フランソワ・ルヴァスールのことだ。\nスペイン人どもは今も奴をそこから引きずり出せずにいるし、プアンシーは本気で、海軍の支援もなく、 ただサント・ドミンゴ守備隊が近いせいで内戦を起こすのは政治的に大失策になるからという理由だけで、 俺が一人でそれを成し遂げられると信じていた。\nあの老いぼれ悪党は、自分の汚れなき経歴と、間近に迫った年金のために、そんな危険を冒す気はさらさらないのさ。 それでも、ルヴァスールはやりすぎて、今や王冠にとって危険な存在となっている。\nルヴァスールを今の地位に任命したのは他ならぬプアンシー自身であり、この恐るべきユグノーを個人的な敵と見なして、 マルタから俺をここに送り込んだ直属の上官、マルタ騎士フォンテネーに奴を交代させたがっているのだ。";
			link.l1 = "素晴らしい！まずは百万稼いで、その次はトルトゥーガ総督の暗殺か。さて、次の任務は何だ？ エスコリアルで陰謀でも企てろってか？くそっ！お前があれをしくじったのも無理はない。 総督を始末するのはスペインの商人を襲うのとは訳が違うんだぜ。火中の栗を拾うと誓った時、 何かしら計画はあったんだろうな？";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "正直に言うと、特に計画なんてなかったんだ。どうせこの冒険がうまくいけば、 すぐにでも役目を辞めて実家の屋敷に戻るつもりだったしな。個人的には、 ド・ポワンシーの問題なんてどうでもいいんだよ。\nインディオの金を見れば、あいつもきっと態度を変えるだろうさ……まあ、今のところは向こうが完全に主導権を握ってる。ルヴァスールがトルトゥーガ総督でいる間は、 ここに留まるしかなさそうだな。";
			link.l1 = "「それに、マルタ騎士団の連中がド・フォンテネーに率いられて、 総督の座を狙って自分たちでトルトゥーガを襲撃しない理由があるか？」";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "想像してごらんなさい。騎士団がルイに宣戦布告するなんて、馬鹿げている！そんな大騒動はあり得ません。 トルトゥーガを奪取できるのは、あくまで個人――つまり海賊か、あなたのようなカトリックの冒険者だけです。\nその後で、新しい総督としてプアンシーが派遣する人物に島を引き渡せばいいのです。そうすれば、 高官たちの目から見ても非常に都合の良い行動に映ります。";
			link.l1 = "「それで、海賊と交渉する意味なんてあるのか？」";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "問題は、ルヴァスールがバッカニア同盟の多くの海賊、さらにはそれ以外の者たちにも権威を持っていることだ。 やつはトルトゥーガの砲台の陰に海賊どもを匿い、略奪した品を自由に売らせて、その分け前を受け取っている。\n以前はポワンシーとも分け前を分け合っていたが、今はもうそうじゃない。 海賊船たちはトルトゥーガとその守備隊を守るだろうから、要塞を強襲するのはさらに難しくなる。";
			link.l1 = "「この件はもう望みがないと思うか？」";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "解決策は必ずあるんだ、弟よ。ただ、表面には見えないこともあるだけさ。 トルトゥーガのユグノーに同情的な海賊ばかりじゃない。 ルヴァスールを裏切り者でクズだと考えている有力な海賊を少なくとも二人は知っている。スティーブン・ドッドソン、 通称シャークと、モスキート湾の伝説的な男爵ヤン・スヴェンソンのことだ。\nシャークがどこにいるかは分からない。何かあってイスラ・テソロの根城を離れたという噂を聞いた。でも、 スヴェンソンならブルーウェルドで必ず会える。あそこではかなりの大物だ。";
			link.l1 = "「この…スヴェンソンとかいう奴が私を助けてくれると思うか？」";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "彼は、君が手を貸せばきっと助けてくれるだろう。今のところ彼の状況はあまり良くないし、 忠実で有能な人材を必要としている。まずは自分が役に立つ存在だと証明しなければ、本格的な話はできないだろう。 現地に着けば、どうすればいいか分かるはずだ。ここからでは助言しづらいんだ。\nそれだけ質問を重ねるということは、シャルル、君は進む決心をしたということだな？";
			link.l1 = "見てくれよ、ミシェル。俺は今しがた自分の銀貨の山をポワンシーに渡したんだぜ。血と汗と涙で貯めた金だ！ もし立場が逆だったら、お前は俺のためにルイドール一枚すら賭けてくれたかどうか怪しいもんだな。";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "シャルル……";
			link.l1 = "邪魔しないでくれ！手ぶらで父上のもとに戻るなんて愚かだ。問題はまだ解決していないし、 お前は牢屋に入れられたまま、協会への裏切りで有罪になる危険もある。ポワンシーは、俺があいつの「頼み」 を果たさなければ、モンペ家の名を汚すことなど平気でするだろう。顔にそう書いてあったさ。 だから俺はブルーウェルドへ行って、スヴェンソンに近づく方法を探すつもりだ。その間に、お前が俺にまだ 「言い忘れている」ことをよく考えておけ。たとえば、インディアンの金をポワンシーに持っていくはずだったなんて話、 今初めて聞いたぞ。";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "隠しておいた方がいいこともある。君の言う通り、私は知っていることをすべて話したわけではない。 いつかもっと話すかもしれないが、それは君がルヴァスールを片付けてからだ。今は知っても無駄なことだろう。\n君が私を気遣うのは、我が家の名誉を守りたいという思いからに違いない。私を救うことで、まず自分自身を救い、 次にパリの一流の屋敷に出入りする機会を守ることになる。違うか？";
			link.l1 = "もうそうじゃないんだ、兄さん。君の言う通りだったよ。この数ヶ月カリブで過ごしたことで、 俺の心も考え方もすっかり変わった。しかも、それはきっと良い方向に変わったんだ。 もうパリのサロンなんて必要ないし、いつかモンペールの名がなくてもやっていける気がする。 ド・モールだって悪くないさ…";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "...";
			link.l1 = "そして今、私が本当に心を痛めているのは、お前の不名誉が我らの老いた父に汚点を残すという事実だけだ。 父上は本当の事情も、ここで何が起きているのかも知らない。それに、お前が言った通り、 家督もこの惨状から立て直さねばならない。そして、お前の自由のために支払った百万は、 私の財産を大いに減らしたから、間違いなく補填が必要になるだろう。";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			dialog.text = "シャルル、あなたは人生の教訓を見事に身につけましたね。私は本当に嬉しく思います。そして、 フランスへ帰ることなく、ポアンシーの依頼を引き受けてくれてよかったです。すべてがうまくいき、 私が果たせなかったことをあなたが成し遂げられることを願っています。";
			link.l1 = "残念ながら、私には選択肢がない。カリブに来た初日から、私はずっと一人でやってきたんだ。\nじゃあな、ミシェル。次に会う時は、お前の釈放命令も一緒だと思うぜ。";
			link.l1.go = "saga_17a";

		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "saga_17a":
            dialog.text = "ちょっと待て！ヤン・スヴェンソンのところへ行く前に、必ずマーカス・タイレックスに会ってこい――奴は「掟の番人」だ。イスパニョーラ島のラ・ベガを仕切っている。海賊の間では絶対的な権力を持ち、 スペイン人どもは奴を死ぬほど恐れているんだ。\n";
			link.l1 = "「彼は私たちの件で力を貸してくれるだろうか？」";
			link.l1.go = "saga_17b";
		break;
		
		case "saga_17b":
            dialog.text = "疑わしいな。どっちの味方かは正直分からねえが、たぶん自分のためだけに動いてるんだろう。 どのみちシャークとスヴェンソンは必要になるが、今この海で一番力を持ってるのはタイレックスだ。 やつが掟番に選ばれたのも理由がある。そんな重要人物を無視しちゃいけねえ。スヴェンソンに会う前に、 海賊たちともっと親しくなっておくのも悪くねえぞ。もしかしたら、あんたも奴らの間で名を上げられるかもしれねえ……\n";
			link.l1 = "またしても、結局は海賊の話に戻るのか。どうしても逃げられないんだな、俺は？仕方ない。 あいつに会いに行くとしよう。";
			link.l1.go = "saga_17c";
		break;
		
		case "saga_17c":
            dialog.text = "海賊になることと、海賊と商売をすることはまったく別物だ、兄弟よ。その違いが分かるといいんだがな。\nラ・ベガへ行って、タイレックスに仕事を頼んでみろ。もしそいつとウマが合わなければ、 気にせず俺のところに戻ってこい。";
			link.l1 = "承知したよ、ミシェル。またな！..";
			link.l1.go = "saga_17d";
		break;
		
		case "saga_17d":
            DialogExit();
			AddQuestRecord("Sharlie", "22");
			npchar.greeting = "mishelle_3";
			pchar.questTemp.Mtraxx = "to_lavega";
			pchar.questTemp.Saga = "pirate_line";
			AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
			AddMapQuestMarkCity("LaVega", false);
		break;
		
		case "saga_17e":
            dialog.text = "少なくとも努力はしたな。悪名高い海賊男爵と「知り合い」になる機会もあったじゃねえか。まあいい。 ブルーウェルドにいるヤン・スヴェンソンのところへ行け。奴を味方につけてみろ、 さもないとルヴァスールとの取引が血の雨になるぞ。";
			link.l1 = "わかった。今行く。";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17f":
            dialog.text = "止まってくれてよかった、兄弟。昔言っただろう、海賊になるのと海賊と取引するのはまったく別物だって。 お前は道を見失っている。この先、シャークやスヴェンソンで同じ過ちを繰り返さないことを願う。 仕事はきっちりこなせ、だがあいつらとは距離を保て。お前はフランス貴族なんだから、やつらより上に立て。さあ、 ヤン・スヴェンソンのところへ行け。あいつはブルーウェルドにいる。味方にできるよう努めろ。そうしなければ、 ルヴァスールとの取引は血で終わるぞ。";
			link.l1 = "よろしい。これから向かう。";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17g":
            dialog.text = "本当のことを言っているのなら、非常に嬉しいです。\nしかし、たとえスペインの町であっても都市を焼き払い、女性を含む民間人を殺す海賊の言葉を、 本当に信じてよいのでしょうか？";
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice"))
			{
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "good")
				{
			link.l1 = "やめてくれ……タイレックスと一緒にいた頃の自分の行いを、本当に悔いているんだ。地獄をこの目で見たんだよ、兄さん……いや、もう終わりだ！俺は海賊稼業から足を洗ったし、二度とラ・ベガには近づかない。名誉を取り戻すためなら、 どんなことでもするさ。";
			link.l1.go = "saga_17gx";
				}
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "bad")
				{
					link.l1 = "信じるかどうかは勝手だが、檻の中にいるのはお前で、俺じゃないぜ。";
					link.l1.go = "saga_17gxa";
				}
			}
			else //заглушка
			{
				link.l1 = "やめてくれ……タイレックスと組んでいた時に犯した数々の悪行を、本当に悔いているんだ。地獄をこの目で見てきたんだ、兄弟よ！……いや、もう俺の海賊時代は終わった！ここはラ・ベガじゃない。俺は自分の名誉を取り戻すために、 できる限りのことをするつもりだ。";
				link.l1.go = "saga_17gx";
			}
		break;
		
		case "saga_17gxa":
            dialog.text = "ああ、兄さん……神を怒らせるな……スヴェンソンやシャークでも同じことが起きないよう願うよ。やるべきことはやってもいいが、距離を保ち、 彼らがどんな人間か忘れないでくれ。フランス貴族があのような連中に成り下がるのは見苦しい。誇りを持ってくれ。 さあ、ブルーウェルドのヤン・スヴェンソンのもとへ行き、あの老コルセアに近づく方法を探してみなさい。彼なしでは、 ルヴァスールとの問題を最小限の流血で解決することはできないのだから。";
			link.l1 = "わかった。邪魔はしない。";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;

		case "saga_17gx":
            dialog.text = "かなりの努力が必要になるぞ、兄さん。以前言ったことを覚えているか？海賊になることと、 海賊と取引することはまったく別物だって。お前は…いや、やめておこう。シャークやスヴェンソンと同じ過ちを繰り返さないことを願っている。仕事はきちんとこなせ、 だが彼らとは距離を保て。お前はフランス貴族なのだから、彼らより上に立つべきだ。さあ、 ヤン・スヴェンソンのところへ行け。彼はブルーウェルドにいる。彼を味方につけるんだ。 そうしないとルヴァスールとの取引が血みどろの争いになってしまうぞ。";
			link.l1 = "わかった。これから向かう。";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;
		
		case "saga_17":
			DialogExit();
			AddQuestRecord("Sharlie", "22_1");
			pchar.questTemp.Saga = "blueveld";
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			npchar.greeting = "mishelle_3";
			if(CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
				SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
			}
			AddMapQuestMarkCity("SantaCatalina", false);
			AddLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("JS_girl"), "questmarkmain");
		break;
		
		case "Base_fight":
			dialog.text = "今は話している場合じゃないぞ、兄弟！敵が俺たちの隠れ家に入り込んでるんだ！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Base_fight";
		break;
		
		case "Base_afterfight":
			sTemp = "";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) sTemp = "I see you've become a captain of the navy... I didn't see that coming to be honest. I truly congratulate you!";
			dialog.text = "ちょうどいい時に来てくれたな、兄さん！会えて本当に嬉しいよ！この忌々しいカスティーリャ野郎どもがサン＝ ピエールをすっかり乗っ取っちまったんだ。もう絶対に終わりだと思ってたぜ！ "+sTemp+"";
			link.l1 = "まだ安心できねえぜ。街は片付いたが、クズどもは砦に立てこもってるし、 戦列艦に率いられたでっけえ艦隊までいるんだ。\nだが、ちょっと嬉しい知らせがあるぜ――ミシェル、お前は自由の身だ！";
			link.l1.go = "Base_afterfight_1";
		break;
		
		case "Base_afterfight_1":
			dialog.text = "俺の耳を疑うぜ！本当なのか？自由だって！？";
			link.l1 = "ルヴァスールは死に、トルトゥーガは今やお前の元上官が率いている。 そしてあの老獪なポワンシーもお前への全ての罪状を取り下げた。\nこれからは、我々の名誉を脅かすものは何もない。";
			link.l1.go = "Base_afterfight_2";
		break;
		
		case "Base_afterfight_2":
			dialog.text = "最後の瞬間まで疑っていた……シャルル、お前には驚かされたよ。私が惨めな失敗をしたところで、お前は見事に成功したな。";
			link.l1 = "運は勇者に味方する、兄弟よ……見ての通り、俺も今やラテン語くらい知ってるぜ。お前の牢の鍵はどこだ？";
			link.l1.go = "Base_afterfight_3";
		break;
		
		case "Base_afterfight_3":
			dialog.text = "私の独房の鍵は当直士官の机の上にあるはずだ。そこを探してみてくれ。\nもしかしたら床に落ちてどこかに滑り込んでいるかもしれない……";
			link.l1 = "俺が探しに行って、すぐ戻るぜ！";
			link.l1.go = "Base_afterfight_4";			
		break;
		
		case "Base_afterfight_4":
			DialogExit();
			pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Base_afterfight_6":
			dialog.text = "ついに――自由だ！この瞬間をどれだけ待ち望んだことか！";
			link.l1 = "俺もこれをどれだけ待ち望んでいたか、お前には分からねえよ！\nミシェル、反撃するために仲間を集められるか？";
			link.l1.go = "Base_afterfight_7";			
		break;
		
		case "Base_afterfight_7":
			dialog.text = "シャルル、何を考えているんだ？";
			link.l1 = "スペイン人の脅威はまだ消えていない。まずやつらを砦から追い出し、 それから陸と海の両方から艦隊を攻撃するために力を合わせたい！\n堡塁の大砲を使えば、戦列艦と戦うことができるはずだ！";
			link.l1.go = "Base_afterfight_8";			
		break;
		
		case "Base_afterfight_8":
			dialog.text = "人手はある。多くの騎士たちが総督の宮殿を守るために出払っているが、街の中なら必ず誰か見つかるはずだ……見つけられる限り全員を集めるよ。\n城門の向こうで会おう！";
			link.l1 = "...";
			link.l1.go = "Base_afterfight_9";			
		break;
		
		case "Base_afterfight_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, ""); // скрытое бессмертие
			LAi_SetHP(npchar, 500, 500);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
			pchar.quest.DefendSP_base2.win_condition.l1 = "location";
			pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
			AddQuestRecord("Sharlie", "36");
		break;
		
		case "Fort_attack":
			dialog.text = "これだ、兄弟、俺たちの軍勢だ。俺が集められた全員さ。数は多くねえが、祖国のために戦うぜ！ この血まみれの侵略者どもを砦から叩き出してやる！奇襲の利がある――奴らは俺たちの攻撃を予想しちゃいねえ。進め！";
			link.l1 = "「祖国のために死ぬことは甘美で名誉なり！」進め！";
			link.l1.go = "Fort_attack_1";
		break;
		
		case "Fort_attack_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (i=1; i<=7; i++)
			{
				sld = CharacterFromID("DefendSP_frafort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
			pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
			pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
			locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;
		
		case "Fort_attack_2":
			dialog.text = "終わったぞ、兄弟！砦は俺たちのものだ！";
			link.l1 = "スペイン艦隊との戦いであんなに損傷したのは残念だが……それでもまだ十分に戦いを指揮できる力はある。";
			link.l1.go = "Fort_attack_3";			
		break;
		
		case "Fort_attack_3":
			dialog.text = "俺もやるぜ。大砲を装填して、敵にでかい一撃を食らわせてやる！\nだが、お前の艦隊が近づくのを見てからだ。じゃねえと、戦列艦にあっという間に木っ端みじんにされちまうからな。";
			link.l1 = "人を集めろ、ミシェル！俺はすぐに岸へ戻るぞ！";
			link.l1.go = "Fort_attack_4";			
		break;
		
		case "Fort_attack_4":
			dialog.text = "シャルル、覚えておけ。戦隊で一番危険なのは戦列艦だ！まずはあいつを沈めるんだ。砦の砲台が残っている分も、 あいつに集中砲火を浴びせるぞ。\n";
			link.l1 = "わかったよ、兄さん。もしかしたら、俺があの娘を捕まえるべきかもしれないな。";
			link.l1.go = "Fort_attack_5";			
		break;
		
		case "Fort_attack_5":
			dialog.text = "状況から判断すると、教えるべきなのは俺じゃねえ。もうこれ以上、時間を無駄にするのはやめようぜ！";
			link.l1 = "...";
			link.l1.go = "Fort_attack_6";			
		break;
		
		case "Fort_attack_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Shore38", "boat", false); // выпустить в море
			// закрываем городские заведения
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
			pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
			pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
			pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
			pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
			AddQuestRecord("Sharlie", "37");
		break;
		
		case "Victory":
			dialog.text = "栄光は勝者にあり！勝利おめでとう、兄さん！君は本当に素晴らしかった！スペイン人どもは完全に壊滅したぞ！";
			link.l1 = "これでフランス植民地を襲う前に、二度と軽はずみな真似はしないだろう。";
			link.l1.go = "Victory_1";			
		break;
		
		case "Victory_1":
			dialog.text = "さて、シャルル、教えてくれ。お前のこれまでの人生は……この新しい人生と比べて、どれほどの価値がある？";
			link.l1 = "「思い出させないでくれ……」";
			link.l1.go = "Victory_2";			
		break;
		
		case "Victory_2":
			dialog.text = "ここで最初に会った時、私が何を言ったか覚えているか？「お前はこの人生をきっと好きになる」、そう言ったんだ！ ああ、それと本当にありがとう、兄弟よ。お前の助けがなかったら、 あの地下基地から抜け出すことなんて絶対にできなかっただろう。";
			link.l1 = "気にするな、ミシェル。お前は俺の兄弟だし、助ける義理があったからな。";
			link.l1.go = "Victory_3";			
		break;
		
		case "Victory_3":
			dialog.text = "見てみろよ、兄弟。感心したぜ。目には力がみなぎり、動きには自信があり、立ち姿にも威厳がある……あの情けない芸術家で道化者だったお前はどこへ行ったんだ？本当に！俺の想像を遥かに超えてきたな。正直言って、 お前が……こんなふうになるなんて思ってもみなかった。\nそれどころか……少し怖いくらいだ。お前は目的のためなら何だってやるだろう。すごいよ、お前は……すごすぎる。";
			link.l1 = "どういうわけか、また君の言っていることがよく分からなくなってしまったよ。\nまた僕のことが気に入らないのかい？";
			link.l1.go = "Victory_4";			
		break;
		
		case "Victory_4":
			dialog.text = "いや！何を言ってるんだよ……全然違う！ただ興奮していただけさ。";
			link.l1 = "わかった。さて、これからどうするんだ、兄さん？まだソサエティに仕えるつもりか？それとも我が家の領地に戻るのか？ ああ、それともう一つ、忘れるところだった――約束してくれたあの話、聞かせてくれるんだろうな。";
			link.l1.go = "Victory_5";			
		break;
		
		case "Victory_5":
			dialog.text = "具体的に何のことだ？";
			link.l1 = "ド・ポアンシーへの奉仕についてだ。あんたが持ってくるはずだったインディオの金についても。 あんたが投獄されるに至ったすべての経緯についてもだ。ミシェル、まだ俺に話していないことが山ほどあるじゃねえか。 俺はほとんど何も知らされてないんだ。だからさ…";
			link.l1.go = "Victory_6";			
		break;
		
		case "Victory_6":
			dialog.text = "兄さん、私が言ったことはちゃんと覚えているよ。全部話すさ。でも、燃え盛る街の真ん中じゃ無理だ！\n今はお互いにやることが山ほどある。君は自分の艦隊を落ち着かせて、修理して、 再び出航できるように準備しないといけない。総督と私は住民たちをまとめて落ち着かせるよ。\n明日の朝、うまいフランスワインを飲みながら全部話そう。信じてくれ、兄さん、俺には大きな計画がある。 本当にでかいんだ。でも今じゃない。明日午前九時にブノワ修道院長を訪ねてくれ。私は今夜、彼のところに泊まる。 彼は昔からの友人なんだ。";
			link.l1 = "よし、ミシェル。これで決まりだな。明日の話を楽しみにしているぞ。";
			link.l1.go = "Victory_7";			
		break;
		
		case "Victory_6A":
			dialog.text = "「ダイアログ28。」";
			link.l1 = "わかったよ、ミシェル。これで決まりだな。明日の話を楽しみにしているよ。";
			link.l1.go = "Victory_7";
		break;
		
		case "Victory_7":
			dialog.text = "別れの挨拶なんていらないぜ、シャルル！";
			link.l1 = "...";
			link.l1.go = "Victory_8";			
		break;
		
		case "Victory_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Sharlie", "39");
			pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
			pchar.quest.DefendSP_final.win_condition.l1.date.hour  = 9;
			pchar.quest.DefendSP_final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
			// раздача экспы
			ChangeCharacterNationReputation(pchar, FRANCE, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 10);
			AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 1000);
			AddSimpleRumour("All those residing in the French colony owe you, Captain. Defending Saint-Pierre from the vile attack of the Spanish is quite a feat!", FRANCE, 30, 15);
			AddSimpleRumour("It's an honor for me to speak with the brave Captain that has beaten a bunch of Spanish invaders hollow!", FRANCE, 30, 15);
			AddSimpleRumour("The French colonists may sleep in peace, while brave naval officers such as you are at the King's service!", FRANCE, 30, 15);
			AddSimpleRumourCity("We are all forever indebted to you, Captain! You have saved our colony from devastation!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are a brave and astute naval officer. All those residing in Saint-Pierre are praying for you, know that!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are the pride and joy of our nation and the hero of Saint-Pierre. We will never forget that!", "FortFrance", 30, 15, "");
			npchar.greeting = "mishelle_0";
		break;
		
		case "kukulkan":
			PlaySound("Voice\English\sharlie\mishelle-04.wav");
			dialog.text = "「また会ったな」 "+pchar.name+"……私が警告したにもかかわらず、君はなおも私を探し続け、その探索は君を遥か遠くまで連れてきた……";
			link.l1 = "ミシェルか……何故か驚きはしないな。ミゲル・ディチョソがまたテヤサルに宝を漁りに戻ってきたのか？ふふふ。そうだよ、 俺はお前に会いたかったんだ、愛しき兄弟よ。お前の恥知らずな目をこの目で見たくてたまらなかった。しかも、 墓地の地下室で俺を暗殺しようとしたことまで加わって、まさに極めつけだな。さて、まずは聞かせてくれよ、 お前を何と呼べばいい？ミシェル・ド・モンペールか、それともミゲル・ディチョソか？";
			link.l1.go = "kukulkan_1";			
		break;
		
		case "kukulkan_1":
			dialog.text = "「これらの名前はもう重要ではない」 "+pchar.name+"。すべては過去のことだ、それすらも間もなく歴史から消え去るだろう。今こそが真実の瞬間――私が初めて上陸してから四半世紀もの間、少しずつ近づいてきたその時なのだ…";
			link.l1 = "なにっ？！これは…これはありえない！！";
			link.l1.go = "kukulkan_2";			
		break;
		
		case "kukulkan_2":
			dialog.text = "「はい。」 "+pchar.name+"。私の顔を見て、私が誰か理解したようだが、信じられないのだろう。ここ数ヶ月、 お前が会いたいと願ってきたその人物が私だ。お前の神の代理人、 サンティアゴの異端審問官が戦いのためにお前に与えた、その相手が私なのだ。";
			link.l1 = "ククルカン！？";
			link.l1.go = "kukulkan_change";			
		break;
		
		case "kukulkan_change":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kukulkan_3":
			dialog.text = "同意します。 "+pchar.name+"、信じがたいほどだ。人生はどんなおとぎ話よりも複雑で、驚きに満ちている……";
			link.l1 = "何があっても覚悟はできていたが……兄さん！";
			link.l1.go = "kukulkan_4";			
		break;
		
		case "kukulkan_4":
			dialog.text = "兄弟？親父の血を分けただけさ。母親は違うんだ。 "+pchar.name+"私の母はカネクの娘で、ショチケシャルという名だったことを知っておけ。彼女は愚かにもタヤサルを離れた後、 有名なニコラ・ゴティエの指揮下にあったフランスの私掠船員たちにさらわれた。彼らは彼女を奴隷にしようと決めた。 その中にセルジュ・ブノワという男がいた。彼は自分の船長の行いを恥じて彼の元を離れ、修道士となった。 今ではアボット・ブノワとしてお前も知っているはずだ。アンリ・ド・モンペール――我らの父は、当時海軍士官だった。彼はショチケシャルを買い取り、フランスへ連れて行き、そこで私を産ませた。 ほぼ同じ頃、お前も生まれたのだ。\n "+pchar.name+"。お前の母親は出産で亡くなり、我々の父は正妻が双子を産んだと宣言したのだ。\nショチケシャル、私の母は、我々二人の乳母となった。お前はイッツァ族のインディオ女の乳で育てられたのだ。 "+pchar.name+"！その後、母方の祖母があなたを引き取り教育することを決め、あなたには母の姓――ド・モールが与えられた。";
			link.l1 = "どうやってそんなこと全部知ったんだ！？";
			link.l1.go = "kukulkan_5";			
		break;
		
		case "kukulkan_5":
			dialog.text = "兄上、俺は他の誰よりも色々知っていると思わないか？それに、父上からもたくさん聞かされているし、色々 と承知しているんだ……。\nまさに言われている通り、成り行き任せってやつさ。";
			link.l1 = "これで全て分かった……それで、お前の母上はどうなったんだ？なぜ一度も会ったことがないんだ？";
			link.l1.go = "kukulkan_6";			
		break;
		
		case "kukulkan_6":
			dialog.text = "彼女は私の命を救って死んだ。\n私が生まれてから一年ちょっと経った頃、私は病気で死にかけた。\n母はイツァの神官の娘で、私のために秘密のマヤの治癒の儀式を行った。\n私は回復したが、この儀式にはいくつかの…破壊的な副作用が伴い、雷鳴や稲妻、そして熱帯のハリケーンが発生した。\nショチケザルは糾弾され、魔術の罪で異端審問により火あぶりにされたのだ……";
			link.l1 = "それで回復したんだな……";
			link.l1.go = "kukulkan_7";			
		break;
		
		case "kukulkan_7":
			dialog.text = "私を癒やすだけでなく、この儀式は他の能力も授けてくれた。さらに、神々の世界への繋がりも開かれたのだ。 あとのことは、もう知っているだろう。すでに知っている通り、私は白人種の知識と経験の光を過去へと持ち込み、 それをマヤの民に伝えるつもりだ。歴史は書き換えられ、お前たち白人がこの世界を支配することはなくなる。 私が必ずそうしてみせる。";
			link.l1 = "つまり、君の人生すべて――最高の海軍士官学校で学び、陸軍やマルタ騎士団で仕えたことも――結局は軍事経験を積み重ねてきただけってわけか？";
			link.l1.go = "kukulkan_8";			
		break;
		
		case "kukulkan_8":
			dialog.text = "その通りだ。十分な知識を得たと気づいたとき、私はカリブへの赴任を手配した。\nうまく立ち回って、ポアンシー騎士にマルティニークに基地を設けさせた。\n次は、タイアサルへ向かわねばならなかった。\nだが、私にとってそれは決して簡単な任務ではなかった――この肉体はあくまで人間であり、カリブのポータルもまともに機能していなかったからな。";
			link.l1 = "そしてお前はミゲル・ディチョソになったのか……";
			link.l1.go = "kukulkan_9";			
		break;
		
		case "kukulkan_9":
			dialog.text = "兄上、私はこのあだ名をヨーロッパの戦場で得たのだ。そこでラモン・デ・メンドーサ・イ・リバとも出会った。 人生は偶然でできていると思うか？いや、決してそんなことはない。すべての偶然は未知の規則性なのだ。 私がタイアサルへ戻るために、多くのことがなされた。私は二つの人生を生きねばならなかった――ミシェル・ド・モンペールとミゲル・ディチョーソとして。そして人々に両者が別人だと信じさせる必要があった。 お前と同じく、私はド・ポワンシーのために海賊となり、彼の信頼と恩恵、そして金を得なければならなかった。 私はラモン・デ・メンドーサへの貸しとして、海賊の指導者の一人、ブレイズ・シャープを殺さねばならなかった。 遠征の兵士を得るためだ。 私はタイアサルの財宝の話でド・ポワンシーとデ・メンドーサの両方を誘惑しなければならなかった。 私はド・ポワンシーの財務から七十五万枚の銀貨を受け取り、スペインの軍用フリゲート艦を海賊ドッドソンに売った。 そして遠征が始まった。私はタイアサルに戻ったが、待っていたのは失敗だった……\n";
			link.l1 = "なるほど……お前がまだ五歳の子供で、父上の領地で蝶を追いかけていた頃、偉大なる司祭カネクは、 ドン・アロンソ・デ・マルドナードによるタイアサル侵攻を恐れて、 過去へ旅するのに不可欠なククルカンの仮面を厳重に隠したのだ……失礼、いや、お前の仮面と言うべきだったな。";
			link.l1.go = "kukulkan_10";			
		break;
		
		case "kukulkan_10":
			dialog.text = "ああ、カネクはそこで自分自身を出し抜いたのだ。彼は最も難しい儀式を行った――古代人ですら敢えて行わなかった儀式を。彼は新たにできた無人島に仮面を隠し、そしてクソチェアテム――いわゆる「真実の守護者」への鍵を失くしてしまった。\n私は賢く立ち回る必要があった。その儀式は、 タイサルの財宝庫から守護された品を積んだ船がカリブ海を離れるのを阻み、 そうした船をクソチェアテムの岸へと打ち上げるものだった。私はそれを利用するつもりだった。 メンドーサを満足させるだけの財宝を持ち出し、さらに儀式で守られた特別な品も手に入れた。\nこの品を積んだ船は、必ずクソチェアテム――つまり私の仮面の元へと導かれる運命にあった。だから私は海へ出て、自分の存在をメンドーサに知らせたのだ。";
			link.l1 = " それで、テヤサルを自分ひとりで出てきたのか？";
			link.l1.go = "kukulkan_11";			
		break;
		
		case "kukulkan_11":
			dialog.text = "「メンドーサの兵士抜きで、という意味か？もちろんだ。ここタヤサルでスペイン人は全員殺された。 イツァ族自身が財宝を岸まで運び、俺はメンドーサに兵士たちはミスキート族の待ち伏せに遭ったと伝えた。 奴は信じたさ、金にしか興味がなかったからな、人間には興味がなかった。俺は『グリフォン・ドール』 の大砲の下で財宝を積んだ船を準備するつもりだったが、もっと上手くいった。 男爵が財宝を俺の監督下でスペインへ送ると決めたんだ。これ以上ない展開だった。 あとは船がカリブ海の見えない境界を越えるのを待つだけだった。だが、船長には別の命令があったと判明した。 特別な乗組員が大西洋に出た途端に反乱を起こし、乗組員と士官を皆殺しにする手はずだったんだ。その後、 船長はインディオの金をメンドーサに返すよう命じられていた。まったく、白人種の優等生ってやつだな、兄弟よ？ 俺は賭けに出るしかなかった。反乱がいつ起きるか分からなかったからな。だが、すべて計画通りに進んだ。『 サンタ・キテリア』がトリニダード・トバゴ島の東側に達したとたん、嵐が襲いかかり、 フリゲートはカリブ海へ押し戻され、クソチェアテムへ向かった。その後、俺は人生最大の失敗を味わった――波にさらわれて船から落ち、数日後にはマルティニークのル・マラン入り江で目を覚ました。漁師たちに発見され、 ル・フランソワへ連れて行かれた。だが、セザール・クレイグの屋敷で生き返ろうとしていたところを、 ド・ポワンシーの手下に捕まった。『グリフォン・ドール』は俺が指定した場所で『サンタ・キテリア』 を見つけられなかった。インディオの金が消え、修道会の金庫から奪った金と奴自身の貯金も消えたと知った途端、 シュヴァリエ・ド・ポワンシーは激怒した。俺は逮捕された。だが、奴は俺を殺せなかった――殺したくなかったのだ。奴が欲しかったのは金だ。金！それだけがお前たちの望みであり、関心事だ！ 金のためなら何でもする……俺は最悪の状況だった。仮面もなく、ポケットに一枚のコインもないまま牢で腐らされていた。その時、 お前を呼んだんだ。そうだ、そうだよ、愛しき兄弟よ。お前は俺を解放するために呼ばれた。 俺が生まれ持った使命を果たすためにな。そして、お前は素晴らしい働きをした。 イツァの乳を吸って育った甲斐があったようだな。」";
			link.l1 = "俺が知りたいのは、サン・ピエールから逃げ出したときに何を当てにしてたんだ？どんな計画だったんだ？";
			link.l1.go = "kukulkan_12";			
		break;
		
		case "kukulkan_12":
			PlaySound("Voice\English\sharlie\mishelle-05.wav");
			dialog.text = "最初からお前は俺の計画の一部だったんだ、兄弟よ。ククルカンは人の心を読むことができる。 修道院長のところに残した手紙は、お前を動かすためのものだった。俺の読みは正しかった。 お前がサンティアゴの異端審問官と初めて会った時から、ずっとお前の動きを見ていた。 お前はすべて俺のためにやってくれた。真実の守護者を作り、競争相手を排除し、クソチェアテムを見つけ出した。\n俺はそこにいた、お前の後を追ってな。ただ、テヤサルにまで入り込むとは思わなかった。 お前は俺の期待をすべて超えてくれた。そしてお前の助けがあれば、 俺は生まれながらにして果たすべきことを成し遂げる。俺がこの肉体に生まれた理由をな。";
			link.l1 = "お前の理屈にはひとつだけ小さな落とし穴があるんだ、親愛なる兄上よ。お前は自分の仮面を持っていないし、 それがなければ何者でもない。仮面は俺が持っている。そして、 別にお前に渡したいなんてこれっぽっちも思っちゃいない。お前の手に渡すくらいなら、粉々に吹き飛ばしてやるさ。";
			if (CheckCharacterItem(pchar, "mask_true")) link.l1.go = "kukulkan_13";	
			else link.l1.go = "kukulkan_14";			
		break;
		
		case "kukulkan_13":
			dialog.text = "運命で定められたことは変えられぬ。私の秘宝を傷つけることは許さん。感じるぞ……それはお前が持っている。そして今、お前は私の神殿、私の力が満ちる場所にいる！お前がここを出ることは決してない。 さあ、最後の試練の時だ、愛しき弟よ。ククルカンとの戦いで、お前の価値を見せてみろ！";
			link.l1 = "貴様の人間の体はまだ血を流せるはずだな！";
			link.l1.go = "kukulkan_fight";		
		break;
		
		case "kukulkan_14":
			dialog.text = "ははっ！哀れだな、シャルル。実に悲しいことだ。でも、神と戦う機会くらいは与えてやる。たとえ無駄だとしてもな。\n最初の幕を生き延びたら、後で教えてやるよ。";
			link.l1 = "貴様のこの肉体、まだ血を流せるだろう！";
			link.l1.go = "kukulkan_fight";			
		break;
		
		case "kukulkan_fight":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
			DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;
		
		case "kukulkan_twice": // развилка финалов - есть настоящая маска или нет
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				dialog.text = "";
				link.l1 = "どうやらお前の力も衰えてきたようだな、大いなるククルカンよ……いくら強くても、その肉体は所詮人間だ！";
				link.l1.go = "kukulkan_win";
			}
			else
			{
				dialog.text = "これで十分楽しんだだろう。あなたは本当に剣の達人であり、素晴らしい戦士だ。いや、 むしろこの時代で最強の武人とさえ言えるかもしれない。だが、この戦いはあなたの負けだ。 "+pchar.name+"...";
				link.l1 = "俺たちはただ……";
				link.l1.go = "kukulkan_fail";
			}
		break;
		
		case "kukulkan_fail":
			DialogExit();
			SetMusic("music_teleport");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
			LaunchBlast(npchar);
			PlaySound("Sea Battles\udar_metal_003.wav");
		break;
		
		case "kukulkan_fail_1":
			dialog.text = "もう十分だ、愛しき弟よ。ククルカンが自身の秘宝と一体となった時、その力にお前は太刀打ちできぬ！ 私がこれまでお前を生かしてきたのは、お前が本当に何を成し遂げられるのか見届けるためだったのだ。";
			link.l1 = "くそっ……今の一撃は……。だが、どの秘宝のことを言ってる？仮面か？それなら俺が持ってる！";
			link.l1.go = "kukulkan_fail_2";
		break;
		
		case "kukulkan_fail_2":
			dialog.text = "「かわいそうな、かわいそうな船長」 "+GetFullName(pchar)+"…ここまで来て、あらゆる危険を生き延び、最強の敵を何人も倒したというのに、結局は敗北するとはな…！お前がクソチェアテムの「サンタ・キテリア」号の残骸近くの金属箱で見つけた翡翠の仮面は偽物だ！ それはただのタイサルの財宝にあった古代の仮面に過ぎん。ククルカンの仮面ではない！\n私自身が遠征に失敗した後、ここから持ち出したものだ。古代の儀式によって守られている。この仮面こそが、 サンタ・キテリア号が嵐にさらわれてクソチェアテムへ流された理由だ。そしてもう一つの目的があった。 私の本当の秘宝を求めてやってくる者を欺くためのものだったのだ。";
			link.l1 = "でも…じゃあ、本物の仮面はどこにあったんだ！？クソチェアテム中を探し回ったのに…";
			link.l1.go = "kukulkan_fail_3";
		break;
		
		case "kukulkan_fail_3":
			dialog.text = "まだだ。 "+pchar.name+"。私の秘宝は「サンタ・キテリア」とは島の反対側、厳重に守られた聖域に置かれていた。 そこへ行く道は地下洞窟を通っている。見つけるのは難しく、凡人の目には決して明らかではない。\nあれだ！よく見ておけ、これが最後の機会だ……";
			link.l1 = "そんなはずがない！";
			link.l1.go = "kukulkan_fail_4";
		break;
		
		case "kukulkan_fail_4":
			dialog.text = "お前は多くの戦いを生き抜き、勝利してきたな、兄上。しかし、今回は負けたんだ。 "+pchar.name+"...";
			link.l1 = "「それで、これからどうする？」";
			link.l1.go = "kukulkan_fail_5";
		break;
		
		case "kukulkan_fail_5":
			dialog.text = "私は十世紀へ、七世紀遡って直接旅立つつもりだ。\nこれでマヤ文明が白人種に対して揺るぎない軍事的・科学的優位を確立するには十分だろう。";
			link.l1 = "「それで俺たちの世界はどうなるんだ？消えちまうのか？」";
			link.l1.go = "kukulkan_fail_6";
		break;
		
		case "kukulkan_fail_6":
			dialog.text = "いいや、変わるのだ。お前の居場所もあるかもしれんが、この世界で起きたことは何も覚えていないだろう。 ここで生まれた者の中には、あちらでは決して生まれない者もいるし、その逆もまた然りだ。死者は蘇り、生者は死ぬ。 どう転んでも、誰もが生まれ変わる。スーム・クィークェ――それぞれにふさわしいものを、だ。 "+pchar.name+"．\n怖がることはない、弟よ。お前は何が起きたのか決して気づかず、自然と新たな現実を受け入れるだろう。 記憶を持ち続けるのは、この私、ククルカンだけだ……だが、もう十分だ！カネクはすでに儀式の準備を整えている。\n私について来い "+GetFullName(pchar)+"、そしてお前が必死に守ろうとしたこの現実の最後の瞬間を目撃することになるだろう。";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_7";
		break;
		
		case "kukulkan_fail_7":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;
		
		case "kukulkan_fail_8":
			dialog.text = "時の扉が開かれた！喜べ、我が子らよ、偉大さのすぐそばに立っているのだ！我らは新たな世界を創造する。 青白き侵略者どもに居場所などない世界を！\nさらばだ。 "+pchar.name+"、そして新たな運命を受け入れる覚悟をしておけ。それがどんなものであろうとな。スーム・クィークェ！";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_9";
		break;
		
		case "kukulkan_fail_9":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
			DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;
		
		case "kukulkan_win":
			dialog.text = "この戦いはまだ終わっていないぞ、人間よ。\nお前は明らかに疲弊しているし、俺には増援が向かっている！\n俺の秘宝を渡すんだ。さもなくば、お前の死体から奪い取るまでだ――どちらでも構わん……";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;
		
		case "kukulkan_win_1":
			dialog.text = "ウラカン！今すぐこの男を殺せと命じる！";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_2";
		break;
		
		case "kukulkan_win_2":
			dialog.text = "ウラカン！聞こえなかったのか？もう一度言うぞ。お前とお前の戦士たちに、この男を捕らえて殺すよう命じる！";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_3";
		break;
		
		case "kukulkan_win_3":
			dialog.text = "「ウラカン！何だと！？カネク！お前のろくでなしの息子に俺の命令をもう一度伝えろ！！」";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_4";
		break;
		
		case "kukulkan_win_4":
			DialogExit();
			sld = characterFromId("Kanek");
			sld.dialog.currentnode = "kanek_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "kukulkan_win_5":
			dialog.text = "「裏切り者ウラカンよ、お前は自分の民を裏切った！この重大な変革の前に怯んだのだ！戦士たちよ、命じる――自らを我が兄弟と称するこの男だけでなく、裏切り者ウラカンも捕らえ、処刑せよ！」\n";
			link.l1 = "戦士たちよ、カヴィルとフラカンの名において命じる、命が惜しければその場を動くな！ カヴィルに立ち向かって生き残れる者など一人もいない！誰が地上で最強か、神々自身に決めさせよ！\n";
			link.l1.go = "kukulkan_win_6";
		break;
		
		case "kukulkan_win_6":
			DialogExit();
			LAi_SetActorType(PChar);
			LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;
		
		case "kukulkan_win_7":
			dialog.text = "";
			link.l1 = "今日はどんどん面白くなっていくな。こんな展開になるなんて、お前も思ってなかっただろう、兄さん？ 誰が本当に最強なのか、神々自身が決めるしかないさ。そして、みんながそれぞれ相応しいものを手に入れるんだ、 ミシェル。スーム・クイークェ！人それぞれ、ってやつさ…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
