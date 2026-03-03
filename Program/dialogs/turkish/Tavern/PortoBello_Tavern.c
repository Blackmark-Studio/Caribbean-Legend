// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Sana nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bana kısa bir süre önce bir soru sormaya çalıştın, "+GetAddress_Form(NPChar)+"...","Bugün içinde bu soruyu üçüncü kez gündeme getiriyorsun...","Daha fazla sorunuz var sanırım?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Evet, gerçekten de üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Dinle, Francois Gontier adında bir korsanı gördün mü? Son zamanlarda senin kasabanda bulundu.";
                link.l1.go = "Portobello_rat_1";
            }			
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "Dinler misin, bana Jaime Silicio adında bir tüccarın nerede olduğunu söyleyebilir misin? Sana uğraması gerekiyordu...";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "Bakın, Bertrand Pinette adında bir adamı arıyorum, onu duydunuz mu? Kısa süre önce Portobello'ya geldi. Kıvırcık peruklu, heybetli bir beyefendi. Bir tüccar. Belki burada bulunmuş olabilir...";
                link.l1.go = "FMQG";
            }
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Tavern_1"))
            {
                link.l1 = "Bana Marisa Caldera'yı nerede bulabileceğimi söyleyebilir misiniz?";
                link.l1.go = "LFD_Tavern_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("Hayır, bilmiyorum. Tavernaya uğramadı ve onu kasabada da görmedim.","Bunu zaten sordun ve ben de sana cevap verdim.","Sana söyledim, 'bu Gontier hakkında zaten sormuştun.'","Dinle, yürü git ve beni rahat bırak! Aklını tamamen mı kaçırdın?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Peki o zaman, aramaya devam edeceğim.","Hm, sanırım öyle...","Evet, doğru, bunu ben sordum...","Üzgünüm, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			DelLandQuestMark(npchar);
			npchar.quest.trial = true;
			
			dialog.text = "Beni affedin, señor, ama böyle meseleleri bir yabancıyla ancak bir hain ya da ayyaş konuşur. Ben sorun istemem.";
			link.l1 = "Bir ayyaş mı diyorsun? Görüşürüz dostum.";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Ondan hiç haberim yok, dostum.";
			link.l1 = "Don Carlos de Milyar'ın bir tanıdığı. Ondan hiç haberin olmadığından emin misin?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Benim. Eğer de Milyar'ın dostuysa - valiye git ve señor Carlos'u sor. O sana bu tüccarın hakkında bilgi verecektir.";
			link.l1 = "Bunu yapacağım. Tavsiyen için teşekkürler!";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
		
		//--> Письмо от покойника
		case "LFD_Tavern_1_1":
			dialog.text = "Marisa mı? Hm... Onu bir süredir görmedim. Kocasının ölümünü öğrendiğinden beri kasabada hiç görünmüyor.";
			link.l1 = "Yani, dul mu olmuş?";
			link.l1.go = "LFD_Tavern_1_2";
			DelLandQuestMark(npchar);
		break;

		case "LFD_Tavern_1_2":
			dialog.text = "Evet. Kocası, 'Wavereaver' adlı ticaret pinnacesinin kaptanıydı. Hollanda Batı Hindistan Şirketi'nden aldığı ruhsat sayesinde, takımadadaki neredeyse tüm limanlar ona açıktı. Söylentiye göre, Belize'den Capsterville'e giderken bir korsan saldırısından sağ çıkamamış. Buralarda böyle şeyler sık olur, ama onun için bu gerçekten büyük bir yıkım oldu.";
			link.l1 = "Yani, öylece ortadan kayboldu mu?";
			link.l1.go = "LFD_Tavern_1_3";
		break;

		case "LFD_Tavern_1_3":
			dialog.text = "Şey, 'kayboldu' demek belki fazla olur. Ama o zamandan beri kasabada pek görünmüyor. Garip olan şu ki... ara sıra farklı adamlar onun hakkında sorular soruyor. Tıpkı senin gibi, Kaptan. Eğer bu kadar dindar olmasaydı, saklandığını ve geçimini bir şekilde sağladığını düşünürdüm. Ama Marisa, kocası ölmeden önce, hiçbir ayini kaçırmazdı – neredeyse kilisede yaşıyordu – bu yüzden öyle olduğunu sanmıyorum.";
			link.l1 = "Hepsi bu mu? Başka hiçbir şey bilmiyor musun?";
			link.l1.go = "LFD_Tavern_1_4";
		break;

		case "LFD_Tavern_1_4":
			dialog.text = "Bildiğim her şeyi, Kaptan, zaten size anlattım.";
			link.l1 = "...";
			link.l1.go = "LFD_Tavern_1_5";
		break;

		case "LFD_Tavern_1_5":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Tavern_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}