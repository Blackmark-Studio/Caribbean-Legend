//Jason общий диалог дворянок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Hm.   Sen   şu   anda   şu   bayrak   altında   seyrediyorsun:  "+NationNameGenitive(sti(pchar.nation))+", kaptan. Ülkemin düşmanıyla konuşmak istemiyorum. Hıh!";
					link.l1 = "Ah, evet. Gerçek bir vatansever...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("Benden ne istiyorsun, "+GetAddress_Form(NPChar)+"? Sıradan bir denizcinin soylu bir hanımla konuşması uygun değil, ama sizi dinliyorum.","Ah, peki böyle cesur bir kaptan benden ne ister?");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Vaktinizi fazla almayacağım, sadece bir şey sormak istiyorum...";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("Koloninizde neler olup bittiğini bilmem gerekiyor.","Biraz bilgiye ihtiyacım var.");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Tüm şehir diken üstünde - kraliyet müfettişi don Fernando de Alamida geldi. Bilirsin, burada çok şey gördüm ama bu... İnsanları değiştiren keder değil, onunla nasıl başa çıktıklarıdır. Söylenene göre, babasının ölümünden sonra bambaşka biri olmuş. Şimdi tüm Takımadalar'da ondan daha dürüst ve... acımasız bir Taç hizmetkârı bulamazsın.","Şu 'Kutsal Merhamet'e bir bak! Kralın bizzat özel tasarımlarla yapılmasını emrettiğini söylüyorlar. Ve bak - üstünde tek bir çizik bile yok. Sanki Meryem Ana'nın kendisi koruyor gibi. Ama bazı söylentiler duydum... belki de koruyan Meryem değildir.","Don Fernando'u öldürmeye kaç kez teşebbüs ettiklerini biliyor musun? Sadece geçen yıl açık denizlerde ona on iki kez saldırdılar! Ama böylesine sadık ve iyi eğitimli bir mürettebatla ve Tanrı'nın korumasıyla - on üçüncüsünden de sağ çıkacaktır!"),LinkRandPhrase("Düydün mü? Don Fernando de Alamida şehrimize gelmiş, şu anda sokaklarda bir yerlerdeymiş diyorlar. Onu kendi gözlerimle görmek isterdim...","Zor bir adam bu don Fernando. Kimileri onun anavatanı pislikten arındıran bir kurtarıcı olduğunu söyler. Diğerleri ise, babasının ölümünden sonra içinde bir şeylerin koptuğunu ve yakında hepimizin ağlayacağını fısıldar. Ama sana şunu söyleyeyim: ondan korkma. Onu böyle yapanlardan kork.","Ne kadar yakışıklı bir adam, şu don Fernando! Ama biliyor musun, tuhaf olan ne? Sanki kimseyi fark etmiyor. Hep görev, hep hizmet. Bir kız olduğunu duymuştum... ama bir rahiple görüştükten sonra, dünyevi zevklerden tamamen vazgeçmiş. Sanki yemin etmiş gibi."),RandPhraseSimple(RandPhraseSimple("Lanet müfettiş! O buradayken şehir ölü gibi. Ne ticaret var, ne eğlence. Hatta nefes almak bile sanki daha sessiz olmalı. Ve en korkuncu ne biliyor musun? Her limanda aynı bu. Saat gibi işliyor. Majesteleri sanki hepimize işkence olsun diye bunu bilerek icat etmiş gibi!","Don Fernando yine yetimhaneyi ziyaret etti. Cömertçe bağış yapıyor, saatlerce dua ediyor. Böyle değerli bir adam o lanet olası zimmetçilere örnek olmalı!"),RandPhraseSimple("Ha! 'Aziz' Fernando gene bütün genelevleri kapatmış. Neyse, yakında çekip gider, onlar da hemen tekrar açılır.","Müf... müfettiş geldi, işte olan bu! Don Fernando de Almeyda, ya da adı neydi, Alamida! O kadar önemli ki vali bile onun etrafında dikkatli davranıyor. Söylentilere göre gözlerinin içine bakıp bütün günahlarını bir anda görebiliyormuş. Korkunç!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Tekrar mı edeyim?  Arkadaşı olduğumdan şüphelenilmek istemem "+NationNameAblative(sti(pchar.nation))+"! Defol yoksa muhafızları çağırırım! Seninle konuşmak için can atıyorlar.";
					link.l1 = "Pekala, pekala, sakin ol. Gidiyorum.";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("Ne? Yine mi sen? Git, konuşacak başka birini bul. Etrafta dolaşan sıradan insanlar var, onlar sana daha uygun. Şimdi gitmem gerek, bu akşam valinin konutunda bir ziyafet var ve saçım hâlâ hazır değil!","Hayır, artık gerçekten can sıkıcı oluyorsun! Anlamıyor musun? Yoksa biraz ağır mı anlıyorsun?","Beyefendi, artık sadece bir aptal değil, aynı zamanda bir alçak ve kaba biri olduğunuzdan şüphelenmeye başladım. Sizi uyarıyorum, eğer saçma sorularınızla beni rahatsız etmeye devam ederseniz kocamı çağıracağım!","Bir kelime daha edersen, komutana seni halletmesini söylerim!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Anladım. Hoşça kal.","Evet, evet, hatırlıyorum, sadece sormayı unuttum...","Beni yanlış anladın...","Sakin olun, señora, zaten gidiyorum...",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("Pekala, dinleyelim.","Tamam, peki. Ne istiyorsun?","Sorular mı var? Peki denizci, dinliyorum.");
			link.l1 = LinkRandPhrase("Bu kasabada son dedikodular neler, anlatır mısın?","Burada son zamanlarda ilginç bir şey oldu mu?","Karayipler'den bir haber var mı, hanımefendi?");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Sen deli misin?! Korkutuyorsun beni! Silahını kınına koy yoksa komutana söyleyip seni kalede astırırım!","Sen deli misin?! Korkutuyorsun beni! Silahını kınına koy yoksa komutana söyleyip seni kalede astırırım!");
			link.l1 = LinkRandPhrase("Pekala.","Nasıl isterseniz.","Pekâlâ.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
