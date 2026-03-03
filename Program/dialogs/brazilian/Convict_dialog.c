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
			dialog.text = NPCStringReactionRepeat("Desculpe, mas seria melhor para nós dois se não conversássemos mais. Vão me punir, e vão pedir para você ir embora.","Já te contei tudo, amigo. Ou quer que eu seja chicoteado por sua causa?","Eu não estou ouvindo...","O spa-ade está batendo forte e faz o picareta soar...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Regras rígidas que vocês têm aqui...","Não, claro que eu não quero isso.","Hmmm...","Papai, você pode me ouvir...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Capitão, o que você está fazendo? Guarde sua arma antes que arrume uma grande encrenca!";
			link.l1 = LinkRandPhrase("Certo.","Certo.","Não se preocupe, estou escondendo isso...");
			link.l1.go = "exit";
		break;  
	}
}
