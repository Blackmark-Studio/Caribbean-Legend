// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","「どうした、何か用か」 "+GetAddress_Form(NPChar)+"?"),"「さっき俺に何か質問しようとしたよな、」 "+GetAddress_Form(NPChar)+"...","この一日中で、これが三度目だぜ、お前がこの質問を持ち出すのは……","また質問かい？","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わったんだ……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこに行っちまったんだ……","「ああ、本当にこれで三度目だな……」","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
			{
				link.l1 = "お前の砦で疫病が猛威を振るってるって聞いたぜ。町にも流行が広がると思うか？";
				link.l1.go = "Consumption";
			}
			if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "砦の司令官について何か知ってるか？";
				link.l1.go = "Consumption_8";
			}
			if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "「なあ、『フアン』って名前に心当たりはあるか？」";
				link.l1.go = "Consumption_12";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "聞いてくれ、1654年4月にミゲル・ディチョソ船長の指揮するフリゲート艦があんたの港に入港したんだが、その後やつは姿を消したんだ。 何か知ってることはないか？";
				link.l1.go = "guardoftruth";
			}
			//--> Оковы Азарта
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_1"))
			{
				link.l2 = "「教えてくれ、 "+npchar.name+"「こいつは誰だ、ハビエル・カスティーリョ？」";
				link.l2.go = "OZ_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_2"))
			{
				link.l2 = "ハビエルに影響を与えられる男についての話に戻ろう。";
				link.l2.go = "OZ_Tavern_2_1";
			}
			//<-- Оковы Азарта

		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "司令官は危険はないと言ってるぜ。好奇心が強すぎる奴は結局地下牢にぶち込まれるんだ。俺はそんな奴じゃねえ、 悪いな。";
			link.l1 = "そうかい？噂話に耳を貸さない酒場の主人なんて、珍しいもんだな！ ペソの音があんたの好奇心を呼び覚ますかもしれねえぜ？";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "銀はそりゃあ魅力的だが、俺の命の方が大事だぜ。別の話でもしようか、旦那？実は俺、話すのは大好きなんだ。 遠慮なく声をかけてくれよ！";
			link.l1 = "なるほど、そういう展開か……よし、この袋にはエイト金貨三千枚入ってる。天気についてちょっと世間話でもしようじゃねえか、どうだ？";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3000);
			dialog.text = "おや、しつこいねえ、旦那。だが、この話はなかったことにしてくれよ。（ひそひそ声で） もう一年も前から何度も聞いてるが、うちの牢屋で人がどんどん衰弱して、結核で死んでいくんだ。 役人のせいにするもよし、神や悪魔のせいにするもよし、だが大半は運が悪かったってことにされる。この忌々 しい病気は命をあっという間に奪っていく。元気な男を入れても、一週間か二週間であっさり死んじまうこともあるんだ……";
			link.l1 = "なんてこった…一年まるまるだと？それで、誰も何も手を打とうとしなかったってのか？";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "誰が気にするんだ、旦那？囚人なんて誰も気にしやしねえよ。社会のクズ――そう言うのさ、絹をまとった偉い連中はよ。地下牢で働いてた医者がいたんだ。哀れな奴らを治そうとしたが、 長くはもたなかった。どうやら病気にやられちまったらしいな。\n今じゃ司令官が誰も入れやしねえし、お偉方もそんなこと気にしちゃいねえ。特に、 牢屋のメシ代が安く済むってんならなおさらだ。";
			link.l1 = "面白いが、この病気の何がそんなにお前を怯えさせてるんだ？安全な壁の中に閉じこもって、 まるで告解室の修道女みたいにこそこそ話してるじゃねえか？";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "言いにくいんだが、ここに一人そんな奴がいたぜ。密輸で捕まって、 仲間が身代金を払うまで半年ほど牢にぶち込まれてたんだ。まあ、知ってるだろ――必要な奴には金を積んで、言われた額を払えば解放されるってわけさ。だがな、 それ以来そいつはすっかり気がふれちまったんだよ。";
			link.l1 = "ビルジラットよりもイカれてるってのか？";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "そうだと思うぜ。そいつはそれから仲間の役に立たなくなって、一日中ここで酒を飲んで死ぬつもりみたいだった。 何かを頭から消したかったように見えたな。酔うたびに、静かに人を奪っていく「消耗病」の話をしていたぜ\nそれが奴の言葉そのままだ。奴の話じゃ、「消耗病」ってのは男にとって最悪の災いだそうだ。";
			link.l1 = "酔っ払いのたわごとだ。それがどうした？";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
			{
				dialog.text = "何もないさ。ただ、あいつは酒で気が大きくなってどんどん喋り始めてな、 そしたら急に誰かに喉を掻っ切られて溝に捨てられた……やった奴が誰で、理由が何だろうと、俺にはどうでもいいことさ。";
				link.l1 = "司令官について何か言えることはあるか？";
				link.l1.go = "Consumption_8";
			}
			else
			{
				dialog.text = "「いや、特に何も。ただ、あいつが急に勇気を出してどんどん喋るようになったと思ったら、 いきなり誰かに喉を掻っ切られて溝に捨てられた……誰がやったかも、何のためかも、俺にはどうでもいいさ。（声を張り上げて）そうさ、 この辺の湾や岩礁は本当に危ねえんだ、旦那。大アンティル諸島から嵐が吹き荒れてきた時には、 風上を取れなきゃ一巻の終わりだぜ！ゆっくり休んでくれ、旦那、寄ってくれてありがとな！」";
				link.l1 = "嵐か……そうだな。お前にも礼を言うぜ。";
				link.l1.go = "Consumption_7";
			}
			pchar.questTemp.Consumption.Contra = "true";
		break;
		
		case "Consumption_7":
			DialogExit();
			npchar.quest.Consumption = "true";
			AddQuestRecord("Consumption", "2");
		break;
		
		case "Consumption_8":
			dialog.text = "あいつについて何を言えばいいんだ？大佐でな、数年前にヨーロッパからこの役職を与えられてやって来たんだ。 どうやら旧世界でいかがわしい取引をして降格されたらしいぜ。本当かどうかは知らねえが、最初はそんな噂があったさ。 \nだが、噂のひとつやふたつ、ない奴なんていねえだろ？";
			link.l1 = "汚い仕事だと……それは面白いな。他には何かあるか？";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			dialog.text = "そうだな、何と言えばいいか……大佐は自分の身の安全に非常に気を配っている男のようだぜ。この辺りは海賊や盗賊、 インディアンやら他のならず者どものせいで確かに危険だが、 旦那コマンダンテは護衛を何人も連れずに家を出ることは決してないんだ\nあいつの屋敷はこの街にあって、まるで小さな要塞みたいになってる。使用人たちは武装してるし、 窓もきっちり格子で塞がれてるぜ。";
			link.l1 = "でも昼間は牢屋で働いてるんじゃねえか？";
			link.l1.go = "Consumption_10";
		break;
		
		case "Consumption_10":
			dialog.text = "ああ、でもあの屋敷は基本的に待ち伏せや侵入を待っているようなもんだぜ。\nまあ、旦那コマンダントはどうやらあそこにあまり戻らねえらしい――本物の要塞のほうが好みってわけさ、へへ。";
			link.l1 = "助かったぜ、ありがとう。また後でな。 "+npchar.name+"!";
			link.l1.go = "Consumption_11";
		break;
		
		case "Consumption_11":
			DialogExit();
			if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
			else AddQuestRecord("Consumption", "5");
			DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
			pchar.questTemp.Consumption = "current";
		break;
		
		case "Consumption_12":
			dialog.text = "フアン？どのフアンだ？ここにはたくさんいるし、普通は名字があるもんだぜ……せめてあだ名くらいはあるだろう……";
			link.l1 = "ちょっと考えてたんだが……もしかしてあいつのあだ名は「消耗」ってやつじゃねえか、聞いたことあるか？";
			link.l1.go = "Consumption_13";
		break;
		
		case "Consumption_13":
			dialog.text = "ああ神様、またその話かよ！いや、ありがたいことに聞いてねえよ。誓うぜ！さあ、話題を変えよう。頼むから！";
			link.l1 = "わかったよ、落ち着けって…";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption_1 = "true";
		break;
		//<-- Цена чахотки
		
		//--> Оковы Азарта
		case "OZ_Tavern_1":
			dialog.text = "ハビエルはカード賭博師で、いかさま師で、詐欺師だ。いつも酒場にたむろしては、 誰かからペソを巻き上げようと狙ってやがる。";
			link.l1 = "そうか、他の怪しい取引では目撃されてねえのか？もしかして、あいつに敵がいるんじゃねえか？";
			link.l1.go = "OZ_Tavern_2";
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_1");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Tavern_2":
			dialog.text = "そうだな、あいつの首を絞めてやりたいと思ってる奴の方が、友達よりずっと多いってことさ。\nだが、あいつに本当に影響を与えられる人物の名前が知りたいなら、千ペソかかるぜ。\n払うなら――全部教えてやるよ。";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "わかったよ、金を持ってけ、この強欲ジジイめ。";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "この話はまた後でしよう。今はその金額を持ってねえんだ。";
				link.l1.go = "exit";
				pchar.questTemp.OZ_Tavern_2 = true;
				AddLandQuestMark(npchar, "questmarkmain");
			}
		break;
		
		case "OZ_Tavern_2_1":
			dialog.text = "船長、千ペソ持ってきたか？";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "あるぜ。受け取れ、この強欲じじい。";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "くそっ。すぐ戻るぜ。";
				link.l1.go = "exit";
			}
		break;
		
		case "OZ_Tavern_3":
			dialog.text = "そうそう、これでこそ話が進むってもんだ。ハビエルはな、ただの賭博の借金だけじゃねえんだよ。ある時、 骨董品の商売に手を出してみたんだが、まあ予想通り、うまくはいかなかったんだ。最初はそこそこ順調だったが、 ある珍しい品を手に入れるチャンスが舞い込んできてな\nその話にすっかり熱くなっちまって、資金を求めて金貸しを片っ端から回ったんだ。当然、 誰も一銭も貸しちゃくれなかった。だが、同じく骨董品に取り憑かれた男を見つけて、 そいつから十五万ペソも借りちまったんだ。あとは、まあ、想像つくだろう\n見事に騙されて、今じゃその借金が首に重くのしかかってる。返したのはほんのわずかで、 どう見ても残りを返す気なんてさらさらねえ。しかも貸主は取り立て屋まで雇って脅してるってのによ\nハビエルが借りてる相手はフェリペ・アラルコンだ。あいつの家は銀行の向かいにある――すぐに分かるさ、入り口に柱が立った立派な屋敷だからな。";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_2");
			AddDialogExitQuestFunction("OZ_Felip_1");
			DelLandQuestMark(npchar);
		break;
		//<-- Оковы Азарта
		
		case "guardoftruth":
			dialog.text = "あいつのことは覚えてるぜ。よく俺の酒場に寄ってたが、あまり喋らなかったな。ラムを何杯か引っかけて、 客とひそひそ話してはすぐ出ていった。あのフリゲートの連中みたいに、いつも陰気で真面目だったよ。 刃物をすぐ抜けるようにしてる、危なそうな傭兵どもだったな\nあのフリゲートは宝でいっぱいだって噂もあったが、そんな話は信じちゃいねえ。 高価な積荷を護衛もなしに一隻で運ぶなんてありえねえからな。奴らはここに一日いただけで、すぐ出ていった。 ヨーロッパに向かったって聞いたぜ。それが俺の知ってるすべてだ。";
			link.l1 = "なるほどな。まあ、少しはマシってとこか……";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "40");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
