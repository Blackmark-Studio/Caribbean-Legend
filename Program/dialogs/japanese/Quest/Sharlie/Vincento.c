// отец Винсенто
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "ついに、名高いフランスの船長にお目にかかることができた "+GetFullName(pchar)+" ご本人ですか。あなたの武勇伝はよく耳にしております。あなたは勇敢な兵士であり、そして願わくば、 我らが母である聖なるローマ・カトリック教会に忠実で誠実な息子であってほしいものです。どうぞお掛けなさい、 息子よ。私のために立っている必要はありません。ドミヌス・ヴォビスクム！ ";
				link.l1 = "「Et cum spiritu tuo」、閣下。ここまでの旅路は長く、困難を極めました……「Per aspera ad astra」――苦難を越えて星へ、ですね……";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "そうか、君の目を見れば何か知らせがあると分かる。今は君の話だけに耳を傾けよう。";
				link.l1 = "閣下、行方不明だった書記を見つけました…";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "「サンホセから何か知らせを持ってきてくれたのか、息子よ？」";
				link.l1 = "はい、閣下。ご指示の通り、我々 共通の知人ミゲル・ディチョーソと彼の失われたフリゲート艦に何が起きたのか判明いたしました。 彼の船がスペインへ向かう途中で大西洋に入った直後、逆風に巻き込まれ、すぐにカリブ海へ吹き戻されたのです。";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "パックス・ヴォビスクム、息子よ……何かご用かな？";
				link.l1 = TimeGreeting()+"、閣下。私たちの取り決めについて何かご報告はございますか？"link.l1.go ="guardoftruth_17";
				break;
			}
			dialog.text = "何か用かい、息子よ？";
			link.l1 = "いいえ、何もありません、お父様。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "「狭い門から入りなさい。滅びに至る門は広く、その道も広いので、そこから入って行く者が多いのです。 命に至る門は狭く、その道も険しいので、それを見いだす者は少ないのです。」\n正しき者の道は常に困難である、息子よ。しかし、成し遂げた目的は、正しき者の行いに必ず報いをもたらすのだ。";
			link.l1 = "ご同意いたします、閣下。お命じいただいた任務はすべて完了いたしました。教会の貴重な聖具を盗んだ臆病な海賊も、 すでにお手元にございます。今、奪われた品々――聖体顕示台、十字架、香炉――をすべてお返しいたします。どうぞサンティアゴ教区のためにお受け取りください。\n";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "ベネディチテ！心より感謝いたします、我が息子よ。聖母教会とサンティアゴ教区への忠実なる奉仕、 本当にありがとうございます。あなたの行いは必ずや報われるでしょう。教区民たちは、 盗まれた品を取り戻してくれた勇敢な戦士のために献金を集めてくれました。私は彼らを代表して、 喜んでこれをあなたにお渡しいたします。「働く者はその報酬に値する」と申しますからね。";
			link.l1 = "ありがとうございます、閣下。なんと嬉しい驚きでしょう！";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info("You've received a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "「聖母教会への忠実な奉仕は、常に忠実に報われるのです」 "+pchar.name+"。私としては、あなたがキリスト教世界を守るための献身的な戦士であり続けてくださることを願っております。我々 の頭上には、神話のダモクレスの剣のごとき死の脅威が迫っているのですから。";
			link.l1 = "「それは何でございましょうか、閣下？」";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "もしかすると、お前はこの世の闇の力や権勢に立ち向かう戦いで、我らの守護者となる運命なのかもしれん、息子よ。 数多くの兆しや予兆が、何か邪悪なものが近づいていることを示しておる。";
			link.l1 = "「兆しや前兆か？」";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "多いのだ、息子よ……その一つがお前の異教徒タイアサルの失われたインディアンの黄金を探し求める欲望だ。 その財宝に秘められているものこそ、キリスト教世界全体にとって危険そのものなのだ。";
			link.l1 = "この金について少し教えていただけませんか、神父様？消失の話はすでに聞きましたが、あなたが言う「脅威」 とは一体どのようなものなのですか？";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "よく聞きなさい、息子よ。これから話すことはお前だけに伝えるものだ。 ミゲル・ディチョソがあの異教徒の財宝を古代インディアンの都市から持ち出すずっと前に、 私はイツァ族の捕虜を捕まえ、カリブでの我々の使命について尋問した。イツァの民はマヤの末裔であり、 そのマヤ帝国はクリストバル・コロンとその一行が新世界に初めて足を踏み入れる何世紀も前に滅びた偉大な帝国だ。 マヤ帝国は周辺の部族を鉄の支配で従え、悪魔との地獄の契約によって授かった言葉にできぬ力を振るっていた。 幾世代にもわたる人間の生け贄の血で買われた闇の魔術だ。\nこのイツァの男は、失われたマヤの都市タイアサルと、そこに今も封じられている恐るべき邪悪について知っていた。 彼は知っていることをすべて我々に話した。もしその封印が解かれれば、結果は世界の終わりとなるだろう。その時から、 私はこの恐ろしい邪悪が目覚めぬよう、できる限りのことをしてきた。エスコリアルやローマに手紙を書き、 必死に援助を求めた。\n彼らは耳を傾け、ドン・ラモン・デ・メンドーサ・イ・リバを派遣した。彼はプロビデンスに拠点を築き、 タイアサルの捜索を始めた。その時、私は善良なドン・メンドーサが失われた都市を探す動機が…私とは異なることに気づいた。彼は世界の終末を防ぐのではなく、キリストではなくマモンに仕えようとしていたのだ。\nだからこそ神は彼を見捨て、死の天使をその陣営に送り込んだ。彼の行いはすべて無駄であり、 スペイン兵や信仰深いインディアン改宗者たちの無意味な死を招いただけだった。 私はエスコリアルにラモン・デ・メンドーサを無能ゆえ解任するよう手紙を書き、彼らもその職を解くことに同意したが……";
			link.l1 = "ミゲル・ディチョソが到着した。";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "Kukulcan?! Sancta Maria, Mater Dei, ora pro nobis! Kukulcan again, that old serpent...";
			else sTemp = "Hm...";
			dialog.text = "その通りだ。あの悪魔のような冒険者が、タイアサルと古代マヤの財宝を見つけたのだ。だが、 ドン・メンドーサの喜びは長くは続かなかった。その財宝のすべては、 ディチョソと共にスペインへの帰路で消えてしまった。おそらく、すべての金塊や装飾品と一緒に、 ミゲルは悪魔の力の源――ククルカンという名の古代マヤの魔神の恐ろしい仮面――まで持ち去ったのだろう。";
			link.l1 = sTemp+"「しかし、どのような悪事のことをおっしゃっているのですか、閣下？どうしてそれをご存知なのですか？」";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "それはカリブ、新世界、そしておそらく旧世界のすべての洗礼を受けたキリスト教徒に死をもたらす邪悪なものだ。\n終わりは夜の盗人のようにやって来て、誰も何が起きたのかすら気づかないだろう。\nそして、その前兆はすでに至る所に現れているのだ！";
			link.l1 = "「何の予兆だ？私にはわからない……」";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "息子よ、お前は本当にそんなに鈍いのか？あれにすら気づかないとは。もう二十五年も、 ほとんど途切れずに続いているんだぞ！";
			link.l1 = "謹んで申し上げますが、閣下、私の人生の長さはまさにこの期間で数えられておりますし、 しかも私はそのほとんどをヨーロッパで過ごしてまいりました。私の無知も多少はご容赦いただきたく存じます。";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "承知しました。 "+pchar.name+"。さて、ヨーロッパからここカリブに来て以来、奇妙な出来事があちこちで起きていることに気づいていないか？ ここでは、魔術や黒魔法、その他の儀式が本国よりもはるかに強い力を持っているのが不思議だとは思わないか？ インディアンのシャーマンが呪いをかけた異教の護符は、ただ手に取るだけで誰もがその力を感じるほどだ。\n我々のキリスト教の錬金術師たちでさえ――神よ、彼らが自らの過ちに気づきますように！――魔法の品を作り出す術を極めてしまった。だが彼らは、それによって自らが悪魔に仕えていることに気づいていないのだ。 お前も、視界の端に何か地獄のような不自然な存在が潜んでいるのを感じないか？";
			link.l1 = "おっしゃる通りです、お父様。最初は驚きましたが、今ではもう慣れてしまったようです……何しろここは新世界ですから！";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "だが、昔からそうだったわけじゃねえ。この俺が言ってる“闇”がここに現れたのは、およそ二十五年前だ。それ以来、日を追うごとに力を増している。つまり、 ひとつだけ確かなことがある――“それ”はもう来ている、“それ”は俺たちの中にいる、そして“それ”はすでに動き出している……";
			link.l1 = "誰のことを言っているんだ？その謎の「それ」とは誰だ？";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "キリスト教徒の誓いの敵、教会と全キリスト教世界の滅亡を望む者。";
			link.l1 = "…それは反キリストのことを言っているのか？";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "「それが『唯一の』反キリストなのか、ただの『一人の』反キリストなのか、私が断言するつもりはありません。 この獣がどんな名を名乗ろうと、我らの救世主の受肉を嘲るかのように人の姿をまとって現れる時、 それは重要ではないのです。重要なのは、これからその存在が何をしようとしているかということ。 私はそれを止めるためにここにいます。そして、あなたにも手伝ってもらいます。\n…少々話が脱線しましたね。あなたは行動の人。神学的な議論より、さっさと本題に入りたいのでしょう？」";
			link.l1 = "逆に、閣下から新しくて重要なことをたくさん学ばせていただきました。これからもお話を伺う準備ができております。";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "お前は礼儀正しく、立派に育てられた息子だ。それは良いことだ。さて、本題に戻ろう。私たちの共通の目的は、 ディチョソに奪われたタイアサルの財宝を見つけ出すことだ。その財宝の中には、 これから悪魔との戦いで使える武器がきっとあるはずだ。";
			link.l1 = "だが、もしかしてディチョソはすでにカリブを離れて、今ごろスペインで金貨の山に座っているんじゃないか？";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "いや、違う。これらの財宝がまだカリブに存在する証拠があるんだ。情報源については今は話せないが、俺を信じてくれ。 それに、ディチョソは男爵に嘘をついていたと思う。\nタイアサル遺跡についての話は、俺が尋問したイツァ族のインディオの証言と食い違っている。しかも、 ディチョソだけがモスキート族の待ち伏せから生き残ったってのは、どうにも出来すぎてるだろう。";
			link.l1 = "ドン・メンドーサも同じ考えだろうな、ディチョソを探してサン・ピエールを襲撃したんだからな？";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "男爵の行動など気にすることはない、息子よ。あやつは金と私利私欲に目がくらんでおる。 その強欲は自らの首に重しとなろうぞ、周囲の善良なキリスト教徒たちが地獄の力と戦っているというのに。";
			link.l1 = "ディチョソと宝をどこで探せばいいか、何か手がかりはあるか？";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "私は毎分そのことを考えている、息子よ、だが君に特に伝えることはない。しかし、ここには我々 を助けてくれる男がいる。ジェノヴァ出身の博物学者だ。私は新世界の教会の使命に役立つものを分類するため、 彼をここに連れてきた。彼はイツァ族インディアンの尋問を目撃し、私の判断では、彼が聞いたことに衝撃を受け、 そして歪んだ興味を抱いたようだ。\n悪魔は彼の好奇心を餌にした狼鉤のように利用し、彼の身体と魂を支配した。 主は彼に医学や錬金術の大きな才を与えたが、我らがジェノヴァ人は黒魔術と妖術の誘惑に堕ちてしまった。 彼は私の許可なく何度も捕らえたイツァ族と話し、そして姿を消した。我々は彼を見つけ、その魂を救わねばならない。";
			link.l1 = "私が彼を探せばいいんだな？";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "はい、息子よ。彼こそが財宝を見つけるための第一歩であり、我々 を脅かす邪悪な勢力に対抗できる武器を手に入れる鍵なのだ。";
			link.l1 = "このジェノヴァ人は誰だ？";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "彼の名はジーノ・グヴィネイリ。年齢は三十歳前後だ。優秀な医師であり、錬金術師でもある。先ほど言った通り、 今は黒魔術の研究に没頭している。私の得た情報によれば、 彼は今カリブのイギリス植民地のどこかに身を隠しているそうだ。\nジーノ・グヴィネイリを探し出してくれ、息子よ。教会の聖具を盗んだあの海賊を見つけられたのなら、 逃げた私の書記もきっと見つけてここに連れて来られるはずだ。聖アントニウスの取りなしを祈っているぞ。";
			link.l1 = "なるほどでございます、閣下。これ以上一刻も無駄にいたしません。それでは、またお会いしましょう！";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "I almost betrayed myself by a shout of surprise. Father Vincento ordered me to find and bring him his runaway secretary, a physician alchemist named Gino Gvineili. That same Gino who occupies the spare room on the second floor of my house in St. John's!");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "I must find a man named Gino Gvineili, hiding somewhere in the English Caribbean colonies. He is a physician and an alchemist. Where can a man like him hide?");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "「あなたがそう言うと、私は最初から信じていました」 "+pchar.name+"。今や、あなたがまさに神の摂理によって私のもとへ遣わされたと確信できることで、私の信仰はさらに強くなりました。 私の哀れな放蕩息子はどこにいるのですか？";
			link.l1 = "残念ですが、これからお伝えすることはお気に召さないでしょう。しかし、私には他に方法がありません。 あなたの秘書は亡くなりました。";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "神が彼の魂を救い、罪をお許しくださいますように……どうしてそんなことになったのだ、息子よ？";
			link.l1 = "アンティグアでジーノを見つけた。あいつは研究所の下に建てられた古い建物のひとつに隠れていたんだ。 おとなしく俺についてくるつもりはなかった。お前の名前を聞いて、俺が力づくでも連れて行く覚悟だと分かると、 ジーノは長い衣の隙間から透明な液体の入った小瓶を取り出し、一瞬で飲み干したんだ…";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = "そして恐ろしいことが起きた。彼は顔を真っ赤にし、その後濃い青色になった。床に倒れ、 痙攣しながらけいれんを起こし、わずか一分ほどで激しい苦しみの中で息絶えた。 部屋には強いアーモンドの匂いが立ち込めた。\n";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "ジーノ……哀れな愚か者よ……最後の瞬間まで自ら命を絶つという罪を犯してしまったのか。なんと悲劇的な喪失だ。彼の魂のために祈ろう……";
			link.l1 = "彼が亡くなった後、私は彼の住居を探してこのフォリオを見つけたんだ。\nこれが君の興味を引くか、あるいは我々の探索の助けになるかもしれない。\nここには何やら奇妙で難解なメモが書かれているんだ……";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("You've given the almanac");
			PlaySound("interface\important_item.wav");
			dialog.text = "これは哀れなジーノの暦帳だ。彼は自分の探検についてここに色々と書き残していたんだよ。さあ、 それを私に渡しなさい、子よ。ここに書かれていることを調べてみよう。もしかしたら手がかりが見つかるかもしれん。\nジーノ・ヴィネリを私の元に連れ戻してはくれなかったが、お前の努力には満足しているよ、子よ。さて、 お前に知らせたいことがある。";
			link.l1 = "「お話を伺いましょう、神父様。」";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "ディチョーソのフリゲート艦が最後に目撃された場所がトリニダード島だったという情報を手に入れた。 おおよその時期も分かっている――1654年4月初旬だ。\nトリニダードへ行き、フリゲート艦の行方について何か分かることがないか調べてくれ。どこへ向かっていたのか、 船長の計画は何だったのか、どんな些細なことでもいい。長い年月が経って人々の記憶も曖昧だろうが、 溺れる者は藁にもすがるものだ。";
			link.l1 = "私にできる限りのことは全てやります。";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "通行証を見せてくれ。サン・ホセ植民地への訪問許可を追加してやろう。";
			link.l1 = "「ほら。」";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "……よろしい。それで全部だ。自分の船にスペインの旗を掲げるのを忘れるな。前に出て、神の祝福を受けよ、息子よ！";
			link.l1 = "少々お待ちください、閣下。質問してもよろしいでしょうか？";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "はい、もちろんです。何をお知りになりたいですか？";
			link.l1 = "前回お会いした時、あなたはタイアサルについて教えてくれたイツァ族のインディオの話をされましたね。\nそのことについて、私はずっと考えていました……教えてください、その男は何か持っていましたか？何かしらの物や書き物、あるいはそれに類するものなど。\nそれが役に立つかもしれません。";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "特別な品はなかったぞ、息子よ。腰布、原始的な装飾品、薬草入りの竹のパイプ、そして猿轡代わりの粗い革切れだけだ。 \nそれらはすべてドン・ラモン・デ・メンドーサ・イ・リバに送られた。しかし、 興味を引くようなものは何もなかったと断言できる。";
			link.l1 = "なるほど。ありがとうございます、神父様。またお会いしましょう！";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "全能なる神があなたを祝福し、守ってくださいますように……ミゲル・ディチョソはどうなったのですか？何かわかりましたか？";
			link.l1 = "残念ながら、私は知りませんでした。目撃者たちが最後に語ったのは、 サンタ・キテリア号が烈風にあおられてマルティニーク方面へ流されたということだけです。船が助かったのか、 それとも沈んだのかは定かではありません。しかし、 ミゲル・ディチョソだけは生き延びたのではないかと私は疑っています。";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "何がきっかけでそう決めたのだ、息子よ？";
			link.l1 = "要点は、フリゲート艦がマルティニーク方面のどこかに隠れていたということだ。\nそしてごく最近、ドン・ラモン・デ・メンドーサの部下である勇敢なカバジェロ、ディエゴ・デ・モントーヤという男が、 サン＝ピエールを襲撃した。目的は、そこに潜んでいるとされるミゲル・ディチョーソを見つけ出すことだった。";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "つまり、バロンはディチョソがフランス人と一緒に身を隠したと思っているのか……";
			link.l1 = "サン＝ピエールとジャック・ディエル・デュ・パルケ総督のことはよく存じております、閣下。 そこにはミゲル・ディチョソという名のスペイン人は誰も知りませんでした。 ディエゴ・デ・モントーヤの居場所をご存知でしょうか？ディチョソについて彼と話したいのです。";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "本当にあの方が話を聞いてくれると思うのかい、息子よ？剣とピストルで語り合わない限り、話す気はないと思うがね。";
			link.l1 = "あなたの名前を出せば、彼ももっと話を聞いてくれるかもしれませんね？";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "「ああ、」 "+pchar.name+"ドン・メンドーサの忠臣があなたと合意する気になるとは思えません。 彼に私との聴聞のためサンディエゴに来るよう命じるのも一つの手ですが、 ディエゴが私に対して完全に誠実でいるかどうかも疑わしいですね。";
			link.l1 = "「これからどうしましょう、お父様？」";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "少しの間、私を一人にしておいてくれ、息子よ。お前が話してくれたことを整理し、さらに私が様々 な情報源から既に知っている事実もまとめる必要があるのだ。その後で、次にどう動くべきかを伝えよう。 あとでまた来なさい。";
			link.l1 = "はい、閣下。承知しました。定期的にご報告いたします……";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "神のご加護を、息子よ……何か私にできることはあるか？";
			link.l1 = "ご機嫌いかがですか、閣下。何か新しい知らせはございますか？";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "今はまだだ、息子よ。だが、落ち込むな。私の部下たちと共に進めている。後でまた来なさい。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "はい、息子よ。ミゲル・ディチョーソについていくつか情報がある。 ディチョーソがまだ生きていてカリブにいると信じていたのは無駄ではなかったようだ。 ドン・ディエゴ・デ・モントーヤの言う通りだったらしい。ミゲル・ディチョーソの顔を見て本人だと認識した男から、 行方不明になっていた紳士がサンタ・キテリア号の失踪後、1654年4月にマルティニークのル・フランソワという海賊の集落で目撃されたという確証を得たのだ…";
			link.l1 = "つまり、フリゲート艦はマルティニークの岸で座礁したのか？";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "ゆっくり話せ、息子よ。今のところ、その時期にマルティニークで難破した船については何の情報もないんだ。\nそれに、フリゲートはラガーとは違う。その沈没となれば、きっと誰かの目に留まり、 地元のハイエナどもが大騒ぎしてサルベージに群がったはずだ。";
			link.l1 = "岸辺や浜辺を探して、船の残骸を見つける価値はあるだろうか？";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "「息子よ、ドン・ディエゴ・デ・モントーヤはすでにこれらすべてを試みたが、成果はなかった。続きを聞きなさい。 私のプロビデンスの情報筋によれば、 バロンはサンタ・キテリア号が依然としてカリブ海を航行していると確信しているが、今は別の名前で動いているそうだ。 \nだからこそ、彼はミゲル・ディチョーソを必死に追い回しているのだ。彼の話によれば、 サンタ・キテリア号はイスラ・テソロの近くで目撃され、 最近ではイギリスの軍艦隊に護衛されてイギリスの旗の下で発見されたという。」";
			link.l1 = "何だと？信じられないな。あんな規模の嵐に耐えるなんて不可能だと言われていたのに……それなのにサンタ・キテリア号は生き残っただけでなく、今やイギリスの旗の下で航海しているだと？\nこの二つの事実はどうにも噛み合わない。バロンはなぜ、それがサンタ・キテリア号だと断定したんだ？ 本当にあの船はそんなに特別なのか？";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "ああ、そうだ。このフリゲートはヨーロッパの最新技術で建造されたんだ。\n同クラスの中でも武装が非常に優れていて、速力も抜群だから、火力で勝る相手からでも逃げ切れる。\nそれが俺の情報源から聞いた話さ。";
			link.l1 = "「それに、今はサンタ・キテリアと呼ばれているのではないか？」";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "それは、残念ながら私には分かりません……イスラ・テソロへ行きなさい。 "+pchar.name+"、それからディチョソのフリゲートについて何か情報を探ってみろ。そうすれば、元船長も見つけられるかもしれねえ。 一石二鳥ってやつだ。いや、一つの罠で二匹のネズミを仕留めるってところか。";
			link.l1 = "「お任せください、閣下！」";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = "私に会いに来てくれて嬉しいぞ、息子よ。";
			link.l1 = "こんにちは、閣下。ドン・アロンソ・デ・マルドナードとお会いした後、 まさかまたお目にかかれるとは思いませんでした。";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "ドン・アロンソ・デ・マルドナードは私の直接の命令に背いた。彼にはお前に立ち向かうことを厳しく禁じていたのだ、 息子よ、彼がどうなるか分かっていたからだ。私の予感は的中した。彼の任務は、 お前をテヤサルまで護衛することだった。彼は以前そこに行ったことがあったからだ。\nそのうえ、彼の艦隊とスペイン兵の一隊は、イッツァやモスキートの襲撃からお前を守るはずだった。 だがアロンソは卑劣にも、私怨に駆られて行動した。\n彼はテヤサル遠征を失敗させ、託された兵士と船を破滅させただけでなく、 お前の心に私への不信と憎しみの種を蒔いたのだ。だが約束しよう、息子よ、私は完全にお前の味方だ。今こそ共に、 この闇に立ち向かわねばならぬ。";
			link.l1 = "そう信じたいな。";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "「ご安心ください、」 "+pchar.name+"。私は、我らが主イエス・キリストの忠実なる僕であり、教会の代表者として、 ただ一つの目的に突き動かされております――すべての魂が祝福された主の御言葉を聞く機会を得るまで、世界の終焉を阻止することです。そしてそれは、 今まさに悪魔に取り憑かれたインディアンの手にある邪悪なる遺物を止めることを意味します。 私は最初からこれを疑っておりましたが、今や完全に確信いたしました。あなたは主によって、 サタンとの戦いにおける主の勇士として選ばれたのです。";
			link.l1 = "「でも、なぜそうおっしゃるのですか、お父様？」";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "お前は、俺と全ての部下を使っても、バロン・メンドーサやドン・ディエゴですら、 誰にもできなかったことをやってのけたんだな。\n呪われた島を見つけて、ククルカンの秘宝を探し出したんだろう？";
			link.l1 = "ああ、ククルカンの仮面は俺が持っている。";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "そして、これらすべてが偶然に起こったとでも言うつもりか？ただの巡り合わせだと？「人は心に道を思い巡らす、 しかしその歩みを確かにされるのは主である」。息子よ、全能の神がこの道へとお前を導かれたのだ！ 戦いではお前の手を強め、正しい道へと足を導き、危機の時にはお前を守ってくださった！「見よ、 主の剣がエドムに下り、滅ぼすべき民に裁きをもたらす！」\n";
			link.l1 = "ええと……父上、でも任務は基本的にもう達成したのではありませんか。私の手元に仮面があります。つまり、 ククルカンに憑かれた器が我々の歴史に入り込んで変えることはできない、ということでは……？";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "勘違いしているぞ、息子よ。あの悪魔は、この仮面があろうとなかろうと、あの門を通り抜けることができる。 仮面は奴が邪悪な企みを実行しやすくするだけだ。奴を止められる唯一の方法は、地獄の門を完全に破壊することだけだ。 ";
			link.l1 = "ドン・アロンソも同じことを言っていた……";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "そして彼は正しかった！我らが主イエス・キリストとその聖母マリアの御名において、 この邪悪に立ち向かうため十字架を取るのだ、息子よ！お前に課せられた偉大な使命を拒むことはできぬ。私も、 全キリスト教世界も、お前にかかっているのだ、息子よ。";
			link.l1 = "閣下、これはさすがに行き過ぎでございます。私、本当に…かなり気まずい気持ちでございます…";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "謙遜は立派だ、息子よ、だが今は恥じらう乙女のように振る舞っている場合ではない。臆することも恐れることもない、 主なるあなたの神が先立って勝利を授けてくださるのだ！愛する者たちのため、すべてのキリスト教徒のために、 この戦いに臨みなさい……もし彼らのためでなくとも、自分自身のために戦うのだ。あの悪魔が勝利すれば、 お前も他の皆と共に滅びることになるのだから。";
			link.l1 = "どうやら説得されましたよ、お父様。タイアサルへの遠征については自分の立場に迷いがありましたが、 今はもう迷いはありません。何を手伝っていただけますか？";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "テヤサルへの道を知っていたのは、アロンソ・デ・マルドナードとミゲル・ディチョソの二人だけだ。 ドン・アロンソはもう死んでいる。そしてディチョソは……最近、イスラ・テソロのシャープタウンで目撃されたと聞いた。もしかしたら、まだそこにいるかもしれない。 ディチョソを探し出し、案内役を引き受けさせるのだ。\n金か力か、どちらかでこの男にテヤサルまで案内させろ。そこには地獄の門があり、そこでそれを封じることになる。";
			link.l1 = "「男たちはどうするんだ？」";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "私が最後に率いた兵士たちは、アロンソ・デ・マルドナードの指揮下にあった。\n残念ながら、もう一度スペイン兵の部隊を集める機会はない。地元の守備隊には、 私の信用をすべて使い果たしてしまったのだ。\nお前自身の部下たちの力を借りてやるしかないぞ、息子よ。\nだが、それ以外のことならできる限り力を貸そう。";
			link.l1 = "「どんな助けが必要なんだ？」";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "この戦いでは、物質的にも精神的にも、我々が持つあらゆる利点を活かさねばならぬ。私はアドリアン神父に頼み、 五日後にこの礼拝堂で私と合流してもらうことにした。彼は君のために聖なるお守りを持参するだろう。 キリストの戦士たちが戦いで力を得るための護符だ。また、あらゆる種類の霊薬も授けてくれる。私からは、 この剣を受け取ってくれ、息子よ。\nこれはテンプル騎士団の古き剣、我らの祖先が誇った強力な武器だ。今なお鋭く、教会の祝福を帯びて輝いている。 これを手にしたのは、最も偉大なる騎士たちのみ。誇りを持って受け取り、イエス・キリストの御名を唇に、 我らが信仰の敵を打ち砕くのだ！";
			link.l1 = "ありがとうございます！この剣は本当に素晴らしいです。言葉も出ません……";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info("You've received the Tanath");
			PlaySound("interface\important_item.wav");
			dialog.text = "「神のご加護を」 "+GetFullName(pchar)+"、このこれからの戦いにおいて。私はあなたに聖なる十字架の加護を授けます。勝利がその御手にあり、 ダビデにゴリアテを打ち砕く奇跡の力を授けた全能の神よ、どうかこの武器に命を与える御慈悲をもって祝福し、 あなたの僕にお与えください\n "+GetFullName(pchar)+" それを担うことを望む者が、聖なる公教会を目に見える敵にも見えざる敵にも勝利と自由をもって守るため、 これらを用いることができますように。\n主イエス・キリストによって。アーメン。";
			link.l1 = "アーメン！";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "さあ、もう行きなさい、息子よ。\n神があなたを見守り、決して見捨てることのないように――探し物の時も、道中も、戦いの中でも。\nミゲル・ディチョソを探し、彼の助けを借りてタヤサルへ向かいなさい。\nアドリアン神父のことも忘れずに。必要な護符や薬は彼が用意してくれるはずだ。\nさて、私はサンティアゴへ戻る時間だ。\nさらばだ、息子よ。神のご加護を。";
			link.l1 = "さようなら、ヴィンチェント神父……";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
