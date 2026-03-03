// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "話せ、聞いてやる";
			link.l1 = "俺が間違ってた。さらばだ。";
			link.l1.go = "Exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "ここで疫病が発生していると聞いたが、間違いないか？";
				link.l1.go = "Consumption";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "その通りだ、だから理由もなく地下牢に来るんじゃねえぞ。で、なんでこれに興味があるんだ？";
			link.l1 = "ただの興味だ。もし俺の連中が酒を飲みすぎて騒ぎすぎてここにぶち込まれたら、 黄色い布でも用意しといたほうがいいのか？";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "あいにく、旦那、もし冗談だったとしても俺にはわからねえよ。牢屋はじめじめして寒い、気候は知ってるだろう。 ここじゃ肺病がよく出るんだ。食い物を部屋まで運ばせるのにも部下に手当てを払わなきゃならねえ。 あそこを見回るのは重労働と同じくらい嫌がられてるぜ。";
			link.l1 = "申し訳ないが、どれほど深刻なのか知りたかっただけだ。";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "あまりにも深刻だ。こっちには医者すらいねえ、あいつもクソみてえな肺病で死んじまったからな。 今じゃ地元の駐屯地から来る衛生兵が週に一度だけ囚人を診るだけだぜ。だが、 こんな浮浪者や犯罪者どもなんざ誰も気にしやしねえさ。\n大抵の連中は、こいつらがこんな運命を迎えるのも当然だと思ってるし、反論するのも難しいぜ。";
			link.l1 = "俺の医学の知識は大したことねえが、知ってる限りじゃ、肺病ってのは危険で致命的だが、 ここみてえに数日で人を殺すもんじゃねえ。普通は何ヶ月も、あるいは何年も苦しむもんじゃねえのか？";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "今言った通り、お前は医者じゃねえんだろう？だったら病気の特徴について語るなんざ…でたらめな嘘にすぎねえじゃねえか。俺はただ、うちの医者が病に倒れる前に言ってたことを繰り返しただけだ。 だからお前の好奇心や皮肉な態度が理解できねえ。ここじゃ人が死んでいくんだぞ！";
			link.l1 = "さっき「奴らは自業自得だ」と言ったばかりじゃねえか？";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "もう十分だ、旦那！俺とあんたには、機知を競い合うより他にやるべきことがあるだろう。ドアはすぐ後ろにあるぞ。";
			link.l1 = "わかった、無礼を許してくれ、もう出ていく。";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			DialogExit();
			npchar.quest.Consumption = "true";
			pchar.questTemp.Consumption.Commandant = "true";
			AddQuestRecord("Consumption", "3");
			pchar.quest.Consumption.win_condition.l1 = "location";
			pchar.quest.Consumption.win_condition.l1.location = "PortSpein_houseF2";
			pchar.quest.Consumption.function = "Consumption_CommandantHouse";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
