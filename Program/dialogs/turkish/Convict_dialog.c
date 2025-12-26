// диалог каторжников в шахте
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
			dialog.text = NPCStringReactionRepeat("Üzgünüm, ama artık birbirimizle konuşmamamız ikimiz için de daha iyi olur. Beni cezalandıracaklar, seni de buradan göndermemi isteyecekler.","Sana zaten her şeyi anlattım, dostum. Yoksa senin yüzünden kırbaçlanmamı mı istiyorsun?","Dinlemiyorum...","Spa-ade kazmayı kuvvetle vuruyor ve çınlatıyor...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Burada kurallarınız bayağı sıkı...","Hayır, tabii ki istemiyorum.","Hmmm...","Baba, beni duyabiliyor musun...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Kaptan, ne yapıyorsunuz? Başınızı büyük belaya sokmadan önce silahınızı indirin!";
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekala.","Merak etme, onu saklıyorum...");
			link.l1.go = "exit";
		break;  
	}
}
