// Ян Свенсон - пиратский барон Западного Мэйна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson")) {
				if (pchar.questTemp.HelenDrinking.Result == "won") {
					dialog.text = "ああ、シャルル。来てくれてありがとう。ヘレンと一緒に過ごしてくれて感謝してるんだ。 あの子には傷を癒す時間が必要だったし、君も楽しく過ごせたと聞いたぞ、ははっ！くそ、俺まで嫉妬しちまうぜ！";
					link.l1 = "怒ってないのか？あの樽のことや…他のいろいろについても？";
					link.l1.go = "after_drinking";
				} else {
					dialog.text = "ああ、シャルル。来てくれてありがとう。ヘレンと一緒に過ごしてくれて感謝しているんだ。 あの娘は傷を癒す必要があったし、君も楽しい時間を過ごしたと聞いたよ、はは！カルタヘナでの幸運を祈っているぜ！";
					link.l1 = "ああ、昨日はすべてうまくいって本当に良かったわ。また会いましょう、ヤン。";
					link.l1.go = "exit";
				}
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson");
				break;
			}
		
			if(CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga_Late")) // отсекание при провале по времени
				{
					dialog.text = "「ああ、友よ」 "+pchar.name+"！お会いできて嬉しいです！何かご用でしょうか？";
					link.l1 = "ちょっと様子を見に寄っただけだ。";
					link.l1.go = "exit";
					if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
					{
						if (GetDataDay() == 14 || GetDataDay() == 28)
						{
							link.l2 = "「ヤン、アイアンウッドを買いたいんだ。」";
							link.l2.go = "trade_bakaut";
						}
					}
					break;
				}
				if(pchar.questTemp.Saga == "svenson")
				{
					dialog.text = "「どうなさいましたか、旦那？」";
					link.l1 = "お力をお借りしたいのです、フォレストデビル。";
					link.l1.go = "saga";
					break;
				}
				if(pchar.questTemp.Saga == "svenson1")
				{
					dialog.text = "あはは、友よ "+pchar.name+"「！何か知らせか？」";
					link.l1 = "俺は絞首人から面白いことをたくさん聞き出すことができたぜ。";
					link.l1.go = "saga_11";
					break;
				}
				if(pchar.questTemp.Saga == "svenson2")
				{
					dialog.text = "「それで、」 "+pchar.name+"「グラディスと話したか？」";
					link.l1 = "ああ、そうだ。ヤン、ちょっとこれを見てくれ……この羊皮紙の切れ端について何かわかるか？";
					link.l1.go = "saga_17";
					break;
				}
				if(pchar.questTemp.Saga == "helena1" || pchar.questTemp.Saga == "helena2" || pchar.questTemp.Saga == "svenson_wait")
				{
					dialog.text = "「まだ新しい話は何もないぜ」 "+pchar.name+"。しかし、俺はこの問題の解決策に取り組んでいるところだ。後でまた来てくれ。";
					link.l1 = "わかった、ヤン。また後で会おう。";
					link.l1.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests") // старт трех квестов баронов
				{
					// первая проверка времени. Свенсон очень недоволен растяпством ГГ. Счищаем Элен, к Свенсону доступ закроем
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = ""+pchar.name+"、お前には心底失望したぞ。私はお前がもっと真面目な男だと思っていたが、結局ただの愚かな坊やだったとはな。 今まで一体どこで何をしていたんだ？お前がどこかで何をしていたかも分からんうちに、 イギリス人どもがイスラ・テソロを奪いやがった！\n私の計画はすべて台無しだ！正直なところ、お前の存在なんてほとんど忘れていたし、これからも思い出したくもない。 さっさと消え失せろ！";
						link.l1 = "信じられない！";
						link.l1.go = "saga_l1";
					}
					else
					{
						dialog.text = "「そこにいたのか」 "+pchar.name+"…少し俺たちの窮地について考えてみたんだ。計画とまでは言えねえが……";
						link.l1 = "話を聞こう、ヤン。";
						link.l1.go = "saga_25";
					}
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests_1") // идут три квеста баронов
				{
					dialog.text = "調子はどうだ？何か俺に手伝えることはあるか？";
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "after_marlow")
					{
						link.l3 = "黒い牧師と話をしたんだ。残念ながら、その会話の結果、また君の助言を求めて戻ってきてしまったよ。お手上げなんだ。 ";
						link.l3.go = "shark_hunt_2";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "LSC" && !CheckAttribute(pchar, "questTemp.Saga.BaronReturn"))
					{
						link.l3 = "ディオスを見つけて、楽しくおしゃべりしたんだ。\n彼はいろいろ面白い話をしてくれたけど、残念ながら核心には触れなかったよ。";
						link.l3.go = "shark_hunt_7";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "third_teleport")
					{
						link.l3 = "ああ、ヤン。話したいことが山ほどあるけど、全部語ったら夜が明けてしまうから、手短にするわ。";
						link.l3.go = "return_LSC";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "shamane" && !CheckAttribute(npchar, "quest.shamane"))
					{
						link.l3 = "ジャスティス島でナサニエル・ホークを拾った。今は俺の船に乗ってるぜ。";
						link.l3.go = "nathaniel";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "treatment")
					{
						link.l3 = "ネイサン・ホークをミスキート族の村に降ろしてきた。 そこではスネークアイという名のシャーマンが治療してくれるそうだ。 彼はネイサンの健康を回復させると約束してくれた。";
						link.l3.go = "nathaniel_2";
					}
					link.l4 = "今のところ特に話すことはないよ。ちょっと様子を見に寄っただけさ。";
					link.l4.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "fail_centurion") // провал - потоплен Центурион
				{
					dialog.text = "「何か新しい知らせはあるか、」 "+pchar.name+"？調子はどうだ？";
					link.l1 = "ああ、これ以上悪くなりようがないよ。俺はあれだけ苦労したのに……ジャックマンを突き止めて、鞘も捨てて、あいつをとんでもない馬鹿みたいに沈めちまった。しかも、 船室にあったかもしれない物も全部一緒にね。これじゃシャークの汚名を晴らす手がかりも、 バルバゾンに罪をなすりつける証拠も何も残っちゃいない。もう、どうしようもない気がするよ、ヤン。";
					link.l1.go = "saga_f_1";
					break;
				}
				if(pchar.questTemp.Saga == "calendar") // квесты баронов завершены
				{
					// вторая проверка времени. Отбираем Элен, со Свенсоном нейтральные отношения - ну не выщло и не вышло, хоть попытались. Данни и Натана - в Марун-Таун
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "あなたの英雄的な活躍は聞いたぜ！ダニーが簡単に説明してくれたんだ。ちなみに、今じゃ俺たち友達さ。 それにナサンもすっかり変わったぜ！自分の“センチュリオン”を見た瞬間、あいつの落ち込みは全部吹き飛んじまった。\nでも、悪い知らせがあるんだ。 "+pchar.name+"。俺たちはあまりにも時間を無駄にしたせいで、シャープの遺言に対する相続権はとうの昔になくなっちまったし、 イスラ・テソロもイギリスの軍事基地になっちまった。ルヴァスールの件でこれ以上お前を助けることはできねえよ。"link.l1 ="まったく言葉も出ません……これだけ苦労したのに、全部無駄だったなんて。\n本当に、どうしようもないのでしょうか？";			dialog.text = "お前の武勇伝は全部聞いてるぜ！ダニーから説明も受けたしな。ちなみに、俺たちはもう仲直りしたんだ。 ナサンのことなんて、きっとお前はもう分からないだろうな。あいつ、自分の“センチュリオン”を見た瞬間、文句なんて悪い夢みたいに忘れちまったよ…";
						link.l1 = "ネイサンが元気になったのか？それは嬉しい知らせだ！";
						link.l1.go = "saga_26";
					}
					break;
				}
				if(pchar.questTemp.Saga == "mine") // рудник взят
				{
					dialog.text = "「さあ、どうぞ。」 "+pchar.name+"！さて、今伝えたいことがあるんだ。";
					link.l1 = "やあ、ヤン。私はとても嬉しいよ！何か知らせがあるのかい？いい話だといいんだけど？";
					link.l1.go = "saga_32";
					break;
				}
				if(pchar.questTemp.Saga == "mine_1") // рудник взят совместно
				{
					dialog.text = "「はい、どうぞ。」 "+pchar.name+"！休めたか？さて、また壮大な冒険に出る準備はできたってことでいいんだな？";
					link.l1 = "やあ、ヤン。ああ、準備はできている。";
					link.l1.go = "saga_32a";
					break;
				}
				if(pchar.questTemp.Saga == "late_l3") // провал по времени у адвоката
				{
					dialog.text = "「何か新しい知らせは」 "+pchar.name+"？調子はどうだ？";
					link.l1 = "ああ。状況は本当に最悪だよ。必死に戦ったけど、結局負けてしまったんだ。覚えているだろう、 シャープの遺言には期限があった。それが切れて、今やイスラ・テソロはイギリス軍の基地になってしまった。 もう望みはないよ、ヤン。";
					link.l1.go = "saga_l3";
					break;
				}
				if(pchar.questTemp.Saga == "bakaut") // пришёл от адвоката за деньгами
				{
					dialog.text = "「ごきげんよう。」 "+pchar.name+"！朗報だぜ：評議会が開かれて、コースト同盟の新しい頭領が決まったんだ。";
					link.l1 = "こんにちは、ヤン。君のことを嬉しく思うよ。";
					link.l1.go = "saga_44";
					break;
				}
				if(pchar.questTemp.Saga == "sellbakaut" && GetSquadronGoods(pchar, GOOD_SANDAL) >= 1) // отдает бакаут
				{
					dialog.text = "「さて、」 "+pchar.name+"？ムリガンに追いついたのか？";
					link.l1 = "俺がやったんだ。お前の鉄木を盗んだのはあいつだ。";
					link.l1.go = "saga_55";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut") && GetNpcQuestPastDayParam(npchar, "bakaut_date") >= 1) // за деньгами за бакаут
				{
					dialog.text = "「いつも通り時間通りだな。」 "+pchar.name+"。君が持ってきてくれた鉄木は売ったよ。";
					link.l1 = "素晴らしい。いくら稼いだんだ？";
					link.l1.go = "saga_57";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut_sum")) // сам продал бакаут
				{
					dialog.text = "「さて、」 "+pchar.name+"？モリガンに追いついたか？";
					link.l1 = "俺がやったんだ。お前の鉄木を盗んだのはあいつだよ。たまたま、あいつの買い手にも出くわしたぜ。 オランダの軍の指揮官だった。俺がその品をそいつに売ったんだ。";
					link.l1.go = "saga_59";
					link.l2 = "やったよ。無理やりあいつに貨物室を見せさせようとしたんだ……そしたら小競り合いになって……もうモリガンはいない。だが、貨物室には黒檀とマホガニー以外、何も見当たらなかったぜ。";
					link.l2.go = "saga_59_1";
					break;
				}
				if(CheckAttribute(npchar, "quest.jessika")) // информация о Джессике
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"。何か新しいことはあるか？";
					link.l1 = "ヤン、ちょっと話したいことがあるんだ。エレンの母親、ベアトリスの過去を調べていたら、 君がよく知っている人物に偶然行き当たったんだ。私が聞いた限りでは……";
					link.l1.go = "saga_62";
					break;
				}
				if(pchar.questTemp.Saga == "lastpages") 
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"。調子はどうだ？その顔を見る限り、祝福を述べてもいいのかな？ ";
					link.l1 = "ああ、やっとこの混乱を解決できた。エレンはイスラ・テソロの全権利を手に入れたんだ。 もう二度と誰もカリブ海兄弟団の聖域に手を出すことはない！";
					link.l1.go = "saga_82";
					break;
				}
				if (pchar.questTemp.Saga == "end") sTemp = "Oh, my friend "+pchar.name+"! Pleased to see you! What brings you here?";
				else sTemp = "Anything else, "+pchar.name+"?";
				dialog.text = sTemp;
				link.l1 = "いや、ヤン。今のところ何もない。";
				link.l1.go = "exit";
				if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
				{
					if (GetDataDay() == 14 || GetDataDay() == 28)
					{
						link.l2 = "ヤン、君のアイアンウッドを少し買いたいんだ。";
						link.l2.go = "trade_bakaut";
					}
				}
				NextDiag.TempNode = "First time";
			}
			else
			{
				// заглушка Элен
				if(startHeroType == 4)
				{
					dialog.text = "ヘレン、やあ、愛しい人。何か知らせはあるかい？何か用があったのか？";
					link.l1 = "やあ、ヤン！ちょっと顔を見に寄っただけだよ。";
					link.l1.go = "exit";
					NextDiag.TempNode = "First time";
					break;
				}
				dialog.text = "何かお手伝いしましょうか？";
				link.l1 = "いいえ、大丈夫です。";
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;
		
		case "saga":
			dialog.text = "俺はお前を知ってるぜ、くそっ！お前はルンバを救い、 イギリスのコルベットの大砲に正面から立ち向かった勇敢な船長じゃねえか！会えて本当に嬉しいぜ！ ヘレンは俺にとって娘みたいなもんだ。今日から俺は一生お前に借りができたってわけだ。 好きにヤンでもスヴェンソンでも呼んでくれ。何か俺にできることはあるか？\n";
			link.l1 = "私はトルトゥーガ総督のルヴァスールを排除しなければなりません。\n彼の島にたどり着くのは簡単なことではないと分かっているので、あなたに助言を求めに来ました。";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "あらまあ、あなたが数年前にいてくれたらよかったのに！私も同じ冒険を企んでいたんだよ。 あいつがフランス人相手に全部ぶち壊してくれたせいで、俺たちの計画は台無しさ。だが、 あの頃は今とは全然違っていた。ブレイズは生きていたし、シャークには威厳があったし、 ネイサンがマルーンタウンで全てを仕切っていた……今じゃ何もかも変わっちまって、しかも良くなったとはとても言えねえ。俺たちのこと、兄弟団のこと、 何か知ってるかい？";
			link.l1 = "私はここに来たばかりなので、ほとんど何も知りません。\nあなたとジャックマンが評議会のメンバーだということ以外は。";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "ああ、あのジャックマンには我慢できない！あいつが来てから、俺たちの災難が始まったんだ。\n君の頼みは考えておくよ。今のところ思い当たることはないな。";
			link.l1 = "ジャックマンについて面白い話があるんだ。";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "ふむ。何だ？";
			link.l1 = "ジャックマンはグラディス・チャンドラーとその娘を探している。\nヒギンズと話した後、奴が探しているのはルンバじゃないかと思い始めた。\nどうやらグラディスはヘレンの実の母親ではなく、ショーン・マッカーサーと結婚する前はチャンドラー姓だったようだ。 ";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			dialog.text = "ちくしょう！それは悪い知らせだ。ジャックマンは今まで以上に強くなってやがる。しかも、 奴は一人で動いてるわけじゃなさそうな気がするんだ。背後に不吉な影がついてるぜ。もし本当にヘレンが奴に必要なら、 あの娘には守ってくれる奴が絶対必要だ。俺じゃもう歳を取りすぎて、その役目は無理そうだがな…";
			link.l1 = "それだけじゃねえ。ジャックマンは“ネプチューン”号の元甲板長、ヘンリー・ザ・ハングマンって野郎も探してるんだ。あいつはブッチャー船長の乗組員だったらしいぜ。";
			link.l1.go = "saga_5";
		break;
		
		case "saga_5":
			dialog.text = "カランバ！最悪の予感が的中しちまった！あの「ブッチャー」とその「ネプチューン」は、 かつてこの諸島全体を恐怖に陥れていたんだ。その頃はまだ兄弟団なんてなくて、みんながバラバラだった。 あの男は多くの悪事を働き、俺の大切な人も奴のせいで死んじまった。\n俺は奴に会う機会はなかった。「ネプチューン」はイギリスのフリゲートに沈められ、 ブッチャーはセント・ジョンズで処刑されたんだ。せいせいしたぜ！だが、 奴の運の良さと無謀な勇気に憧れる奴も多かった。\nジャックマン自身が「ネプチューン」の右腕であり、一等航海士だったんだ。驚いたか？元犯罪者どもが今や国の英雄だ、 全部クロムウェルのおかげさ。古き良きイングランドはどこへ行っちまったんだろうな。\nジャックマンの手下より先にヘンリー・ザ・ハングマンを見つけなきゃならねえ。もしまだ生きてりゃ、 あいつがこの謎を解く鍵を握ってるかもしれねえ。";
			link.l1 = "干し草の山から針を探す方がまだ簡単だろうな。少なくとも何か手がかりはあるのか？";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "ヘンリーがまだガキだった頃から知ってるぜ。カルタヘナの娼婦の息子で、スペイン人の血が半分入ってるが、 それはずっと隠してたな。母親は気性の激しい女だった！美人とは言えねえが、 あんなフラメンコを踊れる女は他にいなかったぜ。チカ・ゴンザレスとカスタネットの裸踊りは、 娼館中の連中が見物してたもんさ。可哀想にな、ひどい病気にかかって、蝋燭みてえに消えちまった。 それで俺はヘンリーにプロビデンスへ行くよう勧めたんだ。あいつはすぐに名を上げて、 ニコラス・シャープの親友トマス・ベルトロープの船に乗り込んだ。あの二人はエリザベス女王の最後の犬どもで、 いつも一緒に仕事してた。いい時代だったぜ！相棒が死んだ時、トマスはイングランドに帰った。仲間を連れてな。 でもヘンリーだけはカリブに残ったんだ。いろんな船長の下で航海してたが、ブッチャーが現れるまではな。ちなみに、 あいつが「ブッチャー」と呼ばれるのは、いつも手元にカトラスを置いてたからだぜ。";
			link.l1 = "「で、この情報から何が分かるんだ？」";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "もし絞首人が海賊から身を隠すと決めたなら、奴にとって最適な場所はスペインの町だろう。 特に友人や親戚がいるカルタヘナの自宅が一番だ。\nヘンリーはかなり信心深かったから、他の聖人の教会に行くとは考えにくい。\nきっと子供の頃からの名前、エンリケを今も使っているはずだ。";
			link.l1 = "ああ……獲物は少ねえが、何もないよりはマシだな。";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "探してみてくれ、シャルル！ヘンリーにスペインの血が流れていることを知っている者は少ないから、 ここでは少し有利だ。ルンバをお前の乗組員に引き入れる方法は俺が考えておく。あの娘は根性がある、 父親以外の下で仕えたことがないんだ。\nだが、彼女には船も仲間もなく、食っていくためには何かしなきゃならない。もちろん、 俺はこれまで通りグラディスを助け続けるが、ヘレンをいつまでもブルーヴェルドに置いておくことはできない。 お前にとって、あんな士官はきっと役に立つはずだ。ショーンは自分の知っていることをすべて彼女に教え、 まるで息子のように育てたんだ。\nお前みたいな船長の下に彼女がついてくれたら、俺も安心できるよ。";
			link.l1 = "ルンバは実に有能だと証明してくれた。俺の船にはああいう奴がもっと必要だぜ。だから、 もしお前がうまく説得できたら、俺が彼女を士官にしてやるよ。ただし、まずは彼女が本当は何者で、 なぜジャックマンが彼女を必要としているのか知りたいんだ。ドノヴァンと違って、 ジャックマンは彼女の魅力には興味がないんじゃないかと心配してる。だから俺がハングマンを探してみるが、 何も約束はできねえぞ。\n";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "では、素晴らしい。オランダ西インド会社の三ヶ月間有効な許可証を渡そう。そこに名前を書きなさい。 君の捜索にきっと役立つはずだ。その間に、ルヴァスールとトルトゥーガについて君が言ったことを考えておこう。";
			link.l1 = "本当にありがとう！この書類は俺にとって大助かりだぜ。そういうことなら、俺はこれからカルタヘナに向かうとするか。 ";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			DialogExit();
			GiveNationLicence(HOLLAND, 90);
			AddQuestRecord("Saga", "14");
			pchar.questTemp.Saga = "cartahena";//идем в Картахену
			pchar.quest.Saga_Gonsales.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales.win_condition.l1.location = "Cartahena_town";
			pchar.quest.Saga_Gonsales.function = "Saga_CreateGonsalesB";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			LocatorReloadEnterDisable("FortOrange_town", "reload6", true); // закрыть резиденцию Джекмана
			npchar.greeting = "svenson_3";
			
			AddQuestRecord("HelenDrinking", "1");
			pchar.questTemp.HelenDrinking.CanDrink = true;
			SetFunctionTimerConditionParam("HelenDrinking_NoVisit", 0, 0, 1, 24 - GetHour(), false);
			
			pchar.questTemp.Saga.HelenRelation = 0;
		break;
		
		case "saga_11":
			dialog.text = "ヘンリーは死んだのか？待て、お前が殺したのか？";
			link.l1 = "そんなに目を見開いて俺を見るなよ！俺は何も関係ねえ。あいつは自分の手で死んだんだ、 腐った良心とジャックマンへの恐怖に負けてな。あの老いぼれ海賊は心臓に問題があって、もう長くはなかったんだ。 俺が調べたのはこうだ……";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "お願いだ、教えてくれ！";
			link.l1 = "二十年前、ヘンリーはブッチャー船長の代理として、実の娘の養母に金貨の入った箱を届けるはずだった。\nこの養母がマクアーサー夫人であることに疑いの余地はまったくない。当時、彼女はチャンドラーという姓を名乗り、 ベリーズに住んでいた。\nだが、事情により絞首人はさらに一ヶ月もセントジョンズに足止めされ、ようやくベリーズに到着した時には、 スペイン人の襲撃で町は廃墟となり、グラディスおばさんとショーンはすでにあなたの保護下で去っていたのだ。";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "";
			link.l1 = "彼らはエレンを実の娘として偽り、自分たちの子として育てた。ヘンリーは彼らの行方を見失い、 ジャックマンの復讐を警戒して身を潜め、この二十年間ずっと怯えて暮らしていたらしい。\nどうやらジャックマンは自分の船長の娘を探しているようだ。だが、なぜなのかは私にも分からない。";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "もしかすると、誰かの命令を実行しているのかもしれない……";
			link.l1 = "疑わしいな。誰があいつに命令できるってんだ？ブッチャーは死んだ。公式書類でその死が確認されてる。何十人、 いや何百人もの人間がやつの最期を目撃したんだぜ。";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "もしかすると、これはヘレンの父親が誰かという問題じゃないのかもしれない。もしかしたら、 すべては彼女の実の母親に関わることなのかもしれない。もう誰だったのか察しはついているが、認めるのが怖いんだ。 しかし、グラディス！どうして彼女はこんなにも長い間、夫にさえ打ち明けずに秘密にしていられたんだろう！ ショーン・マッカーサーなら、きっと私に話してくれただろうに。私たちの間には、 分かち合わない秘密なんて一つもなかったんだ。";
			link.l1 = "これからグラディスと腹を割って話してくるぜ。あいつに口を割らせる手はもうあると思うんだ。\nまたな、ヤン！";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			DialogExit();
			pchar.questTemp.Saga = "gladis1";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_history";
			AddQuestRecord("Saga", "21");
		break;
		
		case "saga_17":
			dialog.text = "それ、どこで手に入れたんだ！？";
			link.l1 = "グラディスが俺にくれたんだ。『エレンの母親の遺産』だってさ。名前は知らないらしい。何となくだが、 これはただの紙切れじゃない気がするぜ。";
			link.l1.go = "saga_18";
		break;
		
		case "saga_18":
			dialog.text = "ヘレンの本当の母親が誰か、勘があるって言ったのを覚えているか？今は確信している。 彼女の名はベアトリス・シャープ。私の師であり友人でもあったニコラス・シャープの実の娘であり、 我らが同志団の創設者ブレイズ・シャープの公認の妹、そしてイスラ・テソロの共同所有者だったんだ。 ジャックマンが狙っているのはこの地図の断片さ。";
			link.l1 = "へえ、そう来たか！でも、なんで奴は島の地図の半分なんか欲しがるんだ？";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "この島はニコラ・シャープによって発見された。彼は島にイスラ・テソロと名付け、地図を作成し、 コネのあったプロビデンス島会社を通じて島の所有権を主張した。\nニコラは証言の中で、島は地図の両方の部分を持つ者だけが相続できると記した。これは争いを避けるためだった。 彼はその地図の部分をベアトリスと義理の息子ブレイズに託し、その後スペイン人の手によって悲劇的な最期を遂げた。";
			link.l1 = "なんてこった！こりゃ妙だな。";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "君の言う通りだ。あれは最善の策じゃなかった。そして抜け目のない公証人が、 もし相続人たちの死後一年以内に地図の両方の断片を誰も提出できなければ、 その島はイギリス王室のものになると付け加えたんだ。\n当時は誰もそんなことになるとは思わなかった。そして今、俺たちは自分たちの愚かさのツケを払っている。 ベアトリスは二十年前に死んだ。これだけの年月が経っても、彼女の墓と地図の断片がどこにあるのか、 いまだに分からない。ブレイズ・シャープもつい最近殺された。彼の断片も消えてしまった。\nもし誰も一年以内にイスラ・テソロの全体地図を当局に提出できなければ、シャープタウンはイギリスに取られてしまう。 あいつらは総督と守備隊を送り込んでくるだろうし、我々同志も終わりだ。";
			link.l1 = "俺たちはどうすればいいと思う？";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "こんなことは絶対に許せない。シャルル、君が必要だ、君にこの事態を阻止してもらわねばならない。そして、 俺がルヴァスールを排除する手助けができるのは、イスラ・テソロを掌握し、 シャーク・ドッドソンをバラナスの新たな首領に選出した後だけだ。彼こそ我々の中で最もふさわしい男だ。 君に同盟を申し出よう。\nそれから、ちなみにヘレンとも話した。彼女は君の船員になることを承諾したぞ。";
			link.l1 = "ヤン、君がこう出るなら、私に選択肢はない。家名の名誉を回復せずにフランスへ帰るわけにはいかないのだ。 そのためには、君の助けがあろうとなかろうとルヴァスールを排除しなければならない。無駄な死は望んでいないし、 できるだけ血を流さずにトルトゥーガを手に入れる方法を君が見つけてくれることを願っている。もっとも、 シャープ家の相続をめぐる曖昧な過去については、私自身で確かめてみたい気持ちもあるのだが。";
			link.l1.go = "saga_22";
		break;
		
		case "saga_22":
			dialog.text = "まともな話が聞けて嬉しいぜ！トルトゥーガをどう攻略するか、ちゃんと考える。約束するぜ。さあ、行くか？";
			link.l1 = "行こうぜ！また後で寄るからよ。今は、どこから問題に取りかかるか考えておけ。";
			link.l1.go = "saga_23";
		break;
		
		case "saga_23":
			dialog.text = "二、三日後にまた来てくれ。その頃には俺の計画も実を結んでいるはずだ。それと、 ヘレンを必ずお前の船に乗せてやってくれよ。あの娘は海が恋しくて仕方ないんだ。きっと忠実な助手になるし、 頼りにしても間違いないぜ。";
			link.l1 = "わかった、ヤン。今すぐ彼女を迎えに行くよ。";
			link.l1.go = "saga_24";
		break;
		
		case "saga_24":
			DialogExit();
			pchar.questTemp.Saga = "helena1";
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);//закрыть выходы из города
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			AddQuestRecord("Saga", "23");
		break;
		
		case "saga_25":
			dialog.text = "まず、シャークを探さなければならない。あいつは自分でルヴァスールを始末したがっていたし、 きっと妙案があるはずだ。もちろん、マーカスを説得してリーダーに就かせることもできる。 何しろ彼はコーデックスの管理者だからな。ただ、あいつが助けになるとは思えない。 ルヴァスールやトルトゥーガとの接触を意図的に断っている、信念の男だ。\nスティーヴンとその手下がどこに隠れているかは全く分からないが、彼のフリゲート艦『フォーチュン』 がプエルト・プリンシペで目撃された。ブラック・パスターことザカリー・マーロウが、 シャークの居場所を探す手がかりを教えてくれるかもしれない。\n次に、他のバロンたちの支持を得てドッドソンを選出しなければならない。そのためには、彼らのインディアンの破片――つまり投票権を集める必要がある。新しいリーダーは五つすべてを持たねばならない。 前のリーダーが死んだ場合はそうしろと、コードに定められているのだ。\n馬鹿げてる！法律を変える時だが、それができるのは新しいリーダーだけだ。俺の票はすでにある。 ブラック・パスターは誰がシャープタウンの椅子に座ろうが気にしちゃいないだろう。 ジャックマンが先に話をつけてなければいいがな。それから、 互いに大嫌いなタイレックスとジャック・バルバゾンも説得しなきゃならない。だが、 シャークがどうなったか分かるまでは、全部無意味だ。\n三つ目は、いつかジャックマンを殺して別の誰かにすげ替えなきゃならないってことだ。 あいつは俺たちと交渉する気なんてない。\nホークが死んじまったのは残念だ！みんなあいつを信頼していたし、彼の言葉は役に立ったはずだ。 マルーンタウンにはあれ以上のバロンはいない。ジャックマンがブレイズ殺しに関わっている可能性もあるし、 それが地図の第二の断片を見つける手がかりにもなる。ジェイコブは誰も信用せず、たぶん『センチュリオン』 の自分の船室に地図の一部を隠しているだろう。\nホークの家族は元々そのフリゲート艦を所有していたが、ジャックマンが奪い取った。ホークのバロン位と同じようにな。 もしジャックマンの手元に地図の第二の断片が見つかれば、スティーヴンを選ぶ大きな理由になる。 特にコードの管理者であるマーカス・タイレックスと、名誉にうるさい彼にはな。地図の両方の断片を手に入れたら、 ヘレンにイスラ・テソロの権利を返してやるつもりだ。\nだが気をつけろ。ジャックマンは黙ってお前の捜索を見ているような奴じゃない。";
			link.l1 = "さて……これからブラック・パスターに会いに行くところだ。彼について教えてくれ。";
			link.l1.go = "shark_hunt";
			pchar.questTemp.Saga = "baronsquests_1";
		break;
		
		case "shark_hunt":
			dialog.text = "あいつが何を考えてるかなんて、俺にはさっぱり分からねえ。時々、完全にイカれた奴に見えるが、まあ、 あれも巧妙な芝居だと思うぜ。それに、あいつの手下どもは、愛する牧師のためなら悪魔とでも戦う覚悟ができてるんだ。 \nやつらはキューバでスペイン異端審問所のすぐ近くに、なんかプロテスタントの一派を作っちまった。だから、 あそこで神学の話なんか始めるなよ。絶対に気に入られねえからな。";
			link.l1 = "それを考慮しておく……";
			link.l1.go = "shark_hunt_0";
		break;
		
		case "shark_hunt_0":
			dialog.text = "「そして、」 "+pchar.name+"：一分たりとも無駄にしないでくれ。本気で言っているんだ。遺言書の条項を覚えているだろう、 もし相続人が一年以内に島を請求しなければ、イスラ・テソロはイギリス王室のものになるってやつだ。 今は時間が俺たちの味方じゃない。前に君と会ったとき、残りはあと十一ヶ月ほどしかなかったんだ。\n";
			link.l1 = "覚えてるぜ、ヤン。\nお前の言う通り、時間は金だ。すぐに取りかかる！";
			link.l1.go = "shark_hunt_1";
		break;
		
		case "shark_hunt_1":
			DialogExit();
			AddQuestRecord("SharkHunt", "1");
			pchar.questTemp.Saga.SharkHunt = "begin";
			pchar.GenQuest.LigaAttack = "true"; // киллеры Лиги активированы
		break;
		
		case "shark_hunt_2":
			dialog.text = "ふむ……ザカリーはお前に何を話したんだ？";
			link.l1 = "失踪する前に、シャークが彼を訪ねてきて、ザカリーにフリゲート艦を担保として預け、 食料を積んだブリッグと引き換えにしたんだ。それからどこかキューバの北西に向かって出航していった。";
			link.l1.go = "shark_hunt_3";
		break;
		
		case "shark_hunt_3":
			dialog.text = "それは本当に怪しいな。続けてくれ。";
			link.l1 = "一ヶ月後、ドッドソンは戻らず、約定通り牧師が自分のものとしてフリゲート艦を手に入れ、 パターソンという男にかなりの高値で売り払った。\n我々の件については、ザカリーが「シャークはキューバの北西、 そう遠くない場所にあるという伝説のジャスティス島へ向かったかもしれない」と話していた。";
			link.l1.go = "shark_hunt_4";
		break;
		
		case "shark_hunt_4":
			dialog.text = "ジャスティス島の噂は聞いたことがある。白人も黒人も平等に仲良く暮らしている島があるなんて話だが、 そんなのは夢想家どもの戯言さ。\nだが、北西の方角に密輸業者の拠点がある可能性は否定できねえ。十年前までは、 あいつらのバルク船がよく外海で目撃されていたもんだ。食料と引き換えに、 いろんな品物をキューバに運び込んでいたのさ。";
			link.l1 = "食料と引き換えに財宝だと？牧師も牛肉を運ぶバッカニアたちの話をしていたな。まったく、矛盾だらけじゃないか。";
			link.l1.go = "shark_hunt_5";
		break;
		
		case "shark_hunt_5":
			dialog.text = "この噂にも必ず元があるはずだ。あの密輸業者やバッカニアたちの小舟が、 何か理由があってその地域へ向かっていたんだ。俺はシャークが若い頃の話をしてくれたのを覚えてる――海の真ん中にある難破船でできた奇妙な建物で、奴隷みたいなことをしていたらしい。\nもしかしたら、そこが俺たちの探している場所かもしれねえな。まあ、見当もつかねえが。とにかく、牧師の言う通りだ――あそこには何かがある。秘密基地か、シャークが行ったかもしれない島か。いいか、 サント・ドミンゴへ行ってホセ・ディオスという科学者を探せ。\nスペイン人の地図製作者だ。昔、俺が汚い悪党どもから助けてやったことがある。俺は知識人を尊敬してるんだ。 俺の名前を出せば、必ず力になってくれる。イスパニョーラへ行って、ディオスを探し、話を聞け。\nあいつはこの地方の地理を完璧に知ってる。もしディオスが助けてくれないなら、他に頼れる者はいねえぞ。";
			link.l1 = "よし、ヤン。いい考えだな。じゃあ、行ってくるぜ！";
			link.l1.go = "shark_hunt_6";
		break;
		
		case "shark_hunt_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "dios";
			AddQuestRecord("SharkHunt", "3");
		break;
		
		case "shark_hunt_7":
			dialog.text = "それは残念だ。ホセが手を貸してくれると期待していたんだが。";
			link.l1 = "俺もそれを期待してたんだが、残念だな。まあ、いつまでも自分を哀れんでても仕方ねえ。 もう少しこの件について考えてみるさ。さて、ヤン、教えてくれ、ホークはどうやって死んだんだ？";
			link.l1.go = "baron_return";
		break;
		
		case "baron_return":
			dialog.text = "誰も彼の死を目撃していないし、遺体を見た者もいない。数ヶ月前にふっと姿を消しただけだ。それ以来、 シャークの時と同じで、まったく消息がない。だがスティーブンと違って、ネイサンには身を隠す理由がなかった。 だから皆、彼はジャングルで死んだのだと思い込んだのさ。もしそれがなければ、 ジャックマンを後任に選ぶことにも同意しなかっただろう。";
			link.l1 = "ホークは一体何をジャングルでやってたんだ？";
			link.l1.go = "baron_return_1";
		break;
		
		case "baron_return_1":
			dialog.text = "私のせいだ、わしは年寄りの愚か者じゃ！新しく現れた盗賊どもと取引するよう、わしが彼に勧めてしまったんじゃ。 奴らが何者かも、誰が頭かも全く分からん。普段なら気にせんが、奴らは友好的なミスキート族を誘拐し始めた。 戦士長クンバナが戦争宣言をほのめかし、わしに助けを求めてきた。わしは介入せざるを得なかったのじゃ。\nホークは少数の部下と共にモスキート・コーストに上陸したが、見事に仕組まれた待ち伏せに遭い、敗北した。 どうやらホークたちがそこに上陸することを予想されていたようじゃ。ジャングルで他の者たちの遺体は見つかったが、 ホークの遺体はなかった。";
			link.l1 = "お前の目と鼻の先でいろんな悪さが起きてるじゃねえか！ ホークの手下どもは誰も盗賊どもをどうにかしようとしなかったのか？";
			link.l1.go = "baron_return_2";
		break;
		
		case "baron_return_2":
			dialog.text = "ジャックマンが誰よりも先に動いた。兄弟会の評議会で問題解決を申し出て、決断を下したんだ。 ミスキート族の失踪は止まったが、盗賊どもはそのまま居座り、目立たぬようにしていた。\nジャックマンは、「襲撃者を人質にしているわけじゃないから、兄弟会がやつらに宣戦布告する理由はない」と言った。 最初に手を出したのはホークの方で、我々の掟に従えば盗賊どもにも自衛する権利がある、と。みんな納得した。みんな……あいつを除いては。";
			link.l1 = "「誰以外の全員だ？」";
			link.l1.go = "baron_return_3";
		break;
		
		case "baron_return_3":
			dialog.text = "ネイサンには妻がいた。名はダニエル・ホーク、気の強い女だったぜ！ 旦那を失ったことを彼女が乗り越えられたとは思えねえし、最初から何かを疑ってホークを止めようとしたのも確かだ。 あいつらがそのことで大喧嘩したのを覚えてるが、あの二人にとっちゃそれが普通だったんだよな。\n";
			link.l1 = "「それで、今ダニエルはどこにいるんだ？」";
			link.l1.go = "baron_return_4";
		break;
		
		case "baron_return_4":
			dialog.text = "誰にも分からねえよ！ジャックマンが彼女をマルーンタウンから追い出したのは確かだ。 あいつは俺のところに顔を出すこともねえし、もともとお互い気に食わなかったが、年々 ますます意地悪になってきやがった。今じゃ俺のことを本気で憎んでるだろうな、 自分の不幸の元凶が俺だと思い込んでるんだろうから。たぶん自分でホークを探してるんだろうが、 女一人で何ができるってんだ、ズボン履いてサーベル持ってたとしてもな！ちなみに、 あいつはサーベルの腕前は相当なもんだ。もし出くわしても、試そうなんて思わない方がいいぜ。\nそれに、盗賊どもと話す意味もねえ。あいつらは立派な野営地を作って、武装もバッチリだ。元軍人らしく、 手際もいいしな。自分たちの縄張りには誰も入れさせねえ。昔はスペイン人がそこで金を掘ってたらしいが、 金が尽きて鉱山は捨てられた。あの野郎どもがそこで何してるのか、俺にはさっぱり分からねえよ。";
			link.l1 = "そうだな、ホークの死体を誰も見ていない以上、生きている望みはまだ残っている。\n神のみぞ知るが、もしかしたら彼をバロンの地位に戻すことだってできるかもしれねえ。";
			link.l1.go = "baron_return_5";
		break;
		
		case "baron_return_5":
			dialog.text = "ああ、そういうことだ。ほら、この手紙を受け取れ。スティーブ・ドッドソンに会ったら、すぐにこれを渡せ。 この手紙の内容があんたの身の安全を保証してくれる。まあ、念のためにな。";
			link.l1 = "ありがとう、ヤン。必ずそうするよ！";
			link.l1.go = "baron_return_6";
		break;
		
		case "baron_return_6":
			DialogExit();
			GiveItem2Character(pchar, "letter_svenson");
			AddQuestRecord("BaronReturn", "1");
			pchar.questTemp.Saga.BaronReturn = "begin";
			pchar.quest.Saga_DannyMeeting.win_condition.l1 = "location";
			pchar.quest.Saga_DannyMeeting.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.Saga_DannyMeeting.function = "Saga_DannyMeeting";
		break;
		
		case "return_LSC":
			dialog.text = "どうした、そんな浮かない顔して？疲れたのか？ラム酒でも一杯やるか？";
			link.l1 = "俺は別にかまわねえ…";
			link.l1.go = "return_LSC_1";
		break;
		
		case "return_LSC_1":
			LAi_AlcoholSetDrunk(pchar, 51, 5600);
			dialog.text = "ほら、一杯やれ。さあ、話せ。";
			link.l1 = "（飲みながら）ああ、ずっと良くなった……さて、ヤン、お前もブラック・パスターも正しかったぜ。ジャスティス島は本当に存在する。俺はそこに行ってきたんだ。 ";
			link.l1.go = "return_LSC_2";
		break;
		
		case "return_LSC_2":
			dialog.text = "あそこに密輸の拠点があるはずだって言っただろう！";
			link.l1 = "実際には、いかなる拠点も存在しないんだ。\nそしてカリブ中に広まっていた噂は嘘じゃなかった。あそこでは黒人も白人も本当に一緒に暮らしてる――必ずしも平和ってわけじゃなく、まるで犬と猫みたいにさ。\nそれに島自体が、数えきれないほどの難破船の寄せ集めでできてるんだ。";
			link.l1.go = "return_LSC_3";
		break;
		
		case "return_LSC_3":
			dialog.text = "信じられないぜ！ホセ・ディオスはお前の話にきっと興味津々だろうな、間違いねえ。ところで、 いつかあいつに会いに行ってやれよ。";
			link.l1 = "後で彼に会いに行くつもりだ。\n今はその時じゃない。\n今はもっと急ぎの用事があるんだ。\n島でネイサニエル・ホークを見つけた。";
			link.l1.go = "return_LSC_4";
		break;
		
		case "return_LSC_4":
			dialog.text = "ネイサンを見つけたのか？それは驚きだ！彼はどうしている？";
			link.l1 = "うーん……あいつは病気で、いつも酔っ払ってて、ひどく落ち込んでるんだ。";
			link.l1.go = "return_LSC_5";
		break;
		
		case "return_LSC_5":
			dialog.text = "くそっ、そりゃ気が滅入るぜ。奴はどこだ？お前の船か？";
			link.l1 = "いいや、彼は自分の船にいる。島の上だ。";
			link.l1.go = "return_LSC_6";
		break;
		
		case "return_LSC_6":
			dialog.text = "何？彼をここに連れてこなかったのか？なぜだ？";
			link.l1 = "奴に立ち向かう手立てがなかったからだ。俺は船もなく島までたどり着いたんだ。";
			link.l1.go = "return_LSC_7";
		break;
		
		case "return_LSC_7":
			dialog.text = "「くそっ、」 "+pchar.name+"、ラムを一杯しか飲んでないのに、まるで酔いつぶれたみたいに訳の分からないことを言ってやがるな。 まさかカリブ海を泳いで渡ったのか？それとも亀を足にくくりつけてきたのか？";
			link.l1 = "いや、泳いで来たんじゃない。ヤン、俺はナサンと同じように、本土のジャングルから直接この島に来たんだ、 魔法のインディアンの偶像を通ってな。\nこの話はもう何人にもしたし、俺が正気だって証明するのにも疲れた。だから言いたいのは一つだけだ――信じてくれ、いいな！？";
			link.l1.go = "return_LSC_8";
		break;
		
		case "return_LSC_8":
			dialog.text = "インディアンの偶像か？";
			link.l1 = "カリブにはククルカン像として知られる偶像が少なくとも三体存在する。ひとつはウェストメインのミスキート村の近く、 ひとつはジャスティス島沖の浅瀬の底、もうひとつはドミニカのカリブ村にある。\nこれらの偶像は、インディアンの魔術の力を借りて、人間を時空を超えて瞬時に転送することができるのだ。";
			link.l1.go = "return_LSC_9";
		break;
		
		case "return_LSC_9":
			dialog.text = "";
			link.l1 = "俺は三体の像をぐるりと回って、結局ミスキート村で旅を始めた場所に戻っちまったんだ。\n信じられねえなら、ダニエルを呼んでこようか？あいつ、自分の目で全部見てたぜ！";
			link.l1.go = "return_LSC_10";
		break;
		
		case "return_LSC_10":
			dialog.text = "ダニエル？ホークの女房か？あんたと一緒だったのか？";
			link.l1 = "一部はそうだ。彼女は自分で俺をブルーヴェルドで見つけて、ミスキート族の村まで連れていったんだ。 そこでシャーマンに会って、魔法の像のところへ送り出された。今は俺の士官の一人として働いてる、 もちろん一時的にな。";
			link.l1.go = "return_LSC_11";
		break;
		
		case "return_LSC_11":
			dialog.text = "私はまったくもって仰天しております。 "+pchar.name+"！まさにイギリス人が言う通りだな。お前は生まれつき恵まれてやがる、運のいい野郎だぜ！まあ、信じてやるよ、 信じがたいがな。だがネイサンの件は変わらねえ、あいつには助けが必要だ。";
			link.l1 = "それをやるつもりだ。今、ジャスティス島への遠征を準備している。これで必要なものはすべて揃った――島の座標と航路案内も手に入れた。";
			link.l1.go = "return_LSC_12";
		break;
		
		case "return_LSC_12":
			dialog.text = "素晴らしいですね。私に何かお手伝いできることはありますか？";
			link.l1 = "いいえ、結構です。しかし、一つ小さなことを言い忘れていました。ネイサンの他に、 島でシャーク・ドッドソンも見つけたんです。";
			link.l1.go = "return_LSC_13";
		break;
		
		case "return_LSC_13":
			dialog.text = "「じゃあ、やっぱりあそこに行ったんだな！さて、」 "+pchar.name+"、素晴らしい働きだったな。あっちでドッドソンはどうしている？もちろん、彼と話したんだろうな？";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				link.l1 = "彼と話しただけじゃなく、友達にもなったんだ。島へ戻るために必要な航海指示も彼がくれたんだよ。 スティーブンは自分の軍艦の船室をシャープタウンの邸宅と交換することに同意したんだ。";
				link.l1.go = "return_LSC_14";
			}
			else
			{
				link.l1 = "話はした、ああ、だが結局は無駄だった。俺が島に滞在している間に、スティーブンは殺されたんだ。彼のボースン、 チャド・キャッパーが仕組んだ陰謀が動き出した時にな。";
				link.l1.go = "return_LSC_17";
			}
		break;
		
		case "return_LSC_14":
			dialog.text = "ははっ！それで、どうやってシャークが軍艦の船長になれたんだ？";
			link.l1 = "その船は半世紀以上も終わらない「凪」にとらわれているんだ。彼は乗組員たちと一緒にあの島に閉じ込められている。 それで長い間カリブ海に姿を見せなかったのさ。\nまあ、すぐに彼をここへ連れてくるから、冒険の話は本人から聞けるぜ。";
			link.l1.go = "return_LSC_15";
		break;
		
		case "return_LSC_15":
			dialog.text = "それが待ちきれないぜ！これで状況が良くなり始めたな。俺たちは今、もっと強くなったってわけだ。 "+pchar.name+"。いつ島へ戻るつもりだ？";
			link.l1 = "今すぐだ。ちょっとだけここに来て知らせに来ただけさ、ダニエルが遠征の準備をしている間にな。\nあいつはナサンに会いたくてたまらないんだよ。それにさ、ヤン、あいつはそんなに嫌な女じゃないぜ。";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_16":
			dialog.text = "ああ？まあ、彼女について完全に正しかったわけじゃないかもな。いいだろう、 "+pchar.name+"、もうこれ以上引き止めはしない。行ってこい、幸運を祈る！帰りを楽しみにしているぞ。";
			link.l1 = "じゃあな、ヤン。";
			link.l1.go = "return_LSC_19";
		break;
		
		case "return_LSC_17":
			dialog.text = "チャド・キャッパーか？くそっ、あいつのことは知ってたぜ。スティーブンを殺したのか？あの野郎……";
			link.l1 = "カッパーは死んだ。だがスティーブンは戻らねえから、これからどうやって俺たちの政をまとめていくか考えねえとな。";
			link.l1.go = "return_LSC_18";
		break;
		
		case "return_LSC_18":
			dialog.text = "ははっ！それは残念だな……何を悩むことがある？タイレックスに兄弟団を率いてもらうしかねえだろ。\nそれに、ブレイズの後なら、掟の守り手であるタイレックスが一番の大物だぜ。\nだがまずはホークを連れ戻して、せめて切り札を一つ手に入れねえとな。\nお前はいつ島へ出発するんだ？";
			link.l1 = "今すぐだ。俺はちょっとだけここに来て知らせに来ただけさ、ダニエルが遠征の準備をしてる間にな。\nあいつはナサンに会いたくてたまらないんだよ。それにさ、ヤン、あいつ、そんなに嫌な女じゃないぜ。";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_19":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "return_LSC";
			// LSC ждёт своего героя!
			i = FindIsland("LostShipsCity");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			pchar.quest.return_LSC.win_condition.l1 = "location";
			pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.return_LSC.function = "LSC_ReturnCheckShips"; // проверка типов кораблей
			pchar.quest.return_LSC_attack.win_condition.l1 = "location";
			pchar.quest.return_LSC_attack.win_condition.l1.location = "Beliz";
			pchar.quest.return_LSC_attack.function = "LSC_ReturnJackmanAttack"; // атака наймитов Джекмана
			pchar.quest.return_LSC_main.win_condition.l1 = "Ship_location";
			pchar.quest.return_LSC_main.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.return_LSC_main.function = "LSC_ReturnMain"; // основная функция возвращения
		break;
		
		case "nathaniel":
			dialog.text = "彼の具合はどうだ？体調が悪いと言っていたな。";
			link.l1 = "ああ、その通りだ。俺は彼を連れてスネークアイという呪術師に治療してもらうためにミスキート村へ行くつもりだ。";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "それなら、ぐずぐずしてる暇はねえ！急げ、 "+pchar.name+"！ナサンをお前の呪術師に引き渡したら、すぐに俺のところへ戻ってこい。";
			link.l1 = "よし、ヤン。いい考えじゃねえか。";
			link.l1.go = "exit";
			npchar.quest.shamane = "true";
		break;
		
		case "nathaniel_2":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				if (CheckAttribute(npchar, "quest.shark")) //и на месте
				{
					dialog.text = "よろしい。スティーブンはすでに私のところに立ち寄ってくれた。これでようやく計画の話し合いを続けられるな。";
					link.l1 = "聞いてるぜ、ヤン。";
					link.l1.go = "barbazon";
				}
				else
				{
					dialog.text = "それはもちろん嬉しいけど、でもなぜドッドソンはまだ俺に会いに来てないんだ？どうした、島に置き去りにしたのか？";
					link.l1 = "ふむ……ナサンをスネークアイのところへ急いで連れて行こうとしていたんだ……";
					link.l1.go = "nathaniel_wait";
				}
			}
			else
			{
				dialog.text = "よし。シャークのことを思うと胸が痛むが、これも人生だ。だからタイレックスが代わりを務めることになる。さて、 これでようやく計画の話を続けられるな。";
				link.l1 = "聞いてるぜ、ヤン。";
				link.l1.go = "barbazon";
			}
		break;
		
		case "nathaniel_wait":
			dialog.text = "「……それでシャークを連れてくるのを忘れたのか？信じられねえな。」"+pchar.name+"！スティーブンを今すぐブルーヴェルドへ連れて行け！聞こえたか？行け！";
			link.l1 = "落ち着け、ヤン。俺が全部何とかする。";
			link.l1.go = "exit";
			NextDiag.TempNode = "nathaniel_wait_1";
		break;
		
		case "nathaniel_wait_1":
			if (CheckAttribute(npchar, "quest.shark"))
			{
				dialog.text = "スティーブンが私に会いに来てくれた。これでようやく計画の話し合いを続けられるな。";
				link.l1 = "聞いてるぜ、ヤン。";
				link.l1.go = "barbazon";
			}
			else
			{
				dialog.text = "「ああ、」 "+pchar.name+"…最近ラム酒を飲みすぎてるようだな。\n見てみろ、ろくなことにならねえんだ。\n最初は手が震え始めて、それから記憶が抜け落ちて、最後には黒い印をもらう羽目になるんだぜ…";
				link.l1 = "分かった、ヤン。すぐにスティーブンを連れてくるぜ！";
				link.l1.go = "exit";
				NextDiag.TempNode = "nathaniel_wait_1";
			}
		break;
		
		case "barbazon":
			dialog.text = "黒い牧師は非常に明確に言っている、彼が興味を持っているのはあの神学書だけだ。私は部下たちに探させているが、 誰かが見つけてくれるかもしれない。マーカス・タイレックスは問題ではない、彼を説得するのは難しくないだろう。 ジャックマンは君が彼を訪ねた後すぐにマルーン・タウンを離れた。彼はホークスのフリゲート艦『センチュリオン』 でどこかへ航海した。\n残るはバルバゾンだけだ――彼はジャック・ザ・カインドマンとも呼ばれている。彼を我々に協力させる方法を見つけなければならない。 今のところどうすればいいかは分からない。しかし一つだけ明らかなことがある――君は彼を訪ねるべきだ。";
			link.l1 = "バルバゾンについて教えてくれ。"; // Addon 2016-1 Jason пиратская линейка патч 17/1
			link.l1.go = "barbazon_1";
		break;
		
		case "barbazon_1":
			dialog.text = "秘密主義者だ。貧乏人のふりをしているが、実はカリブで一番の金持ちかもしれない。東側の密輸をすべて牛耳っている。 もしマーカスが立ちはだかっていなければ、バルバゾンがウィンドワード諸島の密輸を独占していただろう。 タイレックスは彼の喉に刺さった骨のような存在だ。\n評議会ではいつも口論しているが、バルバゾンには公然と戦争を仕掛ける度胸がない。彼が自分で言うように、 かつてダンケルクの海賊だったのかもしれないが、今ではむしろ金貸しにしか見えないな。";
			link.l1 = "一体どうやってあいつが男爵に選ばれたんだ？";
			link.l1.go = "barbazon_2";
		break;
		
		case "barbazon_2":
			dialog.text = "金だよ、旦那、すべてを支配するのは金だし、どこでも金を持つ者がルールを作るんだ。\nそれに、バルバゾンは儲かる違法な仕事を考え出すのが本当に得意なんだ。自分では手を汚さないが、 必ず取り分はもらう。\nだから、いつも彼の周りには勇敢だけど頭の弱いごろつきどもがたくさんいる。\nあいつがいなけりゃ、そいつらはみんな飢え死にするか、絞首台行きさ。";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "あいつを見るとマルクスを思い出す……ヤン、実はな……バルバゾンにどう接すればいいのか全く分からないんだ。お前が知らない問題があるんだよ。\n";
				link.l1.go = "barbazon_5";
			}
			else
			{
				link.l1 = "バルバゾンへはどう行けばいい？";
				link.l1.go = "barbazon_3";
			}
		break;
		
		case "barbazon_3":
			dialog.text = "太っ腹な仕事の情報を欲しがる間抜けの一人を装えばいいんだ。やつの取り分を騙し取ろうなんて考えるなよ。 慈悲深きバルバゾンは許さねえからな。";
			link.l1 = "言うまでもないことだ。俺があいつに関わるのは自分のためじゃねえ。とにかく、そろそろあいつに会いに行く時間だな。 ";
			link.l1.go = "barbazon_4";
		break;
		
		case "barbazon_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "1");
			pchar.questTemp.Saga.BarbTemptation = "begin";
			pchar.questTemp.Saga.BaronReturn = "barbazon";
			NextDiag.CurrentNode = "First time";
			// тут вычищаем квестовый мусор от LSC
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
			if (CheckCharacterItem(pchar, "letter_chad_1")) RemoveItems(pchar, "letter_chad_1", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "barbazon_5":
			dialog.text = "本当か？やってみろ。";
			link.l1 = "「チャーリー・プリンスって聞いたことあるか？」"; 
			link.l1.go = "barbazon_6";
		break;
		
		case "barbazon_6":
			dialog.text = "ああ、噂は聞いたぜ。そいつは少し前までマーカス・タイレックスの下で働いてたらしい。 短期間でかなりのことをやって、カルタヘナを襲って名を上げたって話だ。で、どうするんだ？";
			link.l1 = "こいつが俺だ。俺はチャーリー・プリンスだった。今は違う。わかったか？"; 
			link.l1.go = "barbazon_7";
		break;
		
		case "barbazon_7":
			dialog.text = "なんてこった！お前がチャーリー・プリンスなのか？とんでもねえ展開じゃねえか！ "+pchar.name+"、感心したぞ！なるほど、お前の腕力の秘密がわかった…だが、バルバゾンがこれにどう関係しているんだ？";
			link.l1 = "プリンスがバルバゾンを訪ねてみるのはどうだ、ヤン？.."; 
			link.l1.go = "barbazon_8";
		break;
		
		case "barbazon_8":
			dialog.text = "ふむ……なるほど。以前にもあいつとやり合ったことがあるのか？";
			link.l1 = "正確には違うぜ。バルバゾンの直々の命令で、イグナシオ・マルコって名の手下が俺に手を出そうとしたんだ。 あいつらの小競り合いの一環さ。"; 
			link.l1.go = "barbazon_9";
		break;
		
		case "barbazon_9":
			dialog.text = "奴はお前の顔を見たのか？自己紹介したのか？";
			link.l1 = "いいや。"; 
			link.l1.go = "barbazon_10";
		break;
		
		case "barbazon_10":
			dialog.text = "ここには特に問題はなさそうだな。それに、コルセアのチャーリー・プリンスの噂も聞いたことがあるが、 お前がその本人だとは、お前に言われるまで知らなかったぜ。";
			link.l1 = "バルバゾンに俺の正体が見抜けないとでも思ってるのか？"; 
			link.l1.go = "barbazon_11";
		break;
		
		case "barbazon_11":
			dialog.text = "彼があなたの顔を見たこともないのに、どうやってできるんだ？彼がやったのは、 マーカスの部下の一人を始末しろと命令を出しただけさ。";
			link.l1 = "ふむ……その点については君の言う通りかもしれないな。"; 
			link.l1.go = "barbazon_12";
		break;
		
		case "barbazon_12":
			dialog.text = "バルバゾンなしじゃ、この状況は乗り越えられねえ。\nあいつに会いに行け、だが気をつけろ。もしお前のことを見抜かれたら、すぐ逃げろ。その時は別の方法を考えるぜ。";
			link.l1 = "よし。そろそろ行くとしよう。あの野郎に会うのを楽しみにしてたんだ。"; 
			link.l1.go = "barbazon_13";
		break;
		
		case "barbazon_13":
			dialog.text = "とぼけたり、ジャックをからかったりするんじゃねえぞ。あいつは絶対に許さねえからな。 楽に金を稼ぎたがってる間抜けを演じろ。";
			link.l1 = "どうやら俺のお気に入りの役回りらしいな……さらばだ、ヤン！"; 
			link.l1.go = "barbazon_4";
		break;
		
		case "saga_26":
			dialog.text = "ああ。インディアンのシャーマンができる限りのことをしてくれたから、ホークはすっかり元気になったぜ。 もうダニーと一緒にマルーンタウンにいるはずだ、会いたけりゃ行って挨拶してこいよ。あいつら、 お前に会えたらきっと大喜びだろうさ。";
			link.l1 = "必ず様子を見に立ち寄るよ……ヤン、シャープの地図の後半部分を見つけたんだ！ジャックマンの船室にあったんだよ。 これでエレンのイスラ・テソロの権利を証明するのにもう困ることはないさ。";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			dialog.text = "よし、それを見せてくれ。\nやはり俺たちの推理は正しかったな。ブレイズを殺したのはジェイコブだった。 これでシャークの名についた汚名はきっちり晴らさなきゃならねえ。証拠の件となると、もっと慎重に扱う必要がある。 十分に考え抜いた上で動かないといけねえな。";
			link.l1 = "もう一つだ、ヤン。これを見てくれ。このメモもジャックマンの持ち物の中にあったんだ。";
			link.l1.go = "saga_28";
		break;
		
		case "saga_28":
			RemoveItems(pchar, "letter_parol", 1); // удалить записку
			dialog.text = "さて、見てみようか…はは、だからジャックマンの言うことを盗賊どもが聞いて、ミスキート族の誘拐をやめたのか！ 他にこうなる道はなかったってわけだ！あの悪党め、すべて計画していて何歩も先を読んでいたんだな。";
			link.l1 = "ああ、ホークの手下たちがなぜ皆殺しにされたのかも納得だぜ。だが、俺には二つ分からねえことがある。まず一つ目は、 ジャックマンの仲間たちが鉱山で何をしているのか、そして二つ目は、こんな騒ぎが自分の縄張りで起きてるってのに、 なんであんたはそんなに落ち着いていられるんだ？\n";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "恥ずかしい……お前の言う通りだ。ジャックマンは本当にやりすぎた。あいつの手下どもが俺の縄張りで好き勝手する筋合いはねえ。 どうやらカリブの連中に、誰が相手か思い出させる時が来たようだな。";
			link.l1 = "ヤン、何を考えているんだ？";
			link.l1.go = "saga_30";
		break;
		
		case "saga_30":
			dialog.text = "過去を蘇らせるか……私は懲罰遠征を組織し、鉱山にいる盗賊どもを一人残らず始末するつもりだ。 今や奴らがジャックマンの手下である証拠もあるし、私の領地からこのクズどもを一掃せねばならん。\n"+pchar.name+"、素晴らしい働きだったな。そろそろ俺が動く番だ。お前は今はゆっくり休め。ホークスのところに行ってこい。 十日後に戻って来い！";
			link.l1 = "わかった、ヤン。やってくるぜ。言った通りの時間で戻るからな！";
			link.l1.go = "saga_31";
			link.l2 = "はっ！俺もこの戦いに参加したいんだぜ。なんで俺だけ休ませるつもりなんだ？";
			link.l2.go = "saga_31_1";
		break;
		
		case "saga_31_1":
			dialog.text = "許してくれよ、旦那。そろそろ俺も少しは働いて、お前さんには休んでもらう時かと思っただけさ。\nだが、それがお望みなら大歓迎だぜ！一緒に嵐に立ち向かおうじゃねえか！\n鉱山で見つけたものは、兄弟たちの掟どおり、俺たちの乗組員同士で平等に分け合おう。";
			link.l1 = "話は決まりだな、ヤン！いつ出航するんだ？";
			link.l1.go = "saga_31_2";
		break;
		
		case "saga_31_2":
			dialog.text = "三日後に部下を連れてモスキート海岸へ来い。\nその頃には俺の仲間も集めて、もう待ってるはずだ。\n遅れるんじゃねえぞ！";
			link.l1 = "よし、森の悪魔。お前と背中合わせで戦うのが待ちきれねえぜ！またすぐ会おう！";
			link.l1.go = "saga_31";
			npchar.quest.mine_tw = "true";
		break;
		
		case "saga_31": 
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if (CheckAttribute(npchar, "quest.mine_tw"))
			{
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1 = "location";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1.location = "Shore53";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2 = "Timer";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.hour  = sti(GetTime());
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.function = "Saga_MineBanditsPrepareAttack";
				SetFunctionTimerCondition("Saga_MineBanditsAttackOver", 0, 0, 4, false); // таймер
			}
			else SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 10, false); // таймер
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
		break;
		
		case "saga_32a":
			dialog.text = "素晴らしい。鉱山の謎の所有者、ローレンス・ベルトロープについて何か突き止めたぜ。";
			link.l1 = "それで、この女は誰だ？";
			link.l1.go = "saga_35";
		break;
		
		case "saga_32":
			dialog.text = "ジャックマンの手下どもから鉱山で無理やり吐かせたんだ。あいつらもなかなか手強かったが、 うちの連中も伊達に生きちゃいねえ。それに、お前が見つけたメモの合言葉を教えたら、やつらの警戒も緩んだ。 そんで鉱山に突入して、派手に見送ってやったぜ。\n";
			link.l1 = "お前が鉱山を奪ったのか？すげえじゃねえか！";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "これが「森の悪魔」が鈍ってきたなんて思ってる奴らへの教訓だぜ。ここ数年、俺は本当にだらけすぎてた。 その結果がこれだ！ジャックマンの野郎、俺の鼻先で悪だくみを進めてやがったんだ！";
			link.l1 = "あの鉱山で何を見たんだ？詳しく話してくれ！";
			link.l1.go = "saga_34";
		break;
		
		case "saga_34":
			dialog.text = "鉱山は確かにスペイン人によって放棄されたが、 しかしポートロイヤルのローレンス・ベルトロープが二束三文で買い取り、密かに採掘を続けていたんだ。 どうやらスペイン人は坑道を早まって捨てたらしい。というのも、俺たちは金そのものは見つけられなかったが、 つい最近まで金があったと証言する奴隷たちを何人も見つけたからな。\n";
			link.l1 = "ローレンス・ベルトロープ？聞いたことがねえな。誰だそいつは？";
			link.l1.go = "saga_35";
		break;
		
		case "saga_35":
			dialog.text = "彼はこの地の現地人で、トーマス・ベルトロープの息子だ。かつてはニコラス・シャープの義兄弟であり、 プロビデンス島会社の私掠船員だった。私自身もトーマスとはよく知り合いだったよ。\n一年前、ローレンスは再びカリブにやってきた。どうやらジャックマンは彼のために働いていたらしい。覚えておけ、 そして油断するなよ！";
			link.l1 = "「ジャックマンのあの手紙に書かれていた謎の“ボス”ってのは、ローレンス・ベルトロープだったのか……よし、その名前は覚えておくぜ。」";
			link.l1.go = "saga_36";
		break;
		
		case "saga_36":
			dialog.text = "もう一つ思い出したことがある。ちょっと変だがな。ブレイズが昔、廃坑になったスペインの金鉱の話をして、 その金をシャープタウンに投資するつもりだと言っていたんだ。でも、その鉱山の地図は、 妹がブッチャー船長と駆け落ちしたときに消えちまった。もしかしたら、 あれは俺たちの鉱山のことだったのかもしれねえな。\nまあ、昔のことだし、今さら大した違いはねえ……俺たちは評議会に対処しなきゃならねえ。お前、五つの欠片は全部集めたか？";
			link.l1 = "ああ。この四人だ：ネイサンエル、タイレックス、マーロウ、そしてバルバゾン。全員が同意したぞ。";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			sTemp = "Shark";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			dialog.text = "素晴らしい。選出に問題はないはずだ "+sTemp+" カリブ海兄弟団の長として、すぐに評議会の招集を手配しよう。";
			link.l1 = "じゃあヤン、これでひとまず全ての問題は片付いたと考えていいか？\nネイサンはマルーンタウンにいるし、ジャックマンは死んだし、兄弟団には新しい頭領もできた……\nそろそろ最初に戻って、つまりトルトゥーガを奪還する時じゃないか？";
			link.l1.go = "saga_38";
		break;
		
		case "saga_38":
			dialog.text = "「覚えている」 "+pchar.name+"、だがもう少し時を待つ必要があるんだ。それに加えて、シャープの遺産整理の期限も迫っているし、 その問題はご存知の通り、本当に早急に対処しなきゃならねえ。";
			link.l1 = "遺産に何の問題があるんだ？地図の両方の部分はもう手に入れてる。あとはそれを見せるだけで終わりじゃないか…";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = ""+pchar.name+"、今どき島を簡単に人に譲るなんてことはありませんよ。 たとえ遺言状のすべての条項を満たした正当な相続人であっても、です。 イギリス当局がこの島を強く欲しがっていることは、私もよく承知しています。\nドイル大佐が、自分たちのものだと考えている島を私たちが奪うのを黙って見ているとは思えません。それに、 あなたも私も、しばらくは目立たないようにしておくべきです。";
			link.l1 = "「それで、どうしろと言うんだ？」";
			link.l1.go = "saga_40";
		break;
		
		case "saga_40":
			dialog.text = "ポートロイヤルへ向かい、アルバート・ロクスリーという男を探せ。\nあいつはカリブ一の腕利き弁護士だ。\nいかがわしい案件にもすっかり慣れていて、高額な報酬さえ積めばどんな仕事でも引き受けるぜ。\n大食漢だが、その価値は十分ある。";
			link.l1 = "シャープの遺言には何か落とし穴があると思うか？";
			link.l1.go = "saga_41";
		break;
		
		case "saga_41":
			dialog.text = "私はそう思うだけじゃなく、確信している。役人と取引したことがあるか？やつらが何か欲しがれば、 魂まで引きずり出し、ちょっとした句読点の間違いまで指摘し、自分たちに都合よく全てを解釈して、 最後には盲目の子猫のように丸裸にされるんだ。\nだからこそ弁護士というものが生まれた。やつらの武器――言葉遊び、書類の山、屁理屈――で役人と戦うためにな。だからロクスリーのところへ行って、俺たちの利益を守るために雇ってくれ。 俺は選挙の方を片付ける。";
			link.l1 = "よし。これからポートロイヤルへ向かう。評議会が集まって選挙を開くまで、どれくらいかかるんだ？";
			link.l1.go = "saga_42";
		break;
		
		case "saga_42":
			dialog.text = "十日間だ。それより早くブルーヴェルドで俺を探そうなんて思うなよ。";
			link.l1 = "了解だ。じゃあ、ヤン、そういうことなら、また後で会おうぜ！";
			link.l1.go = "saga_43";
		break;
		
		case "saga_43":
			DialogExit();
			AddQuestRecord("Testament", "1");
			pchar.questTemp.Saga = "loxly"; // обновляем флаг
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			SetFunctionTimerCondition("Saga_GoldForLoxly", 0, 0, 10, false); // таймер
		break;
		
		case "saga_44":
			sTemp = "Steven Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = ""+sTemp+" 心からのご挨拶をお送りします。彼はいつでもイスラ・テソロの邸宅であなたにお会いできることを喜ぶでしょう。 機会があれば、ぜひお訪ねください。";
			link.l1 = "「念のため」 "+sTemp+" 新しい住まいから出てこないからな、ヤン、俺たちにはこれから少し仕事が待ってるぜ。";
			link.l1.go = "saga_45";
		break;
		
		case "saga_45":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "もうロクスリーには行ったんだろうな……";
			link.l1 = "ああ、あるよ。彼が俺たちの件を引き受けてくれたが、その代わりに山ほどの金貨を要求してきたんだ。 "+sTemp+" 前金でドゥブロンを払うんだ。前払いだぜ！それに、ヘレンの権利証明がどう進むかによって、 さらにもっと払わなきゃならねえ。あいつの話じゃ、金額は倍にも三倍にもなるってさ。";
			link.l1.go = "saga_46";
		break;
		
		case "saga_46":
			dialog.text = "はっ！まあ、あの老いぼれ野郎ならそれくらいやると思ってたぜ。あいつはハイエナみてえに、 何マイルも先の獲物の匂いを嗅ぎつけるからな。もちろん、今回は島まるごと一つの話だ。 アルベールが二百や三百で済ませるわけがねえ。ってことは、合計で金貨千五百枚くらいにはなるだろうな……";
			link.l1 = "「ヤン、それは大金だぜ！」";
			link.l1.go = "saga_47";
		break;
		
		case "saga_47":
			dialog.text = "お前の言いたいことは分かってるぜ。確かに、お前が自腹で全部払うような間抜けじゃねえってことも認めるさ。だが、 残念ながら今はそんな大金を隠してねえんだ。こういう出費も想定してたが、 あるろくでなしのせいで全部台無しになっちまったんだよ。";
			link.l1 = "何の話だ？";
			link.l1.go = "saga_48";
		break;
		
		case "saga_48":
			dialog.text = "聞いてくれ。たぶんもう知っているかもしれないが、うちの集落は半分合法、半分違法みたいなもんだ。 イギリス人が駐屯していて、俺たちはマホガニーをいい値段で卸してるんだ。だが、リグナムバイタ――お前も鉄木として知ってるだろ――っていう、とても重くて頑丈な木がある。\nあれは珍しいし、焼き入れした鋼でも加工が難しい。昔、マヤ・イッツァ族が恐ろしい棍棒をそれで作ってたって話だ。 鉄木は市場じゃ手に入らねえし、密輸品だと銀と同じくらいの値がつく。\nドイルの手下どもが時々来て、加工済みの分を安く全部買い取っていく。だが、 俺はいつも自分用に少しは確保しておくんだ。";
			link.l1 = "この木のことは聞いたことがあるぜ。火縄銃の弾も油っぽい木にタールみたいにめり込むらしい！その頑丈さなら、 鋼鉄の機械の歯車だって作れるって話だ。";
			link.l1.go = "saga_49";
		break;
		
		case "saga_49":
			dialog.text = "歯車のことはちょっと誇張してるが、他はまったくその通りだ。だから、 費用を見越して大量のアイアンウッドを用意しておいたんだが、数日前に誰かが俺の倉庫を空っぽにしやがった。 仲間の誰かだってのは分かってる。心当たりはあるが、確証はないんだ。";
			link.l1 = "ネズミどもは踏み潰してやる！お前が疑っているのは誰だ？";
			link.l1.go = "saga_50";
		break;
		
		case "saga_50":
			dialog.text = "ポール・モリガンだ。あいつの東インド船『オイスター』は昨日バルバドスへ向かった。 俺は積荷を確認する暇がなかったんだ。だが、どうせブリッジタウンには鉄木を持ち込まねえだろう。 ウィロビー卿のところには厳しい税関役人がいるし、鉄木はイギリス海軍にとって戦略的に重要な原材料だからな。\nもし本当にあいつが俺の鉄木を持ってるなら、ブリッジタウンに着く前に売りさばくはずだ。モリガンを途中で捕まえて、 積荷を調べられたらいいんだがな……";
			link.l1 = "昨日ブリッジタウンへ向かったと言うのか？まだ全てが終わったわけじゃない。俺が追いついてみせる。";
			link.l1.go = "saga_51";
		break;
		
		case "saga_51":
			dialog.text = "モリガンが裏切り者だった場合、どうすべきかは分かっているな。ただし、まずは奴の依頼主の名前を探り出せ。 その後は、貨物を依頼主に自分で届けてもいいし、俺のところに戻しても構わねえ。\nそれから「オイスター」号もブルーヴェルドに持ってこい。あれはいい船だ、俺が自分用に改装して使いたい。 お前も好きなだけ戦利品を取っていいぜ……もしモリガンが犯人じゃなかった場合は……いや、奴が俺の鉄木を盗んだ裏切り者だと俺は確信してる。";
			link.l1 = "時間を有効に使うぞ！";
			link.l1.go = "saga_52";
		break;
		
		case "saga_52":
			dialog.text = "もし自分でアイアンウッドを売るなら、ロクスリーのために金貨ドゥブロン1500枚を取っておいてくれ。残りは半分ずつ分けよう。これ、信用していいんだよな？";
			link.l1 = "もちろんだ。俺はネズミじゃねえ。";
			link.l1.go = "saga_53";
		break;
		
		case "saga_53":
			dialog.text = "疑いはない。幸運を祈るぞ、 "+pchar.name+"！今度こそ、運があなたに微笑みますように。";
			link.l1 = "ありがとう。また後で会おう！";
			link.l1.go = "saga_54";
		break;
		
		case "saga_54":
			DialogExit();
			pchar.questTemp.Saga = "molligan"; // обновляем флаг
			AddQuestRecord("Testament", "3");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			Saga_CreateMolliganInWorld(); // ставим корабль Моллигана на карту
		break;
		
		case "saga_55":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "やっぱりな。奴の船倉にはどれだけ積んでたんだ？";
			link.l1 = "見つけた "+FindRussianQtyString(sti(npchar.quest.bakaut))+" 「オイスター号」で。";
			link.l1.go = "saga_56";
		break;
		
		case "saga_56":
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp > 100)
			{
				dialog.text = "おおっ！そんなに倉庫に入ったことは今までなかったぜ。自分の手で大金を手に入れたやつがいるとはな。ありがとな、 "+pchar.name+"、あんたは本当に頼りになるな。すぐに品物を売ってくるぜ、もう買い手はついてるんだ。 明日には金を用意しておくからな。";
				link.l1 = "わかった。それじゃあ、これ以上邪魔しないよ。明日また会おう。";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 90 && iTemp < 101)
			{
				dialog.text = "ああ、もううんざりだ。小さいネズミめ！礼を言うぜ、 "+pchar.name+"、お前は本当に頼りになるな。すぐに品物を売ってくる、もう買い手はついてるんだ。明日には金を用意しておくぜ。";
				link.l1 = "わかりました。これ以上お邪魔しません。それでは、また明日。";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "おそらく、あいつはすでに積荷の一部を誰かに売りさばいたんだろうな、もっとあるはずだったからな。\nだが大したことじゃねえ、ほとんど取り戻せたからな。\n礼を言うぜ。 "+pchar.name+"「すぐに商品を売るぜ、もう買い手はついてるんだ。明日には金を用意してやるよ。」";
				link.l1 = "わかった。それ以上は邪魔しないよ。じゃあ、また明日。";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 50 && iTemp < 70)
			{
				dialog.text = "くそっ、あの野郎、もう荷のかなりを売りさばきやがったか……ああ、残念だな。まあいいさ。俺の手元にある分は売るぜ、もう買い手はついてるんだ。明日には金が手に入るさ。";
				link.l1 = "わかった。それ以上は邪魔しないよ。じゃあ、また明日。";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 20 && iTemp < 50)
			{
				dialog.text = "くそっ、なんてこった！あの野郎、もう積荷の半分以上を売りさばきやがった……ああ、残念だな。まあいいさ。手元に残った分は俺が売る。もう買い手は見つけてある。明日には金が手に入るぜ。";
				link.l1 = "わかった。それ以上邪魔はしないよ。また明日会おう。";
				link.l1.go = "saga_oust";
				break;
			}
			dialog.text = "俺は本当に運がねえな。あいつ、ほとんど全部売っちまった……ほら、このアイアンウッドはお前が持ってな。 "+pchar.name+"、好きにしろ。今や金を稼ぐ唯一の望みはお前だけだ。";
			link.l1 = "了解だ。わかった、自分で探すよ。これが初めてじゃないしな……じゃあな、ヤン。";
			link.l1.go = "saga_oust";
		break;
		
		case "saga_oust":
			if (CheckAttribute(npchar, "quest.bakaut"))
			{
				if (sti(npchar.quest.bakaut) < 20) DeleteAttribute(npchar, "quest.bakaut");
				else 
				{
					SaveCurrentNpcQuestDateParam(npchar, "bakaut_date");
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(npchar.quest.bakaut));
				}
				pchar.questTemp.Saga = "removebakaut";
			}
			int iUst = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == "Oyster") iUst = 1;
				}
			} // есть ли у нас Устрица
			dialog.text = "待て！「オイスター」を拿捕したのか？";
			if (iUst == 1)
			{
				link.l1 = "はい。今、彼女は港に停泊しています。ご要望通り、あなたのために係留しておきました。";
				link.l1.go = "saga_oust_yes";
			}
			else
			{	
				link.l1 = "いや、戦闘で船がひどく損傷したから、沈めるしかなかったんだ。";
				link.l1.go = "saga_oust_no";
			}
		break;
		
		case "saga_oust_no":
			dialog.text = "残念だな。しかし仕方ないさ。また後でな、 "+pchar.name+"!";
			link.l1 = "じゃあな、ヤン。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_oust_yes":
			dialog.text = "素晴らしい！この美しい船にふさわしい装備をしてやるぜ。あとで、 約束通りしばらくの間なら貸してやってもいいからな。たぶん二か月もすれば準備が整うだろう。";
			link.l1 = "よし。この船があれば、時には本当に役立つこともあるだろう……またな、ヤン！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_RemoveOuster");
			npchar.quest.ouster = "true";
			SaveCurrentNpcQuestDateParam(npchar, "ouster_date"); // через 2 месяца
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_57":
			int idlt;
			iTemp = sti(npchar.quest.bakaut)*30; // Ян за 1 шт бакаута даёт 30 дублонов
			if (iTemp > 1600)
			{
				idlt = makeint(iTemp-1500)/2; // доля Бонса :)
				dialog.text = "受け取った "+iTemp+" そのための金貨だ。千五百は弁護士への支払い分で、さらにお前のドゥブロン分け前もある―― "+idlt+"。はい、どうぞ。";
				link.l1 = "見事だ！これで安心してロクスリーへ出発できる。";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500+idlt);
				break;
			}
			if (iTemp > 1450 && iTemp <= 1600)
			{
				dialog.text = "それで千五百ドゥブロン受け取った。\n弁護士に払うにはちょうどいい額だ。\nほら、どうぞ。";
				link.l1 = "素晴らしい。これでロクスリーへ向かえるな。";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500);
				break;
			}
			dialog.text = "受け取った "+iTemp+" ドゥブロン金貨はこれだけだ。ほら、持っていけ。残りは自分で掘り出すんだな。";
			link.l1 = "まあ、一人でやるしかないなら、一人でやるさ。よし、ロクスリーに会いに行くとするか。";
			link.l1.go = "saga_58";
			TakeNItems(pchar, "gold_dublon", iTemp);
		break;
		
		case "saga_58":
			DialogExit();
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.bakaut");
		break;
		
		case "saga_59":
			dialog.text = "どうだ？それは面白いな。それで、あのオランダ野郎はいくら払うつもりなんだ？";
			link.l1 = "一人につき四十ドゥブロンだ。";
			link.l1.go = "saga_60";
		break;
		
		case "saga_60":
			dialog.text = "おっと！俺の買い手たちはもっと安く払うんだが……";
			link.l1 = "全体として、俺はロクスリーのために二千ゴールド手に入れたし\n "+sti(npchar.quest.bakaut_sum)*2+" その上にドゥブロン金貨もだ。";
			link.l1.go = "saga_61";
		break;
		
		case "saga_61":
			dialog.text = "よし。じゃあ、半分ずつ分けよう。";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.bakaut_pay = func_min(sti(npchar.quest.bakaut_sum), PCharDublonsTotal()); // дублоны в кармане
				link.l1 = "はい、どうぞ。持ってきたぞ "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "ドゥブロン金貨は船に置いてきた。ちょっと取りに行ってすぐ戻るよ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "saga_61_1":
			dialog.text = "ごきげんよう。どれくらい持ってきたのですか？";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.bakaut_pay = func_min(sti(npchar.quest.bakaut_sum), PCharDublonsTotal()); // дублоны в кармане
				link.l1 = "ほら、持ってきたぞ。 "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "俺の記憶はどうなってんだ！もうこのラムでふざけるのはやめ時だな。\nまたしてもドゥブロン金貨を自分の箱に置きっぱなしにしちまった。ちょっと急いで取りに行ってくるぜ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay": // оплата
			if (sti(npchar.quest.bakaut_sum) < sti(npchar.quest.bakaut_pay)) // полная сумма
			{
				npchar.quest.bakaut_pay = sti(npchar.quest.bakaut_sum);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.bakaut_sum)-sti(npchar.quest.bakaut_pay);
			npchar.quest.bakaut_sum = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.bakaut_pay));
			Log_Info("You have given "+sti(npchar.quest.bakaut_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "「ご苦労だった」 "+pchar.name+"！やっぱりあなたと関わるのはいいことだと改めて思うよ。";
				link.l1 = "やってみるよ、ヤン……";
				link.l1.go = "bakaut_done";
			}
			else
			{
				dialog.text = "素晴らしい。残りも持ってきてくれるか "+FindRussianQtyString(sti(npchar.quest.bakaut_sum))+" あとでドゥブロン金貨か？";
				link.l1 = "はい。そんな大量の金貨を一度に運ぶなんて無理だったんだ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay_wait":
			dialog.text = "それで、 "+pchar.name+"「で、俺のドゥブロンはどうなってる？」";
			link.l1 = "もう少し金貨を渡してやってもいいぜ。";
			link.l1.go = "saga_61_1";
		break;
		
		case "bakaut_done": // рассчитались
			dialog.text = "お前に提案があるぜ。儲かる買い手を見つけられたんだから、俺がアイアンウッドを売ってやってもいい。 前は一本につき三十ドゥブロンもらってたんだ。その値段で買いたいなら譲るぜ。 どうせなら他の奴よりお前に売りたいからな。";
			link.l1 = "どれくらい鉄木を売れるんだ？";
			link.l1.go = "bakaut_done_1";
		break;
		
		case "bakaut_done_1":
			dialog.text = "俺は大量に貯め込むのは避けてるんだ。モリガンの時は例外だったけどな。 地元の闇市の話なんて当局が聞いたら気に入らねえだろうからな。だから、こうしよう。毎月14日と24日にお前のためにアイアンウッドを25本ずつ取り置きしてやる。\n買いたいなら、ドゥブロン金貨750枚持ってきて、全部まとめて持っていけ。その日に来なかったら、他の客に売るぜ。こうすりゃ月に50本手に入るってわけだ。どうだ？";
			link.l1 = "話はまとまったな、ヤン！やろうぜ。さて、そろそろ俺は行く時間だ……";
			link.l1.go = "saga_oust";
			DeleteAttribute(npchar, "quest.bakaut_sum");
			npchar.quest.trade_bakaut = "true"; // генератор купли-продажи бакаута
			AddQuestRecordInfo("Unique_Goods", "1");
		break;
		
		case "saga_59_1": // укрысил у Яна - нет генератора на бакаут, потерял больше
			dialog.text = "ああ、じゃあ奴じゃなかったか、あるいはすでに鉄木を売り払ってしまったんだな……残念だ。まあ、今や弁護士に払う金を手に入れるにはお前だけが頼みの綱だ。";
			link.l1 = "その責任、俺が引き受けるぜ。これが初めてじゃねえからな。";
			link.l1.go = "exit";
			// Ян расстроен и забыл про Устрицу - так что и Устрицы тоже не будет
			DeleteAttribute(npchar, "quest.bakaut_sum");
		break;
		
		case "saga_62":
			dialog.text = "そうかい？それは面白いな。さあ、聞いてくれ。誰について話したいんだ？";
			link.l1 = "娘のことだ。名前は……ジェシカ・ローズだった。";
			link.l1.go = "saga_63";
		break;
		
		case "saga_63":
			dialog.text = "ふむ。我らが同胞団の新しい頭領が彼女について話したのか？";
			link.l1 = "ああ、そうだった。しかし、俺はベイカー――セントジョンズの昔の死刑執行人――から彼女のことを聞き出したんだ。同じ男がブッチャー船長を処刑したんだぜ。";
			link.l1.go = "saga_64";
		break;
		
		case "saga_64":
			dialog.text = "……そうか。ふむ。さて、最後にジェシカに会ってからもう二十年以上経つな。彼女について何か知っているのか？";
			link.l1 = "そうだな、彼女がどうやってブッチャー船長と一緒になり、二人で海賊稼業をしていたかは知っている。 彼がベアトリスのために彼女を捨てたこともな。後になって、彼女はジョシュア・リードビーター、 通称マスクと呼ばれる男の助けを借りて、その仕返しをしたんだ……";
			link.l1.go = "saga_65";
		break;
		
		case "saga_65":
			dialog.text = "";
			link.l1 = "それに、ヤン、お前には率直に言わせてもらうが、ジェシカに興味があったことも知っている。\nだからこそ、お前のところに来たんだ。\nジェシカは俺の捜索において重要な人物だ。\n俺の理解する限り、ベアトリス・シャープを殺したのは彼女で、嫉妬が原因だった。";
			link.l1.go = "saga_66";
		break;
		
		case "saga_66":
			dialog.text = "ほう、よく知ってるじゃねえか。そうさ、確かに俺はジェスに言い寄ってた。でも驚くことじゃねえ、 当時イスラ・テソロの海賊どもは二つの派閥に分かれてたんだ――ベアトリスを抱きたい奴らと、ジェシカを狙う奴らとな。\nあいつのことはよく覚えてる……美人だったよ、本当に美しかった！…";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Jess");
			NextDiag.TempNode = "saga_66a";
		break;
		
		case "saga_66a":
			dialog.text = "彼女は特別だった……それに、ジェスがベアトリスを殺した可能性もかなり高い。ブッチャーに『ネプチューン』号から追い出された後、 ジェスはきっと彼とベアトリスへの復讐しか考えていなかったはずだ。\nところで、ブッチャーがどうやってジェシカを始末したか知っているか？";
			link.l1 = "いや。バルバドスで彼女を降ろしたか、身代金目当てでどこかに監禁したかのどっちかだ。";
			link.l1.go = "saga_67";
		break;
		
		case "saga_67":
			dialog.text = "二つ目だ。あいつは彼女を信じられないほど侮辱したんだぜ。船室に閉じ込めてバルバドスまで連れてきて、 彼女の父親オリバー・ローズと交渉を始めて、結局は彼女を大量のドゥブロン金貨と引き換えに売り飛ばしたんだ……彼女があいつのためにしてきたことすべての後でな。";
			link.l1 = "ふむ。ネプチューン号がジョシュア・リードビーターから海賊に奪われた時、 ブッチャーが彼女の名誉を守ったと思っていたが……";
			link.l1.go = "saga_68";
		break;
		
		case "saga_68":
			dialog.text = "それも確かだ。しかし、彼女は彼にたっぷりと報酬も払った。ジェシカは何度もあのろくでなしの命を救ってやったんだ、 酒と女遊び、短気な性格で自分自身に招いた災難から引っ張り出してな。実のところ、 彼が繁栄する海賊として名声を得られたのも、すべて彼女のおかげだったんだ。";
			link.l1 = "ああ、ああ、あいつの「赤いお守り」な。そんな話は聞いたぜ。ブッチャーがジェスを蹴り飛ばした途端、 運もあいつを見捨てたってさ……";
			link.l1.go = "saga_69";
		break;
		
		case "saga_69":
			dialog.text = "もちろんだ。ジェシカがいなければ、彼はただの普通の海賊になってしまった、無鉄砲で勇敢ではあったがな。 だがジェシカは彼のそばにはいなかった。危険な作戦を立てるのはいつも彼女で、 彼はいつでも彼女の剣を頼りにできたんだ。\n確かに、ベアトリスもお行儀のいい娘じゃなかったが、ジェスには敵わなかった。ベアの魅力はまったく別物……彼女はブッチャーに逆らうという過ちを犯した。";
			link.l1 = "どこかでそれを聞いたことがあるような……";
			link.l1.go = "saga_70";
		break;
		
		case "saga_70":
			dialog.text = "すべての海賊がそう思っていたんだ、ブレイズ・シャープ――彼女の兄貴もな。あいつはブッチャーが大嫌いだった……だが、話をジェシカに戻そう。彼女が『ネプチューン号』に乗っていた間は、俺は彼女のことを考えることすら恐れたよ。 彼女は愛する船長のもとを絶対に離れなかっただろうからな。だが、 ブッチャーがあんな卑劣なやり方で彼女を追い出した時……\n俺はバルバドスに着いて、彼女と友達になった。彼女にとっては簡単なことじゃなかった。 海と危険な冒険を愛していたからな。あの退屈な植民地生活は彼女を蝕んでいた。それに、『ネプチューン号』 で働いていたせいで、カリブ海ではかなり悪名高い存在になっていたし、 ブリッジタウンの連中も彼女のことをブッチャーの共犯者だと考える理由があったんだ……";
			link.l1 = "「だが、奴らは何一つ証明できなかったんだ……」";
			link.l1.go = "saga_71";
		break;
		
		case "saga_71":
			dialog.text = "いや、だが誰も彼女と関わりたがらなかったんだ。ブリッジタウンでの地位にもかかわらず、 呪われているとみなされていた。俺だけがジェシカとあそこで三十分以上一緒に過ごした男だったと思う。\n俺は彼女に、西インディアへ一緒に来て新しい人生を始めないかと誘った。彼女がずっと望んでいた人生――海、船、航海、冒険だ。その頃にはもうブルーヴェルドで大きな事業を立ち上げていたから、 あのろくでなしのブッチャーより百倍は良いものを提供できた。でもジェスはひどく傷ついていた。 ブッチャーの裏切りと、その後の扱いを許していなかった。そして、あの時点でもまだ彼に未練があったんだと思う……どれだけ努力しても、彼女に過去を忘れさせることはできなかった。復讐の念に取り憑かれていたんだ。";
			link.l1 = "ああ、彼女のことは羨ましくないよ。かわいそうな娘だな……";
			link.l1.go = "saga_72";
		break;
		
		case "saga_72":
			dialog.text = "私も彼女に対して同じ気持ちを抱いていた。後になって、 彼女は古代インディアンのカルトや儀式に興味を持つようになった。それは、 ユカタンの奥地から捕らえられて地元のプランテーションに連れてこられたインディアンの魔術師がきっかけだった。 ジェシカはその男を買い取り、自分の屋敷に家を与えた。\n彼女はその魔術師と多くの時間を過ごし、「魔法的なインディアンの儀式に対する歴史的関心からだ」と言っていた。 ブリッジタウンの住民たちは心配し始め、とくに地元の牧師が気にかけていた。実のところ、 彼はジェシカに親切に接した数少ない人物の一人だった。\n牧師はよく彼女と話し、魔術師を追い出すように勧め、危険や異端審問の恐れを警告したが、 ジェシカを脅しても無駄だった。ある夜、何者かが魔術師の家に押し入り、彼を殺害した。\n同じ夜、二人の男がジェシカの寝室に押し入って彼女を襲ったが、彼らにとって事態は最悪だった――ブリッジタウンの誰も、ジェシカが炎の刃を持つ剣の使い手だとは知らなかったのだ。彼女は文字通り、 彼らをバラバラに斬り捨てた。";
			link.l1 = "ああ、もちろん……あの向こう見ずな女傑め！";
			link.l1.go = "saga_73";
		break;
		
		case "saga_73":
			dialog.text = "その後、町中が彼女を恐れるようになった。\nそして仮面の男が現れた。二人はすぐに出会ったのさ。";
			link.l1 = "記録によれば、「仮面」の正体は元『ネプチューン』号船長ジョシュア・リードビーターだ…";
			link.l1.go = "saga_74";
		break;
		
		case "saga_74":
			dialog.text = "そのことを知ったのは、ずっと後のことだった。仮面の到着から一週間後、ジェスは荷物をまとめ、俺に別れを告げて、 軍艦フリゲートで未知の海へと旅立っていった。彼女は二度と戻らなかった……ちょうどベアトリスがイスラ・テソロに戻らなかったように。\nそのすぐ後、セント・ジョンズでブッチャーが絞首刑にされた。彼をそこへ連れてきたのは仮面自身だった。しかし、 仮面もブッチャーより一日長く生き延びただけだった。";
			link.l1 = "ああ……うちのスティーブン・ドッドソンは見事だったな……";
			link.l1.go = "saga_75";
		break;
		
		case "saga_75":
			dialog.text = "ああ、そう聞いたよ。彼はベアトリスの仇を討った……そしてそれがジェシカの物語の終わりさ。 彼女はどこかの無人島でブッチャーの海賊たちとの小競り合いの中で亡くなったんだ。誰もその場所がどこかは知らない。 ブッチャーは死んだし、ジャックマンもハングマンも同じさ。";
			link.l1 = "そこが間違ってるぜ、ヤン。ブッチャーは生きてるんだ。";
			link.l1.go = "saga_76";
		break;
		
		case "saga_76":
			dialog.text = " 「なんだと！？そんなはずがない！あいつは絞首刑にされたんだぞ！」";
			link.l1 = "レイモンド・ベイカーの証言を読んでみろ。どんな物語より面白いぜ。";
			link.l1.go = "saga_77";
		break;
		
		case "saga_77":
			PlaySound("interface\important_item.wav");
			dialog.text = "見せてくれ…（読む）ふむ。信じられん！処刑は偽装だったのか！";
			link.l1 = "抜け目ないだろ？でも、それだけじゃねえ。お前はブッチャーを知ってる。だが、今の奴が誰かは知らねえんだよ。";
			link.l1.go = "saga_78";
		break;
		
		case "saga_78":
			dialog.text = "ああ？で、そいつは誰だ？";
			link.l1 = "ポートロイヤルから来たローレンス・ベルトロープ。鉱山の持ち主であり、 あのジャックマンの背後にいる謎めいた影そのものだ。俺はベイカーを通じてそれを知ったし、 ベイカーは仮面の男から聞き出したんだ。";
			link.l1.go = "saga_79";
		break;
		
		case "saga_79":
			dialog.text = "なんてこった！つまり、全部仕組んだのはあいつだったのか？まあ、いいさ……俺たちもブッチャーに向かうぜ。あの厄介者をどうやって倒すか考えてやる。簡単にはいかねえが、 あいつはいつもイギリス当局の庇護下にいるからな。\n";
			link.l1 = "奴の最期も近いぜ、ヤン。すぐに、あいつも自分の甲板長と航海士に会うことになるだろう。\nさて、話を聞かせてくれてありがとう。そろそろ俺は行く時間だ。";
			link.l1.go = "saga_80";
		break;
		
		case "saga_80":
			dialog.text = "今どこへ向かっているんだ？";
			link.l1 = "どこかの島だ。ジェスとベアトリスが死んだ場所、そして仮面の男がブッチャー＝ ベルトロープを襲った場所と同じだと思う。\nヘレンがシャープ家の一員だという証拠が必要で、それをそこで見つけられると期待している。";
			link.l1.go = "saga_81";
		break;
		
		case "saga_81":
			dialog.text = "「よし。さて、」 "+pchar.name+" 、幸運を祈るよ。戻ったら全部聞かせてくれ。";
			link.l1 = "ああ、わかったぜ。またな、ヤン！";
			link.l1.go = "saga_81a";
		break;
		
		case "saga_81a":
			DialogExit();
			LAi_SetHuberType(npchar);
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(npchar, "quest.jessika");
			npchar.quest.jessika_peace = "true"; // атрибут на мирное разрешение после боя
		break;
		
		case "saga_82":
			dialog.text = "「よくやった」 "+pchar.name+"。お前は不可能を成し遂げたんだ。俺たちカリブの兄弟団のバロン全員が、お前に借りができたぜ。";
			link.l1 = "ああ、勝利への道は狭かった。もし事前にこれほど耐えねばならぬと知っていれば…";
			link.l1.go = "saga_83";
		break;
		
		case "saga_83":
			dialog.text = "エレンはどうしている？彼女は何をするつもりなんだ？";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "彼女は俺の船で一緒に過ごしている。もうただの士官じゃねえんだ。島の支配権はバラナスの頭領に渡るし、 彼女が得るのは地代だけさ。それはヘレン自身が決めたことだ。";
				link.l1.go = "saga_84";
			}
			else
			{
				link.l1 = "彼女は自分の手で男爵領を継ぐためにイスラ・テソロへ旅立った。";
				link.l1.go = "saga_85";
			}
		break;
		
		case "saga_84":
			dialog.text = "「さて、」 "+pchar.name+"…おめでとうございます！多くの男たちがあなたの立場を夢見てきました。エレンが彼女にふさわしい男を選んでくれて、 私は嬉しいです。彼女の人生の伴侶として、あなた以上の候補者はいませんよ。";
			link.l1 = "ありがとう、ヤン！さて、トルトゥーガとルヴァスールについての話に戻りたいんだ。";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "ありがとう、ヤン！";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_85":
			dialog.text = "素晴らしい。彼女にはこの資格があるよ。新しい海賊同盟の長が、きっと彼女の仕事を助けてくれるだろう。 彼女は才能があって聡明な娘だし、物事をすぐに覚えて何でも学べる。ありがとう。 "+pchar.name+"「ヘレンは俺にとって娘のような存在だ。そんな素晴らしい未来が彼女に開けたこと、本当に嬉しいぜ。」";
			link.l1 = "どういたしまして、ヤン…。さて、トルトゥーガとルヴァスールについての話に戻りたいんだが。";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "どういたしまして、ヤン。";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_86":
			sTemp = "Shark Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = "「あなたが留守の間、」 "+sTemp+" そして私はすでにこの件について話し合い、ルヴァスールの処分に関して意見が一致している。\nイスラ・テソロへ向かい、我々の新しい頭領に会え。計画の詳細を話してくれるし、 できる限りの協力もしてくれるだろう。";
			link.l1 = "ついに火薬の匂いが嗅げるぜ！\nぐずぐずしてる暇はねえ、俺はイスラ・テソロへ向かう！";
			link.l1.go = "saga_87";
		break;
		
		case "saga_87":
			dialog.text = ""+pchar.name+"「ちょっと待ってくれ。ヘレンと海賊同盟の件で助けてくれたお礼に、いくつか贈り物があるんだ。\nまず一つ目は、極東から来たサラセンの魔法のお守りだ。その力で船の規律が強化されることは、俺自身が確かめたぜ。 さあ、受け取ってくれ。」";
			link.l1 = "ありがとうございます！";
			link.l1.go = "saga_88";
		break;
		
		case "saga_88":
			GiveItem2Character(pchar, "talisman4");
			Log_Info("You've received the 'Janissary' amulet.");
			PlaySound("interface\important_item.wav");
			dialog.text = "二つ目は、ただの昔の冒険の記念品だ。評議会を説得して、 石のかけらを風に投げるという馬鹿げた伝統をやめさせたんだ。もう必要ない。君にあげよう。 もしかしたら何か役に立つかもしれないな。";
			link.l1 = "破片の使い道？ふむ、わからないな……でも、記念品としてならありがたくもらうよ！";
			link.l1.go = "saga_89";
		break;
		
		case "saga_89":
			GiveItem2Character(pchar, "splinter_js"); 
			GiveItem2Character(pchar, "splinter_nh"); 
			GiveItem2Character(pchar, "splinter_mt"); 
			GiveItem2Character(pchar, "splinter_zm"); 
			GiveItem2Character(pchar, "splinter_jb"); 
			Log_Info("You've received five ornamental pattern fragments");
			dialog.text = "「まあ、自分の友達のことを忘れるなよ」 "+pchar.name+"。ブルーヴェルドに停泊したら俺のところに寄ってくれ。腰を落ち着けてラムでも飲もうぜ。 お前に会えるのはいつだって嬉しいんだ。";
			link.l1 = "間違いないな、ヤン。これで俺たちにも語れる思い出ができたじゃねえか？ははっ！さて、とにかく俺はそろそろ行くぜ。 ";
			link.l1.go = "saga_90";
		break;
		
		case "saga_90":
			dialog.text = "「幸運を祈る」 "+pchar.name+"!";
			link.l1 = "じゃあな……";
			link.l1.go = "saga_91";
		break;
		
		case "saga_91":
			DialogExit();
			pchar.questTemp.Saga = "end";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock")) AddQuestRecord("Saga", "26_1");
			else 
			{
				AddQuestRecord("Saga", "26");
				pchar.questTemp.Terrapin = "islatesoro";
			}
			CloseQuestHeader("Saga");
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
	// --> провалы Саги
		case "saga_f_1":
			dialog.text = "ああ……本当に俺たちの計画は台無しになっちまったな。これじゃ、俺たちが望んだ奴をバラナスの頭に据えることもできねえ。 ジャックマンが死んだのはまあいいとしても、残念ながら俺の策はもう通用しねえ。\n結局、バラナスの頭はいつものやり方で選ぶしかねえし、どんな展開になるかは神のみぞ知るってわけだ……";
			link.l1 = "それは残念だな。実に残念だ。どうやらヘレンは遺産を受け取れずに終わりそうだな。";
			link.l1.go = "saga_f_2";
		break;
		
		case "saga_f_2":
			dialog.text = "「はい。」 "+pchar.name+"。それに、俺も本当はお前がトルトゥーガを手に入れるのを手伝いたいんだが、 今となってはどうすればいいのか分からねえ。たぶん、俺にできることは何もないだろう。\nどうやら自分自身の力と戦う腕だけを頼りにするしかなさそうだな。";
			link.l1 = "もう他に手はなさそうだな……よし、ヤン、俺はこれからどうするか考えてくるぜ。また後でな……";
			link.l1.go = "saga_f_3";
		break;
		
		case "saga_f_3":
			dialog.text = "「寄っていけ」 "+pchar.name+"。お会いできていつも嬉しいです。";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			CloseQuestHeader("Testament");
		break;
		
		case "saga_l1": // проход первый - отбираем Элен и закрываем вход к Свенсону
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l1";
			pchar.quest.Saga_Late_1.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_1.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_1.function = "Saga_HelenaTalk";
			pchar.questTemp.Saga.Jackman = "true";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
		break;
		
		case "saga_l2": // проход второй - отбираем Элен, Натана и Данни в Марун-Таун, чистим квестовый лут
			dialog.text = "しかし、あいにく今さら何をしても手遅れだ。\nイスラ・テソロは正式にイングランド王室の支配下に移された。\n今では駐屯部隊までいる。\nこれはバッカニア同盟にとって大きな打撃で、残念だが立ち直ることはできそうにない。";
			link.l1 = "なんてひどいんだ……ああ、もっと早く動くべきだったな。そうすれば、全部うまくいったはずだ。よし、ヤン、 これからどうするか考えてくる。また後で会おう……";
			link.l1.go = "saga_l2_1";
		break;
		
		case "saga_l2_1":
			dialog.text = "「寄っていけ」 "+pchar.name+"。お会いできていつも嬉しいです。";
			link.l1 = "...";
			link.l1.go = "saga_l2_2";
		break;
		
		case "saga_l2_2":
			DialogExit();
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "letter_parol", 1);
			RemoveItems(pchar, "map_sharp_full", 1);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l2";
			pchar.quest.Saga_Late_2.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_2.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_2.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
		
		case "saga_l3":
			dialog.text = "ああ……本当にひどい敗北を喫したんだ。\nしかも最悪なのは、あと一歩で勝利だったってことさ。カランバ！どうしてこんなことになっちまったんだよ、なあ。 "+pchar.name+"？あんなに頑張って、あれほど尽くしたのに……なんてひどい運命なんだ！";
			link.l1 = "これをやらかしたのは俺という間抜けだ。もっと早く動くべきだった。俺のせいでヘレンは遺産を失うことになる。\nそしてトルトゥーガの計画も、もう実現しやしねえ。";
			link.l1.go = "saga_f_2";
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
	// <-- провалы Саги
		
	//-----------------------------------генератор торговли бакаутом--------------------------------------------
		case "trade_bakaut":
			if (CheckAttribute(pchar, "questTemp.UpgradeBakaut"))
			{
				dialog.text = "よし、構わねえよ。俺の倉庫には125ユニットあるぜ。値段は覚えてるだろ、一つにつき3,150だ。";
				if (PCharDublonsTotal() >= 3150)
				{
					link.l1 = "よし、取引成立だ。ほら、これだ。3150ドゥブロンだぞ。";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "なんてついてねえんだ。金は船に置いてきちまった。すぐに取りに戻るぜ。";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "よし、構わねえよ。倉庫には二十五個あるぜ。値段は覚えてるだろ、一つ三十ドゥブロンだ。";
				if (PCharDublonsTotal() >= 750)
				{
					link.l1 = "よし、取引成立だ。ほら、これだ。七百五十ドゥブロンだぞ。";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "なんてついてねえんだ。金を船に置いてきちまった。すぐに取りに戻るぜ。";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && !CheckAttribute(pchar, "questTemp.SvensonBakautBlock")) // увеличить объём поставок бакаута
			{
				link.l4 = "ヤン、鉄木の出荷量を増やすことは可能だろうか？";
				link.l4.go = "UpgradeBakaut";
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && CheckAttribute(pchar, "questTemp.SvensonBakautPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок бакаута, если в первый раз не принесли
			{
				link.l4 = "ヤン、三千枚の金貨を集めたぞ。ほら、これを俺たちの寄生虫どもに贈り物として渡してくれ。 今日はあいつらにとっていい日になるだろうな。";
				link.l4.go = "UpgradeBakaut_Agreed";
			}
		break;
		
		case "trade_bakaut_1":
			RemoveDublonsFromPCharTotal(750);
			Log_Info("You have given 750 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "感心だな。俺の部下に鉄の木をお前の船まで運ばせるぜ。";
			link.l1 = "ありがとうございます！";
			link.l1.go = "trade_bakaut_2";
		break;
		
		case "trade_bakaut_2":
			dialog.text = "もっと買いたいなら、二週間後にまた来てくれ。\nその頃には新しい品を用意しておくぜ。";
			link.l1 = "よし、ヤン。また今度な！";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SANDAL, 25);
			DeleteAttribute(npchar, "quest.trade_bakaut");
			SetFunctionTimerCondition("Bakaut_SvensonAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "UpgradeBakaut": //
			if (startHeroType == 1) sStr = "old friend";
			if (startHeroType == 2) sStr = "old friend";
			if (startHeroType == 3) sStr = "old friend";
			if (startHeroType == 4) sStr = "Helen";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "鉄木を気に入ってくれて嬉しいぜ。 "+sStr+"「出荷量を増やすのは問題ないが、分かるだろう、ひとつ厄介なことがある。量が増えれば、それだけ足跡も大きくなり、 特にイギリス当局に目をつけられるかもしれねえ。だが、信頼できる手と耳、 それに屋敷の中で俺たちを影に隠してくれる連中を加えれば、全部うまくやれるさ。ただし、安くはねえ――市の財務官とイングランドの目をかいくぐるには三千ドゥブロンが必要だ。それさえ払えば、今の五倍の量を用意できる。 どうする？」";
				link.l1 = "三千ドゥブロンだと？ヤン、それじゃまるで白昼強盗じゃねえか！もっと安く済ませられねえのか？ そんな大金を使わずに解決する方法があるんじゃないか？";
				link.l1.go = "UpgradeBakaut_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "いい考えだが、正直言って、その量の取引にはもう少し経験と腕が必要だ。急げば、得よりもリスクの方が大きい。 こうしよう――もう少し経験を積んで、大口の取引に自信がついたらまた来てくれ。その時に改めてしっかり話し合おう。";
				link.l1 = "ふむ……わかった。この話はまた後で続けよう。";
				link.l1.go = "exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeBakaut_1":
			dialog.text = "「ああ、」 "+pchar.name+"、これが今どきの平和の代償ってやつさ――カツラと軍服を着た旦那どもの欲は日ごとに増すばかりだ。 連中の宝箱でドゥブロン金貨が鳴る音ほど魅力的なものはねえよ。もし慰めになるなら、 今後のすべての積荷は十五パーセント引きで保証してやるぜ。";
			link.l1 = "くそったれどもめ！こんな大金を要求しやがって！そんな強欲なら王の財宝でも買い漁るべきだろうが、 黙ってろと取引するとはな！ヤン、俺たちがこの諸島で本当の力を持ってるのは誰か、思い知らせてやるか？";
			link.l1.go = "UpgradeBakaut_2";
		break;
		
		case "UpgradeBakaut_2":
			if (startHeroType == 1) sStr = "my friend";
			if (startHeroType == 2) sStr = "my friend";
			if (startHeroType == 3) sStr = "my friend";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "ははっ！いい根性してるな、 "+sStr+"！だが、今はイングランド全体を敵に回す気はねえし、俺も昔ほど若くはねえんだ。ここは血吸いどもに金を払って、 大人しくさせとこう――俺たちにはやるべきことがあるからな。必要な金を用意しろ、そうすりゃ余計な詮索もされずに道が開けるぜ！\n";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "よし、わかったよ、ヤン。お前の言う通りにするしかないみたいだな。仕方ねえ、三千ドゥブロンやるよ。 だが覚えておけ、俺はいつまでもあいつら守銭奴どもを養うつもりはねえからな。\n";
				link.l1.go = "UpgradeBakaut_Agreed";
			}
			link.l2 = "悪魔にでもくれてやれ、ヤン！本当に他に道はないと思うのか？仕方ない。あのドゥブロン金貨を探してやるさ。 だが今はそんな大金、持ってねえんだ。";
			link.l2.go = "UpgradeBakaut_4";
			link.l3 = "くそっ、ヤン、お前、本当にあの役人どもとその甘やかされた女たちに飯を食わせたいのか？\nあいつらは椅子に座って何もしねえくせに、金だけ要求しやがる！\n俺はこんなの気に入らねえ！俺の汗と血であいつらの懐を肥やすつもりはねえぞ！\n前の条件に戻そうぜ。それで十分だ。";
			link.l3.go = "UpgradeBakaut_3";
		break;
		
		case "UpgradeBakaut_Agreed":
			dialog.text = "そうこなくっちゃな！あんたの出資で、俺たちの商売もうまく回るぜ。あのケチどもも思い知るだろうし、 もう鉄木には目もくれなくなるさ。保証するぜ、すぐにでも投資は百倍になって返ってくるからな。";
			link.l1 = "そうだといいな、ヤン、そうだと本当に思うよ。";
			link.l1.go = "UpgradeBakaut_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "1_1");
			pchar.questTemp.UpgradeBakaut = true;
			pchar.questTemp.SvensonBakautBlock = true;
			DeleteAttribute(pchar, "questTemp.SvensonBakautPotom");
		break;
		
		case "UpgradeBakaut_Agreed_1":
			dialog.text = "商売は滞りなく進みますので、ご心配には及びません。さて、今後のお取引についてですが、これまで通り毎月14日と28日までに鉄木材125本をご用意いたします。全てまとめて3,150ドゥブロンでお渡しできます。";
			link.l1 = "こういう会話の方がずっと好きだ！じゃあ、丸太百二十五本でどうだ？素晴らしいな、ヤン。じゃあ、またすぐ会おう。 荷の到着を待ってるぜ！";
			link.l1.go = "exit";
		break;
		
		case "UpgradeBakaut_3":
			if (startHeroType == 1) sStr = "old friend";
			if (startHeroType == 2) sStr = "old friend";
			if (startHeroType == 3) sStr = "old friend";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "かしこまりました "+sStr+"。そんなに熱くなるな。この世の中ってのは、そういうもんだぜ。";
			link.l1 = "ああ、ヤン、この世の仕組みは分かっているさ。\nだが、それを我慢しなきゃならないってわけじゃねえ。\nよし、俺は行くぜ。";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
		break;
		
		case "UpgradeBakaut_4":
			dialog.text = "お前が金を集めるまで待ってるぜ。お前なら何とかするって分かってるからな。準備ができたら、 金を持って待ってるから、そしたら続きをやろう。";
			link.l1 = "よし。";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
			pchar.questTemp.SvensonBakautPotom = true;
		break;
		// <-- генератор бакаута
		
	//----------------------------------- штурм рудника --------------------------------------------
		case "mine_attack":
			dialog.text = "お会いできて嬉しいです。 "+pchar.name+"。俺の仲間は準備万端だ。ジャングルへ行くか？";
			link.l1 = "ああ、ヤン。俺の部隊は戦闘の準備ができてるぜ。";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			dialog.text = "それじゃあ出発しよう。鉱山はこの道沿い、ジャングルの奥深くだ。分かれ道では右に進め。行くぞ！";
			link.l1 = "進め！";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_attack_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("shore53", "boat", true);
			LocatorReloadEnterDisable("mine_03", "reload3_back", true);
			LocatorReloadEnterDisable("mine_02", "reload3_back", true);
			pchar.quest.Saga_MineAttack_01.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_01.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_01.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_3":
			dialog.text = "「それで、」 "+pchar.name+"、これからこの作戦をどう進めるか話し合う時だ。すでに数人のミスキート族を先行させて周辺を偵察させ、 その報告をもとに行動計画を立ててある。";
			link.l1 = "詳しく教えてくれ！";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "この穴は、ジャングルの山の下にある鉱山を表している。鉱山の入り口の近くにはキャンプがある。家が数軒と柵がある。 柵へと続く小道もある。見てみろ、ここからそう遠くないジャングルの中の小さく開けた場所へと続いている。 そこが穴の主な入り口だ\nそれは、二つの急な丘の間にある高い石壁を表していて、誰もこっそり中に入れないようになっている。 門は六人の男たちが守っている。大したことはないが、そこには大砲も二門設置されている。それが一番の問題だ\nぶどう弾を二斉射されたら、我々の部隊の半分がやられてしまう。それは大惨事だ。 だから正面からの攻撃は選択肢にできない……";
			link.l1 = "はっ！だが俺たちには切り札がある――中に入れる合言葉を知ってるんだぜ…";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			dialog.text = "その通りだ。それを利用させてもらうが、まずは最後までの俺の計画を全部話してやるぜ。";
			link.l1 = "もちろんだ、ヤン。話を聞こうじゃねえか。";
			link.l1.go = "mine_attack_6";
		break;
		
		case "mine_attack_6":
			dialog.text = "穴への別の入口がある――あのジャングルの小道を通るんだ。道は鉱山を守る丘をぐるりと回って、小さくて狭い窪地に通じている。 そこから中に入ることができるが、盗賊どもが高い柵を建てて見張りを配置している。柵には小さな門があるが、 向こう側からしっかりバリケードされている。\nさて、これから我々がどう動くかよく聞いてくれ。まず、鉱山の第二の入口を守っている連中を片付ける。 部隊の一部はその場に残り、丸太を見つけて破城槌として使うんだ。\nそれから本来の入口に戻って、砲手どもを始末する。俺たちの持っている合言葉が二度役に立つはずだ。その後、 両側から鉱山を攻撃する。俺が第一突撃隊を率いる。お前は第二突撃隊を率いてくれ。";
			link.l1 = "まあ、理にかなってるな。奴らを二方面で戦わせるんだ。進め！";
			link.l1.go = "mine_attack_7";
		break;
		
		case "mine_attack_7":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.quest.mine01 = "true";
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_02.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_02.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_02.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_8":
			dialog.text = "よし、着いたな……ここが盗賊の盗品買いのところへの道だ。さて、どうやって奴らに対処するか決めないとな。 全員で行けば怪しまれて警戒されちまうだろう。\n三人だけの少人数で行くべきだ、それ以上は多すぎる。そうすれば怪しまれずに近づいて、不意打ちできるはずだ。 俺は顔が割れてるから、グループの先頭には立てねえ。\nだから、お前に任せるぜ。 "+pchar.name+"なぜなら、作戦全体を危険にさらすことなく指揮を任せられるのはお前だけだからだ。 グレゴリーと銃士を補佐につけてやろう…";
			link.l1 = "柵の見張りには何人の護衛がいるんだ？";
			link.l1.go = "mine_attack_9";
		break;
		
		case "mine_attack_9":
			dialog.text = "四人だ。銃士が二人、兵士が二人。";
			link.l1 = "俺たちが奴らをやっつけてやるぜ…";
			link.l1.go = "mine_attack_10";
		break;
		
		case "mine_attack_10":
			dialog.text = "お前のことはよく知ってるから、一秒も疑わねえよ。あいつらのところに行って、「ジャックマンが寄越した」と伝えろ。 合言葉も忘れずにな。\nそして、みんなが安心したら……あとは状況に応じて動け。";
			link.l1 = "よし。奴らを油断させねえようにしてやるぜ。";
			link.l1.go = "mine_attack_11";
		break;
		
		case "mine_attack_11":
			dialog.text = "「幸運を祈るぜ」 "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "mine_attack_12";
		break;
		
		case "mine_attack_12":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 2)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 12)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);//запрет диалога
			}
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(npchar, "quest.mine01");
			npchar.quest.mine02 = "true";
			pchar.questTemp.Saga.MineAttack = "true";
			pchar.quest.Saga_MineAttack_03.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_03.win_condition.l1.location = "Mine_01";
			pchar.quest.Saga_MineAttack_03.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_13":
			dialog.text = "「よくやった」 "+pchar.name+"！さすがだな、今回もお前が勝ったぜ。さて、俺の連中がこの鉱山側から嵐をぶちかます準備をする。 正面入口を一気に片付けるぞ。";
			link.l1 = "また衛兵たちのところへ歩いて行くことになるのか？";
			if (GetCharacterIndex("Svensons_off_2") != -1 && GetCharacterIndex("Svensons_sold_12") != -1) link.l1.go = "mine_attack_14";
			else link.l1.go = "mine_attack_14a";
		break;
		
		case "mine_attack_14a":
			dialog.text = "「はい」 "+pchar.name+"、また頼むぞ。俺自身が行きたいところだが、奴らに顔が割れてるから作戦が台無しになっちまう。 敵も増えてて危険度も上がってるし、武器も忘れるなよ。\n";
			link.l1 = "俺の士官たちを連れて行くぜ。";
			link.l1.go = "mine_attack_14_1";
		break;
		
		case "mine_attack_14":
			dialog.text = "「はい」 "+pchar.name+"、またしてもだ。俺自身が行きたいところだが、奴らに顔が割れてるから作戦が台無しになっちまう。 敵も増えてるから前より危険だし、武器のことも忘れるな。誰を連れていくつもりだ？お前の士官たちか、 それとも前回みたいにグレゴリーと銃士か？\n";
			link.l1 = "俺の士官たちを連れていくぜ。";
			link.l1.go = "mine_attack_14_1";
			link.l2 = "グレゴリーとマスケティアを連れて行く。";
			link.l2.go = "mine_attack_14_2";
		break;
		
		case "mine_attack_14_1":
			dialog.text = "よし。自分の仲間が一番の後ろ盾だ。さて、正面入口まで戻ろう。道は覚えているか？";
			link.l1 = "もちろんだ。来た道を戻って、それから左に進み、丘の周りの小道を行くんだ。";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "officer";
		break;
		
		case "mine_attack_14_2":
			dialog.text = "いいだろう。一度やり遂げたんだから、二度目も楽勝のはずだ。これから正面入口まで戻るぞ。道は覚えているか？";
			link.l1 = "もちろんだ。来た道を戻って、左に進み、丘を回る小道を行こう。";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "soldiers";
		break;
		
		case "mine_attack_15":
			dialog.text = "無駄にしている暇はない。進軍するぞ！";
			link.l1 = "進め！";
			link.l1.go = "mine_attack_16";
		break;
		
		case "mine_attack_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 12) LAi_ActorFollowEverywhere(sld, "", -1);
				else LAi_ActorRunToLocation(sld, "reload", "reload3_back", "mine_01", "goto", "goto"+i, "", 5);
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			if (pchar.questTemp.Saga.MineAttack == "soldiers") LAi_LocationDisableOfficersGen("mine_exit", true);//офицеров не пускать
			LocatorReloadEnterDisable("mine_03", "reload3_back", false);
			LocatorReloadEnterDisable("mine_02", "reload3_back", false);
			DeleteAttribute(npchar, "quest.mine02");
			npchar.quest.mine03 = "true";
			pchar.quest.Saga_MineAttack_05.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_05.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_05.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_17":
			dialog.text = "「了解だ」 "+pchar.name+"、最後の指示をよく聞け。門を守っている悪党どもは手強いから、簡単にはいかねえぞ。お前の主な目標は、 門の近くにいる砲手どもを仕留めることだ。あいつらが生きてる限り、俺たちは助けに行けねえからな。\n二人とも倒して、銃撃の心配がなくなったら、俺たち全員で一気に片付けてやる。わかったか、 "+pchar.name+"「？無理に英雄ぶるな、大砲手どもを倒して、あとは俺たちに任せろ。」";
			link.l1 = "わかった、ヤン。計画通りに全部やってみるさ。もし何かうまくいかなかったら、その場の流れで対応するぜ。";
			link.l1.go = "mine_attack_18";
		break;
		
		case "mine_attack_18":
			dialog.text = "いいだろう。神のご加護を！";
			link.l1 = "ありがとう……";
			link.l1.go = "mine_attack_19";
		break;
		
		case "mine_attack_19":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2)
					{
						LAi_SetActorType(sld);
						LAi_ActorFollowEverywhere(sld, "", -1);
					}
					else LAi_SetStayTypeNoGroup(sld);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			DeleteAttribute(npchar, "quest.mine03");
			pchar.quest.Saga_MineAttack_06.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_06.win_condition.l1.location = "Mine_exit";
			pchar.quest.Saga_MineAttack_06.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_20":
			dialog.text = "ふう！あのクソ野郎どもをぶっ倒したぜ…なかなか手強いチンピラどもだったな。あいつら、元は正規軍にいた傭兵だってのがよく分かる。 ここで大騒ぎしちまったから、誰かに聞かれたかもしれねえ。ぐずぐずしてる暇はねえぞ！\n "+pchar.name+"、そろそろ鉱山を襲撃する時だ。\n私は第二の入口にいる自分の仲間の元へ戻る――やつらはもう柵を破る丸太を見つけて準備しているはずだ。お前と部下たちは中央門から進め。俺たちを三十分待て、 すぐには攻撃するな……";
			link.l1 = "ヤン、もし奴らが鉱山での銃声を聞いていたら、俺たちにはあと半時もないぞ。あの野郎どもが防衛線を張るか、 あるいは中央門にまっすぐ突っ込んできて、俺の隊を総攻撃してくるかもしれねえ……";
			link.l1.go = "mine_attack_21";
		break;
		
		case "mine_attack_21":
			dialog.text = "くそっ！それは十分あり得るな。どうするつもりだ？";
			link.l1 = "ふむ…はっ！いい考えが浮かんだぞ！大砲だ！見てみろ。散弾だけじゃなく、爆弾もあるじゃねえか！ これであの野郎どもも終わりだ！なんで今まで気づかなかったんだ！？";
			link.l1.go = "mine_attack_22";
		break;
		
		case "mine_attack_22":
			dialog.text = "俺たちはどうすべきだと思う？";
			link.l1 = "大砲は一門だけ持っていくぜ。一門だけなら、もっと素早く効率的に動けるからな。門の向こう、 鉱山まで転がして設置するつもりだ。もし奴らが攻めてきたらドカンと一発お見舞いしてやるし、 引っ込んでるならこっちから奴らの野営地を砲撃してやる。\n門の向こう、奴らの野営地が正確にどこにあるか教えてくれないか？";
			link.l1.go = "mine_attack_23";
		break;
		
		case "mine_attack_23":
			dialog.text = "キャンプは山のふもとの低地にある。門を越えた先に小道があり、丘を下ってぐるりと回り込んでいる。 キャンプはこの丘のすぐ裏手に位置している。";
			link.l1 = "素晴らしい！道の上に陣取って、丘の向こうの奴らの巣に爆弾を何発かぶち込んでやるぜ！ あいつらを踊り狂わせてやろうじゃねえか！";
			link.l1.go = "mine_attack_24";
		break;
		
		case "mine_attack_24":
			dialog.text = "「くそっ、」 "+pchar.name+"、よくやった！全速前進だ！ランドルフをお前の指揮下に置いていく、あいつは俺の一番の砲手だ。砲手に任命すれば、 絶対にお前を裏切らねえ。俺はこれから自分の部隊に戻るぜ。";
			link.l1 = "よし。お前たちが門を破るまで、俺があいつらの陣地を三十分ぶっ壊してやるぜ。";
			link.l1.go = "mine_attack_25";
		break;
		
		case "mine_attack_25":
			dialog.text = "間に合うように頑張るよ。キャンプで会おう！";
			link.l1 = "取引成立……分隊！俺の号令を聞け！大砲を新しい位置に移す準備をしろ！火薬と爆弾、それにブドウ弾も持っていけ！ 門を通って鉱山へ向かうぞ。前進、行進！";
			link.l1.go = "mine_attack_26";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
			}
		break;
		
		case "mine_attack_26":
			DialogExit();
			int n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "mine_bandits");
			LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.location = "Mine";
			pchar.quest.Saga_MineAttack_07.function = "Saga_MineGunAttack";
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine_exit", "reload2_back", true);
			LAi_LocationDisableOfficersGen("mine_exit", false); // офицеров пускать
			n = Findlocation("mine");
			locations[n].models.always.Gun = "mortair";
			Locations[n].models.always.Gun.locator.group = "goto";
			Locations[n].models.always.Gun.locator.name = "fire"; // орудие - к бою!
			Locations[n].hidden_sound = true;
		break;
		
		case "mine_attack_27":
			dialog.text = "ふう、俺たち遅すぎじゃねえか？ "+pchar.name+"?";
			link.l1 = "ヤン、くそっ！なんでそんなに遅かったんだ！？俺の部隊は今、大打撃を受けたばかりだぞ！";
			link.l1.go = "mine_attack_28";
		break;
		
		case "mine_attack_28":
			dialog.text = "あの忌々しい木の柵、思ったより頑丈だったぜ。力ずくでぶっ壊したんだ…お前の騒ぎとドタバタが聞こえてな。どうやらここをきれいに片付けてくれたみたいじゃねえか！もうすぐ丸焼けだ！";
			link.l1 = "ランドルフのやり口よ……お前にも見せてやりたかったぜ、俺たちがどれだけの野郎どもを埋めてから、ようやく白兵戦に突入したかをな！";
			link.l1.go = "mine_attack_29";
		break;
		
		case "mine_attack_29":
			dialog.text = "カランバ！あんたには脱帽だぜ、 "+pchar.name+"。よくやった！さて、損失についてだが……戦争中ならいつでもあるものだ。";
			link.l1 = "今やるべきことは鉱山そのものを一掃することだ。\n中に生き残りが隠れている可能性がある。";
			link.l1.go = "mine_attack_30";
		break;
		
		case "mine_attack_30":
			dialog.text = "行こう、二人きりで。そこで何が起きているか見てみよう。";
			link.l1 = "いい考えだな！";
			link.l1.go = "mine_attack_31";
		break;
		
		case "mine_attack_31":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, "");
			TakeNItems(npchar, "potion2", 8); 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "Mine_mines", "reload", "reload1", "", -1);
			LAi_LocationDisableOfficersGen("Mine_mines", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_08.win_condition.l1 = "locator";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator_group = "reload";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator = "reload4";
			pchar.quest.Saga_MineAttack_08.function = "Saga_MineAttackMines";
		break;
		
		case "mine_attack_32a":
			dialog.text = "まだ鉱山全体を探し終えてねえぞ！ここにはまだ何人かあの悪党どもが隠れてるに違いねえ！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_32a";
		break;
		
		case "mine_attack_32":
			dialog.text = "もう他に悪党は残っていないと思うんだが……";
			link.l1 = "「ヤン、俺たちはただ様子を探りに来ただけだと思ってたんだが……」";
			link.l1.go = "mine_attack_33";
		break;
		
		case "mine_attack_33":
			dialog.text = "ははは、まあ、特別な探索、血まみれの探索になるなんて言ってなかっただろ……こんなウォームアップは久しぶりだぜ！これで誰もが安心できる、 クズどもは一人残らずこの鉱山から逃げられなかったってな！";
			link.l1 = "それで次はどうするんだ、ヤン？";
			link.l1.go = "mine_attack_34";
		break;
		
		case "mine_attack_34":
			dialog.text = "「次はどうするつもりかって？金銀を探すに決まってるだろ。 ジャックマンがこんな要塞を退屈しのぎで守ってたわけじゃねえ。ここにまるごと守備隊を置いてたんだぜ。 鉱山の奴隷どもを見ただろ？どこに鉱石を貯めてるか調べてみろよ。」";
			link.l1 = "わかった。じゃあ、お前は奴隷どもを尋問してくれ。俺は高い所に登って、このキャンプの家々を全部調べてみる。 何か見つかるかもしれねえ。";
			link.l1.go = "mine_attack_35";
		break;
		
		case "mine_attack_35":
			dialog.text = "捕まえたぜ！動くぞ！";
			link.l1 = "...";
			link.l1.go = "mine_attack_36";
		break;
		
		case "mine_attack_36":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine", "reload1", true);
			LocatorReloadEnterDisable("mine", "reload6", true);//закрыть выходы с рудника
			pchar.quest.Saga_Mine_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Mine_letter.win_condition.l1.item = "letter_mine";
			pchar.quest.Saga_Mine_letter.function = "Saga_FindMineLetter";
			NextDiag.CurrentNode = "mine_attack_36a";
		break;
		
		case "mine_attack_36a":
			dialog.text = "行け、相棒。そいつらみすぼらしい小屋を徹底的にひっくり返してやれ！";
			link.l1 = "今行くぞ！";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_36a";
		break;
		
		case "mine_attack_37":
			dialog.text = "「ははっ！」 "+pchar.name+"、俺と一緒にこの鉱山をぶっ壊しに来てくれるなんて最高だぜ！お前が幸運の星の下に生まれたって、 これでまたはっきりしたな。";
			link.l1 = "金を見つけたか？";
			link.l1.go = "mine_attack_38";
		break;
		
		case "mine_attack_38":
			dialog.text = "ああ、くそっ！金じゃなくて銀だが、かなりの山だったぜ。あと一日遅れてたら、 奴らはもうキャンプから運び出してたはずだ。だからここにゴロツキどもが大勢いたんだ――護衛の連中さ。\nお前のおかげで間に合ったぜ。お前がいなきゃ、まだ仲間集めに奔走してたところだ。おめでとう、相棒！";
			link.l1 = "ははっ、なるほどな……俺たちの銀貨はどれくらい残ってる？";
			link.l1.go = "mine_attack_39";
		break;
		
		case "mine_attack_39":
			dialog.text = "俺たちにはおよそ四千ユニットある。\n約束通り、半分は俺、半分はお前の取り分だ。";
			link.l1 = "すげえな！あれを売れば山ほど金が手に入るぜ！";
			link.l1.go = "mine_attack_40";
		break;
		
		case "mine_attack_40":
			dialog.text = "それは間違いないな……何か価値のあるものを見つけたか？";
			link.l1 = "いや、ここらのあばら家にはドゥブロン金貨一枚すらなかったぜ。\nただ、書類をいくつか見つけた。読んでみたら、 この鉱山の持ち主はポートロイヤルのローレンス・ベルトロープって奴らしい。";
			link.l1.go = "mine_attack_41";
		break;
		
		case "mine_attack_41":
			dialog.text = "「ほう、本当か？その書類を見せてくれ……」";
			link.l1 = "「はい、どうぞ。」";
			link.l1.go = "mine_attack_42";
		break;
		
		case "mine_attack_42":
			RemoveItems(pchar, "letter_mine", 1);
			dialog.text = "（読みながら）…ふむ…ベルトロープ？どこかで聞いたことのある姓だな。ああ、そうだ！トマス・ベルトロープ！これは面白い…よし、ブルーヴェルドに戻ったら調べてみるとしよう。もし構わなければ、これらの書類は俺が預かっておくぜ？";
			link.l1 = "全然だ。俺にはあいつらなんて必要ねえよ。";
			link.l1.go = "mine_attack_43";
		break;
		
		case "mine_attack_43":
			dialog.text = "よし。さて、これからが一番の見せ場だ。俺が銀を船まで運ぶ。ミスキート族が手伝ってくれるぜ。 荷車を用意するからな……\nその間、お前は先に行って休んでくれ。 "+pchar.name+"。誰よりも君がふさわしいよ！";
			link.l1 = "ありがとう、ヤン。あの丘の上に野営しようぜ、ここは煤けた臭いがきつすぎる。\nそうだな、それにこの小屋の火も消さなきゃな。\nいつか将来、役に立つかもしれねえし……";
			link.l1.go = "mine_attack_44";
		break;
		
		case "mine_attack_44":
			dialog.text = "鉱山を手に入れようって考えてるのか？ははっ！俺もその考えは浮かんだが、略奪と所有するのは別物だぜ。友よ、 ここにはもう持ち主がいるんだ。イギリス当局と揉める羽目になるかもしれねえ。\nそれに、俺が話した奴隷たちによれば、ここの鉱脈はほとんど掘り尽くされてるらしい――何度も大量の銀が運び出されたそうだ。残念だが、この鉱山はもう終わりだな。";
			link.l1 = "ふむ……どうかな。まだ全部が尽きたわけじゃないかもしれない。まあいい、そろそろ休まないと。本当に。またな、ヤン\n";
			link.l1.go = "mine_attack_45";
		break;
		
		case "mine_attack_45":
			dialog.text = "さあ、行け。心配はいらねえ。あとのことは全部俺たちが引き受けるぜ。";
			link.l1 = "...";
			link.l1.go = "mine_attack_46";
		break;
		
		case "mine_attack_46":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "attack1", "Saga_MineWaitTime", -1);
			n = Findlocation("mine");
			DeleteAttribute(&locations[n], "hidden_sound");
			DeleteAttribute(&locations[n], "hidden_fire");
			n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "models.always.Gun1");
		break;
		
		case "mine_attack_47":
			dialog.text = "「よく休めたか」 "+pchar.name+"?";
			link.l1 = "悪くはなかった……でも正直なところ、酒場を見つけて一杯やり、清潔なベッドで眠れたら最高なんだが。";
			link.l1.go = "mine_attack_48";
		break;
		
		case "mine_attack_48":
			dialog.text = "インディオたちは銀を岸に運び、私の部下の監督のもとでお前の船に積み込んでいる。もう戻ってもいいぞ。ラム酒、 酒場、そしてベッドの願いもすぐに叶うだろう。\nそれと、五日後に私の屋敷に立ち寄ってくれ、まだやるべきことがたくさんあるからな。";
			link.l1 = "よし、ヤン。五日後にブルーヴェルドで会おう！幸運を祈るぜ！";
			link.l1.go = "mine_attack_49";
		break;
		
		case "mine_attack_49":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 15.0);
			LocatorReloadEnterDisable("shore53", "boat", false);
			LocatorReloadEnterDisable("mine", "reload1", false);
			LocatorReloadEnterDisable("mine", "reload6", false);
			LocatorReloadEnterDisable("mine_01", "reload3_back", false);
			LocatorReloadEnterDisable("mine_exit", "reload2_back", false); //открыть выходы с рудника
			LAi_LocationDisableOfficersGen("mine_mines", false); // офицеров пускать
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			SetFunctionTimerCondition("Saga_ReturnFromMine", 0, 0, 5, false); // таймер
			pchar.questTemp.Saga.Mines = "true"; // после Саги рудник будет разрабатываться
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			DoQuestReloadToLocation("Shore53", "goto", "goto6", "");
		break;
		// <-- штурм рудника
		
		case "helensleep":
			dialog.text = "";
			link.l1 = "ヤン、そんなに怒鳴らないでくれ。理性的に話をつけようじゃないか――俺たちにはやるべき商売があるんだから！";
			link.l1.go = "helensleep_1";
		break;
		
		case "helensleep_1":
			dialog.text = "今すぐ俺の犬どもをけしかけてやるぞ、このヒキガエルめ！ルヴァスールのことなんか忘れて、とっとと失せろ！";
			link.l1 = "ヤン！俺の話を聞け……";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenSleep_SvensonThrowOut");
		break;
		
		case "after_drinking":
			dialog.text = "「どの樽のことだ？エレンについては、しっかりお仕置きしてやるさ……冗談だよ、シャルル、冗談だって！事情は分かってるし、ジョアンナのことだけど――この話で少しは考え直してくれるといいな。最近は特に機嫌が悪いからな……まあ、人生ってそういうもんさ。ともかく、カルタヘナでの幸運を祈ってるぜ！」\n";
			link.l1 = "また会う日までだ、ヤン。";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
