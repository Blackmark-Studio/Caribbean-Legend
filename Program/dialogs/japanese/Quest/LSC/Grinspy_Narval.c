// Дональд Гринспи - лидер нарвалов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "「何だ？何の用だ？」";
				link.l1 = TimeGreeting()+"。私の名前は "+GetFullName(pchar)+"。俺はその一族の長に会いたかったんだ。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"！何か用か？";
				link.l5 = "ちょっと挨拶したかっただけだ。またな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "これで俺のことは分かっただろう。俺の名はドナルド・グリーンスパンだ、俺や部下を怒らせるなよ。それから、 合言葉を手に入れるまでは『サン・ガブリエル』に近づくんじゃねえ。店は誰にでも開いてるぜ、 みんな取引が必要だからな。何か質問はあるか？";
			link.l2 = "いや、分かった。またな。";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
	// ----------------------------------после разгрома Чада и Мэри на Каролине---------------------------
		case "shark":
			dialog.text = "俺に何の用だ？";
			link.l1 = "とても不愉快な話だ、ドナルド。昨夜スティーブンの命が狙われた。お前の一族の戦士たちが関わっていたんだ。\n";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "それは知らねえな。なんであいつらが俺の手下だと思ったんだ？";
			link.l1 = "俺はそこにいたからだ。お前たちの仲間、海賊、そしてリヴァドスの違いは見分けがつく。 あの一団を率いていたのはメアリー・キャスパーとチャド・カッパーだった。\nこれ以上の証拠が必要か？";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "俺と俺の部下たちは、その件には一切関わってねえとだけは断言できるぜ。";
			link.l1 = "それを提督に納得させなければならないが、簡単にはいかないぞ。襲撃の後、 ドッドソンはナーヴァル全員に激怒している。お前たちに戦争を宣言するつもりだ――補給を止め、機会があればお前の仲間を撃つだろう。それは口先だけじゃないんだ。";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "提督が自分のやっていることを分かっているといいんだがな。俺の部下たちの射撃の腕前を疑ってるってのか？";
			link.l1 = "そう思うぜ。あいつは『サン・アウグスティン』を要塞に変えて、お前たちが飢え死にするまで戦うつもりだ。それに、 ドッドソンはリバドスと話し合って協力を申し出るつもりらしい。お前たちじゃ、 提督とリバドスが手を組んだら勝ち目はねえよ。";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "くそっ！だが俺たちはこの企みに関わっちゃいねえ！なんで一人の馬鹿女メアリーと、 俺の手下のクズどもがやったことで一族全体が罰を受けなきゃならねえんだ？\nそれに、理屈で言えば、マーロウを殺したことでドッドソン自身がメアリーや俺の兵隊を挑発したんだ。 そんな卑劣な真似をすりゃ、当然こうなるさ。";
			link.l1 = "お前は何も分かっちゃいねえ。騙されてるんだぜ。どうしてそんなにドッドソンがアランを殺したって確信してるんだ？ 実際のところ、あいつはお前が自分の地位を奪うためにやったと思ってるんだぞ…";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "俺はあいつがどう思おうが知ったこっちゃねえ。証拠は全部あいつに不利だ。 牢屋に出入りできたのはあいつと手下だけだ。アランはあいつの手中にあった。 レッド・メアリーがいろいろ話してくれた。アランが殺される前、ドッドソンが自ら牢屋を訪ねたんだ。 あいつがそんなことするのは滅多にねえんだぜ。";
			link.l1 = "「奴が死ぬところを見たのか？」";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "ばか言うな！もちろん持ってねえよ。";
			link.l1 = "「チミセットもだ。そうそう、アランの隣に座っていたリヴァドスの魔術師さ。あいつも最近そこで殺されたんだ。 俺は奴が死ぬ前日に牢屋にいて、話をしたんだ。ミルローはシャーク号の甲板長、チャド・カッパーに殺された。」";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "本当か？";
			link.l1 = "考えてみろよ。チミセットはお前と提督の関係なんて気にしちゃいなかった。嘘をつく理由もなかったんだ。 あの年寄りの魔術師はチャドを恐れていて、自分が次だと思ってた。実際その通りだった。 提督が彼を解放するつもりだと知った途端、チャドはあいつを殺したんだ。";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "「でも、なぜカッパーはアランの死を望んだんだ？」";
			link.l1 = "くそっ、本当にわかってねえのか？カッパーがレッド・メアリーと組んでたって言っただろ。 あいつはシャークの地位を奪いたくて、ずる賢い計画を立てたんだ。アラン・ミルローを殺して、 その死にシャークが関わってるって噂を流したことで、ナーワル族は提督に敵意を持つようになったんだよ…";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			dialog.text = "";
			link.l1 = "愚かな娘メアリーは彼を信じて、恋人の本当の殺人犯に味方したんだ。 彼らは何人かのナーワルを仲間に引き入れたらしいが、メアリーにとっては簡単なことだったんだろうな。\nそれからファジオの船室で提督への襲撃を計画して、そこで提督は無理やり招待状を書かされたんだ…";
			link.l1.go = "shark_10";
		break;
		
		case "shark_10":
			dialog.text = "";
			link.l1 = "ファジオからの手紙があって、すべてが説明されているんだ。チミセットは危険な証人としてチャドに殺された。 彼はナーヴァルと協力していて、リヴァドスはシャークとの会談の時にそれを聞けばきっと喜ぶだろう。\nこの手紙を見せれば、チャドがあんたたちの仲間になったことをブラック・エディに簡単に証明できるさ。";
			link.l1.go = "shark_11";
		break;
		
		case "shark_11":
			dialog.text = "ふむ。お前は切り札を全部持ってるじゃねえか、じゃあ何しにここへ来たんだ？俺に何か用があるんだろ？";
			link.l1 = "そうだ。なぜなら、これはすべてチャドの企みで、お前は関わっていないと俺は信じているからだ。 チャドはメアリーを裏切り、メアリーはお前の一族の仲間に助けを求めた――それが全ての話さ。少なくとも、俺はお前や他のナルワル族に不利な証拠は何も見つけていない……\n";
			link.l1.go = "shark_12";
		break;
		
		case "shark_12":
			dialog.text = "";
			link.l1 = "だが、他に陰謀を企む者が残っていないとは限らない。そいつらを探し出してほしい。そうすれば、 もしかしたら血を流さずに決着をつけられるかもしれない。";
			link.l1.go = "shark_13";
		break;
		
		case "shark_13":
			dialog.text = "もう言ったはずだが、俺の部下は誰も関わってねえ。マーロウが死んだ後、メアリーは実質的に一族を離れ、 自分の船室に閉じこもった。正直、どうやって他の連中を説得して巻き込んだのかは全く分からねえが、 どうやらうまくやったらしい。誓って言うが、俺も俺の一族の誰も提督に逆らうようなことはしていない。 最近はあまりにも多くの仲間を失ったから、今は面倒事に首を突っ込みたくねえんだ。 たとえリヴァドスと手を組んで提督が攻めてきても、俺は怖くねえ。ナーワルは本物の戦士だ、 最後の戦いでそれを証明してやるぜ。だが、それは無意味だ。俺たちはすでに提督と和平を保つと決めている。 リヴァドスは別だ。黒人とは交渉しねえ。俺は提督に直接謝る覚悟がある。ミルローの死で疑いを持ったこと、 そして彼の命を狙ったことについて許しを請うつもりだ。誠意を示すために聖書に誓おう。 お前とドッドソンはそれでいいのか？\n";
			link.l1 = "俺だ。お前の手下どもに何か企みはないと本当に言い切れるのか？";
			link.l1.go = "shark_14";
		break;
		
		case "shark_14":
			dialog.text = "もちろんだ。アラン・ミルローの本当の殺し屋について、俺の一族に伝えるぜ。 俺の部下たちと提督との関係もすぐに変わるだろう、保証する。\nそれで……その後に虐殺が必要になるのか、教えてくれよ？";
			link.l1 = "いや、そんなことにはならない。俺がそれを防ぐためにここにいるんだ。ドナルド、お前のことは信じてるし、 シャークを説得してみるつもりだ。まだいくつか切り札が残ってる……またな、ドナルド！";
			link.l1.go = "shark_15";
		break;
		
		case "shark_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "narval"; // ноду Акуле
			AddQuestRecord("SharkHunt", "26");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "narval_wait":
			dialog.text = "もう提督と話したのか？何か成果はあったか？";
			link.l1 = "進展している。後でまた会おう…";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "shark_16":
			dialog.text = "もう提督と話したのか？何か成果はあったか？";
			link.l1 = "ああ、そうだ。謝罪は受け入れたし、お前の一族への非難も取り下げる。さらに伝えることがある。シャークが、 お前に会ってナーワル族と海賊たちの将来の和平協定について話し合いたいと招待している。";
			link.l1.go = "shark_17";
		break;
		
		case "shark_17":
			dialog.text = "正直に言うと、まさかこんなことになるとは思わなかった……これは素晴らしい知らせだ。もしかしたら、俺たちの一族の食糧の値段や、 リヴァドスに関する新しい方針も見直せるかもしれねえな。";
			link.l1 = "それはあんたと提督だけの問題だ。";
			link.l1.go = "shark_18";
		break;
		
		case "shark_18":
			dialog.text = "ああ、もちろんだ。無駄な流血を防ぎ、もしかすると俺の部下たち全滅すらも阻止してくれたことで、 ナーワル族に大きな恩を売ってくれたな。感謝の印としてこのタワーマスケットを受け取ってくれ、 こんな武器は他に手に入らねえぜ\nそれに、他の部族員と同じく、俺たちの立入禁止区域にも入っていいぞ。";
			link.l1 = "ありがとう！それじゃあ、またな。やることが山ほどあるんだ。";
			link.l1.go = "shark_19";
		break;
		
		case "shark_19":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower mousqueton");
			PlaySound("interface\important_item.wav");
			dialog.text = "幸運を祈る。何か質問があれば俺のところに来い。";
			link.l1 = "了解だ。またな！";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
		break;
		
		case "grinspy_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "おう！ "+GetFullName(pchar)+"！お前は……いや、まさか！生きているのか！？";
				link.l1 = "俺が死んだって噂はちょっと大げさだったな、ドナルド。ははっ、会えて嬉しいぜ！";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "あ、ああ、友よ "+GetFullName(pchar)+"！何か用か？";
			link.l1 = "いや、知らねえよ。ただ挨拶したかっただけだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "grinspy_wait";
		break;
		
		case "negotiations":
			dialog.text = "俺に何の用だ？";
			link.l1 = "とても不愉快な話だ、ドナルド。スティーブンの命が狙われたんだ。お前の一族の戦士たちが関わっていたぞ。";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			dialog.text = "それは知らねえな。なんで俺の手下が関わってると思うんだ？";
			link.l1 = "俺が何人かをチャド・キャッパーと一緒にこの手で殺したからだ。あいつはこの混乱の元凶で、提督の水夫長だ。 自分一人じゃできなかったから、お前の手下たちがずいぶん手を貸してたんだよ。提督はそのことを知ってるし、 ものすごく怒ってるぜ。";
			link.l1.go = "negotiations_2";
		break;
		
		case "negotiations_2":
			dialog.text = "俺の仲間？誰のことだ？名前を挙げてみろよ。";
			link.l1 = "名乗りもしなかったよ。撃ち合いと剣を振るうだけだった。お前たちの連中は無鉄砲だな。 仲間同士でも襲いかかるくらいだ。俺や提督に向かってくるのはまだしも、女の子を殺そうとするなんて、 どうかしてるぜ。";
			link.l1.go = "negotiations_3";
		break;
		
		case "negotiations_3":
			dialog.text = "ふむ。誰のことを言っているんだ？";
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "俺が誰の話をしているかわかるか？レッド・メアリーへの襲撃のことだ。ナーワルの二人が彼女を殺そうとしたんだ。 偶然にも、俺はまさに危機一髪の時に彼女の船室にたどり着いた。もしあと少し遅れていたら、 彼女は殺されていただろう。名前は聞かなかった、すまない、話している暇なんてなかったんだが、 メアリーは奴らがナーワルだと言っていた。";
				link.l1.go = "negotiations_4";
			}
			else
			{
				link.l1 = "俺が誰のことを話しているかわかるか？俺が言ってるのは、レッド・メアリーへの襲撃と、 彼女を殺したあの二人のナーワルどものことだ。"link.l1.go ="negotiations_6";
			}
		break;
		
		case "negotiations_4":
			dialog.text = "何だと？なぜ彼女は俺に言わなかったんだ！？すぐにでも動いたのによ！";
			link.l1 = "最近は自分の船室から出るのも怖がっていたんだ。\nついこの前もお前と口論してただろう、そんな相手に助けを求めて駆け寄るわけがないじゃねえか？";
			link.l1.go = "negotiations_5";
		break;
		
		case "negotiations_5":
			dialog.text = "俺は彼女と口論なんかしてねえ！あいつが無理難題を押し付けてきて、きついやり取りになったから追い返したんだ。 だが、それが俺が…\n";
			link.l1 = "まあ、いいさ。どうせ、もう全部片付いたんだろう。\nだが、お前の仲間の中にはクズ野郎もいるってのは事実だぜ。";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_6":
			dialog.text = "「何だって？彼女はナーワル族に殺されたのか？なぜだ？」";
			link.l1 = "チャド・カッパーの命令だ、ドナルド。あの娘は知りすぎていたし、チャドに協力するのも拒んだんだ。だから今、 可哀想に死んじまったんだよ！";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_7":
			dialog.text = "誓って、俺はそんなこと知らなかったんだ！";
			link.l1 = "ああ、そうじゃないのは分かってる……だが、提督の話をしよう。チャド・キャッパーがその企てを仕組み、お前の部下たちも手を貸したんだ。 奴らはドッドソンを毒殺しようとした――俺がかろうじて止めたんだぜ。";
			link.l1.go = "negotiations_8";
		break;
		
		case "negotiations_8":
			dialog.text = "そんな注文はしていない。ドドソンも、俺が亡きアランの方針を支持していないことは知ってるし、 俺は分の悪い訴訟よりも、痩せた妥協の方がマシだと思ってるんだ。";
			link.l1 = "提督を説得しなければならないが、簡単にはいかないぞ。あの一件の後、ドッドソンはナーワル族全員に激怒している。 お前たちに宣戦布告するつもりだ。";
			link.l1.go = "negotiations_9";
		break;
		
		case "negotiations_9":
			dialog.text = "提督が自分の行動を理解してくれているといいんだがな。俺の部下たちが撃ち返せることを疑ってるのか？";
			link.l1 = "そうだよ。あんたの一族は盗賊団だと思ってて、皆を殺し始める前に滅ぼさなきゃならねえって考えてるんだ。\nそれに、俺たちはリヴァドスと強いつながりがある。ブラック・エディに話をつけて、 同盟を持ちかけることだってできる。\nあんた一人じゃ、俺たち全員には太刀打ちできねえぜ。";
			link.l1.go = "negotiations_10";
		break;
		
		case "negotiations_10":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Call Red Mary if you don't believe me and ask her! She will confirm.";
			else sTemp = "I have a letter from Chad to Mary which proves everything.";
			dialog.text = "くそっ！なんで数人の馬鹿のせいで一族全員が罰を受けなきゃならねえんだ？俺が怖がってるなんて思うなよ。 俺たちは戦士だ、最後の戦いでもそれを証明してやるぜ。だが、俺は正義が欲しいんだ。実際、 アラン・ミルローを牢屋で殺したのは提督の責任だ。";
			link.l1 = "どうしてお前がリーダーになれるんだ、ドナルド……お前はメアリーやアランのことなんて何も知らねえだろ。チャド・キャッパーがあいつを殺したんだ。 "+sTemp+" 奴はそれをしてナーワルたちを提督に反抗させ、一部を自分の側に引き込もうとしたんだ。";
			link.l1.go = "negotiations_11";
		break;
		
		case "negotiations_11":
			dialog.text = "なるほど。いいだろう。別の話し方をしようじゃねえか。お前、ここに来た理由があるんだろ？何が望みだ？";
			link.l1 = "この島で血まみれの騒ぎはごめんだ。誰にも死んでほしくねえ。ナーワル族を皆殺しにするなんて考えも好きじゃねえが、 リヴァドスと俺たちならそれもできるってのは保証するぜ。だがな、 ほんの数人のろくでなしのせいで一族全体が責任を取るべきだとも思わねえんだ…";
			link.l1.go = "negotiations_12";
		break;
		
		case "negotiations_12":
			dialog.text = "";
			link.l1 = "だが、俺の票だけじゃ足りねえ――お前は正式に提督に、今回の企てはお前の承認じゃなく、お前の一族もドッドソン殺しを企んでいないと保証すべきだ。";
			link.l1.go = "negotiations_13";
		break;
		
		case "negotiations_13":
			dialog.text = "どうすればいい？俺はあの企てとマーロウの死について疑ったことを謝る用意がある。 ナーワル族が彼に対して何も企んでいないと保証できるし、聖書にかけて誓うこともできる。 お前とドッドソンはそれで十分だと思うか？";
			link.l1 = "そうします。ドドソンにも直接会いに行けばきっと効果があるはずです。まずはあなたの意図を彼に伝えてから、 結果を持ってまたお伺いします。";
			link.l1.go = "negotiations_14";
		break;
		
		case "negotiations_14":
			dialog.text = "わかった。待つとしよう。";
			link.l1 = "すぐ戻るからな……";
			link.l1.go = "negotiations_15";
		break;
		
		case "negotiations_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "peace"; // ноду Акуле
			sld = characterFromId("Dexter");
			sld.dialog.currentnode = "First time"; 
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto11");
			AddQuestRecord("SharkHunt", "56");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "negotiations_17":
			dialog.text = "もう提督と話したのか？何か成果はあったか？";
			link.l1 = "ああ、あるよ。正式に彼を訪ねれば、それで問題は解決だ。";
			link.l1.go = "negotiations_18";
		break;
		
		case "negotiations_18":
			dialog.text = "正直言って、予想していなかった……これは素晴らしい知らせだ。";
			link.l1 = "ああ、そうだな、俺も嬉しいぜ。";
			link.l1.go = "negotiations_19";
		break;
		
		case "negotiations_19":
			dialog.text = "無意味な虐殺、そしておそらく我々ナーワル族の完全な滅亡さえも防いでくれたことで、 君はナーワル族に大きな恩を与えてくれた。\nこの塔銃を授けよう――他に同じものは見つからないはずだ。\nさらに、我々の船にも自由に立ち入ってよい。";
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				link.l1 = "ありがとう。とても貴重な贈り物だ。そうだ、ドナルド、もう一つ頼みがある。レッド・メアリーと和解してくれ。 あいつは短気だが、誠実で正直な女だ。お前と口論したせいで彼女は一族を出ていき、命を落としかけたんだ。";
				link.l1.go = "negotiations_20";
			}
			else
			{
				link.l1 = "ありがとうございます。これはとても貴重な贈り物です。そして、本当にうまく終わって嬉しいです。";
				link.l1.go = "negotiations_21";
			}
		break;
		
		case "negotiations_20":
			dialog.text = "彼女に、俺が彼女を傷つけたことと、あの二人のクズが彼女に手を出したことを許してほしいと伝えてくれ。\nお前たちは……友達なんだろう？";
			link.l1 = "ドナルド、その通りだ。彼女に伝えるよ。そして、すべてがこんなにうまく終わって本当に嬉しい。";
			link.l1.go = "negotiations_21";
		break;
		
		case "negotiations_21":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower musket");
			PlaySound("interface\important_item.wav");
			dialog.text = "幸運を祈るぜ。何か質問があったら俺のところに来な。";
			link.l1 = "わかった。じゃあな！";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			sld = characterFromId("Mary");
			sld.quest.donald = "true";
			LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload4", false); // открываем Церес изнутри
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			// здесь почищу весь хлам, который накопился
			DeleteAttribute(pchar, "questTemp.LSC.Donald_enter"); // атрибут гардов
			DeleteAttribute(pchar, "questTemp.LSC.Florentina");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_poison");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_warning");
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			DeleteAttribute(pchar, "questTemp.LSC.CapperDie_Aeva");
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Take care of Red Mary cause you are lucky to be with her - she is so reckless! She always gets in trouble...", "LostShipsCity", 20, 5, "LSC", "");
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("そこで何してるんだ、え？泥棒め！","見てくれよ！俺がちょっと物思いにふけった途端に、お前は俺の箱を調べる気になったんだな！","俺の宝箱を調べるつもりか？ただじゃ済まねえぞ！");
			link.l1 = "「くそっ！」";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "「なんだと？！俺の宝箱を調べるつもりか？ただじゃ済まねえぞ！」";
			link.l1 = "「愚かな娘め！」";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("聞け、武器はしまってくれ。見てると落ち着かねえんだ。","ここでは刃物を持って走るのは許されていないんだ。しまってくれ。","聞けよ、剣を振り回して中世の騎士みたいな真似はやめとけ。しまっとけ、そんなのはお前に似合わねえんだよ…");
			link.l1 = LinkRandPhrase("いいだろう。","ああ、いいぜ。","おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、俺はこの街の住人だ。剣を下ろしてもらえないか。","聞いてくれ、俺はこの街の住人だ。剣を下ろしてくれないか。");
				link.l1 = LinkRandPhrase("「いいだろう。」","ああ、いいぜ。","おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"気をつけろよ、相棒、武器を持ってうろつくのは。俺、そういうの見ると落ち着かねえんだ…","男たちが武器を抜いたまま俺の前を歩くのは好きじゃねえ……怖いんだよ……");
				link.l1 = RandPhraseSimple("了解だ。","俺が持っていくぜ。");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
