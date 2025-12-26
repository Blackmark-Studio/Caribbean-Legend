// Филипп де Пуанси - генерал-губернатор французских колоний
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
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyFox"))
			{
				dialog.text = "「ごきげんよう。」 "+pchar.name+"。入れ、すでに知らせは受けている。";
				link.l1 = "ご存知と？何かの間違いでしょう、閣下。私は任務の成功を報告しに参りましたが、ご機嫌が優れないご様子ですね。";
				link.l1.go = "PZ_PoincyAngry1";
				DeleteAttribute(pchar, "questTemp.Terrapin");
				DeleteAttribute(pchar, "questTemp.Terrapin_KathyFox");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "お会いできて嬉しいです。 "+pchar.name+"。あなたの功績についてはすでに報告を受けておりますし、何よりも任務を見事に果たしましたね！ あなたは最高の働きを見せてくれました。私の見立てが間違っていなかったことを嬉しく思います。";
				link.l1 = "今すぐ兄を釈放するための書面による命令をいただけますか？";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "お会いできて嬉しいです。 "+pchar.name+"。あなたの働きぶり、そして何より任務が完了したことは聞き及んでおります！ただ、正面突破とは、 もう少し賢い策を期待していたのですがね。亡くなったフランス兵たちは残念です。\nしかし戦争とはそういうもの、犠牲はつきものです。あなたは任務を果たしました、 私の見立てが正しかったことを嬉しく思いますよ。";
				link.l1 = "今、兄を釈放するための書面による命令をいただけますか？";
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && GetCharacterIndex("Noel") == -1 && pchar.questTemp.Patria != "epizode_12_barondie" && pchar.questTemp.Patria != "epizode_12_baronfail" && pchar.questTemp.Patria != "epizode_12_baronkilled" && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "お会いできて嬉しいです、シャルル。まずは、サン・ピエール植民地をスペインの侵略者から見事に守り抜いたこと、 心よりお祝い申し上げます。素晴らしい働きでした、友よ！";
					link.l1 = "「ありがとうございます、シュヴァリエ。」";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "お会いできて嬉しいですよ、シャルル。まずは、 サン・ピエール植民地をスペインの侵略者から守るという複雑な任務を見事に果たしたことを祝福させてください。 素晴らしい働きでした、友よ！\nまた海軍との協力の機会を与えましょう。フランスにはあなたのような士官が切実に必要なのです。 今度はもう少し分別を持ってくれることを願っています……特許状を受け取りなさい、シャルル・ド・モール船長！";
					link.l1 = "ありがとうございます、シュヴァリエ。祖国のために力になれて嬉しいですし、これからもお仕えしたい所存です！";
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "シャルル、私を失望させましたね。あなたの軽率な行動の結果、王立海軍での特許と階級を失いました。 これ以上の協力の余地はありません。退室なさい。";
					link.l1 = "ふむ……";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "会えて嬉しいぞ、シャルル。報告せよ！";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "仕事は終わりました。サンホセ植民地からの身代金も受け取りました。\nしかし悪い知らせがあります。砦との戦いで「エクラタン」が沈没しました。私は船長に注意するよう警告しましたが、 彼は私の言うことを聞きませんでした、そして…";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "任務は完了した、サンホセ植民地から身代金を受け取った。";
						link.l1.go = "patria_8";
					}
					break;
				}
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(!IsUniformEquip())
				{
					dialog.text = "旦那、今日からは、きちんとした服装で私の館に入るようにしなさい！";
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && IsUniformEquip())
				{
					dialog.text = "バロン、船長！お会いできて嬉しいです！";
					link.l1 = "任務は完了しました、シュヴァリエ。";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+"、船長。何か知らせはあるか？";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "スペイン人たちはポルトープランスへの攻撃を計画していた。\nイスパニョーラ島の西端で、我々は強力な敵艦隊と遭遇した。\nその艦隊は完全に壊滅させた。\nしかし、「エクラタン」は沈没した。";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "スペイン人はポルトープランスへの攻撃を計画していた。\nイスパニョーラ島の西端で我々は強力な敵艦隊と遭遇した。\nその艦隊は完全に壊滅させた。";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+"「、シャルル。スタイフェサント旦那の様子はどうだ？」";
					link.l1 = "すべて順調でございます、シュヴァリエ殿。配達は無事に完了いたしました。こちらがご書簡への返事でございます。";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && IsUniformEquip())
				{
					dialog.text = "「シャルル男爵……もう戻ってきたのですか？」";
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && IsUniformEquip())
				{
					dialog.text = "そのしかめっ面は気に入らんな、シャルル。スタイフェサントは何と言った？報告せよ！";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "文字通り、彼はこう言ったんです。「シュヴァリエに伝えろ。もうシント・マールテンの責任者ではない、と。 もうたくさんだ。それから本国からの査察については――何かうまくごまかせ、と。デ・ポワンシなら、何だってひっくり返すのは簡単だっただろう」と。この伝言を伝えたあと、 旦那は私を邸宅から追い出しました。これで交渉は終わりでした。";
					else link.l1 = "さて、彼が言ったのはこうだ。「お前の主君は最近シント・マールテンであまりにも強欲すぎる。だから、 その飽くなき欲望を抑える時が来た」とな。その後、奴は俺を逮捕しようとした。 俺は剣を抜いて船まで戦い抜くしかなかった。オランダの外交もこの程度だな。";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && IsUniformEquip())
				{
					dialog.text = "船長、お待ちしておりました。私が現状を男爵に説明し、彼は私の決断を全面的に支持してくれました。 オランダ人どもにはその傲慢の報いを受けさせます。";
					link.l1 = "戦争ということですかな？";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && IsUniformEquip() && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "さて、友よ、東インド船とその積荷を拿捕したようだな。素晴らしい！";
						link.l1 = "船をあなたに引き渡しますので、港の役人たちに指示を出してください、シュヴァリエ。";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "何か質問があるか、シャルル？";
						link.l1 = "今は特にありません、旦那。では、これで失礼します…";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && IsUniformEquip())
				{
					dialog.text = "やっと来たな、船長！セントクリストファーで緊急事態だ！";
					link.l1 = "「敵対する艦隊か？」";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && IsUniformEquip() && GetCompanionQuantity(pchar) < COMPANION_MAX)
				{
					dialog.text = "我々の伝令ラガー船を引き受ける準備はできているか？";
					link.l1 = "私です。";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "ド・モール船長、ドイリー旦那！お会いできて嬉しいです！\nあなたが我々の植民地を狙ったスペインとオランダの悪党どもに思い知らせてやった場面を、町中の者が見ていましたよ！ ";
					link.l1 = "私の務めでございました、シュヴァリエ。";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+"「チャールズ。始めましょうか？」";
					link.l1 = "もちろんでございます、シュヴァリエ。だからこそ私がここに参りました。";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && IsUniformEquip())
				{
					dialog.text = "フランス王立海軍の副提督を私の執務室にお迎えできて嬉しく思います！\nそうです、友よ、君は間違っていない。君の任命命令書には私自身が署名したのだ。\n形式上はまだフランス本国の承認が必要だが、それは間違いなく行われるから心配はいらない。\nおめでとう！";
					link.l1 = "私は祖国に仕えております！";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && IsUniformEquip())
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "will be ready soon and"; // в зависимости от времени сколько добирался
					else sTemp = "is ready and";
					dialog.text = "ご自身の任務はうまくいきましたか？ドイリー大佐は満足していましたか？";
					link.l1 = "すべて完璧にいきました、シュヴァリエ。スタイフェサントの隊商は拿捕し、 奴隷たちは全員ジャマイカへ連れて行きました、大佐の戦隊も\n "+sTemp+" キュラソーへ向かう途中で。";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && IsUniformEquip())
				{
					dialog.text = "勝者に栄光あれ！おめでとう、おめでとう、友よ！君にはいつも驚かされるよ。";
					link.l1 = "ありがとうございます、シュヴァリエ。スタイフェサントは処罰され、賠償金の支払いも準備できております。 平和は回復し、サン・マルタンは今や完全にフランスの領土となりました。";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "さて、友よ、また会えて嬉しいぞ。よく休めたか？";
					link.l1 = "はい、シュヴァリエ。とても良い息抜きになりました……繊細なご用件があるとおっしゃっていましたね？";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "友よ、君は魔法使いに違いない！本当に見事な偉業を成し遂げたな！我々 の男爵はもうここに商会を設立したがらなくなった。";
					link.l1 = "今の彼の唯一の願いはパリに戻ることだと思います。";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "シャルル、バロンのことを聞いたか？海賊に連れ去られたんだ……";
					link.l1 = "はい、シュヴァリエ。残念ながら、バロンは死にました。それは確かなことです。";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "シャルル、進捗はどうだ？男爵が君の船に乗り込んだと聞いたが…";
					link.l1 = "はい、シュヴァリエ。彼は船に乗っていて、私が看病していましたが……熱病で亡くなりました。";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "シャルル、進捗はどうだ？男爵が君の船に乗り込んだと聞いたが…";
					link.l1 = "はい、シュヴァリエ。彼は乗船していて、私が手当てをしていましたが…戦闘で亡くなりました。";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "友よ、君は魔法使いに違いない！とんでもない偉業を成し遂げたな！ 我らが男爵はもうここに商会を設立したがらなくなったぞ。";
					link.l1 = "今ごろパリに向かっているだろう。";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "何か質問があるか、シャルル？";
				link.l1 = "今は違います、旦那。では、これで失礼します……";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "何の用だ、旦那？";
			link.l1 = "大したことではありません、ただのご挨拶です。では、これで失礼します…";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// в тюрьме при старте игры
		case "Puancie_Jail":
			dialog.text = "ごきげんよう、シャルル。自己紹介させていただきます。私はフィリップ・ド・ポアンシーでして、私が…";
			link.l1 = "なぜ俺を牢屋にぶち込んだんだ！？無礼じゃないか！俺はフランスの貴族だし…";
			link.l1.go = "Puancie_Jail_1";			
			// belamour legendary edition -->
			link.l2 = "……こんにちは？冗談がうまいな、旦那。どうして俺が誰か知っているんだ？";
			link.l2.go = "Puancie_Jail_1a";	
		break;
		
		case "Puancie_Jail_1a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			dialog.text = "若者よ、私の話を遮らないでもらいたい！\n君はカリブ諸島におけるフランス植民地の総督と話しているのだぞ！\n君の無礼な口ぶりは、目の前に誰がいるか知らなかったためだと見逃してやろう。\nだが、今後はもっと慎みを持つことを勧める。";
			link.l1 = "ふむ……申し訳ありません、閣下。";
			link.l1.go = "Puancie_Jail_2";
		break;
		
		case "Puancie_Jail_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			// <-- legendary edition
			dialog.text = "私の話を聞きなさい、若者よ、口を挟むな！\n今お前が話している相手は、カリブ諸島におけるフランス植民地の総督である私だ！\nお前が誰に向かって口を利いているのか知らなかった無知ゆえに、その態度は今回だけ大目に見てやろう。\nだが、今後はもっと慎みを持つことを勧めるぞ。";
			link.l1 = "ふむ……ご無礼をお許しください、閣下。";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "よろしい。さて、先ほどの質問についてだが――お前は誤ってスペインの間者と見なされ、身元がはっきりするまで拘留されていたのだ。最近、忌々 しいカスティーリャ人どもが活発になってきたので、私は怪しい者すべての拘束を命じた。しかし、 今やお前が何者かは分かっている――お前はまさしくミシェル・ド・モンペの弟、シャルル・ド・モール本人だ。だからこそ、私自らここまで降りてきて、 お前を釈放しに来たのだぞ。それなのに、お前はまるで子供のように私に怒鳴りつけるとは！\n";
			link.l1 = "再度失礼いたします、閣下。これで私はもう行ってもよろしいでしょうか？";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "そうだ、君だ。しかし、看守が独房を開ける前に、君と二人きりで話したいのだ。君の兄弟――マルタ騎士団でも屈指の勇士――が逮捕され、監視下に置かれていることを知っているか？";
			link.l1 = "兄が困っていて助けが必要だとしか知らなかった。だから私はパリからここへ来たんだ。";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "それは良かったです。知っておいてほしいのだが、モンペール殿は重大な問題に巻き込まれている。私は彼が職権乱用、 財産横領、偽証の疑いがあると強く考えている。しかし、あなたなら彼を助けることができる。";
			link.l1 = "旦那、もう少し詳しく教えていただけますか？私にはよく分かりません、ミシェルは騎士団の誇りだったのに……";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "私もそう思っていました。皆も同じでした！しかし、最近の彼の行動によって、我々 は彼の騎士団への忠誠心に疑念を抱くようになり、彼は逮捕されました。 詳細についてはミシェル自身があなたに話すでしょう。彼がどのようにしてその嫌疑に対処し、 不名誉を避ける助けになるかを説明してくれるはずです。";
			link.l1 = "今、兄はどこにいるんだ？牢にいると聞いたが、姿を見かけないんだが……";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "私が「投獄」と言ったかね、若者よ？ちゃんと聞いているのか！？私は「逮捕されている」と言ったのだ！ 同じ意味ではないぞ。ミシェル・ド・モンペはサン・ピエールの地下基地で拘束されているが、 そこはマルタ騎士団の所有地だ。\n私は君が制限なくその基地を訪れ、必要だと思うだけ兄と話すことを許可する。 騎士団の士官や兵士たちには私の指示を伝えてあるので、君を止めることはないだろう。";
			link.l1 = "その地下基地はどこだ？";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "ここ、サン・ピエールにある、もちろんだ。地元の牢獄を探し、修道会の印がついた扉から入るのだ。 地下二階のカズマットまで降りていけ。モンペール旦那がそこにいる。しかし心配はいらん。牢獄を出たら、 お前は迎えられ、兄上のもとへ案内される――すべて私が手配してある……以上だ。また会えることを願っているぞ、シャルル。軍曹！";
			link.l1 = "お待ちください、閣下！それで私の…持ち物はどうなるのですか？剣やその他の品々は？";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "あなたの持ち物は兄上の借金返済のために没収された。さらば、ド・モール旦那。";
			link.l1 = "なんてこった…";
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 3.5);
			NextDiag.CurrentNode = "First time";
			locCameraFromToPos(-11.09, 0.65, 3.05, true, -12.59, 0.09, -4.66);
		break;
		
		// возвращаем деньги
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = "おお、シャルル・ド・モールご本人か！お会いできて嬉しいです。さて、 あなたはご兄弟の運命について私と話し合いに来られたのでしょうか？";
			link.l1 = "私はミシェル・ド・モンペが騎士団とあなた個人に負っている借りを返す用意があります。";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "ふむ……しかし、金はどこだ？君は妙なユーモアの持ち主だな、若者よ、私には理解できん。";
			link.l1 = "失礼します、シュヴァリエ殿。船のロッカーに金を置いてきてしまいました。すぐ戻ります。";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "金は持ってきたか、シャルル？";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "もちろんでございます！この金額であなたの全ての出費が十分に賄えることを願っております。";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "「まだだ……」";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Charles");
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "素晴らしい！私がそれらを預かろう。君は最高の働きを見せてくれたな、シャルル！";
			link.l1 = "ミシェル・ド・モンペの釈放命令はいつ受け取れるのですか？";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "急ぐことはない、若者よ。自分の命を危険にさらしてまで借金を返し、家族を守ろうとするその姿勢、私は敬意を表する。 今どき、そんな高潔さは滅多に見られぬ……だが、この悲しい話の主役は金ではない。君の兄は、 非常に繊細な任務を遂行するという条件で多額の金を受け取ったのだ。\nミシェル・ド・モンペは、忠実なるカトリック信者として、異端者の無礼を罰し、彼が犯した正義の回復を果たすため、 そして騎士団と聖教会の栄光のために、聖書に誓いを立てたのだ……";
			link.l1 = "しかし、彼は逮捕されたままでは約束を守れません！彼を解放していただければ、 私一人でやるよりも二人で任務をはるかに早く達成できます。";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "見てごらん、友よ、君の兄上は私に彼の品位を信用できない十分な理由を与えてくれたのだ。 彼が逃亡して誓いを破らない保証はどこにもない。だから、もし彼への全ての非難を取り除きたいのなら、 君自身が誓いを立てなさい。詳細はモンペール旦那が説明してくれるだろう。";
			link.l1 = "ふむ……それは予想外だ。しかし、君は私に他の選択肢を残してくれないな。最終的な決断は兄と話してから下そう。";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "私はだんだん君のことが気に入ってきたよ、シャルル。\nいつか、もしかしたら友人になれるかもしれないな。\nともかく、これが君の兄上を解放する最後の機会だ。\n君が兄上のような過ちを犯さなければ、君の家の名誉は傷つけないと約束しよう。\nそして、今後は私の友情にも頼れるはずだ。";
			link.l1 = "あなたの言うことはよく分かりました。では、ごきげんよう！";
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";//Сага - старт
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		break;
		
		case "serve":
			dialog.text = "「心配するな」 "+pchar.name+"、私は約束を守ろう。あなたの兄は釈放され、すべての罪状は取り下げられる。あなたの家の名誉はこれで守られた。 すべてはあなた自身の尽力のおかげだと言ってよいだろう。あなたの父上も、 これほどの息子を育てたことを誇りに思うはずだ。";
			link.l1 = "ご親切なお言葉、ありがとうございます、シュヴァリエ殿。すぐにマルティニークへ向かってもよろしいのでしょうか？";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = "少し待ってくれ、友よ。友と呼んでも構わないだろうか？個人的に感謝の意を伝えたいのだ。 君がここに来てからの活躍を私はずっと見てきたし、その多くの行いも知っている。カリブ海で君は大いに名を上げ、 間違いなく、ある界隈では広く知られ尊敬されている。フランスには君のような人物が必要なのだ\n船長 "+GetFullName(pchar)+"！フランス国王陛下より授かった権限により、私はあなたに王立海軍の艦長任命を光栄にも申し上げ、 フランス海軍所属の軽フリゲート艦『グリフォン・ドール』を指揮下に置くことを許可いたします！\nあなたのおかげで前任艦長ド・フォントノーはトルトゥーガ総督となり、 カリブで最上の軽フリゲート艦には新たな艦長が必要です。この申し出を受けていただけますか？";
			link.l1 = "興味深いですな。それで、見返りに何を望むのですか？";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "少しだけだ。獲物の一割と、時々繊細な任務をこなしてもらう。\n君の決断を待っているぞ。";
			link.l1 = "このような申し出を断る者はいません、閣下！祖国に仕えることは名誉でございます！";
			link.l1.go = "serve_3";
			link.l2 = "不躾をお許しください、しかし今はご提案をお断りせねばなりません。\n家族の事情で、すぐに本国へ戻る必要があるかもしれませんので。";
			link.l2.go = "serve_no";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "残念です。あなたが同意してくれることを期待していたのですが……しかし、それでもう一つ頼みごとをせざるを得ません。実のところ、これはあなた自身の利益にもなります。 マルティニークが攻撃を受けています。港や市内で激しい戦闘が続いているのです。\nあいにく、駐屯部隊を助けに送れる者は他におらず、あなたしか頼れる者がいません。祖国の愛国者として、 どんな手段を使ってもこの攻撃を撃退してほしいのです。あなたなら十分な戦力があると信じています。\nそれに、あなたの兄弟もまだそこにいます。彼の命を救うことができるでしょう。";
			link.l1 = "兄が危険なのか？すぐに向かうぞ！";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "なんと立派なお言葉でしょう！まさに真の兵士であり、祖国に忠誠を誓う息子の言葉です！おめでとうございます、旦那 "+GetFullName(pchar)+"。フランス海軍の司令官の階級を授与する。私からこの制服を受け取りなさい。誇りを持って着用し、 その名に恥じぬ者であれ！";
			link.l1 = "私は祖国に仕えております！";
			link.l1.go = "serve_4";	
			locCameraFromToPos(-2.63, 2.20, -4.96, true, 2.64, 0.22, -4.96);
			npchar.greeting = "puancie_1";			
		break;
		
		case "serve_4":
			dialog.text = "重コルベット艦『グリフォンドール』は今やあなたの指揮下にある。\nこの瞬間から、この優れた艦はあなたのものだ。\nその優れた性能を陛下の栄光とカリブ諸島におけるフランスの影響力強化のために存分に活用しなさい！";
			link.l1 = "ただちに！";
			link.l1.go = "serve_5";
			LAi_Fade("SharlePutsSuit", "");
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "しかし、あなたの戦隊はすでに大きすぎますので、船を一隻減らしてから「グリフォンドール」 を受け取りに戻ってきてください。";
				link.l1 = "わかった。そうしよう。";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "船と一緒に、その代理船長と乗組員も引き渡します。もしご希望なら、彼を引き続き指揮下に置いてもよろしいですし、 船から降ろしていただいても構いません。その場合は、我々が彼に別の職を用意いたします。";
				link.l1 = "了解した！";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "しかし、悪い知らせがある、船長。たった今、マルティニークが攻撃を受けているとの報告を受けた。 港でも市内でも激しい戦闘が起きているそうだ。\nあいにく、守備隊を助けに送れる者は君しかいない。これが君の最初の任務だ:\nサン・ピエールを守れ！それに、君の兄弟もまだあそこにいる。彼の命を救うことができるぞ。";
			link.l1 = "兄貴が危険なのか？すぐに向かうぜ！";
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			locCameraTarget(PChar);
			locCameraFollow();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = "「グリフォン・ドール」を指揮する準備はできているか？";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "まだだ、艦隊内の自分の船を再配置している最中だ…";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "私です。";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "素晴らしい！船と一緒に、その代理船長と乗組員も引き渡そう。もし望むなら、彼を引き続き指揮下に置いてもいいし、 船から外して我々が別の役職を用意することもできる。";
			link.l1 = "了解した！";
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;
		
		// Jason НСО
		case "patria":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince"); // Rebbebion, удалить команду пиратов на всякий
			DelCharleePrince("");
			dialog.text = "そして、これはほんの始まりでございます、旦那！あなたほどの軍才があれば、きっと遠くまで出世なさることでしょう！ すでに優秀な海軍士官にふさわしい次の任務もございますが、あなたなら見事にやり遂げてくださると確信しております。 しかも、それは前回の任務と直接関係があるのです。";
			link.l1 = "お聞きしますよ、旦那";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "しかし、まずは私の執務室に入ってきた人物を紹介させていただきましょう。バロン・ノエル・フォルジェ、 フランス西インド貿易会社の名誉会員です。彼は我々の植民地を視察し、 サトウキビや他の作物のプランテーション組織を拡大し、 さらにこの地域での貿易関係の発展の可能性を探るために諸島へやって来ました。パリからは、 これらの件について彼に可能な限りの支援と協力を与えるよう命じられており、我々も間違いなくそうするつもりです。 バロン、こちらはフランスの艦隊で最も有能な船長の一人、シャルル・ド・モール旦那でございます…";
			link.l1 = "";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = "さて、シャルル、バロンと私がサン・クリストフを視察している間、君には次の任務を与える。 フランスの植民地を攻撃して無事に済むと思う者などいないし、 スペイン人どもはすでにマルティニークへの侵略で痛い目を見たが、なおもその罪の代償を財布で払わせ、 植民地に与えた損害を償わせねばならん。\nフランスのバロンと共に、強力な戦隊が到着した。その中には、恐るべき66門砲艦『エクラタン』が含まれている。この艦の船長は経験豊富な水夫だが、カリブ海は初めてなので、 君の指揮下に入ることになる。『エクラタン』と共にスペイン領トリニダード島の沿岸へ向かい、スペイン人どもに対し、 サン・ピエール襲撃の賠償金として三十万ペソを要求せよ。";
			link.l1 = "シュヴァリエ、本当にスペイン人たちが同意するとお思いですか？";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "私は確信している――「エクラタン」と君の戦隊がサン・ホセ要塞を粉々にした後ならな。兵を上陸させて市街を占領し、 兵士を失う必要はないと思う。警告なしに攻撃し、要塞を破壊してから、指揮官に条件提示の意志を伝えるのだ。 この状況では、スペイン人たちは逃げ場がなくなり、金で解決する方を選ぶだろう。君が守備のない都市の総督だったら、 どうする？";
			link.l1 = "ふむ、もっともですね、シュヴァリエ。";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "やるべきことは分かったか？";
			link.l1 = "「はい、閣下。」";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip())
			{
				dialog.text = " では、さっそく取りかかりなさい。これが「エクラタン」号の船長宛の、あなたの権限を認める書状だ。 この優れた船と鍛え抜かれた乗組員は、今やあなたの指揮下にある。シャルル、 君はこれからフランスに仕える身だということを忘れないように。そして私のような役人と正式にやり取りするには、 制服を着用することを勧める。実によく似合っているぞ。幸運を祈る、ド・モール船長！";
			}
			else
			{
				dialog.text = " では、さっそく取りかかりなさい。これは「エクラタン」号の船長宛の、あなたの権限を証明する書状だ。 この優れた船と鍛え抜かれた乗組員は、今やあなたの指揮下にある。ああ、そしてシャルル、 キャプテンの制服を着なさい、これは命令だ！まず第一に、 フランス王立海軍の士官が商人や私掠船のような格好をするのはふさわしくないし、第二に、 その制服はあなたによく似合う。直ちに私の命令を実行しなさい、ド・モール船長！";
			}
			link.l1 = "";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = "「エクラタン」が沈没したのか？シャルル、これは大惨事だ！今度は大臣が何と言うだろう？君には失望したぞ、 シャルル！私は君の経験を信頼できると思っていたのに……残念だが、この責任は君が負うことになる。私が報告書を書くから、しばらく姿を消した方がいい。 王立海軍での君の任務はこれで終わりだ。";
			link.l1 = "ふむ……申し訳ありません、旦那。どうやら本当に一、二か月ほど姿を消した方がよさそうですな、大臣の怒りが収まるまで。 では、失礼します。そして改めて、あなたを失望させてしまい本当に申し訳ありません。";
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = "「完璧だ！」";
				link.l1 = "こちらをどうぞ、三十万を受け取ってください。";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "完璧だが、金はどこだ、シャルル？";
				link.l1 = "ふん、船の宝箱にある。すぐに届けるぞ！";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "それで、シャルル、トリニダから身代金を持ってきたのか？";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "はい、旦那。こちらでございます。";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "すぐに持ってきます！";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "私はあなたに満足しています、シャルル、あなたは決して私を失望させませんでした。\n任務は容易ではありませんでしたが、報酬として償還金から五万ペソを授与します。\n受け取りなさい、それはすべてあなたのものです。";
			link.l1 = "感謝します、シュヴァリエ。";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "すでに新しい任務がある。フォルジェ旦那はサン・クリストフでの検査を終え、今度は我々 の北部植民地を視察したいそうだ。バロンをトルトゥーガとイスパニョーラへ連れて行き、 あらゆる面で彼の業務を補佐し、要望を叶えてやってほしい。わかったな、シャルル？";
			link.l1 = "もちろんでございます、シュヴァリエ。";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "男爵は時間がないので、他の事に気を取られず、旅を二ヶ月以上遅らせないようお願いしたい。";
			link.l1 = "もちろんでございます、旦那。島々の間の航海はあまり時間がかかりません、 ただしフォルジェ様の植民地での用事が長引かない限りは、ですが。";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "完璧だ。それではバロンはお前の船で移動する。最上の船室を用意してやれ。";
			link.l1 = "もちろんでございます、シュヴァリエ！";
			if(IsUniformEquip()) link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "それからもう一つ、シャルル。君はまた士官の制服を着ていないな！これが最後の警告だ。 今後は必ず制服姿で私の前に来るように。そうでなければ話は聞かん。君は勤務中なのだ、規律こそが全てだぞ、 特に海軍士官の身なりにおいては！";
			link.l1 = "お許しください、シュヴァリエ。二度とこのようなことはいたしません。";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = "あなたの航海が成功することに疑いはありませんでした。トルトゥーガやポルトープランスから何か知らせはありますか？ ";
			link.l1 = "...";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 = "はい、シュヴァリエ、報告がありますが、あまり愉快な内容ではありません。まず、ポルトープランスの総督は、 スペイン人が植民地への攻撃を準備していると確信しており、そのために軍艦隊を……ええと、何と言いましたか……サンティアゴ、そう、サンティアゴに集結させているそうです。そして、これは単なる噂話ではなさそうです。 この件を無視するわけにはいかないと思います。特に、 ポルトープランスのプランテーションは私が今まで見た中でも最高級のものですから。";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "スペイン人がポルトープランスを攻撃する準備をしているのか？ふむ……よろしい。これについては"+pchar.name+"船長、君に対処を任せよう。「エクラタン号」は修理を終え、装備も整い、すぐに出航できる状態だ……";
			link.l1 = "それからもう一つ、旦那。パリでは、ここから北にあるサン・マルタン島がフランス領と見なされていますが、 シャルル・ド・モール船長は、あそこはオランダ人が支配していると言っていました。本当ですか、シュヴァリエ？";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "ふむ……それはある程度正しいですな。サン・マルタンはフランスの植民地でございます。しかしながら、バロン、 経済的な観点から申しますと、この島はまったく役に立ちません――面積は小さく、土地は痩せて不毛、水も乏しく、井戸にわずかにある水も濁って苦いのです。 飲料水として雨水を集めているとさえ聞きましたぞ。\nそのため、サン・マルタンは長期貸与の形でオランダ西インド会社に引き渡され、 同社の船がこの地域から本国へ向かう際の北の中継地として利用されております。 オランダ人はフィリップスブルフの集落を拡張し、要塞と港を築きました。最近この諸島にやって来たばかりの者――例えばシャルル・ド・モール船長のような方々には、 サン・マルタンがオランダの植民地のように思えるかもしれませんな。";
			link.l1 = "「しかし、法的にはその島は我々のものなのか？」";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "もちろんです。しかし、先ほど申した通り、限られた資源を使うよりも、賃貸収入で稼ぐ方がずっと利益になります。";
			link.l1 = "この島はカリブ海にフランス西インド会社が進出する際、非常に有用だと私には思われます。\nあなたが今おっしゃった意味――ヨーロッパへの道中にある北の前哨基地――もまさにその通りです。\n私はこの植民地を視察する必要がありますし、島のオランダへの貸与もおそらく打ち切られることでしょう。";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "まずはウィレムスタッドにいるオランダ西インド会社の総裁、 ピーター・スタイフェサント殿の元へ照会状を送る必要がある。\n彼が島の査察許可を出さねばならん――何しろ、オランダ人はずっとあそこにいるのだからな。";
			link.l1 = "それならウィレムスタッドへ使者を送らねばなりません。";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "問題はな、スタイフェサント旦那はウィレムスタッドにほとんどいないことだ。彼はいつも旅をしていて、 ガレオン船で会社の用事をこなしているのだよ…";
			link.l1 = "しかし、少なくとも時々はそこにいるのでしょう？\nいずれにせよ、オランダ人には正当な所有者による島の検査を保証する義務があります。\nフィリップスブルフ総督に手紙を送ってみてはどうでしょうか？";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "マルティン・トマス旦那には敬意を表しますが、彼はただの雇われ人にすぎません。本当の経営は会社が行っております。 男爵、私がこの問題を解決いたしますので、ご安心ください。少々お時間をいただきます。";
			link.l1 = "さて、私には時間がたっぷりございます。何しろ、これから南部の植民地、 グアドループとマルティニークも訪れねばなりませんからね。残念ながら、 今回はシャルル・ド・モール船長がご一緒できないのです――またしてもイスパニョーラへ向かわねばならぬのでしょう…";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = "そうだそうだ、つまらん話で我らの親愛なる船長を引き止めてしまっているな！シャルル、「エクラタン」を戦隊に率い、 イスパニョーラへ進出し、スペイン人によるポルトープランスへの実際の脅威がないか調べてくれ。もし何かあれば、 君が対処してくれ。しかし、君に教えることなど何もない、私よりよく分かっているだろう。何も見つからなければ、 時間を無駄にする必要はない、君にはここで必要があるのだ。報告は遅くとも一ヶ月以内に頼む。幸運を祈るぞ、友よ！";
			link.l1 = "ありがとうございます、シュヴァリエ。すぐに出航いたします。";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "それからもう一つ、シャルル。オランダ当局と何か問題を抱えていると聞いたが？どうか、 この件はできるだけ早く解決してくれ。近いうちに彼らの植民地を訪れる必要があるのだ。ご理解いただけると思うが、 砦からの砲撃を受けていては、それは不可能だろう。";
			link.l1 = "承知しました、旦那。必ずやり遂げます。";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "それからもう一つ、シャルル。警告しておくが、オランダ人とのいざこざは避けるのだ。 近いうちに彼らの植民地を訪れることになるからな。ご理解の通り、砦から砲撃を受けていては不可能だからな……";
			link.l1 = "よろしいです、旦那。オランダ人とは争いません。";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = "「エクラタン」が沈没したのか？シャルル、これは大惨事だ！今度は大臣が何と言うだろうか？君には失望したぞ、 シャルル！私は君の経験を信頼していたのに、君は……残念だが、この責任は君に問われることになる。私は報告書を書く、君はしばらく姿を消した方がいい。 王立海軍での君の任務はこれで終わりだ。";
			link.l1 = "ふむ……申し訳ありません、旦那。どうやら本当に一、二か月ほど身を隠した方がよさそうですな、大臣の怒りが収まるまで。 さようなら、そして改めて、あなたを失望させてしまい大変申し訳ありません。";
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
		break;
		
		case "patria_26":
			dialog.text = "素晴らしい！君のような艦長が我が海軍にいる限り、カスティーリャ人の奸計など恐れることはない。明日、 ポルトープランスへ使者を送り、フランスからの公文書と書簡を届けさせるつもりだ。同時に、 ジェレミー・デシャン・デュ・ムサカ旦那宛ての私信で、君の働きに感謝するのが当然だとほのめかしておこう。 だから安心してくれ、シャルル、君には相応しい褒美が必ず与えられるだろう。\nさて、次の任務に移ろう。そうだ、友よ、君に新しい仕事を頼みたい。だが今回は軍事的なものではなく、 非常に繊細な案件だ。ぜひ君に任せたいのだ。";
			link.l1 = "お話を伺いますぞ、ド・ポワンシー殿。";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "サン・マルタンについてフォルジェ旦那と話したことを覚えているだろうな？ バロンに植民地の検査が済んだと安心させる必要がある。そこでお前にはキュラソー、ウィレムスタッドへ行ってもらう。 現地のカンパニー長官、ピーター・スタイフェサントに会うのだ。彼は今そこにいて、あと三週間は滞在する予定だ。 それから、カンパニーの積荷を載せたフリュート船をキュラソーまで護衛し、 スタイフェサント旦那に私からの書簡を渡してくれ。";
			link.l1 = "これで任務は全部ですか？";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "はい、船長。スタイフェサント旦那の返事を私に知らせてください。 フォルジェ旦那がマルティニークとグアドループから戻る前に、ちょうど到着できそうですね。 長い間訪れたがっていたサン・マルタンにも、ついに彼が行けることでしょう。";
			link.l1 = "よろしいでしょうか。もう行ってもよろしいですか？";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = "よろしい、シャルル。だが、あまり時間をかけるな、バロンは待つのが嫌いだからな。\nそれと、ピーター・スタイフェサントを訪ねる時は必ず制服を着用するのだ！すべて公式に見えなければならん、 わかるだろう。";
			link.l1 = "もちろんでございます、シュヴァリエ。さようなら！";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "ありがとう、船長、それを渡してくれ……（読みながら）……ふむ、素晴らしい！ピーテル・スタイフェサントによれば、 バロン・フォルジェが視察のためサン・マルタンを訪れることができ、 フィリップスブルフの総督にも通知して協力させるとのことだ。視察の後、バロンはきっと正しい判断を下すだろう――つまり、この島をオランダ人に貸与することになるはずだ。\nそして今、最も心温まる知らせだ、船長！君に伝えたいことがいくつかある。まず第一に――君のこれまでの軍功を考慮し、君を『コモドール』に昇進させる。おめでとう、旦那！";
			link.l1 = "私はフランスに仕えております！";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "そして二つ目だが、ポルトープランスの総督が君のために商品満載の交易船を送ってきた。コーヒーの大袋が五百、 さらにカカオの袋も五百だ。これらはすべてイスパニョーラのプランテーションで収穫されたもので、 君がスペインの襲撃から守ったものだ。さらに、特に貴重な貨物も用意されていた――リグナムバイタ五十ユニットだ。これが何か、君に説明する必要はないだろう。 君の品物はカプスターヴィルの店の倉庫に保管されている。いつでも商人から受け取ることができるぞ。";
			link.l1 = "ありがとうございます、シュヴァリエ！素晴らしい知らせです！";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "さて、次の任務についてだが、バロン・フォルジェが近日中にサン・クリストフへ戻ってくる。 お前は彼をサン・マルタンまで護衛し、しっかりと警護するのだ。それから、 いわばフィリップスブルフで何が起きているかを注意深く観察し、私に報告せよ。 バロンが到着したらすぐに街を離れるな、船長。私の使いが必ずお前を見つけて知らせるからな。\n";
			link.l1 = "すべて了解しました。もう行ってもよろしいですか？";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "許可しよう。数日間陸で休めば、君にとって良いし役にも立つだろう。";
			link.l1 = "...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // снять таймер
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8+rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // товары-призы
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_37":
			dialog.text = "";
			link.l1 = "はい、シュヴァリエ、もう戻りました！サン・マルタン近くのオランダ人どもは、砦の大砲で俺たちを迎え撃ち、 三隻の艦隊で襲いかかってきました。シャルル・ド・モール船長とその乗組員の腕前のおかげで、 なんとか逃げ延びることができました！どうやらミンヘール・ピーテル・スタイフェサントは、 フィリップスブルクでフランス王の使節に会いたくないようですね。シュヴァリエ、あなたはどうお考えですか？";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "「何だと？！ここにスタイフェサントの直筆署名入りの書簡があるぞ、その中で彼は保証している…」";
			link.l1 = "だが、フィリップスブルク要塞の司令官は明らかにスタイフェサントから別の手紙を受け取っていたんだ、 好きなように砲撃し、中隊で俺たちを待ち伏せしろってな！\n偶然だったのか、シュヴァリエ！？違うだろう！あいつらは明らかに俺たちをそこで待ち受けていたんだ！ 砲弾と散弾でな！";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "バロン、どうかお許しください……この件は私が対処いたします。すぐに我らが親愛なる船長、シャルル・ド・モールを再びキュラソーへ送り、 スタイフェサント殿と会わせましょう。船長は繊細な事態の処理に長けておりますので……。さて、これから召使いたちに風呂と美味しい昼食の用意をさせましょう。";
			link.l1 = "...";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = "シャルル、友よ、ウィレムスタッドへ急ぐのだ。スタイフェサントがまだそこにいるかもしれん。もし不在なら、 彼の居場所を突き止めて追いかけろ。会談の際には、事件について伝え、説明を求めるのだ。 私は君の経験と権威を信頼している、交渉は君に一任する。\nそして、一分たりとも無駄にせず、すぐに戻って会談の結果を私に報告してくれ。";
			link.l1 = "任務は明白です、シュヴァリエ。すぐに船を準備して出発いたします。";
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = "信じられないな……";
			link.l1 = "さらに、帰り道でオランダの海軍戦隊に襲われました。どういうことなのか、シュヴァリエ、説明していただけますか？";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "友よ、あなたの洞察力の鋭さはよく知っている。だから、何も隠さずに話そう。\nただ一つ頼みがある。ここで聞いたことは決してこの部屋から漏らさないでくれ。約束してくれるか？";
			link.l1 = "もちろんでございます、シュヴァリエ。";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "よろしい。フランス海軍で素晴らしい出世が君を待っているだろう。もちろん、私の助力があれば、 副提督の地位にまで昇進することも可能だ！…まあ、それはさておき…さて、オランダ人とサン・マルタンについてだ。\n君がサン・マルタンに来るずっと前から、あそこでは大量の塩が発見されていた。最初は誰も気に留めなかったが、 やがてキューバやイスパニョーラのスペイン人たちが大いに興味を示した――牛の死骸を塩漬けにするためにな。ご承知の通り、我々はスペインと直接取引することはできない。だから……";
			link.l1 = "…君はオランダ西インド会社という形で「交渉人」を作り出したのだな…";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "まさにその通りだ！考えが早く、しかも的確だな、シャルル！さて、パリからの査察を知ったスタイフェサントは、我々 がスペインとの取引を皆に明かす気がないと踏んで、塩の取引を大胆にも完全に自分の手中に収めようとしたのだ。 しかし、そこが奴の誤算だった。フランス総督の手から何かを奪おうなどという者は、決して罰を免れぬ！ そのことを奴に思い知らせてやろう。";
			link.l1 = "私の理解では、このことはフォルジェ男爵には知られてはなりませんね……";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "友よ、まったくその通りだ。バロンに詳細を知らせる必要はない。すでに十分なことが起きている――フランス王の使者への暗殺未遂、外交使節団の船への襲撃、つまり君自身への攻撃、そして何よりも重要なのは、 サン・マルタン島の事実上の併合だ！これだけでオランダに対する軍事行動の正当な理由になる。";
			link.l1 = "戦争だと！？";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "その通りだ！友よ、副提督の地位も君にはそう遠くない、わかるか？ ルーヴルでの会談に提督の制服を着て臨む自分を想像してみたまえ、 ルイ十四世陛下ご自身がそんな名誉ある客人を迎えるのだ……オランダ人どもを思い知らせねばならん！ストイフェサントも自分のしたことを後悔するだろう。君も同意してくれるな？ ";
			link.l1 = "同感です、シュヴァリエ。オランダ人はその無礼で卑劣な行いの責任を取らねばなりません。";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "素晴らしい。私たちの決定をバロンに伝え、すぐにフランス植民地へ使者を送ろう！\nそして、友よ、長旅の疲れを癒してくれ。明日の朝九時以降に私のところへ来てほしい。 君のために戦闘任務を用意しておく。";
			link.l1 = "かしこまりました、旦那。これにて失礼いたします。";
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = "戦争とは呼べん、むしろ平和を強いるようなものだ、実際のところ。\nそれにスタイフェサントが考えを変えれば、我々としてはむしろ喜ばしいことだ。\nだからこそ、今、彼に示さねばならん――サン・マルタン島を手に入れようとすれば、得るものよりも失うものの方がはるかに大きいとな。\nそこでお前の出番だ、シャルル。";
			link.l1 = "聞いているぞ。";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "サン・マルタンは、ヨーロッパへ向かうオランダ船の積み替え拠点だ。 会社の船は定期的にフィリップスブルフの湾に停泊している。今までは、彼らにとって海域はかなり安全だった。 今までは、船長！…君はサン・マルタンの沿岸へ向かい、巡回し、会社の商船を拿捕するのだ。\n貴重な貨物を運ぶため、会社はイースト・インディアマン――頑丈で武装も充実し、巨大な船倉を持つ船――を使っている。それが君の標的だ。そのような船を五隻、積み荷ごと拿捕し、カステルヴィルへ戦利品として持ち帰れ。 その後、我々はストイフェサントとの交渉を続ける。そして、損失を計算した後で、彼の考えも変わるかもしれん。";
			link.l1 = "任務は明白です。行ってもよろしいでしょうか？";
			link.l1.go = "patria_53";
		// belamour legendary edition -->
			link.l2 = "旦那、恐縮ですが、この作戦の資金援助をお願いできませんか。何ヶ月にも及ぶ航海、 絶え間ない修理や損失が発生しますので……";
			link.l2.go = "patria_53a";
		break;
		
		case "patria_53a":
			AddMoneyToCharacter(pchar, 20000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			dialog.text = "残念ながら、我々の備蓄は尽きてしまった、シャルル。エクリアトン号の維持費と戦闘で、 すでにフランス植民地の半年分の予算が消えてしまったのだ。今はこれが私から渡せる全てだ。将来の報酬を考えてくれ、 シャルル！素晴らしい未来が君を待っているぞ！";
			link.l1 = "はい、旦那！";
			link.l1.go = "patria_54";
		break;
		// <-- legendary edtion
		case "patria_53":
			dialog.text = "行きなさい、友よ、そして幸運があなたの一歩一歩に付きますように。";
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = "任務を完了しましたね、船長。素晴らしい働きに感謝します！戦利品の売却益の分け前を受け取る権利があります――二十万ペソです。";
				link.l1 = "それは嬉しいです、旦那！";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "それで、あなたにはたった "+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+" オランダ船は我々の港へ連れて来るだけでよい。";
				link.l1 = "「はい、シュヴァリエ！」";
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		// belamour legendary edition -->
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = "そして、それだけではないのだ。先日、私は考えていた……シャルル、君は本当にフランスのために多大な貢献をしてくれた。裏切り者ルヴァスールの排除、 スペインの卑劣な攻撃からサン・ピエールを守ったこと、サン・ホセ植民地の要塞を見事に攻略したこと、 さらにスペイン人の厚かましい企みへの罰として賠償金を受け取ったこと……そのうえ、ヨーロッパから到着したフランス王室の使者を自ら護衛し、 フィリップスブルク近海でオランダの待ち伏せから命を救ったのだ！\n";
			link.l1 = "旦那、本当に、私は困ってしまいます……私はただ自分の義務を果たしているだけです。";
			link.l1.go = "patria_57_1";
		break;
		
		case "patria_57_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "君は相変わらず謙虚だな、友よ。さて、今回のオランダに和平を強いるという最新の任務も、 君はまたしても私を失望させなかった。誇張抜きで、君は国家の英雄だ！この群島におけるフランス植民地の総督として、 私はフランス最高勲章の複数の複製を所持しているが……ところで、この書類を読んでくれ。";
			link.l1 = "フランスへの卓越した功績により……フランス国王陛下の御名のもと……フランスに仕える海軍士官、アンリ・ド・モンペの息子、シャルル・ド・モール船長に授与する……\nシュヴァリエ、冗談ですか？";
			link.l1.go = "patria_57_2";
		break;
		
		case "patria_57_2":
			dialog.text = "とんでもない、友よ。あなたにふさわしい報酬として、フランス最高の勲章――サン・ルイ勲章を授与する栄誉を私に与えてくれたのです！我が国のすべての市民が、その英雄を知るべきだ！ そしてサン・ピエールもあなたに借りがある！この勲章はあなたにふさわしい、シャルル。";
			link.l1 = "本当に、何と言えばいいのか……ありがとうございます、総督閣下！私は誇りを持ってフランスに仕え、決して敵に背を向けないことを誓います！";
			link.l1.go = "patria_57_3";
		break;
		
		case "patria_57_3":
			GiveItem2Character(pchar, "talisman9");
			Log_Info("You've received the Order of Saint Louis! You are the hero of the nation!");
			PlaySound("interface\important_item.wav");
			DoQuestCheckDelay("sea_victory", 0.5);
			dialog.text = "まさに真の士官の言葉だ！私は本当に誇りに思うぞ、シャルル。今は少し休みなさい。君はその価値がある。\nその間に、私はスタイフェサントとの交渉にあたろう――彼もそろそろ、我々と敵対するより友になる方がはるかに得だと気づいたかもしれん。\n町を離れずにいてくれ、二日後に君が必要だ。";
			link.l1 = "承知しました、旦那。次の指示をお待ちします。";
			link.l1.go = "patria_58";
		break;
		// <-- legendary edtion
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = "はい。スタイフェサントがスペインと同盟を結び、軍事行動に出始めたようです。オランダ・スペインの連合艦隊がサン＝ クリストフを包囲しています。見張り砦からは、彼らの動きについて毎時報告が届いております。";
			link.l1 = "「包囲戦か？」";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "当然です。奴らは正面攻撃には出ませんでしたし、それはむしろ好都合です。敵が島全体を封鎖する前に、 迅速に行動する必要があります、船長。";
			link.l1 = "私たちは何をすればいいのですか？";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "セントジョンズ、アンティグアには、ドイリー大佐率いるイギリス海軍の艦隊が駐留している。\n今は彼がジョナサン・フォックス卿を訪問中だ。\n敵艦をうまくかわしてアンティグアに到着しなさい。そこで大佐に会い、私の手紙を渡して協力を求めるのだ。";
			link.l1 = "「大佐は私たちを助けてくれると思いますか？」";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "そう願いたいものだ。その手紙が、彼の協力に対する報酬がかなりの額になることを納得させてくれるはずだ…。それから、「エクラタン」号の船長にも手紙を送る必要がある。現在グアドループ沖にいるが、 急いでサン・クリストフへ向かわせねばならん。「エクラタン」号の火力は、戦いで我々に大いに役立つだろう。\n君が同時に二箇所にいることはできないから、我々の連絡用ラガー船を君の戦隊に加えよう――敵の包囲を無傷で突破させ、そして「エクラタン」号が南下する前にグアドループへ向けて出発させるのだ…。";
			link.l1 = "なるほど。包囲を突破し、連絡用ラガー船を護衛し、急いでサン＝ジョーンズへ行き、 ドイリー大佐に手紙を届けるのだな。";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "その通りです。あなたの艦隊にもう一隻の船を受け入れる準備はできていますか？";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "私は一隻の船を処分して、あなたのところに戻ります。";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "「はい。」";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "素晴らしい。手紙を受け取りなさい。ラガー船は準備万端で、あなたの指示を待っている。";
			link.l1 = "時間を無駄にせず行きましょう、シュヴァリエ！";
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = "ああ、ああ、友よ、君の謙虚さはよく知っている。君は本物の士官だ！そして、必ず報酬を受け取ることになる、 約束しよう！あれほど激しい戦いの後だ、休息が必要だろう？一週間まるごと与えよう。 七日後に私の部屋へ話しに来なさい――町が英雄にふさわしい褒美を用意するだろう。";
			link.l1 = "はい、旦那。よろしいでしょうか？";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "行ってゆっくり休みなさい。\n後ほど重大な問題に対処しなければならない――ご覧の通り、今のところオランダ人との和平は不可能ですから。\n今は私と大佐でいくつか重要な案件について話し合います。";
			link.l1 = "「では、一週間後にお会いしましょう、シュヴァリエ。」";
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = "私とドイリー大佐で話し合いをし、彼も協力してくれることになった。イングランドは我々 の対オランダ戦争を支援してくれる。君と私は反撃し、正義を取り戻さねばならない――サン・マルタン島はフランスに戻るべきだ。この任務を最も優秀な海軍の艦長、すなわち君、 シャルル・ド・モールに託す！敵はまだ自分たちの戦隊の敗北から立ち直れていない。フィリップスブルクを攻撃し、 奪取するのだ。\n戦いは容易ではない。まず砦を破壊し、次に守備隊の防御を突破しなければならない……（小声で）さらに、私が話した塩田までジャングルを強行軍で進み、そこに陣取る敵を討つ必要もある……";
			link.l1 = "任務はかなり困難です、シュヴァリエ……";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "よく分かりました、友よ。君の戦隊は増強されることになる。バステールとサン＝ピエールの総督たちは、 今ごろそれぞれフリゲート艦を用意しているはずだ。グアドループとマルティニークを訪れて、 そのフリゲート艦を指揮下に収めればよい。もちろん、君自身が望むならの話だ――どの艦を選ぶかは君に任せよう。さらに、旗艦のための補給品や装備を購入するために、２万ペソの補助金も渡そう。 さあ、受け取りたまえ…";
			link.l1 = "かしこまりました、旦那。";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "それから、いつものように『エクラタン』号も君の指揮下にある。修理と装備は済んでおり、停泊地で待機している。 船長と話せば、いつでも受け取ることができるぞ。";
			link.l1 = "「素晴らしい！」";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "時間の無駄はできません、船長。私の密偵によれば、オランダ人はサン・マルタンへの脅威を理解し、 防衛を強化するつもりのようです。\nしかし、まだ二ヶ月の猶予があります。必ず期限内に任務を完了しなさい！";
			link.l1 = "私がやりましょう…（小声で）サン・マルタンの塩鉱床はどこにあるんだ？島のどの地図にも載っていないが…";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = "（小声で）町を攻める時は、フィリップスブルグの副総督、マルティン・トーマス旦那を尋問しろ。 あいつが教えてくれるはずだ。あのオランダ野郎は臆病者だから、お前に逆らうことはない、保証するぜ。";
			link.l1 = "なるほど。では、これで失礼してもよろしいでしょうか？";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "待ちなさい、シャルル。サン・クリストフ救出の報酬をまだ受け取っていないだろう。 市民たちからのこの金貨の入った箱を受け取りなさい。そして、どんな金額でも表せない我々 の心からの感謝も受け取ってほしい！";
			link.l1 = "ありがとうございます、旦那！";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info("You've received 10 chests of doublons");
			PlaySound("interface\important_item.wav");
			dialog.text = "もう行ってよいぞ。幸運を祈る、船長！我々は皆、お前の勝利を待っている！";
			link.l1 = "「さようなら、シュヴァリエ。」";
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = "The warship 'Eclatant' will also be under my command.";
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = "たった一年前に君が副提督に昇進するなんて、誰が想像しただろうか、友よ？この知らせがフランスに届いた時、 君の父上がどれほど誇りに思うか、私には想像するしかないよ！";
			link.l1 = "私の父上はきっと大いに喜ぶことでしょう。";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "君は艦隊での地位を自らの力で勝ち取ったのだ！サン・マルタンはフランスに返還され、 ストイフェサントも痛い目を見た。これは大勝利だった！だが、ここで止まるわけにはいかん、 オランダ人どもに一瞬たりとも休息を与えてはならん。裏切りの報いは必ず受けさせる！ ドイリー大佐は今まさにポート・ロイヤルにいて、海軍戦隊の準備をしている。 キュラソーへの一撃で敵の背骨をへし折るつもりだ。ただし、それは後の話、今は一石二鳥を狙うぞ、シャルル。\n会社が莫大な富をすべて交易で得たわけではない。オランダのこの地域での主な収入源は、 プランテーションでの奴隷労働だ。もし知らなかったなら教えておこう、シャルル――オランダは最大の奴隷所有国であり、奴隷貿易国だ。『黒い象牙』を積んだ東インド会社の船が、 西アフリカから定期的にキュラソーへやって来る。そして、私はその件について少々知っている……ストイフェサントには不運なことだがな。\n今まさに、二隻のオランダ東インド会社船がギニアからカリブ海へ向かって航行中だ。船倉は黒人の囚人でいっぱいだ。 おそらく十日ほどで、その船団はトリニダード島の近海をキュラソーへ向けて通過するだろう。君の任務は、 その船団を発見し、二隻の東インド会社船とその積荷を拿捕することだ。護衛艦を撃沈し、奴隷たちを我々 の同盟者であるドイリー大佐のいるジャマイカへ連れて行け。これは非常に重要な任務だ、シャルル――こうして彼の信頼を得るのだ……分かってくれるだろうな。\n休息の暇も与えられず申し訳ないが、この任務は極めて重要かつ繊細であり、君以外に託せる者はいないのだ。";
			link.l1 = "奉公は甘いものではありません、シュヴァリエ。私が誰よりもよく知っています。すぐに船の準備をして出発いたします。 ";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "順風と安全な航海をお祈りします、副提督殿。\nそしてサン＝クリストフに戻られる頃には、我々 の共通の友人ノエル・フォルジェ旦那がフィリップスブルフの査察を終えているでしょうし、 オランダ人から奪った戦利品の一部があなた個人の手に渡るよう、私が手配いたします。";
			link.l1 = "それは大変ありがたいことでございます、シュヴァリエ。私は行ってもよろしいでしょうか？";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "行け。幸運を祈るぞ、友よ！";
			link.l1 = "...";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = "素晴らしい！君は「不可能」という言葉を知らないのだな、シャルル。 かつては君の兄上こそカリブで最も優れた海軍士官だと思っていたが、もしこの率直な比較を許してもらえるなら、 彼も君から学ぶべきことが多い。\nさて、ウィレムスタッド攻撃に参加するために我らが親愛なる大佐のもとへ行くのが誰か、もう分かっているだろう。";
			link.l1 = "とんでもありません、旦那！私に分かるはずがございません！";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "ああ、君の有名なユーモアのセンスだな、親愛なる友よ！ははは！もちろん、君だよ、副提督。誰よりもふさわしい。 準備はできているか？";
			link.l1 = "もちろんでございます、シュヴァリエ。必要なのは修理と装備だけで、すぐに出発できます。";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = "「エクラタン号」を指揮下に置くのを忘れないようにしなさい。修理と装備が完了し、埠頭であなたを待っている。 ユベール・ダシエ侯爵はすでに苛立ち始めており、あなたと共に再び戦に出るのを心待ちにしているぞ。";
			link.l1 = "素晴らしい。遠距離カルヴァリン砲を備えた強力な艦こそ、砦を砲撃するのにまさに必要なものだ。";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "少し待ちなさい、シャルル。私たちの友人フォルジェ男爵がサン・マルタンからあなたへの知らせを持ってきたのです。";
			link.l1 = "...";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_25";
			sld.greeting = "noel_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = "パリから知らせがございます。副提督への任命が国王によって署名されました。関連書類も受け取ることになるでしょう。 \nおめでとうございます！";
			link.l1 = "ありがとうございます、旦那！フランスと国王陛下にお仕えできて光栄です！";
			link.l1.go = "patria_coat";
		break;
		
		case "patria_coat":
			dialog.text = "そして私は、いつも通り、あなたからそのようなお言葉をいただけて大変嬉しく思います。シャルル、 よろしければ私と一緒に少しワインでもいかがですか？パリから直送されたものでして、 こんな品は一日かけて探してもここでは手に入りませんよ！";
			link.l1 = "ありがとうございます、シュヴァリエ。しかし、今回は遠慮しておきます。後で船に戻らねばなりませんし、 フランス副提督が酔っ払って艦尾甲板に立つのは相応しくありませんので。";
			link.l1.go = "patria_coat_01";
			link.l2 = "「まあ、いいじゃないか？総督閣下ご自身と酒を酌み交わせる機会なんて、そうそうあるもんじゃねえからな！」";
			link.l2.go = "patria_coat_02";
		break;
		
		case "patria_coat_01":
			dialog.text = "まあ、少し休んでもいいんだぞ、すぐに船へ戻る必要はない。しかし、それは君の選択だし、私は尊重しよう。\nよろしい、では早速本題に入ろう。";
			link.l1 = "注意深く聞いております。";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_02":
			dialog.text = "そして、すべての総督が自分の副提督を最高の海軍士官としてだけでなく、同じ卓を囲み、 遠い祖国から運ばれたワインを共に酌み交わせる友人として持てるとは限らないのでございます！";
			link.l1 = "フランスのために！";
			link.l1.go = "patria_coat_03";
			link.l2 = "「ご健康を、シュヴァリエ！」";
			link.l2.go = "patria_coat_04";
		break;
		
		case "patria_coat_03":
			dialog.text = "「そして王のために！」";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_04":
			dialog.text = "「君にも、シャルル！」";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_05":
			LAi_Fade("", "");
			if(LAi_GetCharacterHP(pchar) == LAi_GetCharacterMaxHP(pchar))
			pchar.chr_ai.hp = stf(pchar.chr_ai.hp) - 1.0;
			GiveItem2Character(pchar, "potionwine");
			DoCharacterUsedItem(pchar, "potionwine");
			npchar.dialog.currentnode = "patria_coat_06";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorSetHuberMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.2);
		break;
		
		case "patria_coat_06":
			dialog.text = "ふむ、絶品のワインだ！君もそう思わんか？";
			link.l1 = "はい、あなたの言う通りです。故郷ガスコーニュで作られるワインを思い出しますね……";
			link.l1.go = "patria_coat_07";
		break;
		
		case "patria_coat_07":
			dialog.text = "少し違いますよ、旦那。ボルドーです。それでもガスコーニュのワインもきっと素晴らしいでしょう！";
			link.l1 = "私はその味を忘れかけている気がする……フランスを離れてからどれくらい経った？一年か？二年か？";
			link.l1.go = "patria_coat_08";
		break;
		
		case "patria_coat_08":
			dialog.text = "ああ、シャルル、まるでつい最近会ったばかりのような気がするな……しかも、あまり愉快とは言えぬ状況であった。こんな話を持ち出すのは申し訳ないが、もしあの時、 あの牢獄で私の前に立っていた男が、将来フランス植民地で私の右腕になるなどと誰かに言われていたら、 きっと大笑いしていたことだろう。";
			link.l1 = "「主の御業は計り知れぬものだ。」";
			link.l1.go = "patria_coat_09";
		break;
		
		case "patria_coat_09":
			dialog.text = "失礼ですが、今何とおっしゃいましたか？";
			link.l1 = "ラテン語ですよ、シュヴァリエ。主の御業は計り知れません。人生に何が待ち受けているか、誰にも分からないのです。";
			link.l1.go = "patria_coat_10";
		break;
		
		case "patria_coat_10":
			dialog.text = "君には毎度驚かされるよ、シャルル。見てごらん――まさかラテン語まで話せるとは思わなかった。しかし一方で、ある程度は自分自身で運命を切り開くものだろう？";
			link.l1 = "両方とも真実だと思います。私たちに何が待ち受けているかは主のみぞ知る。しかし、 主は粘り強い者に報いを与えてくださいます。";
			link.l1.go = "patria_coat_11";
		break;
		
		case "patria_coat_11":
			dialog.text = "まったく同感です。例えば、あなたに海軍士官の任命書を渡し、その制服を授けたことを覚えていますよ。そして今、 私の前に立っているのは、なんと副提督ではありませんか！";
			link.l1 = "時の流れは早いものですね、シュヴァリエ。";
			link.l1.go = "patria_coat_12";
		break;
		
		case "patria_coat_12":
			dialog.text = "確かに……しかもその制服にも、サーベルで斬られた跡が見える。いくつかは縫い合わされているが、明らかに新しい傷もある。 これは直さねばならん。";
			link.l1 = "総督閣下、何をお考えですか？";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_13":
			dialog.text = "カリブ諸島のフランス艦隊副提督という新たな地位に加えて、もう一つ贈り物がございます。";
			link.l1 = "おや、照れてしまいますよ、シュヴァリエ。どんな贈り物ですか？";
			link.l1.go = "patria_coat_14";
		break;
		
		case "patria_coat_14":
			dialog.text = "私の専属仕立屋――フランス植民地で一番の腕前だ！――に、あなたの階級にふさわしい制服を仕立てるよう手配しておいた。\n支払いのことは心配いらない、すべて私が済ませてある。";
			link.l1 = "本当に感謝しています！必ずあなたの仕立屋に伺います。どこで会えますか？";
			link.l1.go = "patria_coat_15";
		break;
		
		case "patria_coat_15":
			dialog.text = "今ちょうど港の事務所にいるはずだ――本土から新しい連絡船が小包をいくつか運んできたばかりでね。\nうちの仕立屋は、ここでは手に入りにくい生地をいつも注文しているのだよ。";
			link.l1 = "それでは港の役所に行ってくるよ。改めてありがとう、旦那！";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "さて、今はしっかり休養が必要でしょう。ひと月差し上げますので、有意義に過ごしてください。仕事も心配も無用です。 すべての業務はあなたの士官たちに任せて、ゆっくりお休みなさい。私の邸宅の部屋をお使いになって構いません。 召使いたちが快適にお世話いたします。\nひと月後にまたお会いしましょう――その時、あなたにご相談したい繊細な案件がございます。";
			link.l1 = "承知しました、シュヴァリエ。さようなら！";
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			npchar.dialog.currentnode = "First time";
			LAi_Fade("","");
			LAi_SetHuberType(npchar);
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			SetFunctionLocationCondition("Patria_Tailor", "Charles_PortOffice", false)
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = "ああ、シャルル。自分で何とかできると思っていたが……残念ながら、また君の才覚を頼らねばならんようだ。だがまず、君に渡すものがある。 三十万ペソとドゥブロン金貨の入った五つの箱だ。 これはスタイフェサントが取引に従って私に支払った拠出金の大部分だ。君はほとんどの仕事をやり遂げたのだから、 これを受け取る資格があるだろう。受け取ってくれ。満足かね、友よ？";
			link.l1 = "金は誰にも害を与えません、旦那、それは私がよく学んだ教訓です。";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "ああ、副提督、過去の出来事で気を悪くしてはいませんか？…今やあなたは祖国の英雄ですよ、ご存じでしたか？この新たな地位での気分はいかがです？覚えておいてください、 多くの有能な士官たちは何十年もかけて昇進してきましたが、経験豊富な指導者がいなければ…結局は指揮官止まりなのです。しかし、あなたは不可能を成し遂げる特別な力を持っています！そして、 あなたには高位の友人、すなわち後見人もいますから、今後何か困ったことがあれば、私が必ず力になりますよ。";
			link.l1 = "ご丁寧なお言葉、閣下、ありがとうございます。この地でほとんどのことを成し遂げた気がいたします。もちろん、 閣下のお力添えあってのことです。これでようやく自分のことに専念してもよろしいでしょうか？ 家族のことも考えなければなりません。";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "結婚したいのか、シャルル？あっはっは！パリの美しい女を指させば、すぐにでもお前のものになるぞ！だが、 残念ながらそれは後回しだ。今は少なくとも、ここにいてもらわねばならん、友よ。";
			link.l1 = "どうやら、フランスは群島でかつてないほど強くなっているようだな。イングランドとの同盟、会社との休戦。問題児……「ルヴァスール」ももう残っていない。そうだろう？";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "国家というものは人間と同じで、どれだけ手に入れても、さらに欲しがるものだ……そして実際、我々には新たな「ルヴァスール」がいるのだよ、副提督……";
			link.l1 = "本当か？それで、誰なんだ？";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "我々の旧知、ノエル・フォルジェ男爵だ。なぜ彼がここに来たのか覚えているか？";
			link.l1 = "ふむ……西インド貿易会社について何か言っていたな。パリはオランダと同じような組織を作ることにしたのか？";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "その通りだ。オランダ東インド会社のようにな。しかし、一から作り上げるのは非常に難しい。ご存知の通り、 スタイフェサントは何十年も様々な大陸と交易し、発達したエージェントのネットワークと強力な商船団を持っていた。 フランスにはそれがないし、知らなかったかもしれないが、シャルル、今、国王は深刻な資金不足に悩んでいる。 彼らは貿易をこの地に誘導することで本国の財政状況を立て直そうとしているが、我々 が直面することになる現実を理解していないのだ。\nイギリスとオランダ両国との競争、スペインの領土的野心、かつてないほど盛んになった海賊行為。 すべての商用フリュート船は海軍の護衛が必要で、さもなければ目的地にたどり着けない危険がある。我々 にはオランダ東インド会社のような強大な艦隊も、スペインの大ガレオンのような力もないのだ。";
			link.l1 = "「しかし、そのすべてを男爵に説明したのか？海賊のことも含めて？」";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "もちろん私がやりました。そして、あなたがルヴァスールを排除する任務を果たした後、 トルトゥーガから海賊を追放した件についてもです。海賊たちはそのことを決して忘れず、今も我々を恨んでいます。 私は様々な人物と会合を設け、不安を裏付ける証言も得ましたが、残念ながら男爵には何の効果もありませんでした。 彼は大臣たちによってここへ送り込まれ、彼らに借りがあるのです……そういうものなのですよ。";
			link.l1 = "ふむ……";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "それに、アルキペラゴに貿易会社を作り、パリから直接統制されるなんてことも――正直に言おう、副提督殿――私たちにはここでそんなもの必要ない。";
			link.l1 = "承知しました。";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "ご覧の通り、友よ、私はあなたに対して極めて正直に話しているのです……だからこそ、フォルジェ旦那がこの交易会社の設立を思いとどまってくれることを心から願っていたのですが……それは叶いませんでした。私の影響力はすべて男爵に使い果たしてしまいましたので、 今度はあなたがこの策謀に加わる必要があります。";
			link.l1 = "ふむ……ルヴァスールの時と同じか？";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "おお神よ、まさか、私を何だと思っているのだ、シャルル！？バロンは有力者であり、大蔵大臣の友人なのだぞ！それに、 彼を物理的に排除しても何の意味もない。どうせパリから新しい政治家が送り込まれるだけだ。そもそも、 そんな会社を設立するという考え自体を潰さねばならんのだ、わかるか、シャルル？バロンがフランスへ戻り、 「これは財政的に危険で、馬鹿げている」と報告するようにしなければならん……";
			link.l1 = "何かお考えですか、旦那？";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "残念ながら、違うのだ、シャルル。私もあらゆる手を尽くした。船も金もないと脅し、オランダ人や海賊の話もした……だが、まったく効果がなかった。";
			link.l1 = "どうやら、ただの言葉以上にもっと重大なものが必要なようだな。ふむ……海賊、というわけか？";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "なるほど、友よ、何か考えがあるのか？私には疑いはなかった。君の頭脳は実に素晴らしい。 あの男爵を説得してくれれば、君の父上の家がルーヴル宮殿にも劣らぬ財宝で満ちるほどの金を用意しよう。約束する、 シャルル。";
			link.l1 = "承知しました、シュヴァリエ。任務は明確です。";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "誓うよ、シャルル。もし成功すれば、絶対に後悔はさせない。\nそれは保証する。私が君を裏切ったことが、これまで一度でもあったかね、友よ？";
			link.l1 = "断じて違います、旦那。バロンはどこにいますか？";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "今はポルトープランスにいる。イスパニョーラの果てしない野や谷がとても美しい、と彼は言っていた……";
			link.l1 = "素晴らしい。では、これで失礼させていただきます。";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "まさにその通りだ。バロンからすべて聞いたよ。あれほどの経験をした後で……しかし、副提督、あなたほど物事を明確に説明できる者はいない！私もあなたから学ばねばなりませんな！";
			link.l1 = "私はあなたから多くを学びました、シュヴァリエ。";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "友よ、私は君に借りができた。君のご尊父には生涯必要なものはすべて揃えさせると約束しようし、 君の家もこの州で一番、いやフランスでも屈指の邸宅にしてみせる。それに加えて、君には十万ペソ支払おう――これで海賊への借金も返せるだろう…";
			link.l1 = "それは素晴らしいことですね、旦那！";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "あなたのために特別な贈り物も用意しておいた。あなたがこの品の価値、 そして私の感謝の誠意をきっと理解してくれると信じている！さあ、副提督シャルル・ド・モール、 私の個人的なマルタ騎士団の儀礼用剣を贈呈しよう！この貴重な武器は、あなたの制服によく似合うはずだ！ もしパリに戻ることを決めたなら、ノエル・フォルジェ男爵が国王にあなたを紹介すると約束している――その際は、ぜひ制服を着て、この素晴らしい剣を携えて盛装で臨むとよい！フランス海軍では、 さらに栄光ある出世の機会があなたを待っているぞ！";
			link.l1 = "この剣は美しさにおいて比類がありません！ありがとうございます、旦那、 私にはこのような栄誉はもったいないことでございます…";
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			Log_Info("You've received the Maltese Sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "そうだ！そして、ここにいる間に大きな変化が待っているぞ。良い変化だ。シャルル・ド・モール副提督、 君をサン・マルタン総督に任命する！";
			link.l1 = "ははっ！今の言葉、聞き間違いじゃねえか？";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "そうだ、友よ。今やお前はサン・マルタンの総督だ、あれほど熱心に守ってきたその地のな。";
			link.l1 = "シュヴァリエ、どうかこの名誉はお断りさせてください。\n私はこの貧しい島一つに縛られたくはありません！それに、こうした内政の問題も……私の本分ではございません！";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "私は君の拒否を受け入れないよ。友よ、恐れることはない、これまで通りの生活ができる。 面倒な事務は現職の代理総督が処理する。君が事実上の総督となるのだ。シャルル、 なぜ君がサン・マルタン統治者に任命されたのか、分からないのか？今こそ絶好の機会だ、 誰も疑問を持たない時だからな。私の部下の一人をあそこに総督として置く必要がある、分かるだろう？\n";
			link.l1 = "「塩鉱山か？」";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "もちろんだ！そして二つ目の朗報だが、これからは毎月十五日に鉱山の利益とドイリーの交易からの分け前が入る。 君の不労所得は月十万ペソになるぞ。";
			link.l1 = "ははっ！それは嬉しい知らせだ！ありがとう、シュヴァリエ。さて、もしそこに縛り付けられることがないなら、 総督職を引き受けよう。\nそれで、もし私がフランスへ航海したくなったらどうなる？";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "決心したら――君は行くことになるし、私は非常に残念だが、君の代わりを探すしかない。しかし、それだけではない。 ここに君の父上からの手紙がある。見てみなさい。";
			link.l1 = "「父からですか？嬉しいです！…承知しました、旦那、それで決まりですね。もう行ってもよろしいでしょうか？手紙を読みたいのです…私への新しい任務はありませんか？」";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "今はまだです、総督。でも仕事を見つけたら、あなたのところへ伺う方法は知っています。幸運を祈ります、シャルル！";
			link.l1 = "「あなたにも、シュヴァリエ！」";
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = "くそっ、なんてこった！これでまた問題が増えたじゃないか。\nお前がやったのか、シャルル？正直に言え。これは事故だったのか？";
			link.l1 = "さて、何かがおかしくなったようだ……";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "くそっ、なんてこった！これでまた問題が増えたじゃないか。バロンはとんでもなく厄介な場所で死んでくれたもんだ！ お前、本当にあいつの死に手を貸してねえだろうな？";
			link.l1 = "何をおっしゃいます、シュヴァリエ！？もちろんそんなことはありません！";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "くそっ、なんてこった！これでまた問題が増えたじゃないか。お前、 本当にあいつをこの世から送り出す手助けなんかしてねえだろうな？";
			link.l1 = "何をおっしゃいます、シュヴァリエ！？もちろんそんなことはありません！";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "よろしい。さて、友よ、すべてが台無しになったわけではないかもしれんな。熱病は熱病だろう？ 新しい監察官が省から来るまでは、ここを片付けて、客人たちをしっかり武装して迎えるとしよう……さて、シャルル、今はすべての連絡先を閉じる必要がある。理由はわかってくれるだろうな？";
			link.l1 = "もちろんです。";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "よろしい。さて、友よ、すべてが台無しというわけでもなさそうだな。カリブ海での戦いは覚悟の上だろう？ 省から新しい監察官が来るまで、ここで混乱を片付けて、客人たちを万全の備えで迎えよう……さて、シャルル、今はすべての連絡先を閉じる必要がある。理由はわかっているだろうな？";
			link.l1 = "もちろんです。";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "よろしい。さて、友よ、すべてが台無しになったわけではなさそうだな。海賊は所詮、海賊だろう？ 省から新しい監察官が来るまでは、ここを片付けて、しっかり武装して客人を待つとしよう……\nさて、シャルル、今はすべての連絡先を閉じる必要がある。我が意図は理解してくれるだろうな？";
			link.l1 = "もちろんです。";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "いずれにせよ、友よ、お前はできる限りのことをやった。それだけでも十分だ。運命が我々 を引き合わせてくれたことを嬉しく思う。お前の地位はそのままだし、 フランスでは素晴らしい出世が待っていると確信している。そして、そろそろパリへ戻る時だと思う。\nほら、これはお前の父上からの手紙だ。受け取れ。";
			link.l1 = "父ですか？それは何より嬉しいことです！…わかりました、旦那。接触は一切なし、完全な秘密、そしてできるだけ早くパリへ向かうのですね。 もう行ってもよろしいでしょうか？手紙を読みたいのです…";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "行きなさい、シャルル。幸運を祈る！";
			link.l1 = "「あなたにも、シュヴァリエ！」";
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = "まさにその通りです。あなたほど物事を明快に説明できる者はいません、副提督！ 私もあなたからその技を学ぶべきですね！！";
			link.l1 = "私はあなたから多くを学びました、シュヴァリエ。";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "友よ、君には借りができた。君のご尊父には生涯必要なもの全て、これから必要となるもの全てを必ず用意しよう。 そして君の家族の屋敷も、この地方で最も立派なものに――いや、フランスでも屈指の邸宅にしてみせる。\nさらに、君には十万ペソを支払おう――これで旅費は十分に賄えるはずだし、君がしっかりと休養を取れることを願っているよ。";
			link.l1 = "それは嬉しい知らせです、旦那！";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = "どうしてこんなことをしたの、シャルル！どうして私にこんな仕打ちを！？";
			link.l1 = "「ゴホン…」";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "私にはわかっているんだ！お前がやったんだ！とぼけるな！お前の協力がなければ、 バロン・フォルジェは鉱山の管理人からの報告書も、鉱山の場所も、 ピーター・スタイフェサントの書類すら受け取れなかったはずだ。そこにお前の名前はなかったが、断言しよう、 私は確信している――お前だ。なぜだ、シャルル…？ただ答えてくれ…なぜなんだ？ミシェルか？百万ペソか？ルヴァスールか？それとも総督の地位か？";
			// belamour legendary edition -->
			link.l1 = "我々の最初の出会いを覚えていますか、シュヴァリエ？私を従わせたあの日のことを。百万ペソを脅し取ったことも。\nいつか立場が逆転すればいいと、ただそれだけを願っていました。もうあなたに言うことはありません。";
			link.l1.go = "patria_prison_2";
			link.l2 = "ルヴァスールのためだ。百万の借金なら、まだ理解できる。俺は働き、殺し、稼ぎ、奪ったが、 その損害はすべてお前に償った。それでもお前には足りなかったんだな。お前は、シュヴァリエ、 俺を王冠に逆らう自殺同然の任務に送り込んだ――自分の権力をさらに強めるために！お前の裏切りには答えが必要だった。そして、その答えを受け取ったはずだ！";
			link.l2.go = "patria_prison_2";
			link.l3 = "野心ですよ、シュヴァリエ。この奇妙な新世界で、私はすでにできる限りのことを成し遂げてきました。 総督の地位は私にとってふさわしい目標に思えたのです。あなたから多くを学びました。さようなら！";
			link.l3.go = "patria_prison_2";
			link.l4 = "正直言って、私自身もよく分かりません。もしかすると、 男爵と彼の祖国への忠誠心に感銘を受けたからかもしれませんね。\nいずれにせよ、これからはこの件についてじっくり考える時間がたっぷりありますよ。さようなら！";
			link.l4.go = "patria_prison_2";
			// <-- legendary edition
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			SetTimerCondition("PZ_NormanBackToStreets", 0, 0, 1, false);	//Вовзращаем Акулу или Тиракса в Шарптаун
			// ставим сразу прерывание, чтобы потом по тысячу раз не копировать
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang") || CheckAttribute(pchar, "questTemp.PZ.LongwayTorero") || CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))
				{
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1 = "location";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1.location = "Charles_town";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition = "PZ_AfterPoincyLongwayDialog";
				}
			}
			
			if (!CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva")) 
			{
				dialog.text = "会えて嬉しいよ、シャルル。君の活躍は耳にしている。見事な働きだ！";
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "「それだけではございません、閣下。」";
					link.l1.go = "PZ_2";
				}
				else
				{
					link.l1 = "今すぐ兄を釈放するための書面による命令をいただけますか？";
					link.l1.go = "serve";
				}
			}
			else 
			{
				dialog.text = "ごきげんよう、シャルル。入ってくれ、もうすでに知らせは受けている。";
				link.l1 = "ご存知と？何かの間違いでございましょう、閣下。私は任務の無事完了をご報告に参りましたが、 ご機嫌がすぐれないご様子ですね。";
				link.l1.go = "PZ_PoincyAngry1";
			}
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube");
		break;
					
		case "PZ_2":
			dialog.text = "そうか？どういう意味だ、船長？";
			link.l1 = "ルヴァスールを生け捕りにして、あなたのもとへ連れてくることに成功しました。\n用が済み次第、彼をあなたの前に連れて来るよう命じます。";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "そんなことが可能だとは夢にも思わなかった！本当に見事な働きだ、シャルル！君の名高い兄上でさえ、 これ以上はできなかっただろう。君のお父上もきっと誇りに思うだろう、友よ。";
			link.l1 = "ご親切なお言葉、ありがとうございます、フィリップ様。";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "PZ_5":
			dialog.text = "よくやった、シャルル。私はお前に満足しているぞ。";
			link.l1 = "今すぐ兄を釈放するための書面による命令をいただけますか？";
			link.l1.go = "serve";
			LAi_SetHuberType(npchar);
		break;
		
		case "PZ_PoincyAngry1":
			dialog.text = "もしかすると、君が兄上とは違う人物だということを考慮すべきだったかもしれんな――軍人でもなければ、密偵でもなく、繊細な作戦の経験もまだない。トルトゥーガの街中で兵士たちと堂々 と戦うべきではなかったのだ。調査が入るだろうし、私についてもだ。君も分かるだろうが、相手は手厳しい連中だぞ。";
			link.l1 = "失礼いたします、シュヴァリエ。ご存知の通り、ルヴァスールは戦わずして身を引くような男ではありませんでした。";
			link.l1.go = "PZ_PoincyAngry2";
		break;
		
		case "PZ_PoincyAngry2":
			dialog.text = "確かに、だが…いや、何でもない。初めての作戦にしては悪くない。王室監査官とその護衛が公式査察中に襲撃されたと報告しよう。";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
			{
				link.l1 = "閣下、お役に立てるなら、ルヴァスールをお連れできます。私と部下たちは、彼の手下が街中で我々を捕えようとした後、 人気のない場所で運良く彼を捕まえました。";
				link.l1.go = "PZ_PoincyAngry3";
			}
			else
			{
				link.l1 = "今すぐ兄を釈放するための書面による命令をいただけますか？";
				link.l1.go = "serve";
			}
		break;
				
		case "PZ_PoincyAngry3":
			dialog.text = "何だと、シャルル？もう一度言ってみろ。";
			link.l1 = "フランソワ・ルヴァスールは今まさに私の監禁室におります、フィリップ様にお引き渡しする準備ができております。";
			link.l1.go = "PZ_PoincyAngry4";
		break;
		
		case "PZ_PoincyAngry4":
			dialog.text = "先ほど言ったことはすべて忘れてくれ。私は明らかに感情的になりすぎた。見事な働きだ。君の名高い兄上でさえ、 これほどのことはできなかったかもしれないな。";
			link.l1 = "「ありがとうございます、シュヴァリエ。」";
			link.l1.go = "PZ_PoincyAngry5";
		break;
		
		case "PZ_PoincyAngry5":
			dialog.text = "君には大きな将来性がある、友よ。君の才能がもっと国のために活かされればと願っている。しかし、 これからはもう少し……慎重に行動してほしい。私たちの仕事はたいてい繊細な対応が求められるのだ。\nああ、もう一つ伝えておきたいことがある。";
			link.l1 = "「はい、ご閣下？」";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
