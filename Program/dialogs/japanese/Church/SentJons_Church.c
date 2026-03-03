// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんな質問だ」 "+GetSexPhrase("息子よ","娘よ")+"?","何でも聞いてくれ、聞いてるぜ…"),"聞いているぞ、今話せ。 "+GetSexPhrase("息子よ","娘よ")+"...","「三度目だが、」 "+GetSexPhrase("息子よ","娘よ")+"、必要なことがあれば言ってくれ。","「聖職者にはやることが山ほどあるんだ、あんたは俺の邪魔をしているぞ」 "+GetSexPhrase("息子よ","娘よ")+"...","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は違うんだ、神父さん……"),"申し訳ないが、俺には何も言うことはねえ。","後で聞くぜ。すまねえ、神父さん。","失礼します、神父様……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
			{
				link.l1 = "聖父様、トマス・モリソンの娘についてお話ししたいのです。";
                link.l1.go = "dwh_pastor_1";
			}
			if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
			{
				link.l1 = "聖父様、トマスが悔い改めの道を受け入れ、善行に身を捧げ、 どんな犠牲を払ってでも教区に新しい鐘を寄贈するとお伝えするよう頼まれました。";
                link.l1.go = "dwh_pastor_VD_5";
			}
			// <-- Тёмные воды исцеления
		break;

		// --> Тёмные воды исцеления
		case "dwh_pastor_1":
			dialog.text = "話しておくれ、子よ、聞いているぞ。";
			link.l1 = "お前がジプシーがあの娘を助けるのに反対してるのは知ってる。だが、 父親に自分の娘を救うわずかな望みさえも捨てさせるなんてできるのか？あの女のやり方は怪しいかもしれねえが、 役立つ知識を持ってるんだ。";
			link.l1.go = "dwh_pastor_2";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_2":
			dialog.text = "息子よ、少女を癒せるのは主だけだ。主の御心への信仰こそが、我々を試練から導いてくださるのだ。 トマスが熱心に祈り、神の御言葉に従い、教会に惜しみなく施せば、主はその祈りを聞き入れ、 慈悲を示してくださるだろう。";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "（信頼できる）しかし、お前だって認めざるを得ないだろう、主は人を通して働かれるのだ。もしあのジプシーが、 ただ主の御意志の道具に過ぎないとしたらどうだ？主のご計画があまりにも深遠で、我々 のような凡人には理解できないとしたら？主のなさることは不可思議だ、そうじゃないか？";
				link.l1.go = "dwh_pastor_VD_1";
				Notification_Perk(true, "Trustworthy");
			}
			else
			{
				link.l1 = "父親に娘が衰弱していくのを見せつけて、救おうとすることさえ許さないのか。それが慈悲だと言えるのか？";
				link.l1.go = "dwh_pastor_bez_VD_1";
				Notification_Perk(false, "Trustworthy");
			}
		break;

		case "dwh_pastor_VD_1":
			dialog.text = "「あなたの言葉は賢明です、船長。しかし、それでもなお、異端が我らの信徒の心に入り込み、 最も敬虔な息子の信仰を揺るがすことは許せません。」";
			link.l1 = "娘を失うことほど、彼の信仰を揺るがすものはないだろう。しかし、たとえ罪とされる手段であっても、 彼にあらゆる方法を使うことを許せば、彼の信仰は弱まるどころか、むしろ強くなるのだ。";
			link.l1.go = "dwh_pastor_VD_2";
		break;

		case "dwh_pastor_VD_2":
			dialog.text = "しかし…それでは他の信者たちにどんな手本を示すことになるんだ？";
			link.l1 = "教会がただやみくもに罰するのではなく、真の悔い改めへと導くことの一例です。\n聖書は、心からの悔い改めと善行が罪を贖うことができると教えていないでしょうか？\n教会への寛大な寄付こそが、贖罪への第一歩となるかもしれません。";
			link.l1.go = "dwh_pastor_VD_3";
		break;

		case "dwh_pastor_VD_3":
			dialog.text = "もしかするとあなたの言う通りかもしれません、船長。私はトーマスにこの機会を与えるつもりです。しかし、 覚えておいてください――もし彼が正しき道から外れ、信仰を失うようなことがあれば、あなたにも責任が及びますぞ！\n寄付についてですが――教会は富を必要としておりません、必要なものは揃っています。ただし……スペインの襲撃の際に鐘が壊れてしまいまして……";
			link.l1 = "あなたの言葉はトマスに伝えます。お時間をいただき、ありがとうございます、神父様。 主があなたをお守りくださいますように。";
			link.l1.go = "dwh_pastor_VD_4";
		break;

		case "dwh_pastor_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_11";
		break;

		case "dwh_pastor_bez_VD_1":
			dialog.text = "これは冷酷さではありません、船長、これは信仰です。私たちはあの娘の運命を見捨てるのではなく、 主の御手に委ねるのです。トマスが祈り、信じ、謙虚に待つなら、主はきっと我々の祈りを聞き入れ、 彼女を癒してくださると私は確信しています。";
			link.l1 = "知ってるか、島の貴族たちも総督もジプシーの助けを借りてるんだぜ。しかも誰も破門されちゃいねえ。なのに、 なんでトマスにはそんなに厳しいんだ？";
			link.l1.go = "dwh_pastor_bez_VD_2";
		break;

		case "dwh_pastor_bez_VD_2":
			dialog.text = "もちろん知っているよ、息子よ。しかし、彼らはまだ主の真の光に触れていない迷える魂なのだ。トマスは我々 の信徒の柱であり、最も優れた者の一人だ。その信仰を悪が蝕むことを許せば、教会全体が危険にさらされる。 それほど重大な罪を、わしは決して許すことはできん。";
			link.l1 = "それじゃ、ほんの少しのチャンスすら与えねえのか？それが本当に正義ってやつか？";
			link.l1.go = "dwh_pastor_bez_VD_3";
		break;

		case "dwh_pastor_bez_VD_3":
			dialog.text = "お前たちが救いと呼ぶものは、破滅へと導くかもしれねえ。俺の経験から言ってるんだ。かつて、俺の意思に反して、 あいつみたいな癒し手が姪っ子を治療したことがある。まだ幼い娘だったが、苦しみの中で死んじまった。そして、 その儀式で魂がどうなったかは主だけが知っている。俺を説得しようなんて無駄だぜ。";
			link.l1 = "わかった。それがあなたの最終的な答えなら、私はもう何も言わない。主があなたを守ってくださいますように。";
			link.l1.go = "dwh_pastor_bez_VD_4";
		break;

		case "dwh_pastor_bez_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			
			AddQuestRecord("DWH", "4");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_6";
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			LAi_CharacterEnableDialog(sld);
		break;

		case "dwh_pastor_VD_5":
			dialog.text = "素晴らしい、息子よ。新しい鐘は主と教会への献身の象徴となるだろう。必要なことをさせなさい、 だが彼に忘れず伝えなさい――全能なる神の御目はすべての行いを見ておられ、その御意志から逃れられるものは何もないのだと。";
			link.l1 = "そうか、聖父よ。さらばだ。";
			link.l1.go = "dwh_pastor_VD_6";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_VD_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_15";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
			DelLandQuestMark(sld);
			LAi_RemoveLoginTime(sld);
		break;
		// <-- Тёмные воды исцеления
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
