void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Konuşacak hiçbir şeyimiz yok!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("Merhaba! Benim adım  "+GetFullName(npchar)+" . Size nasıl yardımcı olabilirim?","Tekrar merhaba!","Bu ücra yerde misafirler pek nadir gelir...","Yeni bir yüzle konuşmak ne güzel! Şu eski suratlardan zaten bıktım...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ah, hiçbir şey...","Ben de...","Anladım...","Heh...",npchar,Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "Burada inci topluyoruz, hizmet ediyoruz  "+NationNameGenitive(sti(npchar.nation))+", biliyorsun...";
			link.l1 = "Evet, biliyorum...";
			link.l1.go = "exit";
			link.l2 = "Hey, dinle, bu küçük süslerden birkaçını doğrudan 'üreticiden' almak mümkün mü? Ne dersin?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "Ah hayır, tabii ki değil! Küçücük bir inciyi bile çalmanın cezası ölümdür!";
				link.l1 = "Burada gerçekten acımasız emirleriniz var, orası kesin...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Evet, burada kurallar çok serttir ve en ufak bir hatada insanın kellesi gidebilir. Ben bu işin içinde değilim ama sana yerli Kızılderililerle konuşmanı tavsiye ederim. Bir şeyler ters giderse kaçacak yerleri var, bu yüzden bizden daha cesur olmalılar...";
				link.l1 = "Anladım... Peki, teşekkürler.";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("Sen tamamen   "+GetSexPhrase("Deli misin? Kaybol, aptal","Deli misin? Kaybol, aptal herif")+"!",""+GetSexPhrase("Ne?! Aklını mı kaçırdın, seni aptal","Ne?! Aklını mı kaçırdın, aptal kız")+"?! Git bütün sorularınla başımdan...",""+GetSexPhrase("Akıl sağlığını mı yitirdin, canım? Ne korsanı? Burada mı?! Defol git, aptal","Aklını mı kaçırdın, tatlım? Ne korsanı? Burada mı?! Defol git, aptal kız")+"...");
			link.l1 = RandPhraseSimple("Kaba olmana gerek yok...","Diline dikkat et!");
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Solgun surat","Beyaz kadın")+" konuşmak mı istiyor?","Yine sen, "+GetSexPhrase("solgun surat","beyaz kadın")+".",""+GetSexPhrase("Solgun surat konuşmayı seviyor. Bir kadına benziyor.","Beyaz kadın konuşmayı seviyor.")+"","Ruhlar solgun yüzümü getirdi "+GetSexPhrase("kardeşim","kız kardeş")+" bana.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Evet.","Evet, yine ben.","Çok şiirsel.","Seni görmekten ben de memnunum",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "Bana söyle, neden geldin?";
			link.l1 = "Ah, özel bir şey yok, sadece ne söyleyeceğini duymak istedim.";
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "Kaptan, ne yapıyorsunuz? Silahınızı indirin, yoksa başımıza büyük bir bela açacaksınız!";
			link.l1 = LinkRandPhrase("Peki.","Pekâlâ.","Merak etme, zaten kaldırıyorum...");
			link.l1.go = "exit";
		break;  

	}
}
