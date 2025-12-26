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

		case "Juli":
			dialog.text = "...";
			if (pchar.sex == "woman")
			{
				link.l1 = "お嬢さん、あなたが微笑まないとポルトープランスの魅力も色あせると言われてますよ。\n今日は、まさにそんな日みたいですね。\n率直に申し上げますが、何かお悩みでも？";
			}
			else
			{
				link.l1 = "お嬢様、あなたの美しさと気品の噂は私の耳にも届いておりますが、実際にお会いしてみると噂以上でございます。\nあなたが微笑まない日はポルトープランスの魅力も色褪せる、とも聞きましたが、 どうやら今日はまさにその日でございますね。\nあなたの心を曇らせた不届き者の名をお教えください。必ずや私が決闘を申し込み、 再びその麗しき笑顔を取り戻してみせましょう。";
			}
			link.l1.go = "Juli_2";
			DelLandQuestMark(npchar);
		break;

		case "Juli_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "ああ、お嬢さん、あなたのご配慮には心打たれます……正直に申しますと、そのご心配に私は胸を動かされました。\nしかし、残念ながら、私の悲しみの原因は、ただ会話しただけで晴れるようなものではありません。\n誰かのせいではなく、むしろ、いかに強い意志を持つ者でも抗えぬ運命というものなのです。";
				link.l1 = "状況ですか？ご安心ください、嬢さん、私にとっては "+GetFullName(pchar)+" どんな障害も乗り越えられるさ。何があったのか話してくれ――もしかしたら俺に手伝えることがあるかもしれねえ。";
			}
			else
			{
				dialog.text = "ああ、旦那、あなたは本当に言葉の魔術師ですね。正直に申し上げますと、もう少しで私も微笑んでしまうところでした。 しかし、残念ながら、決闘では私の問題は解決しません。今日を曇らせたのは悪党ではなく、 あなたのような立派な紳士でもどうにもできない事情なのです。";
				link.l1 = "事情ですか？お嬢さん、船長 "+GetFullName(pchar)+" どんな嵐でも乗り越えてみせるぜ！もし俺が失敗したら、最初に通りかかった奴の帽子を食ってやると誓うぜ！";
			}
			link.l1.go = "Juli_3";
		break;

		case "Juli_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "もし本当にお望みなら、何が起きたかお話ししましょう。\nですがまず、この会話は私たちだけの秘密にしてくださると約束していただきたいのです。";
				link.l1 = "お約束いたしますわ、お嬢様。あなたが私に打ち明けてくださることは、たとえ海の底まで持っていくことになろうとも、 決して他言いたしません。";
			}
			else
			{
				dialog.text = "Monsieur "+pchar.lastname+"、あなたは本当に、どんな悩めるご婦人にも笑顔をもたらす才能をお持ちですね。しかし、どうか通りすがりの無実な方々 の帽子にはご慈悲を。どうしてもとおっしゃるなら、私が何があったかお話ししましょう。ただし、 私の言葉は私たちだけの秘密にすると約束してくださいね。";
				link.l1 = "お約束します、マドモアゼル。あなたが私に話すことは、たとえ死の脅しを受けても絶対に秘密にいたします。";
			}
			link.l1.go = "Juli_4";
		break;
		
		case "Juli_4":
			dialog.text = "よろしいですわ。私の部屋から首飾りが消えましたの……ですが、ただの装飾品ではございません。それは、私の心に大切な場所を占める方から授かったものです。その喪失は、 単なる持ち物を失った以上の深い傷のように感じますわ\n誰が犯人なのか、長い間考えましたが、結論は一つしかありません。恐らく、私の召使いの誰かに違いありません。 私の私室に出入りできるのは彼らだけで、あのような貴重な品を欲しがるかもしれませんもの……ですが、この疑いを公にする勇気はありませんの。";
			link.l1 = "まことに繊細な問題ですな、とりわけ慎重さをお望みならなおさら。しかし、私が手を貸すには、 なぜそこまで秘密を厳重に守らねばならぬのか、その理由を理解せねばなりません。我々 が直面する危険を知らぬままでは、思わずして二人とも危機に陥れるやもしれません。誰を避けるべきか、 どんな脅威が闇に潜んでいるのか、教えてください。";
			link.l1.go = "Juli_5";
			if (pchar.sex == "woman")
			{
				link.l2 = "自由に話せないのですか？それなら、嬢さん、私ができるのはせいぜい幸運を祈ることくらいですわ。 私は陰謀や秘密ごとにはまったく向いておりませんの。私の考えでは、町の衛兵の助けを借りれば、 あなたの問題はすぐに解決できるでしょうに。それでも、あなたはこの荒れた海を、 より危険な航路で進むことを選ばれたようですわね。";
				link.l2.go = "Juli_end";
			}
			else
			{
				link.l2 = "はっきり話せないのですか？それならば、どうかお許しください、マドモワゼル。秘密の霧の中では、 私はまったく無力でございます。私は陰でこそこそするような事柄や秘密の取引にはほとんど興味がありません。 あなたの悩みは実に単純明快に見えます――町の衛兵が解決できる簡単な問題です。それなのに、 あなたはまるでヨーロッパ王宮にふさわしい陰謀に仕立て上げようとしているようですね。";
				link.l2.go = "Juli_end";
			}
		break;

		case "Juli_end":
			dialog.text = "「これが名高い船長の "+GetFullName(pchar)+" 困難に直面した時、最初の複雑さで逃げ出すのか？お前の才能はラム樽の数を数えるか、 波止場の商人と口喧嘩でもしていた方が向いているんじゃねえか。俺が頼むのはただ一つだ――もし少しでも名誉があるなら、今話したことは絶対に他言しないでくれ。\nそれじゃあ、ごきげんよう、船長。";
			link.l1 = "...";
			link.l1.go = "Juli_end_2";
		break;
		
		case "Juli_end_2":
			DialogExit();
			CloseQuestHeader("UV");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "Juli_5":
			dialog.text = "「賢く話すな、」 "+GetAddress_Form(NPChar)+"。では真実をお話しします。この首飾りは、私の叔父が激しく憎んでいる男――この島のフランス領の総督から贈られたものです。叔父はその人物との接触はもちろん、 名前を口にすることさえ禁じています。もし叔父がこの贈り物の出所を知れば、その報いは私だけでなく……";
			link.l1 = "もう何もおっしゃらなくて結構です、お嬢様。すべて承知いたしました。ご安心ください、 必ずや首飾りを極めて慎重に取り戻し、まるで竜が宝を守るようにあなたの秘密をお守りいたしますわ。";
			link.l1.go = "Juli_6";
		break;

		case "Juli_6":
			dialog.text = "「心より感謝申し上げます。」 "+GetSexPhrase("Monsieur "+pchar.lastname+"",""+pchar.name+"")+"。あなたの勇気とご理解は、この困難な時代に私の心を温めてくれます。私の秘密があなたの手で安全に守られていると、 私は心から信じております。幸運の風が、この繊細な冒険であなたの帆を満たしますように。";
			if (pchar.sex == "woman")
			{
				link.l1 = "「行動する者にこそ運命は微笑むのです、お嬢さん。ご安心ください――必ずやあなたの首飾りを取り戻してみせます、潮が浜に戻るように。」";
			}
			else
			{
				link.l1 = "勇気ある者には幸運が微笑むのです、お嬢さん。あなたの大切な首飾りを取り戻したその時には、 しかるべきその優雅な手元へ必ずお返しいたします。";
			}
			link.l1.go = "Juli_7";
		break;

		case "Juli_7":
			DialogExit();
			
			NextDiag.CurrentNode = "Juli_7_again";
			AddQuestRecord("UV", "2");
			AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
			
			pchar.questTemp.UV_Lavochniki = true;
		break;

		case "Juli_7_again":
			if (CheckCharacterItem(PChar, "SM_necklace_Julie"))
			{
				dialog.text = "ああ、船長、お戻りになったのですね！何か知らせはありますか？ どうか私のネックレスを取り戻してくださったと言ってください。お願いです。";
				link.l1 = "ジュリー、もう心配はいらない。ネックレスは取り戻したよ。こうして本来あるべき場所――君の繊細な手に返せることが、俺にとって何よりの喜びだ。";
				link.l1.go = "Juli_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "ああ、船長、お戻りになったのですね！何か知らせはありますか？ どうか私の首飾りを取り戻してくださったと言ってください。お願いします。";
				link.l1 = "残念だが、ジュリー、まだ見つかっていないんだ。捜索は続いている。だが安心してくれ――君の大切なネックレスを必ず取り戻すまで、俺はどんな手も尽くすつもりだ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Juli_7_again";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Starpom_1":
			dialog.text = "ごきげんよう、旦那。どんなご用件で我々の船に乗り込んできたんだ？";
			link.l1 = "俺はトリスタン・ルニエ船長を探している。奴の懐をたっぷり潤す提案を持ってきたんだ。";
			link.l1.go = "Starpom_2_sneak";
			link.l2 = "私はトリスタン・ルニエ船長と少々繊細な件について話さねばなりません――個人的な事情でして、ご理解いただけるでしょう。";
			link.l2.go = "Starpom_2_fortune";
			DelLandQuestMark(npchar);
		break;

		case "Starpom_2_sneak":
			dialog.text = "船長は上陸してしまいました、申し訳ありません。もしお急ぎのご用件でしたら、 町のどこかでお探しになるとよいでしょう。";
			link.l1 = "彼の行き先をご存知ですか？この港に来るとき、特に好んで立ち寄る場所などはありますか？";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Starpom_2_fortune":
			dialog.text = "船長は上陸してしまったんだ、申し訳ない。もし急ぎの用なら、町のどこかで見つかるかもしれないぜ。";
			link.l1 = "彼の行き先をご存じですか？この港に来た時、特によく立ち寄る場所などありますか？";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Starpom_3":
			dialog.text = "「申し訳ありません」 "+GetAddress_Form(NPChar)+"しかし、船長は自分の行動については口を閉ざしているんだ。俺が知っているのは、数時間前に上陸したってことだけさ。 ";
			link.l1 = "それだけでも助かるぜ。手を貸してくれて感謝する。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RasprashivaemZhiteley");
		break;

		case "Captain_1":
			if (pchar.sex == "man")
			{
				dialog.text = "貴様は何者だ？どんな権利があって俺の私室に無断で踏み込むつもりだ！？";
				link.l1 = "俺は船長だ "+GetFullName(pchar)+"。それで、少々重要な用件で参りました。";
			}
			else
			{
				dialog.text = "「それで、あなたはどなたですの？今夜はどなたにも招待状をお出しした覚えはありませんわ。ですが、 正直に申し上げますと、予期せぬ訪問者の中には……他の方よりも興味深い方もいらっしゃいますの。こんな麗しい方が、私のつましい部屋に何のご用で？」";
				link.l1 = "俺は船長だ "+GetFullName(pchar)+"。俺の訪問は遊びじゃなくて、仕事の用件だぜ。";
			}
			link.l1.go = "Captain_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Captain_2":
			if (pchar.sex == "man")
			{
				dialog.text = "商売だと？どんな用件なら、こんな無作法な邪魔を正当化できるというのだ？";
				link.l1 = "至って単純な話だ。お前が持っている首飾りを、俺は取り返しに来たのさ。";
			}
			else
			{
				dialog.text = "商売とな？実に興味深い……その並外れた魅力を持つご婦人が、わざわざ私の私室までお越しになるほどの切迫した商談とは、一体何でございますの？ ";
				link.l1 = "甘い言葉はいらん、旦那。お前が持っている首飾りを受け取りに来たんだ。そうさ、ちゃんと持ってるのは分かってるぜ。 ";
			}
			link.l1.go = "Captain_3";
		break;

		case "Captain_3":
			if (pchar.sex == "man")
			{
				dialog.text = "はっ！ネックレスだと？確かに最近そんな品を手に入れたが、それがあんたに何の関係があるんだ？まさか、 最初に要求してきた見知らぬ奴に俺の物を渡すとでも思ってるのか？";
			}
			else
			{
				dialog.text = "首飾りか？なるほど……確かに最近そんな小物を手に入れたな。さて、船長、 どうやって俺の正当な持ち物であるこの宝飾品を手放させるつもりだ？";
			}
			if (sti(pchar.Money) >= 5000)
			{
				link.l1 = "この品に五千ペソをお支払いする用意がございます。\nこれは立派な額でして、同じくらい素晴らしい、いや、さらに豪華な装飾品をお求めいただけるでしょう。その間に、 この特別な首飾りは、金銭的価値をはるかに超えて大切に思う者の元へ戻ることになります。";
				link.l1.go = "Captain_4_commerce";
			}
			link.l2 = "はっきり言わせてもらうぜ、旦那。お前の選択肢はもうほとんど残っちゃいねえ。 素直にその首飾りを差し出して生き延びるか、抵抗して俺がお前の死体から奪い取るかだ。決めるのはお前だが、 早く決断したほうが身のためだぜ。";
			link.l2.go = "Captain_4_leadership";
		break;

		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				dialog.text = "五千だと？なるほどな、船長、あんたの交渉力には感心するぜ。ほらよ、そのガラクタがそんなに大事なら持っていきな。 ";
				link.l1 = "旦那のご賢明さはご寛大さに匹敵します。このご決断、後悔なさいませんよ。";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				Notification_Skill(true, 25, SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "この首飾りは、最初に金をちらつかせた浮浪者に渡すために手に入れたものではない！ これは妻への贈り物として用意したのだ、この件についてはもう聞きたくない。これ以上ここにいるなら、 護衛を呼んで追い出させるぞ、さっさと立ち去れ！";
				link.l1 = "紳士の協定を断るなら、俺はもっと野蛮な手段で求めるものを手に入れるまでだ。";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				Notification_Skill(false, 25, SKILL_COMMERCE);
			}
		break;
		
		case "Captain_4_leadership":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 45)
			{
				dialog.text = "うぐっ…この生意気な小僧め…てめえのガキみてえな脅しで俺がビビると思ってんのか？はっ！てめえ、誰に喧嘩売ってるかわかってねえな！";
				link.l1 = "俺はお前が誰だろうと興味ねえ。さっさと首飾りを渡せば、すぐに立ち去ってやる。\nそれとも、お前にとっちゃ何の意味もねえガラクタのために、本気で死ぬ覚悟があるのか？";
				link.l1.go = "Captain_4_leadership_2";
				notification("Check passed", SKILL_Leadership);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "俺はこのネックレスをお前みたいな奴と値切るために買ったんじゃねえ！これは女房への贈り物だ、 お前には関係ねえだろ。さっさと出て行け、さもねえと力ずくで叩き出すぞ！";
				link.l1 = "おとなしく渡さねえなら、力ずくで奪うまでだぜ。";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Skill not high enough (45)", SKILL_Leadership);
			}
		break;

		case "Captain_4_leadership_2":
			dialog.text = "くたばれ、その呪われた首飾りもろとも！持っていけ。持っていって、俺の気が変わらないうちに出ていけ。";
			link.l1 = "賢明な判断だ！さらば。";
			AddDialogExitQuestFunction("UV_Ozherelie");
			GiveItem2Character(pchar, "SM_necklace_Julie");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "Juli_22":
			dialog.text = ""+pchar.name+"、あなたのおかげで私の心に再び喜びが戻りました！あなたは首飾りだけでなく、 私の魂の一部まで取り戻してくれたのです。あなたの高潔さには感服いたします、 そしてあなたの勇気についてできる限り多くの人に伝えることを約束します！";
			link.l1 = "どうか、お嬢さん、名声のために返したわけではありませんの。あなたの微笑みこそ、私が本当に望む唯一の報酬ですわ。 ";
			link.l1.go = "Juli_23";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

		case "Juli_23":
			dialog.text = "「あなたは本当に謙虚ですね」 "+pchar.name+"。しかし、どうかこのドゥブロン金貨の入った箱をお受け取りください。 あなたが私の贈り物を受け取ってくださることで、私は本当にふさわしい感謝を伝えられたと感じられるのです。";
			link.l1 = "どうかご無理をなさらないでください、お嬢さん。あなたの優しいお言葉は、 どんなドゥブロン金貨の箱よりも私にとって価値があります。";
			link.l1.go = "Juli_24_nobility";
			link.l2 = "もしそれであなたの心が安らぐのなら、マドモアゼル、あなたの贈り物を受け取りますわ。\nですが、私は報酬のためにこれをしたのではありませんのよ。 "+GetSexPhrase("あなたの承認","あなたの感謝")+" 「このダブロン金貨なんかより、俺にはずっと大事なものなんだ。」";
			link.l2.go = "Juli_24_chest";
		break;
		
		case "Juli_24_nobility":
			dialog.text = "すっかり聞き忘れてた――誰がネックレスを盗んだか知ってるか？";
			link.l1 = "あたしが知ってるのはね、お嬢さん、商人がジゼルって名の誰かからそれを受け取ったってことだけさ。状況からして、 彼女が売るつもりの宝石はこれが最後じゃないかもしれないよ。";
			link.l1.go = "Juli_25";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;

		case "Juli_24_chest":
			dialog.text = "すっかり聞き忘れてたんだが――誰がその首飾りを盗んだか知ってるか？";
			link.l1 = "俺が知ってるのはな、嬢ちゃん、商人がジゼルって名の誰かからそれを受け取ったってことだけだ。状況からして、 彼女が売ろうとしてる宝石はこれが最後じゃねえかもしれねえぜ。";
			link.l1.go = "Juli_25";
			GiveItem2Character(PChar, "chest");
		break;

		case "Juli_25":
			dialog.text = "ジゼル？でも、あの子は私のメイドよ！前から疑ってはいたけれど……信じたくなかったの。最悪なのは、きちんと罰することもできないってこと。彼女に秘密を暴かれたら――それだけは絶対に許せないわ。";
			link.l1 = "それでどうするんだ？あいつを野放しにして、これからもお前から盗ませ続けるのか？";
			link.l1.go = "Juli_26";
		break;

		case "Juli_26":
			dialog.text = "いや、もちろんそんなことはしないさ。まずは、あいつが俺の近くにいないことを確認する。それから、 罰が別の誰かから下ったように見せかけて、どうやって懲らしめるか考えるぜ。";
			link.l1 = "女の狡猾さは危険な武器だ、とりわけあなたのように洗練されて鋭い方の手にかかればなおさらです。\nきっとあなたの侍女は、すでに勝負がついていて、それが自分に不利だということすら気づいていないのでしょう。";
			link.l1.go = "Juli_27";
		break;

		case "Juli_27":
			dialog.text = "ああ、船長……策を弄するのは本意じゃねえが……時にはずる賢さだけが道を切り開くこともあるんだ。";
			link.l1 = "確かに、ジュリー。君を置いていくのは嫌だが、義務があるんだ。俺がやらなきゃ、誰が船員たちの面倒を見るんだ？";
			link.l1.go = "Juli_28";
		break;

		case "Juli_28":
			dialog.text = "「また会う日まで」 "+pchar.name+"。どうかもっと頻繁に我々の港へお越しください。わが町にはひどく不足しているのです\n "+GetSexPhrase("あなたのような高貴で勇敢な男たち。","あなたのように気高い心と勇敢な魂を持つご婦人方。")+"";
			link.l1 = "お世辞が上手ですね、お嬢さん。あなたの美しい街に戻る機会を一度たりとも逃さないと約束します。\nまたお会いしましょう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_Juli_GoodEnd");
		break;
		
		case "Juli_31":	
			if (CheckAttribute(pchar, "questTemp.UV_ojerelie_Julie"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+pchar.name+"！なんてこった！まだ海を征服し続けているのか？";
						link.l1 = "お会いできて嬉しいです、お嬢さん。できる限り征服していますが、海は相変わらず容赦なく気まぐれですね。\nそしてあなたは――少しは静かな時間を楽しんでいますか？";
						link.l1.go = "Juli_32";
					break;

					case 1:
						dialog.text = "ああ、船長 "+pchar.lastname+"、またお会いできて本当に嬉しいです！お元気でいらっしゃいますか？";
						link.l1 = "あたしもお会いできて嬉しいですわ、マドモアゼル。\n商売はいつも時間と手間がかかりますけれど、こうしてお会いできると一日が明るくなりますの。\nあなたの日々はいかがでしたか？";
						link.l1.go = "Juli_33";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Captain "+pchar.lastname+"「また戻ってきたのか？このつまらねえ町に、まだお前が一握りの金貨のために裏切ってない奴が本当に残ってるのか？」 ";
						link.l1 = "お嬢様、あなたのお気持ちは理解しておりますが、私は正しいと信じる行動をいたしました。\n時には正しい決断が苦しみをもたらすこともありますし、あなたを傷つけてしまったことを悔やんでおります。";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;

					case 1:
						dialog.text = "Captain "+pchar.lastname+"「またか？お前の欲はどこまで深いんだ、この町を放っておけず、次の獲物を探しているのか？」";
						link.l1 = "お嬢さん、私の行動であなたを傷つけてしまい申し訳ありませんが、私は自分の良心に従って行動したのです。";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;
				}
			}
			SetTimerFunction("UV_Julie_HelloAgain", 0, 0, 1);
		break;

		case "Juli_32":	
			dialog.text = "最近は穏やかで静かな日々が続いております――何も平和を乱すものはありません。どうかもっと頻繁に我々の港へお越しください、船長。 きっとお望みのものは店の中にも外にもすべて揃っておりますよ。";
			link.l1 = "ありがとうございます、お嬢さん。もっと頻繁に立ち寄るようにしますね。きっとあなたの町には、 まだまだ素敵な驚きがたくさん隠れているはずです。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;
		
		case "Juli_33":	
			dialog.text = "おかげさまで、船長、今ではずっと穏やかな日々を過ごせています。\nまたぜひお越しくださいね。";
			link.l1 = "もちろんでございます、お嬢様。あなたの町はいつもとても良い印象を残しますわ。では、またお会いしましょう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_repeat_residence_1":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Captain "+pchar.lastname+"、また会ったな。驚きだろう？";
					link.l1 = "今日は運命が私たちの出会いに微笑んでいるようですわ、お嬢さん。";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;

				case 1:
					dialog.text = "Captain "+pchar.lastname+"、また道が交わったようだな。";
					link.l1 = "確かにそうです、お嬢さん。またお会いできて嬉しいですわ。";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;
			}
		break;

		case "Juli_34_zlaya":
			switch (rand(1))
			{
				case 0:
					dialog.text = "どうやら俺たち、ちょっと会いすぎじゃねえか、船長。\nそれとも、一度裏切った奴らから離れられねえってことか？";
					link.l1 = "お嬢さん、私たちの出会いはまったくの偶然ですが、あなたの苦々しさは理解できます。\nただ、いつか私の理由も分かっていただけることを願っています。";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;

				case 1:
					dialog.text = "今度は何の用だ？まさかこんな偶然があるほど運が悪いわけじゃねえだろう。……それとも、自分の恥を俺に思い出させに来たのか？";
					link.l1 = "お嬢様、邪魔をしたり、昔の傷をえぐるつもりはまったくありませんでした。この出会いは本当に偶然なのです。";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;
			}
		break;

		
		
		
		
		
		
		
	}
}