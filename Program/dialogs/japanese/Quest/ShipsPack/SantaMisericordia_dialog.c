void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			link.l1 = "「何でもない。」";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Alamida_church":
			dialog.text = "……そして聖霊の名において。アーメン。";
			link.l1 = "教会で軍人を見ることは滅多にないな。";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "多くの者は、信仰と剣は相容れないと思っている。\nだが、外科医は癒やすために切るのではないか？父親は守るために罰するのではないか？";
			link.l1 = "言い訳に聞こえるな。";
			link.l1.go = "Alamida_church_3";
			link.l2 = "それは賢明だな。時には残酷さも必要だぜ。";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "勘違いしているな。これは正当化じゃない――理解だ。俺が最初にこの務めを始めた頃は、一人ひとりの死が……つらかった。だが、その後……目が覚めたんだ。「残酷さとは、至高の愛の現れだ」とな。";
			link.l1 = "祈りは任せるぜ。";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "ああ…そうだ！まさにあいつが言った通りだ、俺をこの道へ導いた奴がな。「力なき慈悲は無用、手なき剣のようなものだ」 とな。";
			link.l1 = "祈りは任せるぜ。";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "俺たち全員のために祈ってくれ。俺たちがやったことのために……そして、これからやらなきゃならねえことのためにもな。";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "七パーセントの不足だ。前回は五パーセントだった。荒れ果てた庭の雑草みたいに増えてやがるな……";
			link.l1 = "この町に新しい総督が来たのか？";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "何だって？ああ、違う。閣下はあそこ、隅にいらっしゃる。\n私はドン・フェルナンド・デ・アラミダ、王室監察官だ。";
			link.l1 = "大変な仕事だろうな。";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "腐敗と戦う中で一番辛いのは何かわかるか？罪を犯した者が必ずしも悪人とは限らねえ。奴らにも子供や家族がいるんだ。 \nそれでも毎回、自分に言い聞かせなきゃならねえ――毒はどんな金の杯に注がれても、毒のままだってな。";
			link.l1 = "だが、そこまで厳しく裁けるものか？俺たち皆、人間じゃねえか……";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "お前は甘すぎるぜ。奴らを更生させるには牢屋しかねえんだ。";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "狼に情けをかけるのは羊に残酷だ。そう言ったのは……賢者だった。日が経つごとに、その知恵がますます身に染みるんだ。";
			link.l1 = "これ以上仕事の邪魔はしないよ。";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "ふむ。俺も昔は同じように考えていたんだ。しかし、牢獄じゃあ単純すぎる。もっと別のものが必要だ……浄化だ。";
			link.l1 = "これ以上は仕事の邪魔をしないでおくよ。";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "ああ。書類は待ってくれないからな。だが時々、 ここの一つ一つの数字の裏に誰かの運命が隠れているような気がするんだ。";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "「注意深く聞いているぜ」 "+GetAddress_Form(NPChar)+"？どうしてこんなふうに道端で俺に声をかけてきたんだ？";
			link.l1 = "お前は他の連中とは違って目立ってるぜ。";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "ドン・フェルナンド・デ・アラミダ、王室検査官だ。今日はお前が最初の物好きだな。みんな隠れて、 みんな俺を恐れている。だが、正直者には恐れるものなどない。さて、それは何を意味していると思う？";
			link.l1 = "お前の評判が奴らを怯えさせてるってことか？";
			link.l1.go = "Alamida_city_3";
			link.l2 = "「正直者は少ないのか？」";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "面白いな。俺もそう思ってたぜ。だがな、気づいたんだ――恐怖は人を清めるってな。人間は怖がると、もっと正直になる。自分の本性に近づくんだ。神にもな。";
			link.l1 = "面白い考えだな。俺は行かなくちゃ。ごきげんよう、フェルナンド旦那。";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "面白いな……お前は俺の知っていた奴と同じように考えるんだ。残念だが、誰もがこの真実を受け入れられるわけじゃねえ。";
			link.l1 = "面白い考えだ。行かねばならん。ごきげんよう、フェルナンド殿。";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "良いか？ああ、たぶんそうだ。正しいことであればな。";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_DlgExit");
		break;
		
		case "Alamida_repeat":
			dialog.text = "他に何かありますか、船長？";
			link.l1 = "いや、ドン・フェルナンド、ただ挨拶しただけだ、他には何もないぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "剣を持った乙女だと？いやあ、こんな光景をこの目で見る日が来るとは思わなかったぜ。\nそれで、お前は何者だ、セニョリータ？『聖なる慈悲号』に攻撃を仕掛けるとは、いい度胸じゃねえか？";
				link.l1 = "ヘレン・マッカーサー船長だ。それと、その驚いた顔、よく見覚えがあるぜ。";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "よくもそんなことをしやがったな！？「ホーリー・マーシー」を襲うなんて！？あの船は王の意志を運ぶ船だぞ、そして…まあいい。せっかくだ、教えてくれ――なぜだ？なぜお前はこんな狂気を選んだんだ？";
				link.l1 = "俺は海賊だぜ。それに、お前のガレオン船はきっと宝でいっぱいだろうな。";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "なんて美しい船だ……俺のものにしなきゃ気が済まねえ。";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "俺はあんたの国の敵だ、フェルナンド旦那。";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "ただなんとなくだ。理由なんてねえだろ？";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "お前はまるで我らの船を守る聖母マリアのようだな……同じくらい美しい。だが、聖母は正しき者を守るが、お前は……";
			link.l1 = "お前の船をもらいに来たんだ。ここでお世辞は通用しねえぞ、ドン・フェルナンド。";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "悲しいことだな。ならば、俺が力づくで謙虚さを教えてやるしかねえようだ。";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "ああ、そうだ。もちろんだ。金だ。いつも金だ。魂を蝕む毒……そのためにお前は死ぬのだ。";
			link.l1 = "大げさにするなよ。これはただの商売だ。";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "船倉の金貨はすべて、罪人たちが清めのために支払ったものだ。\n欲しいのか？ならば奴らと同じ運命を辿れ。";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "「ホーリー・マーシー」を欲しがった者は多い。その美しさが多くの船長の破滅を招いたのさ。";
			link.l1 = "ならば、俺が最初にそれを手に入れるぜ。";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "力なき慈悲は無用だ、手のない剣と同じだ。\nこの教訓を今日お前に叩き込んでやる。";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "そういうことか。帝国の偉大さにまた一人嫉妬してるってわけだな。";
			link.l1 = "偉大さだと？お前の堅苦しいやり方がこの世界を停滞させてるんだ。";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "自分に嘘をつくな。スペインへの恐怖が、お前をもっと正直にさせるんだ。本当の自分に近づくってことさ。 今に自分でわかるだろう。";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "狂人か。それとも俺を試すために送り込まれたのか？";
			link.l1 = "すべてに理由が必要ってわけじゃねえよ、旦那。";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "「お前みたいな奴が一番危険だ」とあいつは言ってた。\nだが、これで俺の戦いの腕がさらに強くなるだけだぜ。";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_SecondRound":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_1");
		break;
		
		case "Alamida_abordage_TrirdRound":
			if (startHeroType == 4)
			{
				dialog.text = "…なんという精神力……なんという意志……";
				link.l1 = "驚いたか？";
			}
			else
			{
				dialog.text = "悪くねえな。こんな手強い相手に会うのは久しぶりだぜ。";
				link.l1 = "休む暇なんてやらねえぞ。";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "俺は警告されていた……こんな試練について。戦士の信仰すら揺るがすほどの美しさについてな。";
				link.l1 = "いつもそんなに単純なことをややこしくするのか、ドン・フェルナンド？";
			}
			else
			{
				dialog.text = "主は正しき大義に仕える者に力を与えてくださる。\nだが……時に、俺が何に仕えているのか、もう分からなくなることもある。";
				link.l1 = "疑ってるのか？";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "簡単？いや……もっと深い意味があるはずだ。これは試練だ。俺が間違っているはずがない。";
			}
			else
			{
				dialog.text = "いいや。疑うなと教えられた。決してな。";
			}
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_TrirdRound_4";
		break;
		
		case "Alamida_abordage_TrirdRound_4":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_2");
		break;
		
		case "Alamida_abordage_Molitva":
			dialog.text = "待て……待ってくれ。お前の勝ちだ。俺は傷を負い、血を流している。死ぬ前に祈らせてくれ。";
			link.l1 = "「よし。」";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "主よ……この試練の時に、私の罪をお許しになり、力をお与えください。倒れた仲間たちの魂をお恵みください。 忠実な水夫たちは、正義を担っていると信じて死んでいきました\n父よ、私はあなたの教えに従い、不正と戦おうと生きてきました。しかし、 あなたの息子がアラミダ家の名誉を汚しました。お許しください\n祖国よ……私は誠実に、真摯に仕えると誓いました。しかし、私の熱情も怒りも……私は自分が戦おうとしたものになってしまいました\nディエゴ……もしかして、彼は嘘をついていたのか？この間ずっと……もしそうなら、私はなんと不幸なのだろう\nそしてこの女にも祝福を、主よ。もしかすると、あなたの最後の慈悲で彼女を私のもとに遣わしたのかもしれません……私がどれほど道を踏み外したかを知るために。アーメン。";
			}
			else
			{
				dialog.text = "主よ……この試練の時に、私の罪をお許しくださり、力をお与えください。倒れた仲間たちの魂をお恵みください。 忠実な水夫たちは、正義を背負って死んでいきました\n父よ、私はあなたの教えに従い、不正と戦おうと努めてきました。しかし、 あなたの息子がアラミーダ家の名誉を汚しました。どうかお許しください\n祖国よ……私は誠実に、真心をもってあなたに仕えると誓いました。しかし、私の熱情と怒りが……私は自らが戦おうとしたものになってしまいました\nディエゴ……もしかして、彼は嘘をついていたのか？この間ずっと……もしそうなら、私はなんと不幸なのだろう\n聖母マリアよ、私たちのために神に祈り、あなたの慈悲をお与えください。アーメン。";
			}
			link.l1 = "俺には見覚えがねえな、フェルナンド旦那。今じゃまるで別人みてえだ。\nそれで、誰のことを話してたんだ？";
			link.l1.go = "Alamida_abordage_Molitva_3";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Church_Stay_1", "", 5.0);
		break;
		
		case "Alamida_BitvaEnd":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SantaMisericordia_CanLeaveCauta", 5);
		break;
			
		case "Alamida_abordage_Molitva_3":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_3");
		break;
		
		//Элен
		case "Alamida_Helena":
			dialog.text = "俺の船長、おめでとうございます！なんて激しい戦いだったんだ。あの船長は腕が立った、本当にすごかった。 でもあんたは……あんたはそれ以上だったぜ。俺はあんたを誇りに思うよ……";
			link.l1 = "ありがとう、あなた。怪我はない？";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "いや、いや。何度か危なかったと思ったけどな――乗り込む前も、乗り込んでる最中もだ。\nそれで、お前は大丈夫か？";
			link.l1 = "俺は大丈夫だ、改めて礼を言うぜ。船室で休んでてくれ、すぐに俺も行くからな。";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Мэри
		case "Alamida_Mary":
			dialog.text = "チャールズ、大丈夫か？できるだけ早く来たんだ、大丈夫だよな。";
			link.l1 = "大丈夫よ、ありがとう、あなた。だけど、かなり大変だったわ。";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "嬉しいよ！でも……なあ、チャールズ？なんで俺たちはあいつらを襲ったんだ？主はこんなこと、許してくれねえよ。いや、許さない。 この船……まるで大聖堂みてえだ。初めて本じゃなくて本物の教会を見たときみたいに、これを見た瞬間、心が震えたんだ。 そして今、この船は血を流してる！";
			link.l1 = "メアリー……見かけは当てにならないって知ってるだろう。敬虔さの仮面の裏で、 あんたみたいな素朴な信者から金を巻き上げてた連中がいたんだ。わかるか？";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "俺…俺は信じるよ、チャールズ。わかった。ただ…せめてここで見つけた金の一部でも、本当に必要としている人たちに寄付しようぜ？そうすれば、 俺の心も少しは楽になる。";
			link.l1 = "そうするよ、メアリー。約束する。さあ、気持ちを整理して落ち着くんだ。もう全て終わったんだ。";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Томми
		case "Alamida_Tommi":
			dialog.text = "ははっ、まあ、勝利おめでとう、船長！これぞまさに商売ってやつだぜ！このガレオンでこんな大戦利品とはな！..";
			link.l1 = "「今日はいつもよりさらにニヤニヤしてるな、トミー。」";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "ああ、もちろんだぜ！すげえ戦利品だ。それに、あの戦い……まるで革命の時を思い出したぜ。あと……へへっ。";
			link.l1 = "どうした、トミー？さあ、はっきり言えよ。";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "まるで船全体を浮かぶ大聖堂みたいに飾り立てやがってよ。\nあちこちから金をかき集めてきやがるし。\nまさに筋金入りのカトリックの熱狂者だぜ！\n恥さらしで笑っちまうな。";
			link.l1 = "これは財宝船だ、トミー。教会の船じゃねえぞ。";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "俺たちの場合は大して変わらねえさ。どっちにしろ、 あのドンどもやカトリック野郎どもにいい思いをさせてやれて嬉しかったぜ！どっちも大嫌いなんだよ。 今日は本当に楽しかったぜ、ハハハ！";
			link.l1 = "お前は本当に変わらねえな！\nよし、解散だ。ここは全部俺が仕切ってるから安心しな。";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Тичингиту
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "チャールズ船長、俺たちは勝利を手にしたぜ。これは厳しい戦いだった。ティチンギトゥでさえ苦戦したし、 俺は村でも屈指の戦士なんだがな。";
				link.l1 = "そうだな、相棒。奴らはまさに手強い相手だったぜ。";
			}
			if (startHeroType == 2)
			{
				dialog.text = "旦那デ・モントーヤ、船は俺たちのもんだぜ。";
				link.l1 = "よくやったな、Tichingitu。俺もここはちょうど終わったところだ。";
			}
			if (startHeroType == 3)
			{
				dialog.text = "パターソン船長、最後の抵抗は船上で潰された。";
				link.l1 = "遅いぞ、ティッチ！次は俺と一緒に行動したほうがいいぜ。まあ、俺一人でも十分やれるけどな……";
			}
			if (startHeroType == 4)
			{
				dialog.text = "マッカーサー船長、無事か？";
				link.l1 = "ああ、ティチンギトゥ、俺は大丈夫だ、心配してくれてありがとう。\nそれに、船長を疑うのはやめろ――俺はちゃんと自分でうまくやったんだぜ。";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "戦いの最中、精霊たちが俺にこう告げるんだ。なぜ自分たちを殺すのか、と問いかけてくる。 今度は俺が同じことをお前に聞く番だ。ティチンギトゥには、あいつらの目が見えた――まだ悪党じゃねえ。まだな。";
				link.l1 = "ああ、何を言えばいいんだ？俺には答えがないんだ、Tichingitu。";
			}
			if (startHeroType == 2)
			{
				dialog.text = "「お前に質問があるんだ、de Montoya船長。」";
				link.l1 = "聞いてるぜ。";
			}
			if (startHeroType == 3)
			{
				dialog.text = "ティチンギトゥが質問したいんだ、ウィリアム船長、もし許してくれるなら。";
				link.l1 = "承知した。";
			}
			if (startHeroType == 4)
			{
				dialog.text = "俺は疑っちゃいねえ、心配してるんだぜ、船長。";
				link.l1 = "わかった、わかった。お前の目を見れば、まだ何か聞きたいことがあるんだろう。";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "ふむ、あなたの言う通りだな、船長。ここで終わりか？";
				link.l1 = "ああ。もう少し周りを見てから、他のみんなと合流するよ。";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "こいつら、お前と同じ部族じゃねえのか？スペイン人でもねえのか？なんで襲うと決めたんだ？";
				link.l1 = "それは確かだ。しかし、インディアンの部族同士も争ったりしないのか？あるいは、 同じ部族の中でも喧嘩や確執があるんじゃないのか？";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "この船は教会みてえだな。お前は教会と白人の神が嫌いか？";
				link.l1 = "とんでもない。だが、これはただの飾りだぜ？これは財宝船なんだ。まあ、お前らには分からねえだろうな――税金ってものすら知らねえって聞いたぜ。うらやましい野郎どもだ。";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "ああ、正直になれよ。マッカーサー船長、なぜ俺たちはこの浮かぶ教会を襲うんだ？";
				link.l1 = "「浮かぶ教会だと、ははは！いやいや、違うぜ。これは財宝船だ。ふむ、お前さん、いまいち分かってねえな。まあ、 奴らは金を運んでたんだ。フェルナンド・デ・アラミダを倒したってヤンに話したら、 あいつがどれだけ誇らしげになるか想像できるぜ！」";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = "ふむ、あんたの言う通りだな、船長。でもな、インディアン相手だと、白人ほどこういうことは起きねえんだ。";
				link.l1 = "たぶんね。まあ、この男が……俺の邪魔をしてたんだ。";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "正直に言うと、マスコギには城もなければ税金もねえんだ。";
				link.l1 = "そのとおりだ。行っていいぜ、どうせ遅れてるんだしな。あとでこの美しいガレオンをどうするか決めよう。 俺はこういうデカブネは好きじゃねえが、くそっ、こいつは見事だな。";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "ティチンギトゥもお前を誇りに思ってるぜ、船長。\nそして、この激しい戦いでの勝利を祝福する。";
				link.l1 = "ありがとう。さあ、戦利品を分けようぜ。";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "邪魔する気か、de Montoya旦那？";
			link.l1 = "その通りだ。この諸島は俺たち二人には狭すぎる。そして、俺の方がこの地で国家の役に立つんだ。 ココア・リーフを思い出せ――あいつは仲間にとって害の方が大きかった。同じことさ。";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "今なら俺にもわかったぜ。ティチンギトゥは行ってもいいか、船長？";
			link.l1 = "ああ、行け。俺もすぐにみんなのところへ行くからな。";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("おい、なんだよその武器を振り回してるのは！？今すぐしまえ！", "今すぐ武器をしまえと命じる！", "「おい、」 " + GetAddress_Form(NPChar) + "「おい、みんなを脅かすのはやめろ！武器をしまえ。」");
			link.l1 = LinkRandPhrase("よし、しまっておくぜ……", "もう済んだ。", "おっしゃる通りだな……");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("くたばりやがれ！", "俺が使わせてもらうぜ！", "時が来たらしまっておくぜ。");
			link.l2.go = "fight";
		break;
		
	}
} 