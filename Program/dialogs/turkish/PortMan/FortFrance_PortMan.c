// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormaya çalıştın "+GetAddress_Form(NPChar)+"...","Bugün o soruyu üçüncü kez gündeme getiriyorsunuz...","Bak, eğer limanın işleriyle ilgili bana anlatacak bir şeyin yoksa, sorularınla beni meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boşver.","Gerçekten, bu zaten üçüncü sefer...","Üzgünüm, ama şimdilik limanın işleriyle ilgilenmiyorum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			DelLandQuestMark(npchar);
			link.l1 = "Efendim, iş arıyorum. Ama hamallık değil, rütbeme daha uygun bir şey. Bir görev, bir hizmet, hassas meselelerle ilgili bir iş... Vereceğiniz her türlü görevi kabul ederim.";
			link.l1.go = "Sharlie";
		}
		//<-- Бремя гасконца
		
		// Jason „олго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = "Bana bir mektubunuz olduğu söylendi. Adım Kaptan Charles de Maure.";
			link.l1.go = "LH_letter";
		}
		//--> Эпилог
		if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PU_Ulysse"))
		{
			link.l1 = "'"+GetShipName("Ulysse")+"' adlı pinasın yakın zamanda açık artırmaya çıkarıldığını duydum. Doğru mu?";
			link.l1.go = "SharlieEpilog_PU_Ulysse_1";
		}
		//<-- Эпилог
		break;
		
		case "Sharlie":
			dialog.text = "Yardım mı? Hm. Ben iyiyim, Tanrı'ya şükür. Ama bir arkadaşım gerçekten yardıma muhtaç ve durum çok acil. Yalnız başına ormana girip yerlilerle savaşacak, bu tam anlamıyla delilik!\nOnu ikna etmeye çalıştım, yalvardım ama dinlemedi! Kızını çok düşünüyor ve onun için canını vermeye hazır!";
			link.l1 = "Dur, baştan alalım: Arkadaşın kim, onu nerede bulabilirim ve ne tür bir yardıma ihtiyacı var?";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "Ah, affedersiniz, sadece çok endişeliyim. Adı Prosper... Prosper Troubale. Kesinlikle ölecek! Ve ona yardım edemem - ben bir asker değilim. Kızı kayıp ve yerli Kızılderililerin sorumlu olduğuna inanıyor.\nDüşünebiliyor musunuz, kendi başına vahşi yerlilerin peşine gitmeyi planlıyor! Onu paramparça ederler... Şu anda bir tüfek satın alıyor ve ormana gitmek için hazırlanıyor!";
			link.l1 = "Sen berbat bir hikaye anlatıcısısın, efendi. Arkadaşını nerede bulabilirim... adı neydi... Prosper?";
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = "Az önce onunla konuştum ve fikrini değiştirmeye çalıştım. Şehir kapılarından çok uzakta değil, kuyunun yanında, tüfeğini ve cephanesini kontrol ediyor. Ona git ve bir şeyler yap! Eğer tek başına ormana girerse, geri dönemez, bundan eminim. Kızıl derili şeytanlar onu paramparça eder...";
			link.l1 = "Saçmalamayı bırak, yaşlı bir kadın gibi konuşuyorsun! Hemen arkadaşının yanına gidiyorum. Umarım ona yardımcı olabilirim.";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
			QuestPointerDelLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		// Jason „олго и счастливо
		case "LH_letter":
			dialog.text = "Evet, haklısınız - bir zarf var. İşte burada, ama önce teslimat ücreti olarak on iki bin gümüş peso ödemeniz gerekiyor.";
			if (sti(pchar.money) >= 12000)
			{
				link.l1 = "Her zaman ticaretinizin aslında hırsızlıktan ibaret olduğunu düşünürdüm, ama demek ki yanılmışım, hm. Lütfen, işte paranız.";
				link.l1.go = "LH_letter_1";
			}
			else
			{
				link.l1 = "Birazdan geri döneceğim, sanırım cüzdanımı meyhanede unuttum.";
				link.l1.go = "exit";
			}
		break;
		
		case "LH_letter_1":
			DialogExit();
			AddMoneyToCharacter(pchar, -12000);
			LongHappy_RecibeLetter();
		break;
		
		//--> Эпилог
		case "SharlieEpilog_PU_Ulysse_1":
			dialog.text = "Doğru. Geminin sahibi sigorta borçlarına batmış ve gemiyi açık artırmaya çıkarmış. Ama biraz geç kaldınız — müzayede çoktan sona erdi, yeni sahibi belgeleri hazırlıyor.";
			link.l1 = "Onu nerede bulabileceğimi söyler misiniz? Onunla konuşmam gerekiyor.";
			link.l1.go = "SharlieEpilog_PU_Ulysse_2";
			DelLandQuestMark(npchar);
			SharlieEpilog_SpawnPikar();
		break;
		
		case "SharlieEpilog_PU_Ulysse_2":
			dialog.text = "Onu aramana gerek yok. Arkana bak — hemen arkanda duruyor.";
			link.l1 = "...";
			link.l1.go = "exit";			
		break;
		//<-- Эпилог
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
