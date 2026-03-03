// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Sorular, "+GetAddress_Form(NPChar)+"?","Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, neyin peşindesin, "+GetAddress_Form(NPChar)+"? ","Yine mi tuhaf sorular? Tatlım, git biraz rom falan iç...")+"","Bugün içinde bu soruyu üçüncü kez gündeme getiriyorsun..."+GetSexPhrase(" Bunlar bir ilgi göstergesi mi?","")+"","Yine sorularınız var sanırım. "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim","Şu anda konuşacak bir şeyim yok."),"Hayır, hayır, güzelim...","Olmaz, canım...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "Dinle kadın, eski dostum Francois Gontier'le aranızın çok iyi olduğunu söylüyorlar. Hem de çok yakınmışsınız...";
                link.l1.go = "Jamaica_ratW_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
				if (CheckCharacterItem(pchar, "jewelry43"))
				{
					link.l1 = "Kolyesini, taşlarla birlikte getirdim. Al bakalım. Allah beni senin gibi açgözlü kadınlardan korusun.";
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = "Şu anda bir şey yok. Kolyeni arıyorum.";
					link.l1.go = "exit";
				}
            }
			
		break;
		
		case "Jamaica_ratW_1":
            dialog.text = "Evet, öyleydik. Ne olmuş yani? Evli bir kadın değilim ve istediğimle vakit geçiririm. Francois çok saygın bir denizci, buradaki balıkçılar ve çiftçiler gibi değil. O öyle... Ah! Ve bana ne güzel hediyeler verdi!";
            link.l1 = "Pekâlâ, bu kadar yeter! Yoldaşımın ne gibi özellikleri olduğunu biliyorum, bana tek tek saymana gerek yok. Aranızda ne geçtiyse geçti, umurumda değil. Hatta evlenebilirsiniz bile, bana ne! Onu hemen bulmam lazım, anladın mı? Nereye gittiğini biliyor musun?";
            link.l1.go = "Jamaica_ratW_2";
        break;
		
		case "Jamaica_ratW_2":
            dialog.text = "Tee hee... Onun kamaradaşısın ama nereye gittiğini bilmiyorsun. Bu komik!";
            link.l1 = "Komik bir şey yok, kadın. Jamaika'da buluşmak üzere anlaşmıştık ve sonra birlikte bir sefere çıkacaktık... ne demek istediğimi anlıyorsan. Bunu tek başıma yapamam ve o da kim bilir nereye gitti!";
            link.l1.go = "Jamaica_ratW_3";
        break;
		
		case "Jamaica_ratW_3":
            dialog.text = "Anladım. Eh, eğer böyle kârlı bir sefer ufukta görünüyorsa ve seninle François arkadaşsanız... Sana nereye gittiğini söylerim, ama küçük bir ödül karşılığında.";
            link.l1 = "Evet, durumu biliyorum. Ne kadar istiyorsun?";
            link.l1.go = "Jamaica_ratW_4";
        break;
		
		case "Jamaica_ratW_4":
            dialog.text = "Ah, ne kadar çıkarcı! Paraya ihtiyacım yok. Hayır, ben özel bir şey istiyorum. François bana taşlarla süslü güzel bir kolye vereceğine söz verdi. Arkadaşlarıma bile övündüm, o ise hemen ortadan kayboldu... Bana kolyeyi getir, sana nereye gittiğini söylerim, hehe!";
            link.l1 = "Utanmaz kadın! Siz Hollandalı kadınlar gerçekten açgözlüsünüz! Peki, kolyeni alacaksın.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;
		
		case "Jamaica_ratW_5":
            dialog.text = "Ah, bu harika! Şimdi arkadaşlarım kıskançlıktan çatlayacak!";
            link.l1 = "Onlara başsağlığı dileklerimi ilet. Şimdi konuşmaya başla. François nereye gitti?";
            link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry43", 1);
        break;
		
		case "Jamaica_ratW_6":
            dialog.text = "Evet, elbette efendim. François Küba'ya, Havana'ya doğru yelken açtı.";
            link.l1 = "Pahalı ipucu için sağ ol, kadın. İstediğim sadece buydu.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
        break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
